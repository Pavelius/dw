#include "main.h"

static struct timezone_i {
	const char*	id;
	const char*	name;
	const char*	become;
} timezone_data[] = {
	{"Morning", "Утро", "Наступило утро."},
	{"Noon", "Полдень", "Наступил полдень."},
	{"Afternoon", "После обеда", "Наступил день."},
	{"Evening", "Вечер", "Наступи вечер."},
	{"Midnight", "Полночь", "Настала полночь."},
	{"Night", "Глубокая ночь", "Пришла глубокая ночь."},
};

void scene::change(bool interactive, timezone_s& timezone) {
	auto tz = getzone();
	if(tz != timezone) {
		if(interactive)
			logs::add(timezone_data[tz].become);
		timezone = tz;
	}
}