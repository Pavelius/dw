#include "main.h"

static const char* text_dice[] = {"�������", "�����", "������", "������", "������", "�������"};
static const char* text_points[] = {"�����", "����", "����", "����", "����", "�����"};
static struct conflict_info {
	const char*	id;
	const char*	name;
	skill_s		skills[2][4];
} conflict_data[] = {
	{"Fight", "��������", {{Fighter, Nature, Fighter, Nature}, {Fighter, Nature, Fighter, Nature}}},
};
static struct maneuver_info {
	const char*	id;
	const char*	name;
	int			cost;
} maneuver_data[] = {{"Impende", "����������", 1},
{"Gain position", "�������� �����������", 2},
{"Disarm", "�����������", 3},
};
assert_enum(maneuver, LastManeuver);
getstr_enum(maneuver);
struct side {
	int					disposition, maximum;
	hero*				parcipants[8];
	char				penalties[LastManeuver + 1];
	order				orders[3];
	side() { memset(this, 0, sizeof(*this)); }
};

enum roll_event_s {
	MakeRoll, UsePersonaPoint, UseFatePoint,
	SuggestedHelp,
	UseTraits = SuggestedHelp + Weaver + 1,
	UseTraitsPenalty = UseTraits + LastTraits + 1,
	UseTraitsPenaltyOpponent = UseTraitsPenalty + LastTraits + 1,
	UseTraitToBreakTie = UseTraitsPenaltyOpponent + LastTraits + 1,
	UseWises = UseTraitToBreakTie + LastTraits + 1,
};

static int getresult(unsigned char* source) {
	auto result = 0;
	for(auto p = source; *p; p++) {
		if(*p >= 4)
			result++;
	}
	return result;
}

static int getresult(unsigned char* source, unsigned char value) {
	auto result = 0;
	for(auto p = source; *p; p++) {
		if(*p == value)
			result++;
	}
	return result;
}

static int select_players(hero** result) {
	auto pa = result;
	for(auto p : players) {
		if(!p || !p->isalive())
			continue;
		*pa++ = p;
	}
	*pa = 0;
	return pa - result;
}

static action_s choose_action(bool interactive, int sequence) {
	auto content = logs::getptr();
	logs::add("����� �������� ����� ��������� �� ���� [%1i]?", sequence + 1);
	for(auto i = Attack; i <= Maneuver; i = (action_s)(i + 1))
		logs::add(i, getstr(i));
	auto result = (action_s)logs::input(interactive, false);
	content[0] = 0;
	return result;
}

static hero* choose_actor(hero** parcipants, bool interactive, action_s action, skill_s skill, hero* exclude) {
	char temp[512];
	int count = zlen(parcipants);
	if(count == 0)
		return 0;
	else if(count == 1)
		return parcipants[0];
	auto content = logs::getptr();
	logs::add("��� ����� ��������� �������� [%1]?", getstr(action));
	for(int i = 0; parcipants[i]; i++) {
		auto p = parcipants[i];
		if(exclude == p)
			continue;
		szprints(temp, zendof(temp), "%1 ����� ����� %2 [%3i]", p->getname(), getstr(skill), p->get(skill));
		auto weapon = p->weapon;
		if(weapon)
			szprints(zend(temp), zendof(temp), " � ���������� %1", weapon.getname());
		weapon.getbonuses(zend(temp), zendof(temp), action, ", ��� ���� ", 0);
		zcat(temp, ".");
		logs::add(i, temp);
	}
	auto result = parcipants[logs::input(interactive, false)];
	content[0] = 0;
	return result;
}

int hero::roll(skill_s value, int obstacle, int bonus_dices, int bonus_success, bool interactive, roll_type_s roll_type, hero* opponent, hero** allies, hero** helpers, skill_s opponent_skill, int opponent_bonus_dices, int opponent_bonus_success) {
	unsigned char dice_result[32];
	bool use_trait_bonus = false; trait_s trait_bonus;
	bool use_trait_penalty = false; trait_s trait_penalty;
	bool use_wise = false; wise_s wise_bonus;
	hero* helps_data[8]; hero* ally_data[8];
	int result = 0;
	int skill_dices = 0;
	if(roll_type == RecoveryRoll)
		skill_dices = skills[value];
	else
		skill_dices = get(value);
	int opponent_dices = 0;
	if(opponent)
		opponent_dices = opponent->get(opponent_skill) + opponent_bonus_dices;
	char* base_content = logs::getptr();
	if(!allies) {
		allies = ally_data;
		ally_data[0] = 0;
		if(interactive)
			// ������� ��-��������� ��� ������ � ��������
			select_players(ally_data);
	}
	if(!helpers) {
		helpers = helps_data;
		helps_data[0] = 0;
	}
	if(interactive) {
		while(true) {
			base_content[0] = 0;
			auto party_dices = imax(0, skill_dices + bonus_dices);
			logs::add("\n[%1] ����� ����������� ����� [%2]", getname(), getstr(value));
			if(bonus_dices > 0)
				logs::add(" c ������� � %1i %2", bonus_dices, maptbl(text_dice, bonus_dices));
			else if(bonus_dices < 0)
				logs::add(" c� ������� � %1i %2", -bonus_dices, maptbl(text_dice, -bonus_dices));
			logs::add(".");
			for(auto pp = helpers; *pp; pp++)
				logs::add("%1 ������� � ������.", (*pp)->getname());
			logs::add("������� [%1i] %2", party_dices, maptbl(text_dice, party_dices));
			if(opponent) {
				logs::add(" ��� ���� [%1] ����� ������ [%2i] [%3]",
					opponent->getname(),
					opponent_dices, maptbl(text_dice, opponent_dices));
			} else if(obstacle)
				logs::add(" ������ ��������� [%1i]", obstacle);
			logs::add(".");
			logs::add(MakeRoll, "��������� ������.");
			for(auto pp = allies; *pp; pp++) {
				auto p = *pp;
				skill_s skill = Nature;
				if(p != this && zchr(helpers, p) == 0 && p->canhelp(value, &skill))
					logs::add(SuggestedHelp + (pp - allies), "[%1] ����� ������ ����� ������� [%2]", p->getname(), getstr(skill));
			}
			if(!use_trait_bonus) {
				for(auto i = FirstTraits; i <= LastTraits; i = (trait_s)(i + 1)) {
					switch(get(i)) {
					case 0:
						continue;
					case 1:
						if(traits_used[i] >= 1)
							continue;
						break;
					case 2:
						if(traits_used[i] >= 2)
							continue;
						break;
					}
					if(use_trait_penalty && trait_penalty == i)
						continue;
					if(!isbonus(i, value))
						continue;
					logs::add(UseTraits + i, "[%1] ����� ������������ ����� [%2] ����� �������� +1D", getname(), getstr(i));
				}
			}
			if(!use_trait_penalty && party_dices) {
				for(auto i = FirstTraits; i <= LastTraits; i = (trait_s)(i + 1)) {
					if(!get(i))
						continue;
					if(use_trait_bonus && trait_bonus == i)
						continue;
					if(isbonus(i, value))
						continue;
					logs::add(UseTraitsPenalty + i, "[%1] ����� ������������ ����� [%2] ������ ���� ����� �������� -1D, �� �������� ���� ����", getname(), getstr(i));
					if(opponent)
						logs::add(UseTraitsPenaltyOpponent + i, "[%1] ����� ������������ ����� [%2] ����� [%3] ������� +2D, �� �������� ��� �����", getname(), getstr(i), opponent->getname());
				}
			}
			if(!use_wise) {
				for(auto i = FirstWise; i <= LastWise; i = (wise_s)(i + 1)) {
					if(!get(i))
						continue;
					if(ismatch(logc.animal, i)
						|| ismatch(logc.landscape, i)
						|| ismatch(logc.location, i))
						logs::add(UseWises + i, "[%1] %2, ��� ���� ��� �������� �����", getname(), getstr(i));
				}
			}
			if(persona > 0)
				logs::add(UsePersonaPoint, "��������� ���� [��������] (������ ���� [%1i] %2) ����� �������� +1D", persona, maptbl(text_points, persona));
			auto id = logs::input(true, false);
			if(id == MakeRoll)
				break;
			if(id == UsePersonaPoint) {
				bonus_dices++;
				persona--;
			} else if(id >= SuggestedHelp && id <= SuggestedHelp + 8) {
				bonus_dices++;
				zcat(helpers, allies[id - SuggestedHelp]);
			} else if(id >= UseTraits && id <= UseTraits + LastTraits) {
				bonus_dices++;
				use_trait_bonus = true;
				trait_bonus = (trait_s)(id - UseTraits);
				use(trait_bonus);
			} else if(id >= UseTraitsPenalty && id <= UseTraitsPenalty + LastTraits) {
				bonus_dices--;
				use_trait_penalty = true;
				trait_penalty = (trait_s)(id - UseTraitsPenalty);
				checks++;
			} else if(id >= UseTraitsPenaltyOpponent && id <= UseTraitsPenaltyOpponent + LastTraits) {
				opponent_dices += 2;
				use_trait_penalty = true;
				trait_penalty = (trait_s)(id - UseTraitsPenaltyOpponent);
				checks += 2;
			} else if(id >= UseWises && id <= UseWises + LastWise) {
				bonus_dices += 1;
				use_wise = true;
				wise_bonus = (wise_s)(id - UseWises);
			}
		}
	} else {
		// ��� �� ������������� ������ ��� ��� �������� ��������� �����
		if(helpers)
			bonus_dices += zlen(helpers);
	}
	// ���� ���� ��������
	if(opponent)
		obstacle += opponent->roll(opponent_skill, 0, opponent_bonus_dices, 0, false, roll_type);
	// �������� ������ �������
	auto party_dices = imax(0, skill_dices + bonus_dices);
	if(party_dices > sizeof(dice_result) / sizeof(dice_result[0]) - 1)
		party_dices = sizeof(dice_result) / sizeof(dice_result[0]) - 1;
	for(int i = 0; i < party_dices; i++)
		dice_result[i] = 1 + (rand() % 6);
	dice_result[party_dices] = 0;
	// �������� ����� ������
	while(true) {
		result = 0;
		if(interactive)
			logs::add(MakeRoll, "����������");
		if(dice_result[0]) {
			auto roll_result_local = getresult(dice_result);
			result = roll_result_local - obstacle;
			if(opponent) {
				if(result > 0)
					result += bonus_success;
				else if(result < 0)
					result -= opponent_bonus_success;
			} else {
				if(result >= 0)
					result += bonus_success;
			}
			if(interactive) {
				base_content[0] = 0;
				logs::add("\n[%1] ��������[%2]: ", getname(), getA());
				for(auto p = dice_result; *p; p++) {
					logs::add("%1i", *p);
					if(p[1] == 0)
						logs::add(".");
					else
						logs::add(", ");
				}
				logs::add("��������� ������ [%1i]", roll_result_local);
				if(obstacle) {
					if(opponent)
						logs::add("��� ���, ��� [%1] �������%2 [%3i]", opponent->getname(), opponent->getA(), obstacle);
					else
						logs::add("��� ��������� [%1i]", obstacle);
				}
				logs::add(".");
				if(fate > 0 && getresult(dice_result, 6) > 0)
					logs::add(UseFatePoint, "������������ ���� [������] (�������� [%1i] %2) ����� ��������� ���������� ������� ������ '6' � ����������.", fate, maptbl(text_points, fate));
				if(result == 0 && opponent) {
					for(auto i = FirstTraits; i <= LastTraits; i = (trait_s)(i + 1)) {
						if(!get(i))
							continue;
						if((use_trait_bonus && trait_bonus == i) || (use_trait_penalty && trait_penalty == i))
							continue;
						if(isbonus(i, value))
							continue;
						logs::add(UseTraitToBreakTie + i, "[%1] ��������� ����� [%2] ����� ��������� ����� � ������ ��������� � �������� ��� �����.", getname(), getstr(i));
					}
				}
			} else {
				// ��� ��������������� ���������� �� ���������� ������
				break;
			}
		}
		if(opponent) {
			if(result > 0)
				logs::add("�� �������� ����.");
			else if(result == 0)
				logs::add("������ �����.");
			else
				logs::add("�� ��������� ����.");
		} else if(obstacle) {
			if(result >= 0)
				logs::add("���� �������.");
			else
				logs::add("���� �� �������.");
		}
		auto id = logs::input(interactive, false);
		if(id == MakeRoll) {
			base_content[0] = 0;
			break;
		} else if(id >= UseTraitToBreakTie && id <= UseTraitToBreakTie + LastTraits) {
			result = -1;
			checks += 2;
			break;
		} else if(id == UseFatePoint) {
			fate--;
			for(auto count = getresult(dice_result, 6); count > 0; count = getresult(dice_result, 6)) {
				// ������� '6' �� '5' ����� �� ��������
				for(auto p = dice_result; *p; p++) {
					if(*p == 6)
						*p = 5;
				}
				// �������� ������ ����������
				for(int i = 0; i < count; i++) {
					unsigned char r = 1 + (rand() % 6);
					zcat(dice_result, r);
				}
			}
		}
	}
	auto mark = (roll_type != ConflictRoll);
	if(mark) {
		if(result >= 0) {
			if(pass[value] < skills[value])
				pass[value]++;
		} else {
			if(fail[value] < (skills[value] - 1))
				fail[value]++;
		}
	}
	return result;
}

bool hero::rollresource(int obstacle, bool interactive) {
	auto result = roll(Resources, obstacle, 0, 0, interactive);
	return result > 0;
}

static void select_conditions(char* result, hero* p) {
	for(auto i = Healthy; i <= Dead; i = (condition_s)(i + 1)) {
		if(p->is(i))
			result[i]++;
	}
}

static void select_conditions(char* result, hero** parcipants) {
	for(int i = 0; parcipants[i]; i++)
		select_conditions(result, parcipants[i]);
}

static int get_conditions_bonus(hero** parcipants, skill_s base, skill_s skill) {
	char conditions[Dead + 1] = {0};
	int result = 0;
	select_conditions(conditions, parcipants);
	if(conditions[HungerAndThirsty])
		result--;
	if(base == Will && conditions[Angry])
		result--;
	if(conditions[Tired])
		result--;
	return result;
}

static int roll_disposition(hero** parcipants, bool interative, skill_s base, skill_s skill) {
	hero* captain = 0;
	int result = 0;
	if(interative) {
		auto context = logs::getptr();
		logs::add("\n��� ����� ������� ���������� (%1 + %2)?", getstr(base), getstr(skill));
		for(int i = 0; parcipants[i]; i++) {
			auto p = parcipants[i];
			logs::add(i, "%1 (%2 %3i, %4 %5i)",
				p->getname(), getstr(base), p->get(base), getstr(skill), p->get(skill));
		}
		logs::sort();
		captain = parcipants[logs::input(true, false)]; context[0] = 0;
		result = captain->roll(skill, 0, 0, 0, true, ConflictRoll, 0, parcipants);
	} else {
		captain = parcipants[0];
		result = captain->roll(skill, 0, 0, 0, false, ConflictRoll, 0, parcipants);
	}
	result += captain->get(base);
	result += get_conditions_bonus(parcipants, base, skill);
	return result;
}

static void choose_orders(order* orders, hero** parcipants, conflict_s type, bool interactive) {
	for(int i = 0; i < 3; i++) {
		auto previous = i > 0 ? orders[i - 1].actor : orders[2].actor;
		orders[i].action = choose_action(interactive, i);
		orders[i].actor = choose_actor(parcipants, interactive, orders[i].action, conflict_data[type].skills[0][orders[i].action], previous);
	}
}

static void print_header(side& party, side& enemy, int round, int phase) {
	logs::clear(true);
	logs::add("##����� %1i", round, phase + 1);
	if(phase >= 0)
		logs::add(", ���� %1i", phase + 1);
	logs::add("\n");
	logs::add("���� ����������: [%1i], ���������� �����: [%2i]\n", party.disposition, enemy.disposition);
}

static int get_action_bonus(side& e, int phase, conflict_s type) {
	auto result = e.penalties[GainPosition] * 2 - e.penalties[Impende];
	auto weapon = e.orders[phase].actor->weapon;
	if(weapon && weapon.isready())
		result += weapon.getbonus(e.orders[phase].action);
	return result;
}

static int get_action_success(side& e, int phase, conflict_s type) {
	auto result = 0;
	auto weapon = e.orders[phase].actor->weapon;
	if(weapon && weapon.isready())
		result += weapon.getsuccess(e.orders[phase].action);
	return result;
}

static int roll_action(side& e, int phase, conflict_s type, bool interactive) {
	auto action = e.orders[phase].action;
	auto player = e.orders[phase].actor;
	auto result = player->roll(conflict_data[type].skills[0][action], 0,
		get_action_bonus(e, phase, type), get_action_success(e, phase, type),
		interactive, ConflictRoll);
	memset(e.penalties, 0, sizeof(e.penalties));
	return result;
}

static void corrent_disposition(side& e) {
	if(e.disposition < 0)
		e.disposition = 0;
	else if(e.disposition > e.maximum)
		e.disposition = e.maximum;
}

static void resolve_maneouver(side& party, side& enemy, int phase, int result, bool interactive, bool party_is_you) {
	adat<maneuver_s, 4> maneuvers;
	auto context = logs::getptr();
	while(result > 0) {
		logs::add("\n");
		if(maneuvers) {
			logs::add("�� �������: ");
			for(unsigned i = 0; i < maneuvers.count; i++) {
				if(i != 0)
					logs::add(", ");
				logs::add(getstr(maneuvers.data[i]));
			}
			logs::add(". ");
		}
		logs::add("������������ [%1i] %2 �����...", result, maptbl(text_points, result));
		for(auto i = FirstManeuver; i <= LastManeuver; i = (maneuver_s)(i + 1)) {
			if(maneuvers.is(i))
				continue;
			if(maneuver_data[i].cost > result)
				continue;
			logs::add(i, getstr(i));
		}
		if(logs::getcount()) {
			auto id = logs::input(interactive, false);
			result -= maneuver_data[id].cost;
			maneuvers.add((maneuver_s)id);
			context[0] = 0;
		} else {
			context[0] = 0;
			break;
		}
	}
	for(auto e : maneuvers) {
		if(e == GainPosition)
			party.penalties[e]++;
		else
			enemy.penalties[e]++;
	}
	if(enemy.penalties[Disarm]) {
		enemy.penalties[Disarm] = 0;
		if(enemy.orders[phase].actor->weapon)
			enemy.orders[phase].actor->weapon.disarmed = 1;
	}
}

static void resolve_action(side& party, side& enemy, int phase, action_s action, int result, bool interactive, bool party_is_you) {
	if(result <= 0)
		return;
	switch(action) {
	case Attack:
	case Feint:
		enemy.disposition -= result;
		corrent_disposition(enemy);
		break;
	case Defend:
		party.disposition += result;
		corrent_disposition(party);
		break;
	case Maneuver:
		resolve_maneouver(party, enemy, phase, result, interactive, party_is_you);
		break;
	}
}

static void resolve_action(side& party, side& enemy, conflict_s type, int round, int phase) {
	int enemy_result = 0, result = 0;
	auto party_action = party.orders[phase].action;
	auto enemy_action = enemy.orders[phase].action;
	auto party_roll_type = hero::get(party_action, enemy_action);
	auto enemy_roll_type = hero::get(enemy_action, party_action);
	print_header(party, enemy, round, phase);
	logs::add("%1 [%2], %3 [%4].",
		enemy.orders[phase].actor->getname(), hero::getnameby(enemy.orders[phase].action),
		party.orders[phase].actor->getname(), hero::getnameby(party.orders[phase].action));
	switch(party_roll_type) {
	case IndependedRoll:
		if(enemy_roll_type == IndependedRoll)
			enemy_result = roll_action(enemy, phase, type, false);
		result = roll_action(party, phase, type, true);
		break;
	case NoRoll:
		if(enemy_roll_type == IndependedRoll)
			enemy_result = roll_action(enemy, phase, type, false);
		break;
	case VersusRoll:
		result = party.orders[phase].actor->roll(
			conflict_data[type].skills[0][party_action], 0,
			get_action_bonus(party, phase, type), get_action_success(party, phase, type),
			true, ConflictRoll,
			enemy.orders[phase].actor, 0, 0,
			Nature,
			get_action_bonus(enemy, phase, type), get_action_success(enemy, phase, type));
		memset(party.penalties, 0, sizeof(party.penalties));
		memset(enemy.penalties, 0, sizeof(enemy.penalties));
		if(result < 0) {
			enemy_result = -result;
			result = 0;
		}
		break;
	}
	resolve_action(enemy, party, phase, enemy_action, enemy_result, true, false);
	resolve_action(party, enemy, phase, party_action, result, true, true);
}

static void conflict(conflict_s type, side& party, side& enemy) {
	party.disposition = roll_disposition(party.parcipants, true, Health, Fighter);
	party.maximum = party.disposition;
	enemy.disposition = roll_disposition(enemy.parcipants, false, Nature, Nature);
	enemy.maximum = enemy.disposition;
	int round = 1;
	while(enemy.disposition > 0 && party.disposition > 0) {
		print_header(party, enemy, round, -1);
		choose_orders(enemy.orders, enemy.parcipants, type, false);
		choose_orders(party.orders, party.parcipants, type, true);
		resolve_action(party, enemy, type, round, 0);
		resolve_action(party, enemy, type, round, 1);
		resolve_action(party, enemy, type, round, 2);
		round++;
	}
}

void hero::fight(animal_s type) {
	logs::state push;
	logc.animal = type;
	hero animal(type);
	side party, enemy;
	select_players(party.parcipants);
	zcat(enemy.parcipants, &animal);
	animal.act("�� ������� ����� ��������%� [%�����], �����%�� �������� ����� � ������ ������%��� �� ��� �����.");
	conflict(FightConflict, party, enemy);
	animal.act("�� ������� �����. [%�����] ������%� � ������� �����, ������� �� ����� �������� ����. %��� �������%� ������� ���� � ����� � ��������� ����� ���������� ����.");
}