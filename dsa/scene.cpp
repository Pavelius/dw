#include "main.h"

static int creature_index_compare(const void* p1, const void* p2) {
	auto& e1 = bsmeta<creature>::elements[*((short unsigned*)p1)];
	auto& e2 = bsmeta<creature>::elements[*((short unsigned*)p2)];
	return e1.get(Courage) - e2.get(Courage);
}

void scene::add(creature& e) {
	auto index = &e - bsmeta<creature>::elements;
	if(creatures.indexof(index) != -1)
		return;
	creatures.add(index);
}

void scene::makeorder() {
	qsort(creatures.data, creatures.count, sizeof(creatures.data[0]), creature_index_compare);
}

void scene::fight() {
	makeorder();
	while(ishostile()) {
		for(auto i : creatures) {
			auto& e = bsmeta<creature>::elements[i];
			if(!e.isready())
				continue;
			if(e.isplayer()) {

			} else {

			}
		}
		an.add(1, "Завершить раунд боя");
		an.choose();
	}
}

creature* scene::get(reaction_s r) const {
	for(auto i : creatures) {
		auto& e = bsmeta<creature>::elements[i];
		if(!e.isready())
			continue;
		if(e.getreaction() == r)
			return &e;
	}
	return 0;
}

bool scene::ishostile() const {
	return get(Hostile) != 0;
}