#include "main.h"

struct distance_info {
	const char*	id;
	const char*	name;
} distance_data[] = {
	{"Hand", "����"},
	{"Close", "������"},
	{"Reach", "�����"},
	{"Near", "��������"},
	{"Far", "������"},
};
assert_enum(distance, Far);
getstr_enum(distance);