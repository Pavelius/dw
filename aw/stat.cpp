#include "main.h"

static struct stat_i {
	const char* id;
	const char*	name;
} stat_data[] = {
	{"cool", "�����"},
	{"hard", "������"},
	{"hot", "�����"},
	{"sharp", "����"},
	{"weird", "�������"}
};
assert_enum(stat, Weird);
getstr_enum(stat);