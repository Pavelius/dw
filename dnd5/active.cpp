#include "main.h"

struct activei {
	spell_s						id;
	variant						object;
	unsigned					round;
};

DECLDATA(activei, 64);

void creature::add(spell_s id, unsigned rounds) {
	auto p = bsmeta<activei>::add();
	p->id = id;
	p->object = getid();
	p->round = game.getround() + rounds;
}

bool creature::isactive(variant id) const {
	auto v = getid();
	for(auto& e : bsmeta<activei>()) {
		if(e.object==v && e.id==id)
			return true;
	}
	return false;
}