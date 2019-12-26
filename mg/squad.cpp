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
	return play(*p);
}

bool squadi::play(const twisti& e) {
	act(e.text);
	for(auto v : e.conditions) {
		if(!v)
			break;
		switch(v.type) {
		case Skill:
			if(!hero::passtest((skill_s)v.value, 3))
				return false;
			break;
		case Animal:
			hero::fight((animal_s)v.value);
			return true;
		}
	}
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
	sb.adds(bsmeta<weatheri>::elements[getweather()].now_text);
}

void squadi::play() {
	addweather();
	stage();
}

static weather_s random(weather_s previous, season_s season, bool exclude_non_season) {
	adat<weather_s, 32> source;
	for(auto& e : bsmeta<weatheri>()) {
		if(exclude_non_season && e.nonseason())
			continue;
		if(e.season != season)
			continue;
		auto i = e.getid();
		if(i == previous)
			continue;
		source.add(i);
	}
	if(source)
		return source.data[rand() % source.getcount()];
	return ClearAndWarm;
}

void squadi::setyearweather() {
	auto previous = SpringStorms;
	for(auto i = 0; i < sizeof(year_cicle) / sizeof(year_cicle[0]); i++) {
		auto nw = random(previous, year_cicle[i], false);
		if(bsmeta<weatheri>::elements[nw].nonseason())
			nw = random(previous, bsmeta<weatheri>::elements[nw].season_link, true);
		year_weather[i] = nw;
		previous = nw;
	}
}

bool squadi::match(wise_s v) const {
	auto& ei = bsmeta<wisei>::elements[v];
	if(ei.subject == location)
		return true;
	if(opposition) {
		auto animal = opposition->getanimal();
		if(animal != Mouse) {
			auto& ai = bsmeta<animali>::elements[animal];
			if(ai.wise == v)
				return true;
		}
	}
	return false;
}