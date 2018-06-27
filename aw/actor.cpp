#include "main.h"

void actor::sufferharm(int count) {
	count -= getarmor();
	if(count <= 0) {
		//act("%герой перенес%ла удар без поледствий.");
		return;
	} else
		act("%герой получил%а [%1i] урона", count);
	health -= count;
	switch(health) {
	case 3: if(d100() < 25) health = 0; break;
	case 2: if(d100() < 50) health = 0; break;
	case 1: if(d100() < 75) health = 0; break;
	}
	if(health < 0)
		health = 0;
	if(!isalive())
		act(" и похоже %ей гайки.");
	else if(iswounded())
		act(" и заорал%а от боли.");
	else
		logs::add(".");
}

bool actor::ishero() const {
	return this >= players && this <= (players + max_players);
}

int	actor::addbonus(state_s id) {
	if(is(id)) {
		remove(id);
		return 1;
	}
	return 0;
}