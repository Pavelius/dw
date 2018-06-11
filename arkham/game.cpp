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

void game_info::awakening() {
	if(doom < doom_maximum)
		doom++;
}

void game_info::opengate(location_s position) {
	auto value = Abyss;
	if(location_data[position].sealed)
		return;
	if(!location_data[position].gate) {
		awakening();
		location_data[position].clue = 0;
		location_data[position].gate = value;
		monsterappear(position);
	} else {
		for(auto& e : location_data) {
			if(e.gate)
				monsterappear(e.getid());
		}
	}
}

void game_info::monsterappear(location_s position) {
	auto p = monster::getfromcup();
	if(!p)
		return;
	p->set(position);
}