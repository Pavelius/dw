#include "main.h"

static const char* getdescription(item_s type) {
	switch(type) {
	case Potion: return "%герой выпил%а зелье.";
	case Scroll: return "%герой достал%а свиток и зачитал%а его содержимое.";
	case Ring: return "%герой потер%ла кольцо на руке, а затем выставил%а руку перед собой.";
	case Wand: return "%герой взмахнул%а палочкой.";
	case Staff: return "%герой выставил%а посох перед собой.";
	case Rod: return "%герой махнул%а прутиком.";
	default: return "%герой использовал%а %1.";
	}
}

static void use_potion(bool interactive, character* player, item& e) {
	if(interactive) {
		if(player->isplayer())
			logs::add("Это было вкусно.");
	}
}

void character::use(bool interactive, item& e) {
	if(interactive)
		act(getdescription(e.type), getstr(e.type));
	switch(e.type) {
	case Potion: use_potion(interactive, this, e); break;
	default:
		if(interactive)
			logs::add("Ничего не произошло.");
		break;
	}
}