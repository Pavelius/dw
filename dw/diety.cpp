#include "main.h"

struct god_info {
	const char* id;
	const char*	name;
} god_data[] = {
	{"Bane", "Бейн"},
	{"Mystra", "Мистра"},
	{"Tor", "Тор"},
	{"Tempus", "Темпус"},
};
BSENUM(god, Tempus);