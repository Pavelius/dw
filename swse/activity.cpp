#include "main.h"

static bool character_sheet(activityi& a, creature* player, location& area, bool run, bool interactive) {
	if(!player->isplayer())
		return false;
	if(run) {
		player->act("##%герой - %уровни\n");
		logs::next();
	}
	return true;
}

action_s activityi::getaction(const creature* player) const {
	for(auto v : conditions) {
		if(v.type == Action)
			return (action_s)v.subtype;
	}
	return NoAction;
}

wear_s activityi::getwear() const {
	for(auto v : conditions) {
		if(v.type == Wear)
			return (wear_s)v.subtype;
	}
	return FirstGear;
}