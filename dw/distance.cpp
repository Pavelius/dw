#include "main.h"

struct distance_info {
	const char*	id;
	const char*	name;
} distance_data[] = {
	{"hand", "����"},
	{"close", "������"},
	{"reach", "�����"},
	{"near", "��������"},
	{"far", "������"},
};
BSENUM(distance, Far);