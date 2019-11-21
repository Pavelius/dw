#include "main.h"

genderi bsmeta<genderi>::elements[] = {
	{"transgender", "транссексуал"},
	{"male", "мужчина"},
	{"female", "женщина"},
};
assert_enum(gender, Female);

gender_s hero::choosegender(bool interactive) {
	an.add(Male, getstr(Male));
	an.add(Female, getstr(Female));
	return (gender_s)an.choose(interactive, true, "Кто вы?");
}