#include "main.h"

static char					round, phase;
static const char*			text_count[] = {"��������", "������", "�����", "�����", "��������", "�������", "��������", "�������", "����"};
static adat<combatant*, 32> combatants;

static int compare_dices(const void* p1, const void* p2) {
	return *((char*)p1) - *((char*)p2);
}

static struct brute_info {
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
static struct action {
	trait_s		trait;
	knack_s		knack;
	const char*	text;
	bool		hostile;
	bool		heroonly;
	operator bool() const { return text != 0; }
} action_data[] = {{Finesse, AttackBow, "������� ������ �� [����].", true},
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

static action* find_action(knack_s id) {
	for(auto& e : action_data) {
		if(e.knack == id)
			return &e;
	}
	return 0;
}

class brute : public combatant {

	brute_info*	type;
	char		count;

public:

	constexpr brute(brute_info* type, char count = 6) : type(), count(count) {}
	explicit operator bool() const { return type != 0; }

	const char* getname() const override {
		return type->name[1];
	}

	void damage(int wounds_count, int drama_per_wounds, bool interactive) override {
		count -= 1 + wounds_count / drama_per_wounds;
		if(count < 0)
			count = 0;
	}

	int get(trait_s id) const override {
		return type->threat;
	}

	int getpassivedefence() const override {
		return (1 + type->threat) * 5;
	}

	bool ishero() const override {
		return false;
	}

};

int combatant::getblockactions() const {
	if(getaction() == phase)
		return 1;
	return 2;
}

int combatant::getactioncount() const {
	auto result = 0;
	for(auto e : actions) {
		if(e)
			result++;
	}
	return result;
}

int combatant::getinitiative() const {
	auto result = 0;
	for(auto e : actions) {
		if(e == 0)
			break;
		result += e;
	}
	return result;
}

void combatant::rollinitiative() {
	memset(actions, 0, sizeof(actions));
	auto panache = get(Panache);
	for(auto i = 0; i < panache; i++)
		actions[i] = 1 + rand() % 10;
	qsort(actions, panache, sizeof(actions[0]), compare_dices);
}

void combatant::useaction() {
	memcpy(actions, actions + 1, sizeof(actions) - 1);
	actions[sizeof(actions) - 1] = 0;
}

void combatant::beforecombat() {
	round = 1; phase = 0;
	combatants.clear();
}

void combatant::add(side_s side) {
	this->side = side;
	combatants.add(this);
}

void combatant::getdescription(char* result, const char* result_maximum) const {
	if(isplayer())
		szprints(result, result_maximum, "[%1]", getname());
	else
		szprints(result, result_maximum, "%1", getname());
	if(!ishero())
		szprints(zend(result), result_maximum, " (%1i)", getcount());
	else if(getdramawounds())
		szprints(zend(result), result_maximum, " (%1i/%2i)", getdramawounds(), getdramawoundsmax());
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

int combatant::whatdo(bool clear_text) const {
	return logs::input(isplayer(), clear_text, "��� ����� ������ [%1]?", getname());
}

static unsigned select(combatant** result, unsigned result_count, const combatant* player, bool hostile, bool heroonly) {
	auto p = result;
	auto pe = result + result_count;
	for(auto pc : combatants) {
		if(!pc->isready())
			continue;
		if(hostile && !player->isenemy(pc))
			continue;
		if(heroonly && !player->isenemyhero(pc))
			continue;
		if(p < pe)
			*p++ = pc;
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
		auto id = logs::input(interactive, false);
		if(!id)
			return false;
	}
	for(auto i = 0; i < need_actions; i++)
		enemy->useaction();
	if(enemy->roll(interactive, Wits, defence_knack, tn)) {
		enemy->act("%����� �����%� ����.");
		return true;
	}
	return false;
}

static void make_move(combatant* player) {
	char temp[512];
	if(player->ishero()) {
		bool interactive = player->isplayer();
		for(unsigned i = 0; i < sizeof(action_data) / sizeof(action_data[0]); i++) {
			if(!player->get(action_data[i].knack))
				continue;
			if(!has(player, action_data[i].hostile, action_data[i].heroonly))
				continue;
			logs::add(i, action_data[i].text);
		}
		auto& a = action_data[player->whatdo(false)];
		logs::add("\n");
		auto enemy = choose(player, interactive, a.hostile, a.heroonly, &combatant::getpassivedefence);
		auto roll_result = 0;
		auto tn = enemy->getpassivedefence();
		if(enemy->ishero()) {
			if(player->roll(interactive, a.trait, a.knack, tn, 0, &roll_result)) {
				if(!try_defend(interactive, player, enemy, enemy->getdefence(), roll_result)) {
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
			if(player->roll(interactive, a.trait, a.knack, tn + 5 * raises)) {
				enemy->damage(killed * 20, 20);
				player->actvs(enemy, "%����� ��������%� %��������� � ������%� [%1].", maptbl(text_count, killed));
			} else
				player->actvs(enemy, "%����� ��������%� %���������, �� �� ����%�� ������ �������.");
		}
	} else {
		auto enemy = choose(player, false, true, false, &combatant::getpassivedefence);
		auto tn = enemy->getpassivedefence();
		logs::add("\n");
		player->actvs(enemy, "%����� ����������� �� %���������.");
		auto roll_result = hero::roll(player->getcount(), player->get(Finesse));
		int raises = (roll_result - tn) / 5;
		if(raises >= 0) {
			if(!try_defend(enemy->isplayer(), player, enemy, enemy->getdefence(), roll_result)) {
				int weapon = 6;
				int wounds = (1 + raises) * weapon;
				if(enemy->ishero())
					enemy->damage(wounds);
				else
					enemy->damage(20 + wounds);
			}
		} else
			player->act("%����� ������ �����%��� �� �����.");
	}
	player->useaction();
}

static void roll_initiative() {
	for(auto pc : combatants) {
		if(!pc->isready())
			continue;
		pc->rollinitiative();
	}
}

static void resolve_round() {
	roll_initiative();
	for(phase = 1; phase <= 10; phase++) {
		for(auto pc : combatants) {
			if(!pc->isready())
				continue;
			if(pc->getaction() != phase)
				continue;
			make_move(pc);
		}
	}
	logs::next();
}

static bool is_combat_continue() {
	auto side = combatants[0]->getside();
	for(auto pc : combatants) {
		if(pc->getside() != side)
			return true;
	}
	return false;
}

void combatant::combat() {
	logs::state push;
	logc.information = "%round\n%combatants";
	while(is_combat_continue()) {
		resolve_round();
		round++;
	}
};

PRINTPLG(round) {
	szprints(result, result_maximum, "##����� %1i, ���� %2i", round, phase);
	return result;
}

PRINTPLG(combatants) {
	result[0] = 0;
	for(auto p : combatants) {
		if(result[0])
			zcat(result, "\n");
		p->getdescription(zend(result), result_maximum);
	}
	return result;
}