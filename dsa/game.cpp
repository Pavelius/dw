#include "main.h"

gamei game;

void gamei::pass(unsigned v) {
	time += v;
	update();
}

void gamei::update() {
	auto pb = bsmeta<boosti>::elements;
	for(auto& e : bsmeta<boosti>()) {
		if(e.time < time) {
			auto& player = bsmeta<creature>::elements[e.owner];
			player.add(e.id, e.modifier);
		} else {
			*pb++ = e;
		}
	}
	bsmeta<boosti>::source.setcount(pb - bsmeta<boosti>::elements);
}