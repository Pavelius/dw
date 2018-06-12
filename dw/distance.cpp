#include "main.h"

struct distance_info {
	const char*	id;
	const char*	name;
} distance_data[] = {
	{"Hand", "рука"},
	{"Close", "близко"},
	{"Reach", "рядом"},
	{"Near", "недалеко"},
	{"Far", "далеко"},
};
assert_enum(distance, Far);
getstr_enum(distance);