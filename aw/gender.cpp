#include "main.h"

genderi bsmeta<genderi>::elements[] = {
	{"transgender", "������������"},
	{"male", "�������"},
	{"female", "�������"},
};
assert_enum(gender, Female);

gender_s hero::choosegender(bool interactive) {
	an.add(Male, getstr(Male));
	an.add(Female, getstr(Female));
	return (gender_s)an.choose(interactive, true, "��� ��?");
}