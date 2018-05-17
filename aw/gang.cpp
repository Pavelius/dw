#include "main.h"

gang::gang(const char* name, short unsigned count, char harm, char armor) : actor(name, Male, harm, armor),
count(count), dead(0), wounded(0) {
}

char gang::getsize() const {
	auto count = getcount();
	if(count > 50)
		return 3;
	else if(count > 30)
		return 2;
	else if(count > 15)
		return 1;
	return 0;
}

void gang::sufferharm(int harm) {
	count -= getarmor();
	if(count <= 0) {
		return;
	} else
		act("%герой получил%а %1i урона", count);
	health -= count;
	switch(health) {
	case 5: case 4: break;
	case 3: if(d100() < 25) health = 0; break;
	case 2: if(d100() < 50) health = 0; break;
	case 1: if(d100() < 75) health = 0; break;
	default: health = 5; break;
	}
	if(!isalive())
		act(" и похоже %ей гайки.");
	else if(iswounded())
		act(" и заорал%а от боли.");
	else
		logs::add(".");
}