#include "main.h"

static struct gender {
	const char*		id;
	const char*		name;
} gender_data[] = {
	{"No Gender", "��� ����"},
	{"Male", "�������"},
	{"Female", "�������"},
};
assert_enum(gender, Female);
getstr_enum(gender);