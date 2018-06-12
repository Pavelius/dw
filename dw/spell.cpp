#include "main.h"

static struct spell_info {
	const char*		id;
	const char*		name;
	char			level[2];
	target_s		target;
	bool			ongoing;
	dice			random;
	const char*		effect;
	const char*		remove;
} spell_data[] = {
	{"Guidance", "�����������", {-1, 0}},
	{"Light", "����", {0, 0}},
	{"Prestidigitation", "������", {0, -1}},
	{"Sanctify", "��������", {-1, 0}},
	{"UnseenServant", "��������� �����", {0, -1}, Self, true},
	//
	{"Bless", "�������������", {-1, 1}, Self, true, {}, "���� ��� ��������� ������."},
	{"CauseFear", "������� �����", {-1, 1}, Self, true, {}, "���� ������ ��������� ������ ������."},
	{"ContactSpirits", "����� �����", {1, -1}},
	{"CureLightWounds", "������ ������ �������", {-1, 1}, Hero, false, {1, 8}, "%����� �������� ����� ������."},
	{"DetectAlignment", "���������� ������������", {-1, 1}},
	{"DetectMagic", "���������� �����", {1, -1}},
	{"Telepathy", "���������", {1, -1}, Self, true},
	{"CharmPerson", "��������� �������", {1, -1}, Self, true},
	{"Invisibility", "�����������", {1, -1}, Self, true, {}, "�������� ��� ���� ����� ������� �� ����.", "����� ������ �� �������� ��������� ��� ���������."},
	{"MagicMissile", "��������� ������", {1, -1}, Monster, false, {2, 4}, "� ������� ��������� ��������� ������������ �������, ������� �������� �����."},
	{"MagicWeapon", "��������� ������", {-1, 1}, Self, false},
	{"Sanctuary", "�������", {1, -1}, Self, false},
	{"SpeakWithDead", "�������� � ����������", {-1, 1}, Self, false},
	{"Alarm", "�������", {1, -1}},
	//
	{"DispelMagic", "�������� �����", {3, -1}},
	{"VisionsThroughTime", "������� ������ �����", {3, -1}},
	{"Fireball", "�������� ���", {3, -1}, Monster},
	{"Mimic", "�����", {3, -1}},
	{"MirrorImage", "���������� �����������", {3, -1}},
	{"Sleep", "���", {3, -1}},
	//
	{"Cage", "������", {5, -1}},
	{"ContactOtherPlane", "��������� � ������ ����������", {5, -1}},
	{"Polymorph", "����������", {5, -1}},
	{"SummonMonster", "����� �������", {5, -1}},
	//
	{"Dominate", "�������������", {7, -1}},
	{"TrueSeeing", "�������� ������", {7, -1}},
	{"ShadowWalk", "������ �� ��������� �����", {7, -1}},
	{"Contingency", "�����������", {7, -1}},
	{"Cloudkill", "����� ������", {7, -1}},
	//
	{"Antipathy", "���������", {9, -1}},
	{"Alert", "����������", {9, -1}},
	{"SoulGem", "������� ��� ����", {9, -1}},
	{"Shelter", "�������", {9, -1}},
	{"PerfectSummons", "��������� �����", {9, -1}},
};
assert_enum(spell, LastSpell);
getstr_enum(spell);

int	hero::getlevel(spell_s value) const {
	int result = 0;
	switch(type) {
	case Cleric:
		result = spell_data[value].level[1];
		break;
	case Wizard:
		if(value == SpellDetectMagic && race == Elf)
			result = 0;
		else if(race == Human && spell_data[value].level[0] == -1 && spell_data[value].level[0] != -1 && isknown(value))
			result = spell_data[value].level[1];
		else
			result = spell_data[value].level[0];
		break;
	default:
		return -1;
	}
	// Prodigy
	if(result && prodigy.is(value))
		result--;
	return result;
}

static int range(int c, int d, int b, bool effect_maximizd) {
	if(effect_maximizd)
		return c*d + b;
	return dice::roll(c, d) + b;
}

result_s hero::cast(spell_s value, monster* te) {
	auto ability = getstat(CastASpell);
	auto result = roll(get(ability));
	bool effect_maximized = false;
	bool target_doubled = false;
	act("%����� ���������%� ����������� �������.");
	switch(result) {
	case Fail:
		logs::add("��� ������� �������, ������� ������� ���� ������ ����.");
		sufferharm(dice::roll(1, 6));
		logs::add("���������� '%1' ���� ������.", getstr(value));
		setprepared(value, false);
		return Fail;
	case PartialSuccess:
		logs::add("�� ���-�� ����� �� ���.");
		logs::add(1, "�� ��������� ������������� �������� � ������������ ��� ����.");
		logs::add(2, "���������� ��������� ���������� - ���������� ������� ������� ���������� ����� ���� � [--1].");
		logs::add(3, "����� �������� ���������� ��� ����� ������. �� �� ������� ��� ������������ ����� ���� �� �����������.");
		switch(logs::input(true, false, "�������� ���� [������������]")) {
		case 1:
			logs::add("����� ������� ���������� ��������� ���� ����.");
			sufferharm(dice::roll(1, 6));
			break;
		case 2:
			logs::add("���������� ��������� ���� ����� � �����������.");
			castpenalty++;
			break;
		case 3:
			logs::add("���������� '%1' ���� ������.", getstr(value));
			setprepared(value, false);
			break;
		}
		break;
	case Success:
		if(is(EmpoweredMagic)) {
			logs::add(1, "������ ���������� ����� [������������], �� �� �������� 1-3 �����.");
			logs::add(2, "[���������] ���������� �����, �� ���������� ����� ������.");
			logs::add(0, "������ �� ����. ������ ������� ������.");
			switch(logs::input(true, false, "[%1] ����� ������� ���������� �� ��������� �����", getname())) {
			case 1:
				effect_maximized = true;
				sufferharm(xrand(1, 3));
				break;
			case 2:
				target_doubled = true;
				setprepared(value, false);
				break;
			}
		}
	}
	int random_effect = 0;
	if(spell_data[value].random) {
		if(effect_maximized)
			random_effect = spell_data[value].random.maximal();
		else
			random_effect = spell_data[value].random.roll();
	}
	hero* th = 0;
	switch(spell_data[value].target) {
	case Self: th = this; break;
	case Hero: th = game::whodo("�� ���� ������� ���������� [%1]?", getstr(value)); break;
	}
	if(spell_data[value].effect) {
		if(th)
			th->act(spell_data[value].effect, random_effect);
		else
			act(spell_data[value].effect, random_effect);
	}
	void* target = th;
	switch(spell_data[value].target) {
	case Monster:
		if(te) {
			switch(value) {
			case SpellMagicMissile:
				inflictharm(*te, random_effect);
				break;
			case SpellFireball:
				inflictharm(*te, random_effect);
				inflictharm(*te, (random_effect * 2) / 3);
				inflictharm(*te, random_effect / 2);
				break;
			}
		}
		break;
	case Hero:
	case Self:
		switch(value) {
		case SpellCureLightWounds:
			th->healharm(random_effect);
			break;
		}
		break;
	}
	if(spell_data[value].ongoing)
		add(value);
	return result;
}

bool hero::isknown(spell_s value) const {
	return (spells_known[value / 8] & (1 << (value % 8))) != 0;
}

bool hero::isprepared(spell_s value) const {
	return (spells_prepared[value / 8] & (1 << (value % 8))) != 0;
}

void hero::setknown(spell_s value, bool state) {
	if(state)
		spells_known[value / 8] |= 1 << (value % 8);
	else
		spells_known[value / 8] &= ~(1 << (value % 8));
}

void hero::setprepared(spell_s value, bool state) {
	if(state)
		spells_prepared[value / 8] |= 1 << (value % 8);
	else
		spells_prepared[value / 8] &= ~(1 << (value % 8));
}

unsigned hero::getspells(spell_s* source, unsigned maximum) {
	if(!iscaster())
		return 0;
	auto pb = source;
	auto pe = pb + maximum;
	for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1)) {
		if(pb >= pe)
			break;
		if(!isprepared(e))
			continue;
		auto n = getlevel(e);
		if(n == -1 || n > level)
			continue;
		if(pb < pe)
			*pb++ = e;
	}
	return pb - source;
}

int hero::getpreparedlevels() const {
	int result = 0;
	for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1)) {
		if(!isprepared(e))
			continue;
		result += getlevel(e);
	}
	return result;
}

void hero::preparespells(bool interactive) {
	if(!iscaster())
		return;
	memset(spells_prepared, 0, sizeof(spells_prepared));
	castpenalty = 0;
	for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1)) {
		if(getlevel(e) == 0)
			setprepared(e, true);
	}
	auto cup = level + 1;
	while(true) {
		auto left = cup - getpreparedlevels();
		if(left <= 0)
			break;
		for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1)) {
			auto level = getlevel(e);
			if(level < 1)
				continue;
			if(!isknown(e))
				continue;
			if(isprepared(e))
				continue;
			if(level <= 1)
				logs::add(e, getstr(e));
			else
				logs::add(e, "%1. ����� [%2i].", getstr(e), level);
		}
		auto value = (spell_s)logs::input(interactive, false,
			(type == Cleric || type == Paladin) ?
			"[%1] �������%2 ������ � �����%2 ��������. ����� ������� �����������? (�������� [%3i])" :
			"[%1] ������� ������� �� ������ ������� � �������� ������� ����� ����������. ����� ���������� �����������? (�������� [%3i])",
			getname(), getA(), left);
		setprepared(value, true);
	}
}

void spell_state::remove() {
	if(caster && spell_data[spell].remove)
		caster->act(spell_data[spell].remove);
	clear();
}