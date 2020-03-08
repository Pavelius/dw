#include "main.h"

const unsigned Minute = 1;

static unsigned getduration(duration_s v) {
	switch(v) {
	case Action: return 1;
	case Concentration: return 60 * Minute;
	case DurationMinute: return Minute;
	case Duration10Minute: return Minute * 10;
	case DurationHour: return Minute * 60;
	case DurationNight: return Minute * 8 * 60;
	default: return 0;
	}
}

static bool cure_wounds(creature& player, creature& opponent, spelli& e, bool interactive, bool run) {
	if(opponent.gethp() >= opponent.gethpmax())
		return false;
	if(run)
		opponent.damage(-e.damage.roll(), e.damage.type, interactive);
	return true;
}

static bool make_damage(creature& player, creature& opponent, spelli& e, bool interactive, bool run) {
	if(!e.damage)
		return false;
	if(!player.isenemy(&opponent))
		return false;
	if(run)
		opponent.damage(e.damage.roll(), e.damage.type, interactive);
	return true;
}

static bool apply_opponent(creature& player, creature& opponent, spelli& e, bool interactive, bool run) {
	switch(e.value.type) {
	case Spell:
		if(run)
			opponent.set((spell_s)e.value.value, getduration(e.duration));
		break;
	case Feat:
		if(opponent.is((feat_s)e.value.value))
			return false;
		if(run)
			opponent.set((feat_s)e.value.value);
		break;
	default:
		return false;
	}
	return true;
}

static bool remove_opponent(creature& player, creature& opponent, spelli& e, bool interactive, bool run) {
	switch(e.value.type) {
	case Feat:
		if(!opponent.is((feat_s)e.value.value))
			return false;
		if(run)
			opponent.remove((feat_s)e.value.value);
		break;
	default:
		return false;
	}
	return true;
}

spelli bsmeta<spelli>::elements[] = {{"No spell", "��� ����������"},
// 0 - �������
{"Acid Splash", "�������������� �������", 0, {V, S}, Conjuration, Action, Range10, Instantaneous},
{"Dancing Light", "��������� �������", 0, {V, S, M}, Evocation, Action, Range120, Concentration},
{"Fire Bolt", "�������� ������", 0, {}, Evocation, Action, Range120, Instantaneous, {1, 10, 0, Fire}},
{"Guidance", "��������", 0, {V, S}, Divination, Action, Touch, Concentration, {}, Guided},
{"Light", "����", 0, {V, M}, Evocation, Action, Touch, DurationHour, {}, Light},
{"Mage Hand", "��������� ����", 0, {V, S}, Conjuration, Action, Range10, DurationMinute, {}, MageHand},
{"Minor Illusion", "������ �������", 0, {}, Illusion, Action, Range30, DurationMinute, {}, MinorIllusion},
{"Poison Spray", "�������� ������", 0, {}, Conjuration, Action, Range10, Instantaneous, {1, 12, 0, Poison}},
{"Prestidigination", "������", 0, {}, Transmutation, Action, Range10, Instantaneous, {}, Prestidigination},
{"Ray of Frost", "��� ������", 0, {}, Evocation, Action, Range60, Instantaneous, {1, 8, 0, Cold}},
{"Resistance", "�������������", 0, {}, Abjuration, Action, Touch, Concentration, {}, Resisted},
{"Sacred Flame", "��������� �����", 0, {}, Evocation, Action, Range60, Instantaneous, {1, 8, 0, Radiant, Dexterity, Save}},
{"Shocking Grasp", "���������� ������", 0, {}, Evocation, Action, Touch, Instantaneous, {1, 8, 0, Lightning, Strenght, Attack}},
{"Spare the Dying", "������� � ���������", 0, {}, Necromancy, Action, Touch, Instantaneous, {}, SpareOfDying, remove_opponent},
{"Thaumaturgy", "������", 0, {}, Transmutation, Action, Range30, Instantaneous},
// 1 - �������
{"Bless", "�������������", 1, {V, S, M}, Transmutation},
{"Command", "�������", 1, {V}, Transmutation},
{"Cure Wounds", "������ �������", 1, {}, Evocation, Action, Touch, Instantaneous, {1, 8, 0, Healing}, NoFeat, cure_wounds},
{"Detect Magic", "���������� �����", 1, {V, S}, Divination, Action, Self, Instantaneous, {}, DetectMagic},
{"Guiding Bolt", "������������ ���", 1, {V, S}, Evocation, Action, Range120, DurationMinute, {4, 6, 0, Radiant, Dexterity, Attack}, GuidingBolt},
{"Healing Word", "���������� �����", 1, {V}, Transmutation},
{"Inflict Wounds", "������� ����", 1, {V, S}, Transmutation},
{"Sanctuary", "���������", 1, {}, Transmutation},
{"ShieldOfFaith", "��� ����", 1, {}, Transmutation},
};
assert_enum(spell, LastSpell);

bool creature::cast(spell_s id, creature& enemy, bool interactive, bool run) {
	auto& e = bsmeta<spelli>::elements[id];
	if(e.components.is(V) || e.components.is(S)) {
		if(interactive) {
			act("%�����");
			if(e.components.is(S))
				act(" ��������%� ������");
			if(e.components.is(V)) {
				if(e.components.is(S))
					act(" �");
				act(" ���������%� �������� �����");
			}
			act(".");
		}
	}
	if(e.proc) {
		if(!e.proc(*this, enemy, e, interactive, run))
			return false;
	} else {
		if(e.value) {
			if(!apply_opponent(*this, enemy, e, interactive, run))
				return false;
		}
		if(e.damage) {
			if(!make_damage(*this, enemy, e, interactive, run))
				return false;
		}
	}
	return true;
}

int creature::getlevel(spell_s id) {
	return bsmeta<spelli>::elements[id].level;
}