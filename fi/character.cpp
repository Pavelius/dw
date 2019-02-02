#include "main.h"

void character::clear() {
	memset(this, 0, sizeof(*this));
}

char character::getmaximum(ability_s v) const {
	auto r = 4;
	if(getkey(race) == v)
		r++;
	if(getkey(profession) == v)
		r++;
	return r;
}

char character::getminimum(ability_s v) const {
	return 2;
}

void character::apply_talents() {
	for(auto i = FirstTalent; i <= LastTalent; i = (talent_s)(i + 1)) {
		if(getkey(i) == variant(race))
			talents[i] = 1;
	}
}