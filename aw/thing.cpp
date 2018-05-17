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