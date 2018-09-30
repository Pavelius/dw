#include "main.h"

int dice::roll(int reroll) const {
	if(c == 0)
		return d;
	auto r = 0;
	for(unsigned char i = 0; i < c; i++) {
		r = 1 + (rand() % d);
		if(reroll && r <= reroll)
			r = 1 + (rand() % d);
	}
	return r + b;
}