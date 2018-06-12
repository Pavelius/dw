#include "main.h"

void actor::act(const char* format, ...) const {
	logs::driver driver;
	driver.gender = getgender();
	driver.name = getname();
	driver.printv(logs::getptr(), logs::getptrend(), format, xva_start(format));
}

void actor::actvs(const actor* opponent, const char* format, ...) const {
	logs::driver driver;
	driver.gender = getgender();
	driver.name = getname();
	driver.opponent_gender = opponent->getgender();
	driver.opponent_name = opponent->getname();
	driver.printv(logs::getptr(), logs::getptrend(), format, xva_start(format));
}