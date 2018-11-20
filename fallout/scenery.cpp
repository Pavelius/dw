#include "main.h"

struct scenery_info {
	const char*		name;
	gender_s		gender;
	const char*		description;
} scenery_data[] = {{"пусто"},
{"ящик", Male, "несколько сложенных друг на друга ящиков"},
{"дверь", Female, "потертая деревянная дверь"},
{"проход", Male, "темный проход, ведущий в глубь"},
};
assert_enum(scenery, Passage);
getstr_enum(scenery)

const char* geti(char* result, const char* result_maximum, const char* format, scenery_s id) {
	char temp[260];
	return szprints(result, result_maximum, format, grammar::of(temp, zendof(temp), scenery_data[id].name));
}