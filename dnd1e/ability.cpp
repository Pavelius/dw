#include "main.h"

static struct ability {
	const char*		id;
	const char*		name;
} ability_data[] = {
	{"Strenght", "����"},
	{"Dexterity", "��������"},
	{"Constitution", "������������"},
	{"Intellegence", "���������"},
	{"Wisdow", "��������"},
	{"Charisma", "�������"},
};
assert_enum(ability, Charisma);
getstr_enum(ability);
bsreq ability_type[] = {
	BSREQ(ability, id),
	BSREQ(ability, name),
	{}
};
BSMETA(ability);