#include "main.h"

void thing::act(const char* format, ...) const {
	logs::driver driver;
	driver.name = getname();
	driver.gender = getgender();
	driver.opponent_name = 0;
	driver.opponent_gender = Male;
	logs::addv(driver, format, xva_start(format));
}

void thing::act(thing& enemy, const char* format, ...) const {
	logs::driver driver;
	driver.name = getname();
	driver.gender = getgender();
	driver.opponent_name = enemy.getname();
	driver.opponent_gender = enemy.getgender();
	logs::addv(driver, format, xva_start(format));
}

result_s thing::roll(int bonus, int* result, bool interactive) {
	auto d = (rand() % 6) + (rand() % 6) + 2;
	auto r = d + bonus;
	if(r <= 6) {
		if(interactive)
			logs::add("[-{%1i%+2i=%3i}]", d, bonus, r);
		return Fail;
	} else if(r <= 9) {
		if(interactive)
			logs::add("{%1i%+2i=%3i}", d, bonus, r);
		return PartialSuccess;
	} else {
		if(interactive)
			logs::add("[+{%1i%+2i=%3i}]", d, bonus, r);
		return Success;
	}
}