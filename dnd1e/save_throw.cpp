#include "main.h"

struct save_info {
	const char*		id;
	const char*		name;
} save_data[] = {
	{"Save vs Paralization", "������ �� �����������"},
	{"Save vs Poison", "������ �� ���"},
	{"Save vs Death", "������ �� ������"},
	{"Save vs Wands", "������ �� �������"},
	{"Save vs Petrification", "������ �� ����������"},
	{"Save vs Polymorph", "������ �� �����������"},
	{"Save vs Breath Weapon", "������ �� �������"},
	{"Save vs Spells", "������ �� �����"},
};
assert_enum(save, SaveVsSpells);
getstr_enum(save);
metadc_enum(save);