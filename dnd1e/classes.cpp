#include "main.h"

static item_s warrior_items[] = {Axe, BattleAxe, Mace, MorningStar, Hammer,
Spear, Staff, Halberd,
Dagger, ShortSword, LongSword, BastardSword, TwoHandedSword, Scimitar,
ShortBow, LongBow, Crossbow, Sling,
LeatherArmor, StuddedLeatherArmor, ChainMail, ScaleMail, Brigandine, PlateMail, RingMail, SplintMail, FieldPlate, FullPlate,
Shield,
};
static item_s cleric_items[] = {Mace, MorningStar, Hammer,
Staff, Sling, Crossbow,
LeatherArmor, StuddedLeatherArmor, ChainMail, ScaleMail, Brigandine, PlateMail, RingMail, SplintMail, FieldPlate, FullPlate,
Shield,
};
static item_s theif_items[] = {Dagger, ShortSword, LongSword,
Staff, ShortBow, Crossbow, Sling,
LeatherArmor, StuddedLeatherArmor,
};
static item_s wizards_items[] = {Staff, Dagger, Sling,
};

static struct classi {
	const char*		id;
	const char*		name;
	char			minimum[Charisma + 1];
	group_s			group;
	classa			classes;
	racea			races;
	feata			feats;
	aref<item_s>	allowed;
} class_data[] = {
	{"No class", ""},
	{"Bard", "Бард", {0, 12, 0, 13, 0, 15}, Rogues, {Bard}, {Human, HalfElf}, {}, theif_items},
	{"Cleric", "Клерик", {0, 0, 0, 0, 9, 0}, Priests, {Cleric}, {Human, Dwarf, Elf, Gnome, HalfElf, Halfling}, {}, cleric_items},
	{"Druid", "", {0, 0, 0, 0, 12, 15}, Priests, {Druid}, {Human, HalfElf}, {}, cleric_items},
	{"Fighter", "Воин", {9, 0, 0, 0, 0, 0}, Warriors, {Fighter}, {Human, Dwarf, Elf, Gnome, HalfElf, Halfling}, {}, warrior_items},
	{"Mage", "Маг", {0, 0, 0, 9, 0, 0}, Wizards, {Mage}, {Human, Elf, HalfElf}, {}, wizards_items},
	{"Paladin", "Паладин", {12, 0, 9, 0, 13, 17}, Warriors, {Paladin}, {Human}, {}, warrior_items},
	{"Ranger", "Следопыт", {13, 13, 14, 0, 14, 0}, Warriors, {Ranger}, {Human, Elf, HalfElf}, {} , warrior_items},
	{"Theif", "Вор", {0, 9, 0, 0, 0, 0}, Rogues, {Theif}, {Human, Dwarf, Elf, Gnome, HalfElf, Halfling}, {}, theif_items},
	//
	{"Fighter/Cleric", "Воин/Клерик", {9, 0, 0, 0, 9, 0}, Warriors, {Fighter, Cleric}, {Dwarf, Elf, Gnome, HalfElf, Halfling}, {}, warrior_items},
	{"Fighter/Mage", "Воин/Маг", {9, 0, 0, 9, 0, 0}, Warriors, {Fighter, Mage}, {Dwarf, Elf, HalfElf}, {}, warrior_items},
	{"Fighter/Theif", "Воин/Вор", {9, 9, 0, 0, 0, 0}, Warriors, {Fighter, Theif}, {Dwarf, Elf, Gnome, HalfElf, Halfling}, {}, warrior_items},
	{"Cleric/Mage", "Клерик/Маг", {0, 0, 0, 9, 9, 0}, Warriors, {Cleric, Mage}, {HalfElf}, {}, cleric_items},
	{"Mage/Theif", "Маг/Вор", {0, 9, 0, 9, 0, 0}, Warriors, {Mage, Theif}, {Elf, HalfElf}, {}, theif_items},
	{"Fighter/Cleric/Mage", "Воин/Клерик/Маг", {9, 0, 0, 9, 9, 0}, Warriors, {Fighter, Cleric, Mage}, {HalfElf}, {}, warrior_items},
	{"Fighter/Mage/Theif", "Воин/Маг/Вор", {9, 9, 0, 0, 0, 0}, Warriors, {Fighter, Mage, Theif}, {Elf, HalfElf}, {}, warrior_items},
};
assert_enum(class, FighterMageTheif);
getstr_enum(class)
bsreq class_type[] = {
	BSREQ(classi, id),
	BSREQ(classi, name),
	BSREQ(classi, minimum),
	BSREQ(classi, group),
	{}
};
bsdata class_manager("class", class_data, class_type);

char* character::getminimum(class_s value) {
	return class_data[value].minimum;
}

group_s character::getgroup(class_s value) {
	return class_data[value].group;
}

const classa& character::getclasses(class_s value) {
	return class_data[value].classes;
}

class_s	character::getclass(class_s value) {
	return class_data[value].classes[0];
}

const racea& character::getraces(class_s value) {
	return class_data[value].races;
}

aref<item_s> character::getitems(class_s value) const {
	return class_data[value].allowed;
}

void character::set(class_s id) {
	for(auto e : class_data[id].feats)
		set(e);
}