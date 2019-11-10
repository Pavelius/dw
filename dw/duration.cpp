#include "main.h"

const unsigned RMinute = 1;
const unsigned RHour = 60 * RMinute;
const unsigned RDay = 24 * RHour;
const unsigned RMonth = 30 * RDay;
const unsigned RYear = 12 * RMonth;

static unsigned current_minute;

struct duration_i {
	duration_s	id;
	unsigned	base;
} duration_data[] = {
	{Instantaneous},
	{Duration1Minute, RMinute},
	{Duration10Minute, 10 * RMinute},
	{Duration30Minute, 30 * RMinute},
	{Duration1Hour, RHour},
	{Duration8Hour, 8 * RHour},
	{Duration1Day, RDay},
	{Permanent, 500 * RYear},
};

unsigned game::get(duration_s id) {
	return duration_data[id].base;
}

void game::passtime(duration_s id) {
	current_minute += get(id);
}

unsigned game::getround() {
	return current_minute;
}