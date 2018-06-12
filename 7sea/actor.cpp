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

char* actor::sayroll(char* temp, const char* result_maximum, trait_s trait, knack_s knack, int target_number) const {
	temp[0] = 0;
	szprints(temp, result_maximum, "%1 бросает", getname());
	if(knack == NoKnack)
		szprints(zend(temp), result_maximum, " [%1]", getstr(trait));
	else
		szprints(zend(temp), result_maximum, " [%1] + [%2]", getstr(trait), getstr(knack));
	if(target_number)
		szprints(zend(temp), result_maximum, " против [%1i]", target_number);
	zcat(temp, ". ");
	return temp;
}