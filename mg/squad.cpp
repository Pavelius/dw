#include "main.h"

season_s squadi::year_cicle[] = {
	Spring, Spring, Spring,
	Summer, Summer, Summer, Summer,
	Autum, Autum,
	Winter, Winter, Winter, Winter, Winter
};

void squadi::clear() {
	memset(this, 0, sizeof(*this));
}

bool squadi::match(const twisti& e) const {
	for(auto v : e.conditions) {
		if(!v)
			break;
		switch(v.type) {
		case Location:
			if(v != location)
				return false;
			break;
		case Animal:
			if(opposition && opposition->getanimal() != v.value)
				return false;
			break;
		case Season:
			if(getseason() != v.value)
				return false;
			break;
		}
	}
	return true;
}

bool squadi::stage() {
	twista source;
	for(auto& e : bsmeta<twisti>()) {
		if(!match(e))
			continue;
		source.add(&e);
	}
	if(!source)
		return false;
	auto p = source.data[rand() % source.getcount()];
	act(p->text);
	an.next();
	return true;
}

void squadi::set(variant v) {
	switch(v.type) {
	case Location:
	case Landscape:
		location = v;
		break;
	}
}

void squadi::addweather() {
	sb.add("Вокруг");
	sb.adds(bsmeta<weatheri>::elements[getweather()].now_text);
	sb.add(".");
}

void squadi::play() {
	addweather();
	stage();
}