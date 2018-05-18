#include "main.h"

struct weaponinfo {
	char				speed;
	dice				damage[2];
	damage_s			type;
};
struct armorinfo {
	char				AC;
};
static struct itemi {
	const char*			id;
	const char*			name;
	const char*			nameby;
	unsigned			cost;
	unsigned			weight;
	adat<wear_s, 4>		usable;
	weaponinfo			weapon;
	armorinfo			armor;
} itemi_data[] = {
	{"Empthy", "Пусто"},
	//
	{"Axe", "Топор", "топором", 0, 0, {MeleeWeapon, OffhandWeapon}, {0, {{1, 6}}, Slashing}},
	{"Battle Axe", "Боевой топор", "боевым топором", 0, 0, {MeleeWeapon}, {0, {{1, 8}}, Slashing}},
	{"Mace", "Булава", "булавой", 0, 0, {MeleeWeapon}, {0, {{1, 6, 1}}}},
	{"Morningstar", "Шестопер", "шестопером", 0, 0, {MeleeWeapon}, {0, {{2, 4}}}},
	{"Hammer", "Молот", "молотом", 0, 0, {MeleeWeapon}, {0, {{1, 4, 1}}}},
	{"Spear", "Копье", "копьем", 0, 0, {MeleeWeapon}, {0, {{1, 6}}, Piercing}},
	{"Staff", "Посох", "посохом", 0, 0, {MeleeWeapon}, {0, {{1, 6}}, Slashing}},
	{"Halberd", "Алебарда", "алебардой", 0, 0, {MeleeWeapon}, {0, {{1, 10}}, Slashing}},
	//
	{"Dagger", "Кинжал", "кинжалом", 0, 0, {MeleeWeapon, OffhandWeapon}, {0, {{1, 4}}, Piercing}},
	{"Short sword", "Короткий меч", "коротким мечем", 0, 0, {MeleeWeapon, OffhandWeapon}, {0, {{1, 6}}, Slashing}},
	{"Long sword", "Длинный меч", "длинным мечем", 0, 0, {MeleeWeapon, OffhandWeapon}, {0, {{1, 8}}, Slashing}},
	{"BastardSword", "Полуторный меч", "полуторным мечем", 0, 0, {MeleeWeapon}, {0, {{2, 4}}, Slashing}},
	{"TwoHandedSword", "Двуручный меч", "двуручным мечем", 0, 0, {MeleeWeapon}, {0, {{1, 10}}, Slashing}},
	{"Scimitar", "Сабля", "саблей", 0, 0, {MeleeWeapon}, {0, {{1, 6}}, Slashing}},
	{"Short bow", "Короткий лук", "коротким луком", 0, 0, {RangedWeapon}, {0, {{1, 6}}, Piercing}},
	{"Long bow", "Длинный лук", "длинным луком", 0, 0, {RangedWeapon}, {0, {{1, 8}}, Piercing}},
	{"Crossbow", "Арбалет", "арбалетом", 0, 0, {RangedWeapon}, {0, {{1, 4, 1}}, Piercing}},
	{"Sling", "Пращя", "пращей", 0, 0, {RangedWeapon}, {0, {1, 6}}},
	//
	{"Leather armor", "Кожанная броня", "кожаной броней", 0, 0, {Armor}, {}, {2}},
	{"Studded leather armor", "Клепаная броня", "клепаной броней", 0, 0, {Armor}, {}, {3}},
	{"Chainmail", "Кольчуга", "кольчугой", 0, 0, {Armor}, {}, {5}},
	{"Scale Mail", "Кольчуга", "кольчугой", 0, 0, {Armor}, {}, {5}},
	{"Brigandine", "Кольчуга", "кольчугой", 0, 0, {Armor}, {}, {5}},
	{"Plate Mail", "Латы", "латами", 0, 0, {Armor}, {}, {9}},
	{"Ring Mail", "Латы", "латами", 0, 0, {Armor}, {}, {9}},
	{"Splint Mail", "Латы", "латами", 0, 0, {Armor}, {}, {9}},
	{"Banded Mail", "Подитый доспех", "доспехом", 0, 0, {Armor}, {}, {9}},
	{"Field Plate", "Частичные латы", "частичными латами", 0, 0, {Armor}, {}, {9}},
	{"Full Plate", "Полные латы", "полными латами", 0, 0, {Armor}, {}, {9}},
	{"Shield", "Щит", "щитом", 0, 0, {OffhandWeapon}, {}, {1}},
	//
	{"Stone", "Камень", "камнем"},
	{"Arrow", "Стрела", "стрелой"},
	{"Bolt", "Болт", "болтом"},
	//
	{"Potion", "Зелье", "зельем"},
	{"Scroll", "Свиток", "свитком"},
	{"Ring", "Кольцо", "кольцом"},
	{"Rod", "Прутик", "прутиком"},
	{"Wand", "Палочка", "палочкой"},
	{"Book", "Книга", "книгой"},
	{"Tome", "Том", "томом"},
	{"Necklage", "Ожерелье", "ожерельем"},
	{"Cloack", "Плащ", "плащем"},
	{"Robe", "Ряса", "рясой"},
	{"Boot", "Сапоги", "сапогами"},
	{"Glove", "Перчатки", "перчатками"},
	{"Gridle", "Пояс", "поясом"},
	{"Helm", "Шлем", "шлемом"},
	{"Bag", "Сумка", "сумкой"},
	{"Bottle", "Бутылка", "бутылкой"},
	{"Dust", "Пыль", "пылью"},
	{"Flute", "Флейта", "флейтой"},
	{"Guitar", "Гитара", "гитарой"},
	//
	{"Rasbery", "Малина", "малиной", 0, 0},
	{"Grain", "Зерно", "зерном", 0, 0},
	// Ornamental stones
	{"Azurite", "", "", 10 * GP, 0},
	{"Banded Agate", "", "", 10 * GP, 0},
	{"Blue Quartz", "Голубой кварц", "", 10 * GP, 0},
	{"Eye Agate", "", "", 10 * GP, 0},
	{"Hematite", "", "", 10 * GP, 0},
	{"Lapis Lazuli", "Ляпис Лазурь", "", 10 * GP, 0},
	{"Malachite", "Малахит", "", 10 * GP, 0},
	{"Moss Agate", "", "", 10 * GP, 0},
	{"Obsidian", "Обсидиан", "", 10 * GP, 0},
	{"Rhodochrosite", "", "", 10 * GP, 0},
	{"Tiger Eye Agate", "", "", 10 * GP, 0},
	{"Turquoise", "", "", 10 * GP, 0},
	// Semi-Precious
	{"Bloodstone", "Кровавый камень", "", 50 * GP, 0},
	{"Chalcedony", "", "", 50 * GP, 0},
	{"Chrysoprase", "", "", 50 * GP, 0},
	{"Citrine", "", "", 50 * GP, 0},
	{"Jasper", "", "", 50 * GP, 0},
	{"Moonstone", "Лунный камень", "", 50 * GP, 0},
	{"Onyx", "", "Оникс", 50 * GP, 0},
	{"Rock Crystal", "Горный кристал", "", 50 * GP, 0},
	{"Sardonyx", "", "", 50 * GP, 0},
	{"Smoky Quartz", "Дымный кварц", "", 50 * GP, 0},
	{"Star Rose Quartz", "Звездный розовый кварц", "", 50 * GP, 0},
	{"Zircon", "Цирконий", "", 50 * GP, 0},
	//
	{"Amber", "", "", 100 * GP, 0},
	{"Alexandrite", "", "", 100 * GP, 0},
	{"Amethyst", "", "", 100 * GP, 0},
	{"Aquamarine", "", "", 500 * GP, 0},
	{"Chrysoberyl", "", "", 100 * GP, 0},
	{"Coral", "", "", 100 * GP, 0},
	{"Garnet", "", "", 300 * GP, 0},
	{"Jade", "", "", 100 * GP, 0},
	{"Jet", "", "", 100 * GP, 0},
	{"Pearl", "Жемчужина", "", 250 * GP, 0},
	{"Peridot", "", "", 500 * GP, 0},
	{"Spinel", "", "", 200 * GP, 0},
	{"Topaz", "Топаз", "", 500 * GP, 0},
	{"Tourmaline", "", "", 100 * GP, 0},
	//
	{"Black Opal", "Черный опал", "", 1000 * GP, 0},
	{"Black Sapphire", "Черный сапфир", "", 5000 * GP, 0},
	{"Diamond", "Бриллиант", "", 5000 * GP, 0},
	{"Emerald", "Изумруд", "", 5000 * GP, 0},
	{"Fire Opal", "Огненный опал", "", 1000 * GP, 0},
	{"Jacinth", "Гиацинт", "", 5000 * GP, 0},
	{"Opal", "Опал", "", 1000 * GP, 0},
	{"Oriental Amethyst", "Тейский аметист", "", 1000 * GP, 0},
	{"Oriental Emerald", "Тейский изумруд", "", 5000 * GP, 0},
	{"Oriental Topaz", "Тейский топаз", "", 1000 * GP, 0},
	{"Ruby", "Рубин", "", 5000 * GP, 0},
	{"Sapphire", "Сапфир", "", 1000 * GP, 0},
	{"Star Ruby", "Звездный рубин", "", 5000 * GP, 0},
	{"Star Sapphire", "Звездный сапфир", "", 5000 * GP, 0},
};
assert_enum(itemi, LastItem);
bsreq weaponinfo_type[] = {
	BSREQ(weaponinfo, speed),
	BSREQ(weaponinfo, type),
	BSREQ(weaponinfo, damage),
	{}
};
bsreq itemi_type[] = {
	BSREQ(itemi, id),
	BSREQ(itemi, name),
	BSREQ(itemi, weapon),
	BSREQ(itemi, cost),
	BSREQ(itemi, weight),
	{}
};
BSMETA(itemi);
static_assert(sizeof(item) <= sizeof(unsigned), "Size of 'item' structure is too big");

template<> const char* getstr<item_s>(item_s value) {
	return itemi_data[value].name;
}

void item::clear() {
	memset(this, 0, sizeof(item));
}

bool item::is(wear_s value) const {
	return itemi_data[type].usable.is(value);
}

bool item::getattack(attackinfo& e) const {
	if(!itemi_data[type].weapon.damage[0])
		return false;
	e.damage = itemi_data[type].weapon.damage[0];
	e.type = itemi_data[type].weapon.type;
	if(state > Mundane && identify >= KnownMagic) {
		// Magic items adjust THAC0 and damage
		auto m = getbonus();
		e.damage.b += m;
		e.thac0 -= m;
	} else {
		// Mundane items adjust only THAC0
		e.thac0 -= getbonus();
	}
	return true;
}

int item::getAC() const {
	return itemi_data[type].armor.AC ? itemi_data[type].armor.AC + getbonus() : 0;
}

const char* item::getname() const {
	return itemi_data[type].name;
}

const char* item::getnameby() const {
	return itemi_data[type].nameby;
}

unsigned item::getcost() const {
	long long result = itemi_data[type].cost;
	if(isgem()) {
		switch(state) {
		case Magic:
			result = result * 2;
			break;
		case Cursed:
			result = result / 3;
			break;
		}
		result = result * (100 + ((int)quality - 2) * 15) / 100;
		if(result < 1)
			result = 1;
	}
	return (unsigned)result;
}

int item::getbonus() const {
	if(identify == Unknown)
		return 0;
	else {
		switch(state) {
		case Cursed: return (int)quality - 3;
		case Magic: return 1 + quality;
		case Artifact: return 2 + quality;
		default: return quality;
		}
	}
}