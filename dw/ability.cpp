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
BSENUM(stat, Charisma);