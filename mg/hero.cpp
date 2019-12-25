#include "main.h"

hero* players[4];
static adat<hero, 128> creatures;

void* hero::operator new(unsigned size) {
	for(auto& e : creatures) {
		if(!e)
			return &e;
	}
	return creatures.add();
}

void hero::clear() {
	memset(this, 0, sizeof(hero));
}

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

hero::hero(animal_s animal, gender_s gender, skill_s skill, location_s homeland) {
	clear();
	type = type;
	age = xrand(45, 75);
	gender = gender;
	specialization = skill;
	homeland = homeland;
	choosename(false);
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

const char* hero::getA() const {
	return (gender == Female) ? "а" : "";
}

const char* hero::getLA() const {
	return (gender == Female) ? "ла" : "";
}

bool hero::isplayer() const {
	for(auto p : players) {
		if(p == this)
			return true;
	}
	return false;
}

char* hero::getmembers(char* result, hero** helps) {
	result[0] = 0;
	for(auto pp = helps; *pp; pp++) {
		auto p = *pp;
		if(pp != helps) {
			if(pp[1])
				zcat(result, ", ");
			else
				zcat(result, " и ");
		}
		zcat(result, p->getname());
	}
	return result;
}

bool hero::ismatch(bool (hero::*proc)() const) {
	for(auto p : players) {
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
	for(auto e : gears) {
		if(!e)
			return true;
	}
	return false;
}

void hero::act(const char* format, ...) const {
	driver sc = sb;
	sc.name = getname();
	sc.gender = gender;
	sc.addv(format, xva_start(format));
	sb = sc;
}

void hero::buyeqipment() {
}