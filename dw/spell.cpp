#include "main.h"

spelli bsmeta<spelli>::elements[] = {{"Guidance", "�����������", {-1, 0}},
{"Light", "����", {0, 0}},
{"Prestidigitation", "������", {0, -1}},
{"Sanctify", "��������", {-1, 0}},
{"UnseenServant", "��������� �����", {0, -1}, TargetSelf, true},
//
{"Bless", "�������������", {-1, 1}, TargetSelf, true, "���� ��� ��������� ������."},
{"CauseFear", "������� �����", {-1, 1}, TargetSelf, true, "���� ������ ��������� ������ ������."},
{"ContactSpirits", "����� �����", {1, -1}},
{"CureLightWounds", "������ ������ �������", {-1, 1}, TargetHero, false, "%����� �������� ����� ������."},
{"DetectAlignment", "���������� ������������", {-1, 1}},
{"DetectMagic", "���������� �����", {1, -1}},
{"Telepathy", "���������", {1, -1}, TargetSelf, true},
{"CharmPerson", "��������� �������", {1, -1}, TargetSelf, true},
{"Invisibility", "�����������", {1, -1}, TargetSelf, true, "�������� ��� ���� ����� ������� �� ����.", "����� ������ �� �������� ��������� ��� ���������."},
{"MagicMissile", "��������� ������", {1, -1}, TargetMonster, false, "� ������� ��������� ��������� ������������ �������, ������� �������� �����."},
{"MagicWeapon", "��������� ������", {-1, 1}, TargetSelf, false},
{"Sanctuary", "�������", {1, -1}, TargetSelf, false},
{"SpeakWithDead", "�������� � ����������", {-1, 1}, TargetSelf, false},
{"Alarm", "�������", {1, -1}},
//
{"DispelMagic", "�������� �����", {3, -1}},
{"VisionsThroughTime", "������� ������ �����", {3, -1}},
{"Fireball", "�������� ���", {3, -1}, TargetMonster},
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

int casti::roll() const {
	auto r = 0;
	auto& ed = bsmeta<spelli>::elements[id];
	//if(ed.random) {
	//	if(maximized)
	//		r = ed.random.maximal();
	//	else
	//		r = ed.random.roll();
	//}
	return r;
}

int	hero::getlevel(spell_s subtype) const {
	int result = 0;
	auto& ed = bsmeta<spelli>::elements[subtype];
	switch(type) {
	case Cleric:
		result = ed.level[1];
		break;
	case Wizard:
		if(subtype == SpellDetectMagic && race == Elf)
			result = 0;
		else if(race == Human && ed.level[0] == -1 && ed.level[0] != -1 && is(subtype))
			result = ed.level[1];
		else
			result = ed.level[0];
		break;
	default:
		return -1;
	}
	// Prodigy
	if(result && prodigy.is(subtype))
		result--;
	return result;
}

static int range(int c, int d, int b, bool effect_maximizd) {
	if(effect_maximizd)
		return c*d + b;
	return dice::roll(c, d) + b;
}

result_s hero::cast(casti& ci) {
	auto ability = getstat(CastASpell);
	auto result = roll(get(ability));
	auto spell_name = getstr(ci.id);
	act("%����� ���������%� ����������� �������.");
	switch(result) {
	case Fail:
		sb.add("��� ������� �������, ������� ������� ���� ������ ����.");
		sufferharm(dice::roll(1, 6));
		sb.add("���������� '%1' ���� ������.", spell_name);
		setprepared(ci.id, false);
		return Fail;
	case PartialSuccess:
		sb.add("�� ���-�� ����� �� ���.");
		an.add(1, "�� ��������� ������������� �������� � ������������ ��� ����.");
		an.add(2, "���������� ��������� ���������� - ���������� ������� ������� ���������� ����� ���� � [--1].");
		an.add(3, "����� �������� ���������� ��� ����� ������. �� �� ������� ��� ������������ ����� ���� �� �����������.");
		switch(an.choose(true, false, "�������� ���� [������������]")) {
		case 1:
			sb.add("����� ������� ���������� ��������� ���� ����.");
			sufferharm(dice::roll(1, 6));
			break;
		case 2:
			sb.add("���������� ��������� ���� ����� � �����������.");
			castpenalty++;
			break;
		case 3:
			sb.add("���������� '%1' ���� ������.", spell_name);
			setprepared(ci.id, false);
			break;
		}
		break;
	case Success:
		if(is(EmpoweredMagic)) {
			an.add(1, "������ ���������� ����� [������������], �� �� �������� 1-3 �����.");
			an.add(2, "[���������] ���������� �����, �� ���������� ����� ������.");
			an.add(0, "������ �� ����. ������ ������� ������.");
			switch(an.choose(false, "[%1] ����� ������� ���������� �� ��������� �����", getname())) {
			case 1:
				ci.maximized = true;
				sufferharm(xrand(1, 3));
				break;
			case 2:
				ci.doubled = true;
				setprepared(ci.id, false);
				break;
			}
		}
	}
}

bool hero::cast(spell_s subtype, thing& enemy) {
	casti ci = subtype;
	auto result = cast(ci);
	auto success = (result == Success || result == PartialSuccess);
	return success;
}

//result_s hero::cast(spell_s subtype, monster* te) {
//	int random_effect = 0;
//	casti ci = subtype;
//	auto& ed = bsmeta<spelli>::elements[subtype];
//	auto result = cast(ci);
//	if(ed.random) {
//		if(ci.maximized)
//			random_effect = ed.random.maximal();
//		else
//			random_effect = ed.random.roll();
//	}
//	hero* th = 0;
//	switch(ed.target) {
//	case TargetSelf: th = this; break;
//	case TargetHero: th = game::whodo("�� ���� ������� ���������� [%1]?", getstr(subtype)); break;
//	}
//	if(ed.effect) {
//		if(th)
//			th->act(ed.effect, random_effect);
//		else
//			act(ed.effect, random_effect);
//	}
//	void* target = th;
//	switch(ed.target) {
//	case TargetMonster:
//		if(te) {
//			switch(subtype) {
//			case SpellMagicMissile:
//				inflictharm(*te, random_effect);
//				break;
//			case SpellFireball:
//				inflictharm(*te, random_effect);
//				inflictharm(*te, (random_effect * 2) / 3);
//				inflictharm(*te, random_effect / 2);
//				break;
//			}
//		}
//		break;
//	case TargetHero:
//	case TargetSelf:
//		switch(subtype) {
//		case SpellCureLightWounds:
//			th->healharm(random_effect);
//			break;
//		}
//		break;
//	}
//	if(ed.ongoing)
//		add(subtype);
//	return result;
//}

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
	spells_prepared.clear();
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
			if(!is(e))
				continue;
			if(isprepared(e))
				continue;
			if(level <= 1)
				an.add(e, getstr(e));
			else
				an.add(e, "%1. ����� [%2i].", getstr(e), level);
		}
		char temp[512]; stringbuilder sbn(temp);
		auto format = "[%�����] �����%��� ������� �� ������ ������� � ������%��� ������� ����� ����������. ����� ���������� �����������? (�������� [%1i])";
		if(type == Cleric || type == Paladin)
			format = "[%�����] �������%� ������ � �����%� ��������. ����� ������� �����������? (�������� [%1i])";
		act(sbn, format, left);
		auto subtype = (spell_s)an.choose(interactive, true, temp);
		setprepared(subtype, true);
	}
}

void spell_state::remove() {
	if(caster && bsmeta<spelli>::elements[spell].remove)
		caster->act(bsmeta<spelli>::elements[spell].remove);
	clear();
}