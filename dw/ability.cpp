#include "main.h"

struct stat_info {
	const char* id;
	const char*	name;
} stat_data[] = {{"Strenght", "Сила"},
{"Dexterity", "Ловкость"},
{"Constitution", "Телосложение"},
{"Intellegence", "Интеллект"},
{"Wisdow", "Мудрость"},
{"Charisma", "Харизма"}
};
BSENUM(stat, Charisma);