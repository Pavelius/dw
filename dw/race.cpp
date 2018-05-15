#include "main.h"

struct race_info {
	const char* id;
	const char* name;
} race_data[] = {{"Human", "׳וכמגוך"},
{"Elf", "Ýכüפ"},
{"Dwarf", "ִגאנפ"},
{"Halfling", "ױמבבטע"}
};
BSENUM(race, Halfling);