#include "main.h"

static struct damage {
	const char*		id;
	const char*		name;
} damage_data[] = {
	{"Bludgeon", "�������"},
	{"Piercing", "�������"},
	{"Slashing", "�������"},
	{"Fire", "��������"},
	{"Cold", "���������"},
	{"Electricity", "�������������"},
};
assert_enum(damage, Electricity);
getstr_enum(damage);