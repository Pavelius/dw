#include "main.h"

struct god_info {
	const char* id;
	const char*	name;
} god_data[] = {
	{"Bane", "����"},
	{"Mystra", "������"},
	{"Tor", "���"},
	{"Tempus", "������"},
};
assert_enum(god, Tempus);
getstr_enum(god);