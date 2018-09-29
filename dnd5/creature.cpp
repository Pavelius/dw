#include "main.h"

adat<creature, 256> creature_data;

void* creature::operator new(unsigned size) {
	for(auto& e : creature_data) {
		if(!e)
			return &e;
	}
	return creature_data.add();
}

void creature::operator delete (void* data) {
	((creature*)data)->ability[0] = 0;
}

creature::creature(race_s race, gender_s gender, class_s type, background_s background, bool interactive) {
	clear();
	this->race = race;
	this->gender = gender;
	this->background = background;
	apply(race, interactive);
	raise(type, interactive);
	hp = gethpmax();
}

void creature::clear() {
	hp_rolled = 0;
	memset(ability, 0, sizeof(ability));
	memset(feats, 0, sizeof(feats));
	memset(spells, 0, sizeof(spells));
	memset(slots, 0, sizeof(slots));
	memset(classes, 0, sizeof(classes));
	memset(wears, 0, sizeof(wears));
}

int	creature::gethpmax() const {
	auto result = hp_rolled;
	auto level = getlevel();
	result += get(Constitution)*level;
	if(is(DwarvenToughness))
		result += level;
	if(result < level)
		result = level;
	return result;
}

int	creature::getlevel() const {
	auto result = 0;
	for(auto e : classes)
		result += e;
	return result;
}

void creature::raise(class_s id, bool interactive) {
	auto level = classes[id]++;
	// Добавим нужное количество хитов
	if(level == 1 && getlevel() == 1)
		hp_rolled = class_data[id].hd;
	else
		hp_rolled += xrand(1, class_data[id].hd);
	// Применим способности класса
	for(auto e : class_data[id].traits)
		set(e);
	apply(id, level, interactive);
}

race_s creature::getrace() const {
	return race_data[race].basic ? race_data[race].basic : race;
}

bool creature::isallow(item it) const {
	if(item_data[it.type].proficiency[0] == NoFeat)
		return false;
	for(auto e : item_data[it.type].proficiency) {
		if(!e)
			break;
		if(is(e))
			return true;
	}
	return false;
}

int	creature::roll() const {
	auto r = 1 + (rand() % 20);
	if(r == 1 && is(Lucky))
		r = 1 + (rand() % 20);
	return r;
}

int	creature::roll(roll_s type) const {
	int r1, r2;
	switch(type) {
	case Advantage:
		r1 = roll();
		r2 = roll();
		return imax(r1, r2);
	case Disadvantage:
		r1 = roll();
		r2 = roll();
		return imin(r1, r2);
	default:
		return roll();
	}
}