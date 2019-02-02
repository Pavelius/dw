#include "main.h"

void diceroll::clear() {
	memset(this, 0, sizeof(*this));
}

void diceroll::roll(variant_s type, int c, int d) {
	auto multiplier = 1;
	if(c < 0) {
		multiplier = -1;
		c = -c;
	}
	for(int i = 0; i < c; i++) {
		auto p = add();
		p->type = type;
		p->border = d;
		p->result = xrand(1, d);
		p->multiplier = multiplier;
	}
}

int	diceroll::getreroll() const {
	int result = 0;
	for(unsigned i = 0; i < count; i++) {
		if(data[i].result >= 2 && data[i].result <= 5)
			result += 1;
	}
	return result;
}

int	diceroll::getone(variant_s id) const {
	int result = 0;
	for(unsigned i = 0; i < count; i++) {
		if(data[i].type != id)
			continue;
		if(data[i].result == 1)
			result += 1;
	}
	return result;
}

int	diceroll::getsix() const {
	int result = 0;
	for(unsigned i = 0; i < count; i++) {
		if(data[i].result >= 12)
			result += 4 * data[i].multiplier;
		else if(data[i].result >= 10)
			result += 3 * data[i].multiplier;
		else if(data[i].result >= 8)
			result += 2 * data[i].multiplier;
		else if(data[i].result >= 6)
			result += 1 * data[i].multiplier;
	}
	return result;
}

void diceroll::pushroll() {
	for(unsigned i = 0; i < count; i++) {
		switch(data[i].type) {
		case Skills:
			if(data[i].result >= 6)
				continue;
			data[i].result = xrand(1, data[i].border);
			break;
		default:
			if(data[i].result == 1 || data[i].result >= 6)
				continue;
			data[i].result = xrand(1, data[i].border);
			break;
		}
	}
}