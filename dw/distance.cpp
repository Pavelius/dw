#include "main.h"

struct distance_i {
	const char*			id;
	const char*			name;
} distance_data[] = {
	{"hand", "����"},
	{"close", "������"},
	{"reach", "�����"},
	{"near", "��������"},
	{"far", "������"},
};
assert_enum(distance, Far);
getstr_enum(distance);