#include "main.h"

char* roll_info::getname(char* result, const char* result_maximum) const {
	if(bonus > 0)
		return szprints(result, result_maximum, "%1+%2i", getstr(id), bonus);
	else if(bonus < 0)
		return szprints(result, result_maximum, "%1-%2i", getstr(id), -bonus);
	else
		return szprints(result, result_maximum, "%1", getstr(id));
}