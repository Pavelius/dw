#include "main.h"

static struct gender_i {
	const char* id;
	const char*	name;
} gender_data[] = {
	{"transgender", "транссексуал"},
	{"male", "мужчина"},
	{"female", "женщина"},
};
assert_enum(gender, Female);
getstr_enum(gender);

void hero::choosegender(bool interactive) {
	logs::add(Male, getstr(Male));
	logs::add(Female, getstr(Female));
	setgender((gender_s)logs::input(interactive, true, "Кто вы?"));
}