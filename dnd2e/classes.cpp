#include "main.h"

static item_s leather_no_shield[] = {LeatherArmor, PaddedArmor, StuddedArmor};
static item_s leather_wooden[] = {LeatherArmor, PaddedArmor, StuddedArmor, Shield};
static item_s cleric_weapon[] = {Club, Flail, Hammer, Mace, Staff};
static item_s druid_weapon[] = {Club, Dagger, Hammer, Scimitar, Sling, Spear, Staff};
static item_s magic_user_weapon[] = {Dagger, Staff};
static item_s theif_weapon[] = {Club, Dagger, Sling, ShortSword, LongSword};

static struct classi {
	const char*		id;
	const char*		name;
	char			hd, hd_max;
	char			minimum[Charisma + 1];
	class_s			kit;
	racea			races;
	feata			feats;
	bool			use_armor;
	aref<item_s>	armor;
	aref<item_s>	weapon;
} class_data[] = {
	{"No class", ""},
	{"Cleric", "Клерик", 8, 9, {0, 0, 0, 0, 9, 0}, Cleric, {Human, HalfElf, Halfling}, {}, true, {}, cleric_weapon},
	{"Druid", "Друид", 8, 14, {0, 0, 0, 0, 12, 15}, Cleric, {Human, HalfElf}, {}, true, leather_wooden, druid_weapon},
	{"Fighter", "Воин", 10, 9, {9, 0, 0, 0, 0, 0}, Fighter, {Human, Dwarf, Elf, Gnome, HalfElf, Halfling, HalfOrc}, {}, true},
	{"Paladin", "Паладин", 10, 9, {12, 0, 9, 0, 13, 17}, Fighter, {Human}, {}, true},
	{"Ranger", "Следопыт", 8, 10, {13, 13, 14, 0, 14, 0}, Fighter, {Human, Elf, HalfElf}, {}, true},
	{"Magic-User", "Маг", 4, 11, {0, 0, 0, 9, 0, 0}, MagicUser, {Human, Elf, HalfElf}, {}, false, magic_user_weapon},
	{"Illusionist", "Иллюзионист", 4, 10, {0, 16, 0, 15, 0, 0}, MagicUser, {Human, Elf, HalfElf}, {}, false, magic_user_weapon},
	{"Theif", "Вор", 6, 10, {0, 9, 0, 0, 0, 0}, Theif, {Human, Dwarf, Elf, Gnome, HalfElf, Halfling, HalfOrc}, {UsePickPockets, UseClimbWalls, UseDetectNoise, UseFindRemoveTraps, UseHideInShadows, UseOpenLocks, UseReadLanguages, UseMoveSilently}, true, magic_user_weapon},
};
assert_enum(class, Theif);
getstr_enum(class)

char* character::getminimum(class_s value) {
	return class_data[value].minimum;
}

const racea& character::getraces(class_s value) {
	return class_data[value].races;
}

class_s	character::getkit(class_s value) {
	return class_data[value].kit;
}

int character::getHD(class_s value) {
	return class_data[value].hd;
}

bool character::isusearmor(class_s value) {
	return class_data[value].use_armor;
}

aref<item_s> character::getusablearmor(class_s value) {
	return class_data[value].armor;
}

aref<item_s> character::getusableweapon(class_s value) {
	return class_data[value].weapon;
}

void character::raiselevel(bool interactive, class_s type) {
	if(!type)
		return;
	auto pc = const_cast<char*>(find(type));
	if(!pc)
		return;
	// Get maximum hit points for 1-st level
	auto d = getHD(type);
	if((levels[0] + levels[1] + levels[2]) <= getmaxclasses()) {
		hp_maximum = d;
		if(type==Ranger) // Double HD for ranger and monk
			hp_maximum = dice::roll(1, d);
	}
	else
		hp_maximum = dice::roll(1, d);
	// Apply feats for first level
	if(*pc == 0) {
		for(auto e : class_data[type].feats)
			set(e);
	}
	// Raise level
	*pc = *pc + 1;
}