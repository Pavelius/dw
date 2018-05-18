#include "main.h"

using namespace game;

struct state_i {
	character*		player;
	magic_power_s	state;
	unsigned		expired;
	operator bool() const {
		return player != 0;
	}
};
static adat<state_i, 1024> state_data;

bool character::is(magic_power_s id) const {
	for(auto& e : state_data) {
		if(e.player==this && e.state==id)
			return e.expired > getround();
	}
	return false;
}

void character::add(magic_power_s id, unsigned count_rounds) {
	for(auto& e : state_data) {
		if(e.player == this && e.state == id) {
			if(e.expired < getround())
				e.expired = getround();
			else
				e.expired += count_rounds;
			return;
		}
	}
	auto p = state_data.add();
	p->player = this;
	p->state = id;
	p->expired = getround() + count_rounds;
}

void character::removepowers() const {
	for(auto& e : state_data) {
		if(e.player == this)
			e.player = 0;
	}
}

void character::checkstates() {
	// Check trail states for best perfomances
	while(state_data.count>0) {
		if(state_data.data[state_data.count-1])
			break;
		state_data.count--;
	}
	// See if any state if expired and do some actions
	for(auto& e : state_data) {
	}
}