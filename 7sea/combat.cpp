#include "main.h"

static char			round, phase;
static const char*	text_count[] = {"��������", "������", "�����", "�����", "��������", "�������", "��������", "�������", "����"};

static int compare_dices(const void* p1, const void* p2) {
	return *((char*)p1) - *((char*)p2);
}

static struct brute_i {
	struct knackset {
		knack_s			id;
		char			value;
		operator bool() const { return value != 0; }
	};
	const char*			name[2];
	char				threat;
	knackset			skills[8];

	int get(knack_s id) const {
		for(auto& e : skills) {
			if(e.id == id)
				return e.value;
			if(!e)
				break;
		}
		return 0;
	}

} brute_data[] = {
	{{"Cardinal's mens", "���� ���������"}, 3, {Footwork, -1, Sprinting, 1}}
};

struct combatant {

	operator bool() const { return count != 0; }

	void clear() {
		memset(this, 0, sizeof(*this));
	}

	int get(trait_s id) const {
		if(player)
			return player->get(id);
		else
			return brute->threat;
	}

	int get(knack_s id) const {
		if(player)
			return player->get(id);
		else
			return brute->get(id);
	}

	int getinitiative() const {
		auto result = 0;
		for(auto e : actions) {
			if(e == 0)
				break;
			result += e;
		}
		return result;
	}

	const char* getname() const {
		if(player)
			return player->getname();
		return brute->name[1];
	}

	const char* getA() const {
		if(player)
			return player->getA();
		if(count)
			return "";
		return "�";
	}

	const char* getAS() const {
		if(player)
			return player->getAS();
		if(count)
			return "��";
		return "���";
	}

	bool isplayer() const {
		return player && player->isplayer();
	}

	bool ishero() const {
		return player != 0;
	}

	bool isenemy(const combatant* p) const {
		return side != p->side;
	}

	bool isenemyhero(const combatant* p) const {
		if(!p->ishero())
			return false;
		return isenemy(p);
	}

	bool roll(bool interactive, trait_s trait, knack_s knack, int target_number, int bonus = 0, int* result = 0) {
		if(player)
			return player->roll(interactive, trait, knack, target_number, bonus, result);
		return 0;
	}

	knack_s getdefence() const {
		return Footwork;
	}

	int getpassivedefence() const {
		if(brute)
			return (1 + brute->threat) * 5;
		auto knack = getdefence();
		return (1 + player->get(knack)) * 5;
	}

	int getaction() const {
		return actions[0];
	}

	int getactioncount() const {
		auto result = 0;
		for(auto e : actions) {
			if(e)
				result++;
		}
		return result;
	}

	void useaction() {
		memcpy(actions, actions + 1, sizeof(actions) - 1);
		actions[sizeof(actions) - 1] = 0;
	}

	void damage(int wounds, int raises = 0) {
		if(brute)
			count -= 1 + raises;
		else
			player->damage(wounds, true);
		if(count < 0)
			count = 0;
	}

	int getblockactions() const {
		if(getaction() == phase)
			return 1;
		return 2;
	}

	int getcount() const {
		return count;
	}

	char* sayroll(char* temp, const char* result_maximum, trait_s trait, knack_s knack, int target_number) const {
		if(!player)
			return temp;
		return player->sayroll(temp, result_maximum, trait, knack, target_number);
	}

	void getdescription(char* result, const char* result_maximum) {
		zcat(result, getname());
		if(brute && getcount())
			szprints(zend(result), result_maximum, " (%1i)", getcount());
		else if(player && player->isplayer()) {
			if(player->getdramawounds())
				szprints(zend(result), result_maximum, " (%1i/%2i)", player->getdramawounds(), player->getmaxdramawounds());
		}
		if(actions[0]) {
			zcat(result, ": ");
			auto p = zend(result);
			for(auto e : actions) {
				if(!e)
					break;
				if(p[0])
					zcat(p, ", ");
				sznum(zend(p), e);
			}
			zcat(result, ".");
		}
	}

	side_s getside() const {
		return side;
	}

	void rollinitiative() {
		memset(actions, 0, sizeof(actions));
		auto panache = get(Panache);
		for(auto i = 0; i < panache; i++)
			actions[i] = 1 + rand() % 10;
		qsort(actions, panache, sizeof(actions[0]), compare_dices);
	}

	combatant() {
	}

	combatant(hero* object, side_s side) {
		clear();
		this->player = object;
		this->count = 1;
		this->side = side;
	}

	combatant(brute_i* object, side_s side) {
		clear();
		this->brute = object;
		this->count = 6;
		this->side = side;
	}

private:

	brute_i * brute;
	hero*		player;
	char		actions[10];
	int			count;
	side_s		side;

};
static adat<combatant, 32> combatants;

static struct action {
	trait_s				trait;
	knack_s				knack;
	const char*			text;
	bool				hostile;
	bool				heroonly;
	operator bool() const { return text != 0; }
} action_data[] = {
	{Finesse, AttackBow, "������� ������ �� [����].", true},
{Finesse, AttackCrossbow, "���������� �� [��������].", true},
{Finesse, AttackDirtyFighting, "������� ����� � ����������� ��� ������� ����� � �����.", true},
{Finesse, AttackFencing, "��������� ����� [�������].", true},
{Finesse, AttackFirearms, "���������� �� [�������].", true},
{Finesse, AttackHeavyWeapon, "������ ���� ������ [�����].", true},
{Finesse, AttackKnife, "������� �� ����� [�����].", true},
{Finesse, AttackPanzerhand, "������� ���� [������������ �����].", true},
{Finesse, AttackPolearm, "������� ����� [������].", true},
{Finesse, AttackPugilism, "������� ����� ������� � ������.", true},
{Finesse, Beat, "������� ������� ����, ������� ���� �� ������ �����������.", true, true},
{Finesse, Bind, "�������� ������ �����.", true, true},
{Finesse, CorpseACorpse, "������� � ������� �������, ���� � ����.", true, true},
{Finesse, Feint, "��������� �������� �����.", true, true},
{Finesse, Lunge, "������� �������������� ����, ������� ������� ����� �����.", true, true},
{Finesse, PommelStrike, "������� ���� ������ � ����.", true, true},
{Finesse, Togging, "��������� ����� � ���������� ����, ������� ������� ��� ������ �����.", true, true},
};

static unsigned select(combatant** result, unsigned result_count, const combatant* player, bool hostile, bool heroonly) {
	auto p = result;
	auto pe = result + result_count;
	for(auto& e : combatants) {
		if(!e)
			continue;
		if(hostile && !player->isenemy(&e))
			continue;
		if(heroonly && !player->isenemyhero(&e))
			continue;
		if(p < pe)
			*p++ = &e;
		else
			break;
	}
	return p - result;
}

static bool has(const combatant* player, bool hostile, bool heroonly) {
	combatant* result[1];
	return select(result, sizeof(combatants.data) / sizeof(combatants.data[0]), player, hostile, heroonly) != 0;
}

static combatant* choose(const combatant* player, bool interactive, bool hostile, bool heroonly, int (combatant::*gettn)() const) {
	combatant* result[sizeof(combatants.data) / sizeof(combatants.data[0])];
	auto count = select(result, sizeof(combatants.data) / sizeof(combatants.data[0]), player, hostile, heroonly);
	if(count == 0)
		return 0;
	else if(count == 1)
		return result[0];
	for(unsigned i = 0; i < count; i++) {
		if(gettn)
			logs::add(i, "%1 (��������� [%2i])", result[i]->getname(), (result[i]->*gettn)());
		else
			logs::add(i, result[i]->getname());
	}
	auto i = logs::input(interactive, false, "������� [����]:");
	return result[i];
}

static bool try_defend(bool interactive, combatant* player, combatant* enemy, knack_s defence_knack, int tn) {
	auto need_actions = enemy->getblockactions();
	if(enemy->getactioncount() < need_actions)
		return false;
	if(interactive) {
		logs::add(1, "���������� �������������, ������� ������ [%1]+[%2] ������ ��������� [%4i] � �������� %3i ��������.", getstr(Wits), getstr(defence_knack), need_actions, tn);
		logs::add(0, "�� �������� �����������. ��������� �������� ��� ����", getstr(Wits), getstr(defence_knack), need_actions);
		auto id = logs::input(true, false);
		if(!id)
			return false;
	}
	for(auto i = 0; i < need_actions; i++)
		enemy->useaction();
	if(enemy->roll(interactive, Wits, defence_knack, tn)) {
		logs::add("%1 �����%� ����.", enemy->getname(), enemy->getA());
		return true;
	}
	return false;
}

static void make_move(combatant* player) {
	char temp[512];
	bool interactive = player->isplayer();
	if(player->ishero()) {
		for(unsigned i = 0; i < sizeof(action_data) / sizeof(action_data[0]); i++) {
			if(!player->get(action_data[i].knack))
				continue;
			if(!has(player, action_data[i].hostile, action_data[i].heroonly))
				continue;
			logs::add(i, action_data[i].text);
		}
		auto& a = action_data[logs::input(interactive, false, "��� ����� ������ [%1]?", player->getname())];
		logs::add("\n");
		auto enemy = choose(player, interactive, a.hostile, a.heroonly, &combatant::getpassivedefence);
		auto roll_result = 0;
		auto tn = enemy->getpassivedefence();
		if(enemy->ishero()) {
			if(player->roll(true, a.trait, a.knack, tn, 0, &roll_result)) {
				if(!try_defend(true, player, enemy, enemy->getdefence(), roll_result)) {
					item weapon = Rapier;
					auto damage = weapon.getdamage();
					enemy->damage(hero::roll(damage.roll, damage.keep));
				}
			}
		} else {
			logs::add(0, "�������� ������ �� ���. ��������� [%1i].", tn);
			if(enemy->getcount() > 1)
				logs::add(1, "�������� ����� [����] �� ���. ��������� [%1i].", tn + 5 * 1);
			if(enemy->getcount() > 2)
				logs::add(2, "�������� ����� [����] �� ���. ��������� [%1i].", tn + 5 * 2);
			if(enemy->getcount() > 3)
				logs::add(3, "�������� ����� [�������] �� ���. ��������� [%1i].", tn + 5 * 3);
			auto raises = logs::input(interactive, false, player->sayroll(temp, zendof(temp), a.trait, a.knack, 0));
			logs::add("\n");
			auto killed = 1 + raises;
			if(player->roll(true, a.trait, a.knack, tn + 5 * raises)) {
				enemy->damage(0, raises);
				logs::add("%1 ��������%2 %3 � ������%2 [%4].", player->getname(), player->getA(), enemy->getname(), maptbl(text_count, killed));
			} else
				logs::add("%1 ��������%2 %3, �� �� ���� ������ �������.", player->getname(), player->getA(), enemy->getname());
		}
	} else {
		auto enemy = choose(player, false, true, false, &combatant::getpassivedefence);
		auto tn = enemy->getpassivedefence();
		logs::add("\n");
		logs::add("%1 ����������� �� %2.", player->getname(), enemy->getname());
		auto roll_result = hero::roll(player->getcount(), player->get(Finesse));
		int raises = (roll_result - tn) / 5;
		if(raises >= 0) {
			if(!try_defend(enemy->isplayer(), player, enemy, enemy->getdefence(), roll_result)) {
				int weapon = 6;
				int wounds = (1 + raises) * weapon;
				if(enemy->ishero())
					enemy->damage(wounds);
				else
					enemy->damage(0, 1 + wounds / 20);
			}
		} else
			logs::add("%1 ������ �����%2 �� �����.", player->getAS());
	}
	player->useaction();
}

static void roll_initiative() {
	for(auto& e : combatants) {
		if(!e)
			continue;
		e.rollinitiative();
	}
}

static void resolve_round() {
	roll_initiative();
	for(phase = 1; phase <= 10; phase++) {
		for(auto& e : combatants) {
			if(!e)
				continue;
			if(e.getaction() != phase)
				continue;
			make_move(&e);
		}
	}
	logs::next();
}

static bool is_combat_continue() {
	auto side = combatants[0].getside();
	for(auto& e : combatants) {
		if(e.getside() != side)
			return true;
	}
	return false;
}

void hero::combat() {
	logs::state push;
	logc.information = "%round\n%combatants";
	round = 1; phase = 0;
	combatants.add({players[0], PartySide});
	combatants.add({players[1], PartySide});
	combatants.add({brute_data, EnemySide});
	while(is_combat_continue()) {
		resolve_round();
		round++;
	}
};

static void print_round(char* result, const char* result_maximum) {
	szprints(result, result_maximum, "##����� %1i, ���� %2i", round, phase);
}

static void print_combatants(char* result, const char* result_maximum) {
	result[0] = 0;
	for(auto& e : combatants) {
		if(result[0])
			zcat(result, "\n");
		e.getdescription(zend(result), result_maximum);
	}
}