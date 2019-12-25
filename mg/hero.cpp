#include "main.h"

DECLDATA(hero, 128);
squad		party;

int hero::get(skill_s value) const {
	int result = skills[value];
	if(value == Resources || value == Circles) {
		// RULES: Ресурсы и Связи дома дают +1 кубик
		//if(homeland == logc.location)
		//	result++;
	} else {
		// RULES: Состояние Болен и Ранен влияют на броски
		if(is(Sick))
			result--;
		if(is(Injured))
			result--;
	}
	return imax(result, 0);
}

void hero::set(skill_s value, int number) {
	skills[value] = number;
}

void hero::set(wise_s value, int number) {
	if(number > 3)
		number = 3;
	wises[value] = number;
}

void hero::tallyskills() {
	for(auto& e : skills) {
		if(e)
			e++;
	}
}

void hero::tallywises() {
	for(auto& e : wises) {
		if(e)
			e++;
	}
}

void hero::create(animal_s kind, gender_s gender, skill_s specialization, location_s homeland) {
	setkind(kind);
	setname(gender);
	this->age = xrand(45, 75);
	this->specialization = specialization;
	this->homeland = homeland;
}

void hero::use(trait_s value) {
	if(get(value) == 1)
		traits_used[value]++;
}

bool hero::canhelp(skill_s value, skill_s* result) const {
	if(get(value) > 0) {
		if(result)
			*result = value;
		return true;
	}
	auto& help = bsmeta<skilli>::elements[value].help;
	for(auto e : help) {
		if(get(e) > 0) {
			if(result)
				*result = e;
			return true;
		}
	}
	return false;
}

bool hero::is(condition_s value) const {
	switch(value) {
	case Healthy:
		return conditions == 0;
	default:
		return (conditions & (1 << value)) != 0;
	}
}

void hero::set(condition_s value) {
	switch(value) {
	case Healthy:
		conditions = 0;
		break;
	default:
		conditions |= 1 << value;
		break;
	}
}

void hero::remove(condition_s value) {
	conditions &= ~(1 << value);
}

bool hero::isplayer() const {
	return party.indexof((hero*)this) != 0;
}

bool hero::ismatch(bool (hero::*proc)() const) {
	for(auto p : party) {
		if(!p)
			continue;
		if((p->*proc)())
			return true;
	}
	return false;
}

bool hero::isconditions() const {
	return !is(Healthy);
}

bool hero::isfreegear() const {
	for(auto e : wears) {
		if(!e)
			return true;
	}
	return false;
}

void hero::buyeqipment() {
}

void hero::getinfo(stringbuilder& sb) const {
	sb.addn("%1 %2i, Воля %3i, Здоровье %4i", getstr(getanimal()), get(Nature), get(Will), get(Health));
	sb.addn("Связи %1i, Ресурсы %2i", get(Circles), get(Resources));
}

void hero::addplayer() {
	if(party.indexof(this)==-1)
		party.add(this);
}

void hero::setfamily(const hero* v) {
	if(v)
		family_id = v - bsmeta<hero>::elements;
	else
		family_id = Blocked;
}