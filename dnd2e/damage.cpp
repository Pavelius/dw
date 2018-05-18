#include "main.h"

static struct damage {
	const char*		id;
	const char*		name;
} damage_data[] = {
	{"Bludgeon", "Ударное"},
	{"Piercing", "Колющее"},
	{"Slashing", "Режущее"},
	{"Fire", "Огненное"},
	{"Cold", "Морозящее"},
	{"Electricity", "Электрическое"},
};
assert_enum(damage, Electricity);
getstr_enum(damage);