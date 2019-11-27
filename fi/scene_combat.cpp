#include "main.h"

static int compare_int(const void* v1, const void* v2) {
	auto e1 = *((int*)v1);
	auto e2 = *((int*)v1);
	return e1 - e2;
}

void scene::add(character* p) {
	adat<int, character_max> order;
	for(auto i = 0; i < character_max; i++) {
		if(!players[i])
			order.add(i);
	}
	if(!order.count)
		return;
	zshuffle(order.data, order.count);
	unsigned count = 1 + p->get(LightingFast);
	if(count > order.count)
		count = order.count;
	if(count > 0) {
		if(count>1)
			qsort(order.data, count, sizeof(order.data[0]), compare_int);
		players[order[0]] = p;
	}
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

void scene::remove(const character* p) {
	for(unsigned i = 0; i < sizeof(players) / sizeof(players[0]); i++) {
		if(players[i] == p)
			players[i] = 0;
	}
}

void scene::combat() {
	look(sb);
	for(auto p : players) {
		if(!p)
			continue;
		p->set(ActionSingleUse, 1);
	}
	while(isenemy()) {
		an.clear();
		for(auto p : players) {
			if(!p)
				continue;
			p->set(ActionFast, 1);
			p->set(ActionSlow, 1);
		}
		for(auto p : players) {
			if(!p || !p->isready())
				continue;
			auto enemy = get(p->getopposed());
			if(!enemy)
				break;
			auto controlled = p->iscontrolled();
			for(auto i = Slash; i <= Taunt; i = (action_s)(i + 1)) {
				if(p->activity(i, enemy, this, false))
					an.add(i, getstr(i));
			}
			auto id = (action_s)an.choose(true, false, "Что будет делать %1?", p->getname());
			p->activity(id, enemy, this, true);
		}
	}
}