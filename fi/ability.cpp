#include "main.h"

static struct ability_info {
	const char*			id;
	const char*			name;
} ability_data[] = {{"Strenght", "����"},
{"Agility", "�����������"},
{"Wits", "��"},
{"Empathy", "��������"},
};
assert_enum(ability, Empathy);
getstr_enum(ability);
