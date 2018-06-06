#include "main.h"

game_info game;

void game_info::upkeep() {
	day++;
}

void game_info::addterror() {
	terror++;
	// Remove one ally from ally deck
	deck::getdeck(Ally).draw();
}