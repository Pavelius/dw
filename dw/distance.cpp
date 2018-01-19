#include "main.h"

struct distance_i {
	const char*			id;
	const char*			name;
} distance_data[] = {
	{"hand", "рука"},
	{"close", "близко"},
	{"reach", "рядом"},
	{"near", "недалеко"},
	{"far", "далеко"},
};
assert_enum(distance, Far);
getstr_enum(distance);