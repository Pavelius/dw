#include "main.h"

int hero::gethpmax() const {
	auto result = 8 + 4 * level;
	if(is(Tought))
		result += 6;
	return result;
}