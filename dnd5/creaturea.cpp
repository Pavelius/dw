#include "main.h"

void creaturea::match(action_s v, bool remove) {
	auto pb = data;
	for(auto p : *this) {
		if(p->is(v) == remove)
			continue;
		*pb++ = p;
	}
	count = pb - data;
}

void creaturea::match(reaction_s v, bool remove) {
	auto pb = data;
	for(auto p : *this) {
		if(p->is(v) == remove)
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

creature* creaturea::choose(bool interactive, const char* format, ...) const {
	if(!getcount())
		return 0;
	else if(getcount() >= 2) {
		char temp[260]; stringbuilder sc(temp);
		for(auto pc : *this)
			an.add((int)pc, pc->getname());
		an.sort();
		sc.addv(format, xva_start(format));
		return (creature*)an.choosev(interactive, false, true, temp);
	} else
		return data[0];
}