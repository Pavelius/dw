#include "main.h"

struct stat_info {
	const char* id;
	const char*	name;
} stat_data[] = {{"Strenght", "����"},
{"Dexterity", "��������"},
{"Constitution", "������������"},
{"Intellegence", "���������"},
{"Wisdow", "��������"},
{"Charisma", "�������"}
};
assert_enum(stat, Charisma);
getstr_enum(stat);