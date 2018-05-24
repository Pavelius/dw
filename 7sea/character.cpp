#include "main.h"

void character::act(const char* format, ...) const {
	logs::driver driver;
	driver.gender = getgender();
	driver.name = getname();
	driver.printv(logs::getptr(), logs::getptrend(), format, xva_start(format));
}

void character::actvs(const character* opponent, const char* format, ...) const {
	logs::driver driver;
	driver.gender = getgender();
	driver.name = getname();
	driver.opponent_gender = opponent->getgender();
	driver.opponent_name = opponent->getname();
	driver.printv(logs::getptr(), logs::getptrend(), format, xva_start(format));
}