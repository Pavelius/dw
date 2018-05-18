#include "main.h"

static struct group_info {
	const char*		id;
	const char*		name;
	int				HD;
} group_data[] = {
	{"General", "�����"},
	{"Warriors", "�������", 10},
	{"Priests", "�����", 8},
	{"Rogues", "�����", 6},
	{"Wizards", "����������", 4},
};
assert_enum(group, Wizards);
getstr_enum(group);
metadc_enum(group);

int	character::getHD(group_s value) {
	return group_data[value].HD;
}