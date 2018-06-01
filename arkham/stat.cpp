#include "main.h"

static struct stat_i {
	const char*		id;
	const char*		name;
} stat_data[] = {{"", ""},
{"Speed", "��������"},
{"Sneack", "����������"},
{"Fight", "���"},
{"Will", "����"},
{"Lore", "������"},
{"Luck", "�����"},
//
{"Sanity", "��������"},
{"Stamina", "�����"},
//
{"Clue", "�����"},
{"Money", "������"},
{"Focus", "�����"},
{"TurnToSkip", "���������� ���"},
{"Blessed", "�����������"},
{"Movement", "��������"},
// Special damage
{"Stamina Maximum", "�������� �����"},
{"Sanity Maximum", "�������� ��������"},
// Special checks
{"Combat Check", "������ ������"},
{"Evade Check", "������ ���������"},
{"Horror Check", "������ �����"},
{"Skill Check", "������ ������ ������"},
{"Spell Check", "������ ����������"},
// Calculated values
{"Test One Die"},
{"Test Two Die"},
//
{"Ally", "�������"},
{"Common Item", "����� �������"},
{"Skill", "�����"},
{"Spell", "����������"},
{"Unique Item", "���������� �������"},
};
assert_enum(stat, UniqueItem);
getstr_enum(stat);