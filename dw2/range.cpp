#include "main.h"

int range::roll() const {
	if(!dice)
		return 0;
	auto r = 1 + (rand() % dice) + bonus;
	if(r < 1)
		r = 1;
	return r;
}