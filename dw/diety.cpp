#include "main.h"

struct god_i {
	const char*		id;
	const char*		name;
} god_data[] = {
	{"Bane", "Бейн"},
	{"Mystra", "Мистра"},
	{"Tor", "Тор"},
	{"Tempus", "Темпус"},
};
assert_enum(god, Tempus);
getstr_enum(god)