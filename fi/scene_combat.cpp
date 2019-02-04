#include "main.h"

void scene::initiative() {
	for(auto i = 0; i < character_max; i++)
		order[i] = i;
	zshuffle(order, character_max);
}

int scene::getfree(int index) const {
	for(auto i = 0; i < character_max; i++) {
		if(players[order[i]])
			continue;
		if(--index<0)
			return order[i];
	}
	return -1;
}

static int compare_int(const void* v1, const void* v2) {
	auto e1 = *((int*)v1);
	auto e2 = *((int*)v1);
	return e1 - e2;
}

void scene::add(character* p) {
	int positions[8];
	int count = 1 + p->get(LightingFast);
	if(count > sizeof(positions) / sizeof(positions[0]))
		count = sizeof(positions) / sizeof(positions[0]);
	for(auto i = 0; i < count; i++)
		positions[i] = getfree(i);
	qsort(positions, count, sizeof(positions[0]), compare_int);
	if(positions[0] == -1)
		return;
	players[positions[0]] = p;
}

bool scene::isenemy() const {
	for(auto p : players) {
		if(!p || !p->isready())
			continue;
		auto value = p->getreaction();
		switch(value) {
		case Hostile: return get(Friendly) != 0;
		case Friendly: return get(Hostile) != 0;
		}
	}
	return false;
}

character* scene::get(reaction_s value) const {
	for(auto p : players) {
		if(!p || !p->isready())
			continue;
		if(p->getreaction() == value)
			return const_cast<character*>(p);
	}
	return 0;
}

void scene::combat() {
	while(isenemy()) {
		logs::clear();
		for(auto p : players) {
			if(!p || !p->isready())
				continue;
			auto enemy = get(p->getopposed());
			if(!enemy)
				break;
			auto controlled = p->iscontrolled();
			logs::add(Stab, "Ударить мечом");
			auto id = (action_s)logs::input(true, false, "Что будете делать?");
			p->apply(id, enemy, true);
		}
	}
}