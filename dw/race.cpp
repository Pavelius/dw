#include "main.h"

struct race_info {
	const char* id;
	const char* name;
} race_data[] = {{"Human", "�������"},
{"Elf", "����"},
{"Dwarf", "�����"},
{"Halfling", "������"}
};
assert_enum(race, Halfling);
getstr_enum(race);