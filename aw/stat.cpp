#include "main.h"

static struct stat_i {
	const char* id;
	const char*	name;
} stat_data[] = {
	{"cool", "круто"},
	{"hard", "жестко"},
	{"hot", "пылко"},
	{"sharp", "умно"},
	{"weird", "странно"}
};
assert_enum(stat, Weird);
getstr_enum(stat);