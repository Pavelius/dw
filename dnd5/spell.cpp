#include "main.h"

const unsigned Minute = 1;

static unsigned getduration(duration_s v) {
	switch(v) {
	case Action: return 1;
	case Concentration: return 60 * Minute;
	case DurationMinute: return Minute;
	case Duration10Minute: return 10 * Minute;
	case DurationHour: return 60 * Minute;
	case DurationNight: return 8 * 60 * Minute;
	default: return 0;
	}
}

spelli bsmeta<spelli>::elements[] = {{"No spell", "��� ����������"},
// 0 - �������
{"Acid Splash", "�������������� �������", 0, {V, S}, Conjuration, Action, Range10, Instantaneous},
{"Dancing Light", "��������� �������", 0, {V, S, M}, Evocation, Action, Range120, Concentration},
{"Fire Bolt", "�������� ������", 0, {}, Evocation, Action, Range120, Instantaneous, {1, 10, 0, Fire}},
{"Guidance", "��������", 0, {V, S}, Divination, Action, Touch, Concentration, {}},
{"Light", "����", 0, {V, M}, Evocation, Action, Touch, DurationHour, {}},
{"Mage Hand", "��������� ����", 0, {V, S}, Conjuration, Action, Range10, DurationMinute},
{"Minor Illusion", "������ �������", 0, {}, Illusion, Action, Range30, DurationMinute},
{"Poison Spray", "�������� ������", 0, {}, Conjuration, Action, Range10, Instantaneous, {1, 12, 0, Poison}},
{"Prestidigination", "������", 0, {}, Transmutation, Action, Range10, Instantaneous, {}},
{"Ray of Frost", "��� ������", 0, {}, Evocation, Action, Range60, Instantaneous, {1, 8, 0, Cold}},
{"Resistance", "�������������", 0, {}, Abjuration, Action, Touch, Concentration},
{"Sacred Flame", "��������� �����", 0, {}, Evocation, Action, Range60, Instantaneous, {1, 8, 0, Radiant, Dexterity, Save}},
{"Shocking Grasp", "���������� ������", 0, {}, Evocation, Action, Touch, Instantaneous, {1, 8, 0, Lightning, Strenght, Attack}},
{"Spare the Dying", "������� � ���������", 0, {}, Necromancy, Action, Touch, Instantaneous, {}},
{"Thaumaturgy", "������", 0, {}, Transmutation, Action, Range30, Instantaneous},
// 1 - �������
{"Bless", "�������������", 1, {V, S, M}, Transmutation},
{"Command", "�������", 1, {V}, Transmutation},
{"Cure Wounds", "������ �������", 1, {}, Evocation, Action, Touch, Instantaneous, {1, 8, 0, Healing}},
{"Detect Magic", "���������� �����", 1, {V, S}, Divination, Action, Self, Instantaneous},
{"Guiding Bolt", "������������ ���", 1, {V, S}, Evocation, Action, Range120, DurationMinute, {4, 6, 0, Radiant, Dexterity, Attack}},
{"Healing Word", "���������� �����", 1, {V}, Transmutation},
{"Inflict Wounds", "������� ����", 1, {V, S}, Transmutation},
{"Sanctuary", "���������", 1, {}, Transmutation},
{"ShieldOfFaith", "��� ����", 1, {}, Transmutation},
};
assert_enum(spell, LastSpell);

bool creature::use(spell_s id, creature& opponent, int level, int modifier, bool run) {
	auto& ei = bsmeta<spelli>::elements[id];
	auto damage = ei.damage;
	switch(id) {
	case CureWounds:
		if(opponent.gethp() >= opponent.gethpmax())
			return false;
		if(run) {
			damage.d += level -ei.level;
			opponent.damage(-damage.roll(), ei.damage.type, true);
		}
		break;
	default:
		return false;
	}
	return true;
}

bool creature::cast(spell_s id, creature& enemy, bool interactive, bool run) {
	auto& e = bsmeta<spelli>::elements[id];
	if(e.components.is(V) || e.components.is(S)) {
		if(interactive && run) {
			act("%�����");
			auto p = sb.get();
			if(e.components.is(S))
				act(" ��������%� ������");
			if(e.components.is(V)) {
				if(!sb.ispos(p))
					act(" �");
				act(" ���������%� �������� �����");
			}
			if(sb.ispos(p))
				act(" �������� �� %1", enemy.getname());
			act(".");
		}
	}
	auto level = getlevel(id);
	auto modifier = get(Intellegence);
	return use(id, enemy, level, modifier, true);
}

int creature::getlevel(spell_s id) {
	return bsmeta<spelli>::elements[id].level;
}