#include "main.h"

struct distance_info {
	const char*	id;
	const char*	name;
} distance_data[] = {
	{"hand", "рука"},
	{"close", "близко"},
	{"reach", "рядом"},
	{"near", "недалеко"},
	{"far", "далеко"},
};
BSENUM(distance, Far);