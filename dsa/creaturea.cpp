#include "main.h"

bool creaturea::is(creature::procis proc) const {
	for(auto id : *this) {
		auto& e = get(id);
		if(proc(e))
			return true;
	}
	return false;
}

void creaturea::remove(state_s r) {
	auto pb = data;
	for(auto id : *this) {
		auto& e = get(id);
		if(e.is(r))
			continue;
		*pb++ = id;
	}
	count = pb - data;
}

void creaturea::match(state_s r) {
	auto pb = data;
	for(auto id : *this) {
		auto& e = get(id);
		if(!e.is(r))
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

void creaturea::choose(int minimum, int maximum, const char* format, ...) {
	if(maximum == -1)
		maximum = getcount();
	if(minimum > maximum)
		minimum = maximum;
	if(minimum > getcount())
		return;
	creaturea result;
	while(result.getcount() < maximum) {
		for(auto id : *this) {
			if(result.indexof(id) != -1)
				continue;
			auto& e = get(id);
			an.add(id, e.getname());
		}
		if(result.getcount() >= minimum)
			an.add(Blocked, "Этого достаточно. Продолжить.");
		char temp[1024]; stringbuilder sb(temp);
		if(result) {
			sb.add("Вы выбрали:");
			auto pb = sb.get();
			for(auto id : result) {
				auto& e = get(id);
				if(pb != sb.get())
					sb.add(", ");
				sb.add(e.getname());
			}
			sb.add(".");
			sb.addsep('\n');
		}
		sb.addv(format, xva_start(format));
		auto id = an.choosev(true, false, false, sb);
		if(id == Blocked)
			break;
		result.add(id);
	}
	*this = result;
}