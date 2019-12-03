#include "main.h"

bool creaturea::is(creature::procis proc) const {
	for(auto id : *this) {
		auto& e = get(id);
		if(proc(e))
			return true;
	}
	return false;
}

void creaturea::match(reaction_s r) {
	auto pb = data;
	for(auto id : *this) {
		auto& e = get(id);
		if(e.getreaction() != r)
			continue;
		*pb++ = id;
	}
	count = pb - data;
}

void creaturea::match(creature::procis proc) {
	auto pb = data;
	for(auto id : *this) {
		auto& e = get(id);
		if(!proc(e))
			continue;
		*pb++ = id;
	}
	count = pb - data;
}

void creaturea::exclude(const creature* v) {
	auto pb = data;
	for(auto id : *this) {
		auto& e = get(id);
		if(&e == v)
			continue;
		*pb++ = id;
	}
	count = pb - data;
}

creature* creaturea::choose(const char* format, ...) const {
	for(auto id : *this) {
		auto& e = get(id);
		an.add((int)&e, e.getname());
	}
	char temp[256]; stringbuilder sb(temp);
	sb.addv(format, xva_start(format));
	return (creature*)an.choosev(true, false, false, sb);
}