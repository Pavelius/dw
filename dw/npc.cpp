#include "main.h"

void npc::create(class_s type) {
	this->type = type;
	this->race = Human;
	this->level = 1;
	setgender();
	setname(race, getgender());
}

void npc::setalignment() {
	alignment = (alignment_s)(xrand(Good, Evil));
}