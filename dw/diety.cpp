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

//bsreq god_type[] = {
//	BSREQ(god_info, id, text_type),
//	BSREQ(god_info, name, text_type),
//{}};