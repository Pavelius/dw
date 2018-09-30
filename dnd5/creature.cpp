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
			ability[class_data[type].abilities[i]] = random[i];
	}
	memcpy(this->ability, ability, sizeof(this->ability));
	apply(race, interactive);
	apply(background, interactive);
	apply(type, interactive);
	choose_skills(type, interactive);
	choose_languages(type, interactive);
	hp = gethpmax();
}

void creature::clear() {
	domain = NoDomain;
	background = NoBackground;
	monster = NoMonster;
	hp_rolled = hp = 0;
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
	auto r = 10;
	auto m = wears[Armor].getdex();
	if(!wears[Armor])
		m = 20;
	r += imin(m, get(Dexterity));
	r += wears[Armor].getac();
	r += wears[MeleeWeapon].getac();
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

void creature::roll(roll_info& result, bool interactive) const {
	result.rolled = roll(result.get());
	result.result = result.rolled + result.bonus;
	if(interactive)
		logs::add("{%1i} ", result.rolled);
}

void creature::get(attack_info& result, wear_s slot) const {
	memset(&result, 0, sizeof(result));
	auto& weapon = wears[slot];
	if(weapon) {
		static_cast<dice&>(result) = weapon.getattack();
		if(weapon.isranged())
			result.bonus = get(Dexterity);
		else
			result.bonus = get(Strenght);
		if(isproficient(weapon))
			result.bonus += getproficiency();
	} else {
		result.type = Bludgeon;
		result.c = 0;
		result.d = imax(1, 1 + get(Strenght));
	}
	if(is(ImprovedCritical))
		result.critical++;
	if(is(SuperiorCritical))
		result.critical++;
}

void creature::get(attack_info& result, wear_s slot, const creature& enemy) const {
	get(result, slot);
	result.dc = enemy.getac();
}

void creature::attack(wear_s slot, creature& enemy) const {
	attack_info ai;
	get(ai, slot, enemy);
	roll(ai, false);
	if(!ai) {
		act("%герой промазал%а.");
		return;
	}
	act("%герой попал%а.");
}

bool creature::add(const item it) {
	for(auto i = Head; i <= Ammunition; i = (wear_s)(i + 1)) {
		if(wears[i])
			continue;
		if(it.is(i)) {
			wears[i] = it;
			return true;
		}
	}
	for(auto i = FirstInvertory; i < Head; i = (wear_s)(i + 1)) {
		if(wears[i])
			continue;
		wears[i] = it;
		return true;
	}
	return false;
}

const char* creature::getname(char* result, const char* result_maximum) const {
	zcpy(result, "Павел");
	return result;
}

void creature::act(const char* format, ...) const {
	char temp[260];
	logs::driver e;
	e.name = getname(temp, zendof(temp));
	e.gender = gender;
	logs::addv(e, format, xva_start(format));
}