#include "main.h"

static struct group_info {
	const char*		id;
	const char*		name;
	int				HD;
} group_data[] = {
	{"General", "Общая"},
	{"Warriors", "Воители", 10},
	{"Priests", "Жрецы", 8},
	{"Rogues", "Плуты", 6},
	{"Wizards", "Волшебники", 4},
};
assert_enum(group, Wizards);
getstr_enum(group);
metadc_enum(group);

int	character::getHD(group_s value) {
	return group_data[value].HD;
}