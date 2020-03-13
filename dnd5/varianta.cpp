#include "main.h"

void varianta::select(const varianta& source, creature& player, target_s id) {
	if(id == You) {
		data[0] = player.getid();
		count = 1;
	} else {
		auto pb = data;
		creature* pc;
		for(auto v : source) {
			switch(v.type) {
			case Creature:
				pc = v.getcreature();
				switch(id) {
				case HostileCreature:
					if(!player.isenemy(pc))
						continue;
					break;
				case FriendlyCreature:
					if(player.isenemy(pc))
						continue;
					break;
				case Posable:
					if(&player == pc)
						continue;
					break;
				default:
					continue;
				}
				break;
			}
			*pb++ = v;
		}
		count = pb - data;
	}
}

void varianta::match(creature& player, action_s id, bool remove) {
	auto pb = data;
	for(auto v : *this) {
		switch(v.type) {
		case Creature:
			if(player.use(id, *v.getcreature(), false) == remove)
				continue;
			break;
		}
		*pb++ = v;
	}
	count = pb - data;
}

void varianta::match(reaction_s v, bool remove) {
	auto pb = data;
	for(auto v : *this) {
		switch(v.type) {
		case Creature:
			if(v.getcreature()->is(v) == remove)
				continue;
			break;
		}
		*pb++ = v;
	}
	count = pb - data;
}

variant varianta::choose(bool interactive, indext start, const char* format, ...) const {
	if(!getcount())
		return variant();
	else if(getcount() >= 2) {
		char temp[260]; stringbuilder sc(temp);
		for(auto v : *this) {
			auto r = 0;
			if(start != -1) {
				if(v.type == Creature)
					r = iabs(start - v.getcreature()->getposition());
			}
			if(r == 0)
				an.add(v, getstr(v));
			else {
				char temx[260];
				an.add(v, "%1 (%2)", getstr(v), posable::getdistance(temx, r));
			}
		}
		an.sort();
		sc.addv(format, xva_start(format));
		return variant((short unsigned)an.choosev(interactive, false, true, temp));
	} else
		return data[0];
}