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
bsreq race_type[] = {
	BSREQ(race_info, id, text_type),
	BSREQ(race_info, name, text_type),
{}
};
BSMETA(race);