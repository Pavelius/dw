#include "main.h"

static struct ability_info {
	const char*			id;
	const char*			name;
} ability_data[] = {{"Strenght", "Сила"},
{"Agility", "Проворность"},
{"Wits", "Ум"},
{"Empathy", "Интуиция"},
};
assert_enum(ability, Empathy);
getstr_enum(ability);
