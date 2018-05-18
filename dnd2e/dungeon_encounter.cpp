#include "main.h"

const dungeon_encounter* dungeon_encounter::roll() const {
	auto result = 1 + (rand() % 100);
	for(auto p = this; p->chance <= 100; p++) {
		if(p->chance >= result)
			return p;
	}
	return this;
}