#include "adat.h"
#include "range.h"

#pragma once

enum param_types {
	ParameterStandart,
	ParameterWin, ParameterLoose, ParameterDeath,
	ParameterError,
};
enum limit_types {
	LimitStandart,
	LimitMinimum, LimitMaximum
};
struct parameter
{
	const char*		id;
	const char*		name;
	param_types		type;
	limit_types		limit_type;
	int				value, minimum, maximum;
	bool			zeroshow;
	range*			ranges;
	//
	void			add(int value) { set(get() + value); }
	param_types		check() const;
	int				get() const;
	char*			getname(char* temp, const char* result_maximum) const;
	void			set(int value);
};