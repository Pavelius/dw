#include "main.h"

static wear_s wear_slots[] = {Hands, Offhand};
static const char* text_dice[] = {"кубиков", "кубик", "кубика", "кубика", "кубика", "кубиков"};
static const char* text_points[] = {"очков", "очко", "очка", "очка", "очка", "очков"};

struct side : heroa {
	int						disposition, maximum;
	char					penalties[LastManeuver + 1];
	order					orders[3];
	bool					friendly;
	const char*	getname() const {
		if(friendly)
			return "Гвардейцы";
		return data[0]->getname();
	}
	side() { memset(this, 0, sizeof(*this)); }
};

enum roll_event_s {
	MakeRoll, UsePersonaPoint, UseFatePoint,
	SuggestedHelp,
	UseTraits, UseTraitsPenalty, UseTraitsPenaltyOpponent, UseTraitToBreakTie,
	UseImWise, UseDeeperUnderstanding, UseOfCource,
	TapNature,
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

static action_s choose_action(bool interactive, int sequence) {
	for(auto i = Attack; i <= Maneuver; i = (action_s)(i + 1))
		an.add(i, getstr(i));
	return (action_s)an.choose(interactive, false, "Какое действие будем выполнять на шаге [%1i]?", sequence + 1);
}

static hero* choose_actor(heroa& parcipants, bool interactive, action_s action, skill_s skill, hero* exclude) {
	if(!parcipants)
		return 0;
	else if(parcipants.getcount() == 1)
		return parcipants[0];
	for(auto p : parcipants) {
		if(exclude == p)
			continue;
		char temp[512]; stringbuilder sb(temp);
		sb.add("%1 имеет навык %2 [%3i]", p->getname(), getstr(skill), p->get(skill));
		auto weapon = p->get(Hands);
		if(weapon)
			sb.adds("и использует %1", weapon.getname());
		//weapon.getbonuses(zend(temp), zendof(temp), action, ", что дает ", 0);
		//zcat(temp, ".");
		sb.add(".");
		an.add((int)p, temp);
	}
	return (hero*)an.choose(interactive, false, "Кто будет выполнять действие [%1]?", getstr(action));
}

static bool isused(variant* source, wise_s v) {
}

class wiseuse {
	struct element {
		hero*		player;
		wise_s		value;
		explicit operator bool() const { return player != 0; }
	};
	element			elements[UseOfCource - UseImWise + 1];
public:
	bool is(wise_s v) const {
		for(int i = UseImWise - UseImWise; i <= (UseOfCource - UseImWise); i++) {
			if(elements[i].player && elements[i].value == v)
				return true;
		}
		return false;
	}
	bool is(roll_event_s v) const {
		return elements[v - UseImWise].player != 0;
	}
	void set(roll_event_s i, hero* p, wise_s v) {
		elements[i - UseImWise].player = p;
		elements[i - UseImWise].value = v;
	}
	void add(stringbuilder& sb) {
		for(auto& e : elements) {
			if(!e)
				continue;
			e.player->actv(sb, "%герой посоветовал%а интересное решение.", 0);
		}
	}
};

int hero::roll(roll_type_s roll_type, heroa& allies, heroa& helpers, bool interactive, skill_s value, int obstacle, int bonus_dices, int bonus_success, hero* opponent, skill_s opponent_skill, int opponent_bonus_dices, int opponent_bonus_success) {
	wiseuse wises = {};
	unsigned char dice_result[32] = {};
	bool use_trait_bonus = false; trait_s trait_bonus;
	bool use_trait_penalty = false; trait_s trait_penalty;
	bool use_tap_nature = false;
	int result = 0;
	int skill_dices = 0;
	if(roll_type == RecoveryRoll)
		skill_dices = skills[value];
	else
		skill_dices = get(value);
	int opponent_dices = 0;
	if(opponent)
		opponent_dices = opponent->get(opponent_skill) + opponent_bonus_dices;
	if(interactive) {
		while(true) {
			auto party_dices = imax(0, skill_dices + bonus_dices);
			auto context = sb.get();
			sb.addn("[%1] будет тестировать навык [%2]", getname(), getstr(value));
			if(bonus_dices > 0)
				sb.adds("c бонусом в [%1i] %2", bonus_dices, maptbl(text_dice, bonus_dices));
			else if(bonus_dices < 0)
				sb.adds("cо штрафом в %1i %2", -bonus_dices, maptbl(text_dice, -bonus_dices));
			if(bonus_success != 0) {
				if(bonus_dices != 0)
					sb.adds("и");
				else
					sb.adds("с");
				sb.adds("[+%1i] дополнительным успехами в случае удачи", bonus_success);
			}
			sb.add(".");
			for(auto p : helpers)
				sb.adds("%1 поможет в броске.", p->getname());
			wises.add(sb);
			sb.adds("Бросьте [%1i] %2", party_dices, maptbl(text_dice, party_dices));
			if(opponent) {
				sb.adds("при этом [%1] будет кидать [%2i] %3",
					opponent->getname(),
					opponent_dices, maptbl(text_dice, opponent_dices));
			} else if(obstacle)
				sb.adds("против сложности [%1i]", obstacle);
			sb.add(".");
			an.add(MakeRoll, "Выполнить бросок.");
			for(auto p : allies) {
				skill_s skill = Nature;
				if(p != this && !helpers.is(p) && p->canhelp(value, &skill))
					an.add(idu(SuggestedHelp, allies.indexof(p)), "[%1] может помочь своим навыком [%2]", p->getname(), getstr(skill));
			}
			if(!use_trait_bonus) {
				for(auto i = FirstTraits; i <= LastTraits; i = (trait_s)(i + 1)) {
					switch(get(i)) {
					case 0:
						continue;
					case 1:
						if(trait_used.is(i))
							continue;
						break;
					}
					if(use_trait_penalty && trait_penalty == i)
						continue;
					if(!isbonus(i, value))
						continue;
					an.add(idu(UseTraits, i), "[%1] может использовать черту [%2] чтобы получить +1D", getname(), getstr(i));
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
					an.add(UseTraitsPenalty + i, "[%1] может использовать черту [%2] против себя чтобы получить -1D, но добавить один тест", getname(), getstr(i));
					if(opponent)
						an.add(idu(UseTraitsPenaltyOpponent, i), "[%1] может использовать черту [%2] чтобы [%3] получил +2D, но добавить два теста", getname(), getstr(i), opponent->getname());
				}
			}
			if(!wises.is(UseImWise)) {
				for(auto p : allies) {
					if(p == this)
						continue;
					if(!p->isalive())
						continue;
					for(auto i = FirstWise; i <= LastWise; i = (wise_s)(i + 1)) {
						if(!p->is(i))
							continue;
						if(wises.is(i))
							continue;
						if(party.match(i))
							an.add(idu(UseImWise, i, allies.indexof(p)), "[%1] %-2 и может дать совет на +1D", p->getname(), getstr(i));
					}
				}
			}
			if(persona > 0) {
				an.add(UsePersonaPoint, "Потратить очко [Личности] (сейчас есть [%1i] %2) чтобы добавить +1D", persona, maptbl(text_points, persona));
				if(!use_tap_nature) {
					char temp[260]; stringbuilder sb(temp);
					sb.add("Потратить очко [Личности] (сейчас есть [%1i] %2) чтобы усилить бросок мышинной натурой на +%3iD", persona, maptbl(text_points, persona), get(Nature));
					an.add(TapNature, temp);
				}
			}
			idu id = an.choosev(true, false, false, 0);
			sb.set(context);
			if(id.a == MakeRoll)
				break;
			switch(id.a) {
			case UsePersonaPoint:
				bonus_dices++;
				persona--;
				break;
			case SuggestedHelp:
				bonus_dices++;
				helpers.add(allies[id.b]);
				break;
			case UseTraits:
				bonus_dices++;
				use_trait_bonus = true;
				trait_bonus = (trait_s)id.b;
				use(trait_bonus);
				break;
			case UseTraitsPenalty:
				bonus_dices--;
				use_trait_penalty = true;
				trait_penalty = (trait_s)id.b;
				checks++;
				break;
			case UseTraitsPenaltyOpponent:
				opponent_dices += 2;
				use_trait_penalty = true;
				trait_penalty = (trait_s)id.b;
				checks += 2;
				break;
			case UseImWise:
				bonus_dices += 1;
				wises.set(UseImWise, allies[id.c], (wise_s)id.b);
				break;
			case TapNature:
				bonus_dices += get(Nature);
				use_tap_nature = true;
				break;
			}
		}
	} else {
		// При не интерактивном броске тех кто помогает указываем извне
		if(helpers)
			bonus_dices += helpers.getcount();
	}
	// Если есть оппонент
	if(opponent) {
		heroa opponent_allies, opponent_helps;
		opponent_allies.add(opponent);
		obstacle += opponent->roll(roll_type, opponent_allies, opponent_helps, false,
			opponent_skill, 0, opponent_bonus_dices, opponent_bonus_success);
	}
	// Выполним бросок кубиков
	auto party_dices = imax(0, skill_dices + bonus_dices);
	if(party_dices > sizeof(dice_result) / sizeof(dice_result[0]) - 1)
		party_dices = sizeof(dice_result) / sizeof(dice_result[0]) - 1;
	for(int i = 0; i < party_dices; i++)
		dice_result[i] = 1 + (rand() % 6);
	dice_result[party_dices] = 0;
	// Действия после броска
	while(true) {
		result = 0;
		if(interactive)
			an.add(MakeRoll, "Продолжить");
		auto context = sb.get();
		sb.addsep('\n');
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
				act("[%герой] выбросил%а: ");
				for(auto p = dice_result; *p; p++) {
					sb.adds("%1i", *p);
					if(p[1] == 0)
						sb.add(".");
					else
						sb.add(", ");
				}
				sb.adds("Результат броска [%1i]", roll_result_local);
				if(obstacle) {
					if(opponent)
						opponent->act("при том, что [%герой] выросил%а [%1i]", obstacle);
					else
						sb.adds("при сложности [%1i]", obstacle);
				}
				sb.add(".");
				if(fate > 0) {
					if(getresult(dice_result, 6) > 0)
						an.add(UseFatePoint, "Использовать очко [Судьбы] (осталось [%1i] %2) чтобы добросить количество кубиков равное '6' в результате.", fate, maptbl(text_points, fate));
					if(!wises.is(UseDeeperUnderstanding)
						&& (getresult(dice_result, 1) > 0 || getresult(dice_result, 2) > 0 || getresult(dice_result, 3) > 0)) {

					}
				}
				if(result == 0 && opponent) {
					for(auto i = FirstTraits; i <= LastTraits; i = (trait_s)(i + 1)) {
						if(!get(i))
							continue;
						if((use_trait_bonus && trait_bonus == i) || (use_trait_penalty && trait_penalty == i))
							continue;
						if(isbonus(i, value))
							continue;
						an.add(idu(UseTraitToBreakTie, i), "[%1] используя черту [%2] может разрешить ничью в пользу оппонента и получить два теста.", getname(), getstr(i));
					}
				}
			} else {
				// При неинтерактивном результате не используем ничего
				break;
			}
		}
		if(opponent) {
			if(result > 0)
				sb.adds("Вы выиграли тест.");
			else if(result == 0)
				sb.adds("Сейчас ничья.");
			else
				sb.adds("Вы проиграли тест.");
		} else if(obstacle) {
			if(result >= 0)
				sb.adds("Тест пройден.");
			else
				sb.adds("Тест не пройден.");
		}
		idu id = an.choosev(interactive, false, false, 0);
		sb.set(context);
		if(id.a == MakeRoll)
			break;
		switch(id.a) {
		case UseTraitToBreakTie:
			result = -1;
			checks += 2;
			break;
		case UseFatePoint:
			fate--;
			for(auto count = getresult(dice_result, 6); count > 0; count = getresult(dice_result, 6)) {
				// Заменим '6' на '5' чтобы не путаться
				for(auto p = dice_result; *p; p++) {
					if(*p == 6)
						*p = 5;
				}
				// Добросим нужное количество
				for(int i = 0; i < count; i++) {
					unsigned char r = 1 + (rand() % 6);
					zcat(dice_result, r);
				}
			}
			break;
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

int	hero::roll(skill_s value, int obstacle, int bonus_dices, int bonus_success, bool interactive) {
	heroa helps;
	return roll(StandartRoll, party, helps, interactive, value, obstacle, bonus_dices, bonus_success);
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

static void select_conditions(char* result, heroa& v) {
	for(auto p : v)
		select_conditions(result, p);
}

static int get_conditions_bonus(heroa& parcipants, skill_s base, skill_s skill) {
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

static int roll_disposition(heroa& parcipants, bool interactive, skill_s base, skill_s skill) {
	hero* captain = 0;
	int result = 0;
	heroa helps;
	if(interactive) {
		for(auto p : parcipants) {
			an.add((int)p, "%1 (%2 %3i, %4 %5i)",
				p->getname(), getstr(base), p->get(base), getstr(skill), p->get(skill));
		}
		an.sort();
		captain = (hero*)an.choose(true, false, "Кто будет бросать диспозицию (%1 + %2)?", getstr(base), getstr(skill));
		result = captain->roll(ConflictRoll, party, helps, interactive, skill, 0);
	} else {
		captain = parcipants[0];
		heroa allies;
		allies.add(captain);
		result = captain->roll(ConflictRoll, allies, helps, false, skill, 0);
	}
	result += captain->get(base);
	result += get_conditions_bonus(parcipants, base, skill);
	return result;
}

static void choose_orders(order* orders, heroa& parcipants, conflict_s type, bool interactive) {
	for(int i = 0; i < 3; i++) {
		auto previous = i > 0 ? orders[i - 1].actor : orders[2].actor;
		orders[i].action = choose_action(interactive, i);
		auto& ei = bsmeta<conflicti>::elements[type];
		orders[i].actor = choose_actor(parcipants, interactive, orders[i].action, ei.skills[0][orders[i].action], previous);
	}
}

static void print_header(side& party, side& enemy, int round, int phase) {
	sb.clear();
	sb.add("##Раунд %1i", round, phase + 1);
	if(phase >= 0)
		sb.add(", фаза %1i", phase + 1);
}

static int get_action_bonus(side& e, int phase, conflict_s type) {
	auto result = e.penalties[GainPosition] * 2 - e.penalties[Impende];
	for(auto w : wear_slots) {
		auto weapon = e.orders[phase].actor->get(w);
		if(weapon && weapon.isready())
			result += weapon.getbonus(e.orders[phase].action);
	}
	return result;
}

static int get_action_success(side& e, int phase, conflict_s type) {
	auto result = 0;
	for(auto w : wear_slots) {
		auto weapon = e.orders[phase].actor->get(w);
		if(weapon && weapon.isready())
			result += weapon.getsuccess(e.orders[phase].action);
	}
	return result;
}

static int roll_action(side& e, int phase, conflict_s type, bool interactive) {
	auto action = e.orders[phase].action;
	auto player = e.orders[phase].actor;
	auto& ei = bsmeta<conflicti>::elements[type];
	heroa helps;
	auto result = player->roll(ConflictRoll, party, helps, interactive,
		ei.skills[0][action], 0, get_action_bonus(e, phase, type), get_action_success(e, phase, type));
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
	auto context = sb.get();
	while(result > 0) {
		sb.add("\n");
		if(maneuvers) {
			sb.add("Вы выбрали: ");
			for(unsigned i = 0; i < maneuvers.count; i++) {
				if(i != 0)
					sb.add(", ");
				sb.add(getstr(maneuvers.data[i]));
			}
			sb.add(". ");
		}
		sb.add("Распределите [%1i] %2 между...", result, maptbl(text_points, result));
		for(auto i = FirstManeuver; i <= LastManeuver; i = (maneuver_s)(i + 1)) {
			if(maneuvers.is(i))
				continue;
			if(bsmeta<maneuveri>::elements[i].cost > result)
				continue;
			an.add(i, getstr(i));
		}
		if(an) {
			auto id = an.choosev(interactive, false, false, 0);
			result -= bsmeta<maneuveri>::elements[id].cost;
			maneuvers.add((maneuver_s)id);
			sb.set(context);
		} else {
			sb.set(context);
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
		auto& weapon = enemy.orders[phase].actor->get(Hands);
		if(weapon)
			weapon.setdisarm(1);
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
	heroa helps;
	print_header(party, enemy, round, phase);
	sb.addn("%1 [%2], %3 [%4].",
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
		result = party.orders[phase].actor->roll(ConflictRoll, party, helps, true,
			bsmeta<conflicti>::elements[type].skills[0][party_action], 0,
			get_action_bonus(party, phase, type), get_action_success(party, phase, type),
			enemy.orders[phase].actor, Nature,
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
	next();
}

class combat_scene : logs::panel {
	hero	animal;
	side	party, enemy;
	int		round;
	void print(stringbuilder& sb) override {
		if(round > 0)
			sb.addn("Гвардейцы: %1i, %2: %3i",
				party.disposition, animal.getname(), enemy.disposition);
	}
public:
	void conflict(conflict_s type) {
		party.disposition = roll_disposition(party, true, Health, Fighter);
		party.maximum = party.disposition;
		enemy.disposition = roll_disposition(enemy, false, Nature, Nature);
		enemy.maximum = enemy.disposition;
		round = 1;
		while(enemy.disposition > 0 && party.disposition > 0) {
			print_header(party, enemy, round, -1);
			choose_orders(enemy.orders, enemy, type, false);
			choose_orders(party.orders, party, type, true);
			resolve_action(party, enemy, type, round, 0);
			resolve_action(party, enemy, type, round, 1);
			resolve_action(party, enemy, type, round, 2);
			round++;
		}
	}
	combat_scene(animal_s type) : round(0) {
		animal.create(type);
		party.select();
		party.friendly = true;
		enemy.add(&animal);
	}
};

void hero::fight(animal_s type) {
	combat_scene combat(type);
	combat.conflict(FightConflict);
	//combat.animal.act("Вы сразили врага. [%герой] убежал%а в высокую траву, оставив за собой кровавый след. %она получил%а хороший урок и будет в ближайшее время зализывать раны.");
}