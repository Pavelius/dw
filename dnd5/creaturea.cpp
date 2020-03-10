#include "main.h"

void creaturea::match(reaction_s v) {
	auto pb = data;
	for(auto p : *this) {
		if(!p->is(v))
			continue;
		*pb++ = p;
	}
	count = pb - data;
}

bool creaturea::isreach(const creature& player, int v) const {
	auto index = player.getposition();
	for(auto p : *this) {
		if(p == &player)
			continue;
		if(iabs(p->getposition() - index) <= v)
			return true;
	}
	return false;
}