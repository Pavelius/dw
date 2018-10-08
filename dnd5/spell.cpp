#include "main.h"

struct spell_info {
	const char*			id;
	const char*			name;
	char				level;
	school_s			school;
	duration_s			cast;
	range_s				range;
	duration_s			duration;
	dice				damage;
} spell_data[] = {{"No spell", "��� ����������"},
// 0 - �������
{"Acid Splash", "�������������� �������", 0, Conjuration, Action, Range10, Instantaneous},
{"Dancing Light", "��������� �������", 0, Evocation, Action, Range120, Concentration},
{"Fire Bolt", "�������� ������", 0, Evocation, Action, Range120, Instantaneous, {1, 10, 0, Fire}},
{"Guidance", "��������", 0, Divination, Action, Touch, Concentration},
{"Light", "����", 0, Evocation, Action, Touch, DurationHour},
{"Mage Hand", "��������� ����", 0, Conjuration, Action, Range10, DurationMinute},
{"Minor Illusion", "������ �������", 0, Illusion, Action, Range30, DurationMinute},
{"Poison Spray", "�������� ������", 0, Conjuration, Action, Range10, Instantaneous, {1, 12, 0, Poison}},
{"Prestidigination", "������", 0, Transmutation, Action, Range10, Instantaneous},
{"Ray of Frost", "��� ������", 0, Evocation, Action, Range60, Instantaneous, {1, 8, 0, Cold}},
{"Resistance", "�������������", 0, Abjuration, Action, Touch, Concentration},
{"Sacred Flame", "�������� �����", 0, Evocation, Action, Range60, Instantaneous, {1, 8, 0, Radiant, Dexterity, Save}},
{"Shocking Grasp", "���������� ������", 0, Evocation, Action, Touch, Instantaneous, {1, 8, 0, Lightning, Strenght, Attack}},
{"Spare the Dying", "������� � ���������", 0, Necromancy, Action, Touch, Instantaneous},
{"Thaumaturgy", "������", 0, Transmutation, Action, Range30, Instantaneous},
//
{"Bless", "", 0, Transmutation},
{"Command", "", 0, Transmutation},
{"Cure Wounds", "", 0, Transmutation},
{"Detect Magic", "", 0, Transmutation},
{"Guiding Bolt", "", 0, Transmutation},
{"Healing Word", "", 0, Transmutation},
{"Inflict Wounds", "", 0, Transmutation},
{"Sanctuary", "", 0, Transmutation},
{"ShieldOfFaith", "", 0, Transmutation},
};
assert_enum(spell, LastSpell);
getstr_enum(spell);

void creature::cast(spell_s id, creature& enemy) {
	auto damage = spell_data[id].damage;
	if(!damage)
		return;
}

int creature::getlevel(spell_s id) {
	return spell_data[id].level;
}