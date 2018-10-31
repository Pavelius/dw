#include "main.h"

adat<effect, 32>	effect_data;
unsigned			current_round;

static effect* find_effect(const spell_s type, const creature* target) {
	for(auto& e : effect_data) {
		if(e.target == target && e.type == type)
			return &e;
	}
	return 0;
}

static effect* add_effect() {
	for(auto& e : effect_data) {
		if(!e)
			return &e;
	}
	return effect_data.add();
}

void creature::set(spell_s id, unsigned duration) {
	auto p = find_effect(id, this);
	if(!p) {
		p = add_effect();
		p->type = id;
		p->target = this;
	}
	auto n = current_round + duration;
	if(n > p->duration)
		p->duration = n;
}

bool creature::isactive(spell_s id) const {
	for(auto& e : effect_data) {
		if(e.target == this && e.type == id && e.duration >= current_round)
			return true;
	}
	return false;
}