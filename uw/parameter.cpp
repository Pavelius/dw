#include "crt.h"
#include "parameter.h"

int parameter::get() const {
	return value;
}

void parameter::set(int value) {
	if(value < minimum)
		value = minimum;
	else if(maximum && value > maximum)
		value = maximum;
	this->value = value;
}

param_types parameter::check() const {
	if(limit_type == LimitMinimum && value == minimum)
		return type;
	if(limit_type == LimitMaximum && value == maximum)
		return type;
	return ParameterStandart;
}

char* parameter::getname(char* result, const char* result_maximum) const {
	result[0] = 0;
	auto v = get();
	if(!v && !zeroshow)
		return result;
	auto p = ranges->find(v);
	szprints(result, result_maximum, p ? p->text : "%1: [%2i]", name, v);
	return result;
}

