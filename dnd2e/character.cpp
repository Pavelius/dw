#include "main.h"

using namespace game;

adat<character*, 8> party;

static char hit_probability[] = {
	-5, -5, -3, -3, -2, -2, -1, -1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3,
	3, 4, 4, 5, 6, 7
};
static char damage_adjustment[] = {
	-5, -5, -3, -3, -2, -2, -1, -1, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 7,
	8, 9, 10, 11, 12, 14
};
static int weight_allowance[] = {
	1, 1, 1, 5, 10, 10, 20, 20, 35, 35,
	40, 40, 45, 45, 55, 55, 70, 85, 110, 135, 160, 185, 235, 335, 485,
	535, 635, 785, 935, 1235, 1535,
};
static short unsigned max_press[] = {
	0
};
static char open_doors[] = {
	1, 1, 1, 2, 3, 3, 4, 4, 5, 5,
	6, 6, 7, 7, 8, 8, 9, 10, 11, 12, 13, 14, 15, 16, 16,
	17, 17, 18, 18, 19, 19
};
static char open_close_doors[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 8,
	10, 12, 14, 16, 17, 18
};
static char bend_bars[] = {
	-5, -5, -3, -3, -2, -2, -1, -1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 3,
};
char reaction_adjustment[26] = {
	-6, -6, -4, -3, -2, -1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 2, 2, 3, 3,
	4, 4, 4, 5, 5
};
static char defence_adjustment[] = {
	-6, -6, -4, -3, -2, -1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, -1, -2, -3, -4, -4, -4,
	-5, -5, -5, -6, -6
};
static char hit_points_adjustment[] = {
	-3, -2, -2, -1, -1, -1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 2
};
static char hit_points_adjustment_warriors[] = {
	-3, -2, -2, -1, -1, -1, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 2, 3, 4, 5,
	5, 6, 6, 6, 7, 7
};
static char number_languages[] = {
	0, 0, 1, 1, 1, 1, 1, 1, 1, 2,
	2, 2, 3, 3, 4, 4, 5, 6, 7, 8,
	9, 10, 11, 12, 15, 20
};
static char chance_learn_spells[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 35,
	40, 45, 50, 55, 60, 65, 70, 75, 85, 95,
	96, 97, 98, 99, 100
};
static char theive_skills_by_dex[ReadLanguages + 1][20] = {
	{-60, -55, -50, -45, -40, -35, -30, -25, -20, -15, -10, -5, 0, 0, 0, 0, 0, 5, 10, 15},
	{-10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -5, 0, 0, 0, 0, 0, 5, 10, 15, 20},
	{-10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -5, 0, 0, 0, 0, 0, 0, 5, 10},
	{-20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -15, -10, -5, 0, 0, 0, 0, 5, 10, 15},
	{-10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -5, 0, 0, 0, 0, 0, 0, 5, 10, 15},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
static char default_theive_skills[ReadLanguages + 1][18] = {
	{0, 30, 35, 40, 45, 50, 55, 60, 65, 70, 80, 90, 95, 99, 99, 99, 99, 99},
	{0, 25, 29, 33, 37, 42, 47, 52, 57, 62, 67, 72, 77, 82, 87, 92, 97, 99},
	{0, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 99},
	{0, 15, 21, 27, 33, 40, 47, 55, 62, 70, 78, 86, 94, 99, 99, 99, 99, 99},
	{0, 10, 15, 20, 25, 31, 37, 43, 49, 56, 63, 70, 77, 85, 93, 99, 99, 99},
	{10, 10, 10, 15, 15, 20, 20, 25, 25, 30, 30, 35, 35, 40, 40, 50, 50, 55},
	{40, 85, 86, 87, 88, 90, 92, 94, 96, 98, 99, 99, 99, 99, 99, 99, 99, 99},
	{0, 0, 0, 0, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 80},
};
static char wp_melee_attacks[] = {
	0, 0, 1, 1
};
static char wp_melee_thac0[] = {
	0, 0, 1, 3,
};
static char wp_melee_damage[] = {
	0, 0, 2, 3,
};

character::character() {
	clear();
}

character::~character() {
	removepowers();
}

character::character(race_s race, gender_s gender, class_s type, const char* abilities, bool party_member) {
	class_s classes[3] = {type};
	create(false, race, gender, classes, abilities, party_member);
}

character::character(race_s race, gender_s gender, const class_s* type, const char* abilities, bool party_member) {
	create(false, race, gender, type, abilities, party_member);
}

void character::create(bool interactive, race_s race, gender_s gender, const class_s* type, const char* abilities, bool party_member) {
	char temp[Charisma + 1];
	clear();
	if(!abilities) {
		chooseability(false, temp);
		abilities = temp;
	}
	this->race = race;
	this->gender = gender;
	this->monster = Character;
	this->classes[0] = type[0];
	this->classes[1] = type[1];
	this->classes[2] = type[2];
	memcpy(this->abilities, abilities, sizeof(this->abilities));
	if(getkit(classes[0]) == Fighter)
		strenght_percent = rand() % 100;
	// Correct ability
	auto pmn = getminimum(race);
	auto pmm = getmaximum(race);
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
		if(pmn[i] && this->abilities[i] < pmn[i])
			this->abilities[i] = pmn[i];
		if(pmm[i] && this->abilities[i] > pmm[i])
			this->abilities[i] = pmm[i];
	}
	// Adjust racial bonus
	auto pad = getadjustment(race);
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
		this->abilities[i] += pad[i];
	for(auto e : getfeats(race)) {
		if(!e)
			break;
		set(e);
	}
	// Correct for class minimal
	pmn = getminimum(type[0]);
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
		if(pmn[i] && this->abilities[i] < pmn[i])
			this->abilities[i] = pmn[i];
	}
	// Set possible classes
	for(auto e : classes)
		raiselevel(interactive, e);
	// Get random name
	this->name = getrandomname(race, gender, type[0]);
	// Finish generation
	finish(party_member);
	equip(type[0]);
}

bool character::add(item value) {
	if(!value)
		return false;
	for(auto i = FirstWear; i <= LastWear; i = (wear_s)(i + 1)) {
		if(!wears[i] && value.is(i)) {
			wears[i] = value;
			return true;
		}
	}
	return false;
}

int character::getstrenght() const {
	auto value = get(Strenght);
	if(value == 18) {
		if(strenght_percent == 0)
			value += 5;
		else if(strenght_percent <= 50)
			value++;
		else if(strenght_percent <= 75)
			value += 2;
		else if(strenght_percent <= 90)
			value += 3;
		else
			value += 4;
	} else if(value > 18)
		value += 6;
	return value;
}

void character::clear() {
	memset(this, 0, sizeof(*this));
}

const char* character::find(class_s value) const {
	unsigned i = 0;
	for(auto e : classes) {
		if(!e)
			break;
		if(e == value)
			return levels + i;
		i++;
	}
	return 0;
}

void character::finish(bool party_member) {
	hp = getmaxhp();
	if(party_member)
		party.add(this);
}

int	character::get(ability_s value) const {
	return abilities[value];
}

int character::get(class_s value) const {
	auto pc = find(value);
	if(pc)
		return *pc;
	return 0;
}

int character::getmaxclasses() const {
	return classes[0] ? 1 : (classes[1] ? 2 : 3);
}

int	character::getmaxhp() const {
	auto result = hp_maximum / getmaxclasses();
	auto n = imin(getHD(), 9);
	auto i = abilities[Constitution];
	if(getkit(classes[0]) == Fighter)
		result += maptbl(hit_points_adjustment_warriors, i) * n;
	else
		result += maptbl(hit_points_adjustment, i) * n;
	if(result < n)
		result = n;
	return result;
}

int	character::getbonus(int(item::*proc)() const) const {
	auto result = 0;
	for(auto& e : wears) {
		if(!e)
			continue;
		result += (e.*proc)();
	}
	return result;
}

int character::getAC(bool flatfooted) const {
	if(monster && !wears[Armor])
		return getAC(monster);
	auto result = 10;
	if(!flatfooted)
		result += maptbl(defence_adjustment, get(Dexterity));
	result -= getbonus(&item::getAC);
	return result;
}

bool character::get(attackinfo& result, wear_s weapon) const {
	result.damage = {1, 3};
	result.attacks_per_two_rounds = 2;
	result.critical = 20;
	result.multiplier = 2;
	result.thac0 = 20;
	if(wears[weapon]) {
		if(!wears[weapon].getattack(result))
			return false;
		result.weapon = const_cast<item*>(&wears[weapon]);
	}
	if(result.weapon) {
		auto type = result.weapon->type;
		if(is(ElfWeaponTraining)) {
			if(type == LongSword || type == LongBow)
				result.thac0--;
		}
	}
	if(weapon == MeleeWeapon) {
		auto i = getstrenght();
		result.damage.b += maptbl(damage_adjustment, i);
		result.thac0 -= maptbl(hit_probability, i);
	} else if(weapon == RangedWeapon) {
		auto i = get(Dexterity);
		result.thac0 -= maptbl(reaction_adjustment, i);
	}
	return true;
}

void character::attack(bool interactive, character& enemy, wear_s weapon, bool flatfooted) {
	attackinfo ai;
	if(!get(ai, weapon))
		return;
	ai.thac0 -= enemy.getAC(flatfooted);
	if(is(DwarfCombatTactic) && enemy.isvulnerable(DwarfCombatTactic))
		ai.thac0--;
	if(is(RangerCombatTactic) && enemy.isvulnerable(RangerCombatTactic)) {
		ai.thac0 -= get(Ranger);
		ai.damage.b += get(Ranger);
	}
	auto creature_count = getcount();
	if(creature_count > 4)
		creature_count = 4;
	while(creature_count-- > 0) {
		for(auto n = (ai.attacks_per_two_rounds + (getround() % 2)) / 2; n > 0; n--) {
			if(!isenemy(&enemy))
				break;
			auto th_roll = d20();
			if(th_roll >= ai.thac0) {
				if(interactive) {
					if(!ai.weapon) {
						if(monster)
							act("%герой сделал%а укус.");
						else
							act("%герой ударил%а ногой.");
					}
					else if(ai.type == Slashing)
						act("%герой рубану%ла %оружием.");
					else if(ai.type == Bludgeon)
						act("%герой ударил%а %оружием.");
					else if(ai.type == Piercing)
						act("%герой тыкнул%а %оружием.");
					else
						act("%герой нанес%ла удар %оружием.");
				}
				auto d = ai.getdamage(enemy.getsize());
				auto v = d.roll();
				if(th_roll >= ai.critical) {
					for(auto i = 1; i < ai.multiplier; i++)
						v += d.roll(d.c, d.d);
				}
				enemy.damage(interactive, v);
			} else {
				if(interactive) {
					act("%герой промахнул%ась.");
				}
			}
		}
	}
}

void character::damage(bool interactive, int value) {
	if(value <= 0)
		return;
	if(interactive)
		act("%герой получил%а [%1i] повреждений", value);
	hp -= value;
	if(hp <= 0) {
		if(interactive)
			act("и упал%а");
	}
	if(interactive)
		logs::add(".");
	if(count > 0)
		count--;
	if(count > 0) {
		setmonsterhp();
		hp = getmaxhp();
		logs::add("Осталось еще %1i.", count);
	}
}

void character::damage(bool interactive, int value, saveinfo& e) {
	if(e.type != NoSave) {
		auto difficult = get(e.save);
		auto roll = d20();
		auto result = (roll <= difficult);
		if(e.type == Negate) {
			if(interactive)
				act("%герой вовремя отпрыгнул%а в сторону.");
			return;
		} else if(e.type == Half)
			value = value / 2;
	}
	damage(interactive, value);
}

bool character::isplayer() const {
	return party.is(const_cast<character*>(this));
}

bool character::isenemy(const character* p) const {
	return this != p
		&& p
		&& p->isready()
		&& p->side != side;
}

bool character::isusearmor() const {
	for(auto e : classes)
		if(isusearmor(e))
			return true;
	return false;
}

bool character::isuse(item_s value) const {
	if(value >= FirstArmor && value <= LastArmor) {
		if(!isusearmor())
			return false;
		for(auto e : classes) {
			auto ui = getusablearmor(e);
			if(!ui)
				return true;
			if(ui.indexof(value) != -1)
				return true;
		}
	} if(value >= FirstWeapon && value <= LastWeapon) {
		for(auto e : classes) {
			auto ui = getusableweapon(e);
			if(!ui)
				return true;
			if(ui.indexof(value) != -1)
				return true;
		}
	} else
		return true;
	return false;
}

const item* character::getwear(item_s type) const {
	for(auto& e : wears) {
		if(!e)
			continue;
		if(e.type == type)
			return &e;
	}
	return 0;
}

int character::get(skill_s id) const {
	// Get effective class level
	auto n = 0;
	if(getclasses(id)[0]) {
		for(auto e : getclasses(id)) {
			if(!e)
				break;
			auto i = get(e);
			if(i > n)
				n = i;
		}
	} else
		n = classes[0];
	// Return skill
	switch(id) {
	case PickPockets:
	case OpenLocks:
	case FindRemoveTraps:
	case MoveSilently:
	case HideInShadows:
	case DetectNoise:
	case ClimbWalls:
	case ReadLanguages:
		return maptbl(default_theive_skills[id - PickPockets], n)
			+ maptbl(theive_skills_by_dex[id], get(Dexterity))
			+ getskills(race)[id];
	case ForceDoor: return maptbl(open_doors, get(Strenght)) * 5;
	case ForceLockedDoor: return maptbl(open_close_doors, get(Strenght)) * 5;
	case FindSecretDoors: return (100 / 6) * ((race == Elf) ? 4 : 1);
	case LearnSpell: return maptbl(chance_learn_spells, get(Intellegence));
	default: return 0;
	}
}

bool character::is(feat_s id) const {
	return (feats[id / 8] & (1 << (id % 8))) != 0;
}

void character::set(feat_s id) {
	feats[id / 8] |= 1 << (id % 8);
}

void character::addmoney(int count) {
	coopers += count;
}

void character::addexp(bool interactive, unsigned value) {
	if(interactive)
		act("%герой получил%а [%1i] опыта.", value);
	experience += value;
}

reaction_s character::getreaction(reaction_s start, int bonus) {
	static reaction_s modify[][21] = {
		{Friendly, Friendly, Friendly, Friendly, Friendly, Friendly, Friendly, Friendly, Indifferent, Indifferent, Indifferent,
		Indifferent, Cautions, Cautions, Cautions, Cautions, Threatening, Threatening, Threatening, Hostile, Hostile},
		{Friendly, Friendly, Friendly, Friendly, Friendly, Friendly, Friendly, Indifferent, Indifferent, Indifferent, Indifferent,
		Indifferent, Cautions, Cautions, Cautions, Threatening, Threatening, Threatening, Threatening, Hostile, Hostile},
		{Friendly, Friendly, Friendly, Friendly, Cautions, Cautions, Cautions, Cautions, Cautions, Cautions, Threatening,
		Threatening, Threatening, Threatening, Threatening, Threatening, Hostile, Hostile, Hostile, Hostile, Hostile},
		{Flight, Flight, Flight, Flight, Flight, Flight, Cautions, Cautions, Cautions, Threatening, Threatening,
		Threatening, Threatening, Hostile, Hostile, Hostile, Hostile, Hostile, Hostile, Hostile, Hostile},
	};
	auto result = d10() + d10() - bonus;
	if(result < 2)
		result = 2;
	else if(result > 20)
		result = 20;
	switch(start) {
	case Friendly:
		return modify[0][result];
	case Threatening:
		return modify[2][result];
	case Hostile:
		return modify[3][result];
	default:
		return modify[1][result];
	}
}

int character::getsurprise() const {
	auto result = 30 - maptbl(reaction_adjustment, get(Dexterity)) * 10;
	if(result < 10)
		result = 10;
	return result;
}

int character::getsurpriseother() const {
	if(is(LightSteps))
		return 40;
	return 0;
}

bool character::surprise(int bonus) {
	auto chance = getsurprise();
	if(chance < 10)
		chance = 10;
	else if(chance > 100)
		chance = 100;
	auto roll = 1 + rand() % 100;
	auto result = (roll <= chance);
	if(result)
		add(Surprised, RRound);
	return result;
}

char* character::getname(char* result, const char* result_maximum) const {
	if(monster)
		return getmonstername(result, result_maximum);
	zcpy(result, getname());
	return result;
}

character* character::get(aref<character*> source, bool(character::*proc)(const character* opponent) const) const {
	for(auto p : source) {
		if((this->*proc)(p))
			return p;
	}
	return 0;
}

unsigned character::getcount() const {
	return count ? count : (isready() ? 1 : 0);
}

bool character::savingthrow(saveinfo& e) const {
	if(e.type == NoSave)
		return false;
	auto difficult = get(e.save);
	auto roll = d20();
	return roll <= difficult;
}

bool character::roll(tag id) const {
	if(id.type == Skill) {
		auto result = 1 + (rand() % 100);
		if(result < 1)
			result = 1;
		else if(result > 100)
			result = 100;
		auto difficult = get((skill_s)id.value);
		return result <= difficult;
	} else if(id.type == Ability) {
		auto result = 1 + (rand() % 20);
		if(result < 1)
			result = 1;
		else if(result > 20)
			result = 20;
		auto difficult = get((ability_s)id.value);
		return result <= difficult;
	}
	return false;
}

bool character::isallow(const tag id) const {
	// Party depends actions
	switch(id.type) {
	case Alignment: return alignment == id;
	case Feat: return is((feat_s)id.value);
	case Race: return race == id;
	case Skill: return get((skill_s)id.value) > 0;
	default: return true;
	}
}

aref<character::variable> character::getvariables() {
	static variable variables[] = {
		{"AC", "AC", &getAC},
		{"HD", "HD", &getHD},
		{"деньги", "Деньги", &getmoney},
		{"движение", "Норма движения", &getspeed},
		{"опыт", "Опыт", &getexperience, "[%1i%%]"},
		{"сюрприз", "ШIанс удивиться", &getsurprise, "[%1i%%]"},
		{"сюрприз_других", "Шанс удивить других", &getsurpriseother, "[%1i%%]"},
		{"хиты", "Хиты", &gethp},
		{"хиты_максимум", "Максимальные хиты", &getmaxhp},
	};
	return variables;
}