#include "main.h"

enum component_s : unsigned char {
	V, S, M
};

struct spell_info {
	const char*			id;
	const char*			name;
	char				level;
	cflags<component_s>	components;
	school_s			school;
	duration_s			cast;
	range_s				range;
	duration_s			duration;
	dice				damage;
	void(*proc)(creature& player, creature& opponent, spell_info& e, bool interactive);
};

static void make_damage(creature& player, creature& opponent, spell_info& e, bool interactive) {
	if(!e.damage)
		return;
	opponent.damage(e.damage.roll(), e.damage.type, interactive);
}

struct spell_info spell_data[] = {{"No spell", "��� ����������"},
	// 0 - �������
{"Acid Splash", "�������������� �������", 0, {V, S}, Conjuration, Action, Range10, Instantaneous},
{"Dancing Light", "��������� �������", 0, {V, S, M}, Evocation, Action, Range120, Concentration},
{"Fire Bolt", "�������� ������", 0, {}, Evocation, Action, Range120, Instantaneous, {1, 10, 0, Fire}, make_damage},
{"Guidance", "��������", 0, {V, S}, Divination, Action, Touch, Concentration},
{"Light", "����", 0, {V, M}, Evocation, Action, Touch, DurationHour},
{"Mage Hand", "��������� ����", 0, {V, S}, Conjuration, Action, Range10, DurationMinute},
{"Minor Illusion", "������ �������", 0, {}, Illusion, Action, Range30, DurationMinute},
{"Poison Spray", "�������� ������", 0, {}, Conjuration, Action, Range10, Instantaneous, {1, 12, 0, Poison}, make_damage},
{"Prestidigination", "������", 0, {}, Transmutation, Action, Range10, Instantaneous},
{"Ray of Frost", "��� ������", 0, {}, Evocation, Action, Range60, Instantaneous, {1, 8, 0, Cold}, make_damage},
{"Resistance", "�������������", 0, {}, Abjuration, Action, Touch, Concentration},
{"Sacred Flame", "��������� �����", 0, {}, Evocation, Action, Range60, Instantaneous, {1, 8, 0, Radiant, Dexterity, Save}, make_damage},
{"Shocking Grasp", "���������� ������", 0, {}, Evocation, Action, Touch, Instantaneous, {1, 8, 0, Lightning, Strenght, Attack}, make_damage},
{"Spare the Dying", "������� � ���������", 0, {}, Necromancy, Action, Touch, Instantaneous},
{"Thaumaturgy", "������", 0, {}, Transmutation, Action, Range30, Instantaneous},
// 1 - �������
{"Bless", "�������������", 1, {V, S, M}, Transmutation},
{"Command", "�������", 1, {V}, Transmutation},
{"Cure Wounds", "������ �������", 1, {}, Transmutation},
{"Detect Magic", "���������� �����", 1, {V, S}, Transmutation},
{"Guiding Bolt", "������������ ���", 1, {V, S}, Transmutation},
{"Healing Word", "���������� �����", 1, {V}, Transmutation},
{"Inflict Wounds", "������� ����", 1, {V, S}, Transmutation},
{"Sanctuary", "���������", 1, {}, Transmutation},
{"ShieldOfFaith", "��� ����", 1, {}, Transmutation},
};
assert_enum(spell, LastSpell);
getstr_enum(spell);

void creature::cast(spell_s id, creature& enemy, bool interactive) {
	auto& e = spell_data[id];
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
	if(spell_data[id].proc)
		spell_data[id].proc(*this, enemy, spell_data[id], interactive);
}

int creature::getlevel(spell_s id) {
	return spell_data[id].level;
}