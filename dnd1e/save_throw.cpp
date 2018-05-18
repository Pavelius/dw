#include "main.h"

struct save_i {
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
bsreq save_type[] = {
	BSREQ(save_i, id, text_type),
	BSREQ(save_i, name, text_type),
	{}
};
assert_enum(save, SaveVsSpells);
getstr_enum(save);
BSMETA(save);