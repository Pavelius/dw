#include "main.h"

adat<creature, 256> creature_data;
static char proficiency_bonus[] = {1,
2, 2, 2, 2, 3, 3, 3, 3, 4, 4,
4, 4, 5, 5, 5, 5, 6, 6, 6, 6};

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

creature::creature(race_s race, gender_s gender, class_s type, background_s background, char* ability, bool interactive) {
	char temp_ability[6];
	clear();
	this->race = race;
	this->gender = gender;
	this->background = background;
	if(!ability) {
		char random[6]; ability = temp_ability;
		choose_ability(random, false);
		for(auto i = 0; i < 6; i++)
			random[class_data[type].abilities[i]] = random[i];
	}
	memcpy(this->ability, ability, sizeof(this->ability));
	apply(race, interactive);
	apply(background, interactive);
	apply(type, interactive);
	hp = gethpmax();
}

void creature::clear() {
	hp_rolled = 0;
	skills = languages = 0;
	memset(ability, 0, sizeof(ability));
	memset(feats, 0, sizeof(feats));
	memset(spells, 0, sizeof(spells));
	memset(slots, 0, sizeof(slots));
	memset(classes, 0, sizeof(classes));
	memset(wears, 0, sizeof(wears));
}

static int compare_char(const void* v1, const void* v2) {
	return *((char*)v2) - *((char*)v1);
}

static char roll_4d6() {
	char result[4];
	result[0] = 1 + (rand() % 6);
	result[1] = 1 + (rand() % 6);
	result[2] = 1 + (rand() % 6);
	result[3] = 1 + (rand() % 6);
	qsort(result, sizeof(result), sizeof(result[0]), compare_char);
	return result[0] + result[1] + result[2];
}

void creature::random_ability(char* result) {
	for(auto i = 0; i < 6; i++)
		result[i] = roll_4d6();
	qsort(result, 6, 1, compare_char);
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

int creature::getproficiency() const {
	auto r = getlevel();
	return maptbl(proficiency_bonus, r);
}

int creature::getac() const {
	auto r = wears[Armor].getac();
	auto d = wears[Armor].getdex();
	if(!r) {
		r = 10;
		d = 20;
	}
	r += wears[OffhandWeapon].getac();
	r += wears[Head].getac();
	r += wears[Gridle].getac();
	r += wears[Legs].getac();
	return r;
}

int	creature::getlevel() const {
	auto result = 0;
	for(auto e : classes)
		result += e;
	return result;
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