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
	{"Axe", "Топор", "топором", 0, 0, {MeleeWeapon}, {0, {{1, 8}}, Slashing}},
	{"Club", "Дубина", "дубиной", 0, 0, {MeleeWeapon}, {0, {{1, 6}}, Bludgeon}},
	{"Flail", "Цеп", "цепом", 0, 0, {MeleeWeapon}, {0, {{1, 6}}, Bludgeon}},
	{"Mace", "Булава", "булавой", 0, 0, {MeleeWeapon}, {0, {{1, 6, 1}}}},
	{"Morningstar", "Шестопер", "шестопером", 0, 0, {MeleeWeapon}, {0, {{2, 4}}}},
	{"Pick", "Кирка", "киркой", 0, 0, {MeleeWeapon}, {0, {{1, 6}}}},
	{"Hammer", "Молот", "молотом", 0, 0, {MeleeWeapon}, {0, {{1, 4, 1}}}},
	{"Spear", "Копье", "копьем", 0, 0, {MeleeWeapon}, {0, {{1, 6}}, Piercing}},
	{"Staff", "Посох", "посохом", 0, 0, {MeleeWeapon}, {0, {{1, 6}}, Slashing}},
	{"Halberd", "Алебарда", "алебардой", 0, 0, {MeleeWeapon}, {0, {{1, 10}}, Slashing}},
	//
	{"Dagger", "Кинжал", "кинжалом", 0, 0, {MeleeWeapon, OffhandWeapon}, {0, {{1, 4}}, Piercing}},
	{"Short sword", "Короткий меч", "коротким мечем", 0, 0, {MeleeWeapon, OffhandWeapon}, {0, {{1, 6}}, Slashing}},
	{"Long sword", "Длинный меч", "длинным мечем", 0, 0, {MeleeWeapon}, {0, {{1, 8}}, Slashing}},
	{"Bastard sword", "Полуторный меч", "полуторным мечем", 0, 0, {MeleeWeapon}, {0, {{2, 4}}, Slashing}},
	{"Two-handed sword", "Двуручный меч", "двуручным мечем", 0, 0, {MeleeWeapon}, {0, {{1, 10}}, Slashing}},
	{"Scimitar", "Сабля", "саблей", 0, 0, {MeleeWeapon}, {0, {{1, 6}}, Slashing}},
	{"Short bow", "Короткий лук", "коротким луком", 0, 0, {RangedWeapon}, {0, {{1, 6}}, Piercing}},
	{"Long bow", "Длинный лук", "длинным луком", 0, 0, {RangedWeapon}, {0, {{1, 8}}, Piercing}},
	{"Crossbow", "Арбалет", "арбалетом", 0, 0, {RangedWeapon}, {0, {{1, 4, 1}}, Piercing}},
	{"Sling", "Пращя", "пращей", 0, 0, {RangedWeapon}, {0, {1, 6}}},
	//
	{"Banded armor", "Подбитая броня", "доспехом", 90 * GP, 0, {Armor}, {}, {6}},
	{"Chain armor", "Кольчуга", "кольчугой", 75 * GP, 0, {Armor}, {}, {5}},
	{"Leather armor", "Кожанная броня", "кожаной броней", 5 * GP, 0, {Armor}, {}, {2}},
	{"Padded armor", "Мягкая броня", "латами", 4 * GP, 0, {Armor}, {}, {2}},
	{"Plate armor", "Латы", "латами", 400 * GP, 0, {Armor}, {}, {7}},
	{"Ring armor", "Кольцевая броня", "латами", 30 * GP, 0, {Armor}, {}, {3}},
	{"Scale armor", "Чешуйчатая броня", "кольчугой", 45 * GP, 0, {Armor}, {}, {4}},
	{"Splinted armor", "Пластинчатая броня", "латами", 80 * GP, 0, {Armor}, {}, {6}},
	{"Studded armor", "Клепаная броня", "клепаной броней", 15 * GP, 0, {Armor}, {}, {3}},
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
	{"Azurite", "Азурит", "азуритом", 10 * GP, 0},
	{"Banded Agate", "Обрамеленный агат", "обрамленным агатом", 10 * GP, 0},
	{"Blue Quartz", "Голубой кварц", "", 10 * GP, 0},
	{"Eye Agate", "Глазной агат", "глазным агатом", 10 * GP, 0},
	{"Hematite", "Гематит", "гематитом", 10 * GP, 0},
	{"Lapis Lazuli", "Ляпис Лазурь", "ляпис лазурью", 10 * GP, 0},
	{"Malachite", "Малахит", "малахитом", 10 * GP, 0},
	{"Moss Agate", "Зеленый агат", "зеленым агатом", 10 * GP, 0},
	{"Obsidian", "Обсидиан", "обсидианом", 10 * GP, 0},
	{"Rhodochrosite", "Родохрозит", "родохрозитом", 10 * GP, 0},
	{"Tiger Eye Agate", "Агат с тигриный глаз", "агатом с тигриный глаз", 10 * GP, 0},
	{"Turquoise", "Бирюза", "бирюзой", 10 * GP, 0},
	// Semi-Precious
	{"Bloodstone", "Кровавый камень", "кровавым камнем", 50 * GP, 0},
	{"Chalcedony", "Халцедон", "халцедоном", 50 * GP, 0},
	{"Chrysoprase", "Хризопраз", "хризопразом", 50 * GP, 0},
	{"Citrine", "Цитрин", "цитрином", 50 * GP, 0},
	{"Jasper", "Джаспер", "джаспером", 50 * GP, 0},
	{"Moonstone", "Лунный камень", "лунным камнем", 50 * GP, 0},
	{"Onyx", "Оникс", "ониксом", 50 * GP, 0},
	{"Rock Crystal", "Горный кристал", "горным кристалом", 50 * GP, 0},
	{"Sardonyx", "Сардоникс", "сардониксом", 50 * GP, 0},
	{"Smoky Quartz", "Дымный кварц", "дымным кварцем", 50 * GP, 0},
	{"Star Rose Quartz", "Звездно-розовый кварц", "звездно-розовым кварцем", 50 * GP, 0},
	{"Zircon", "Цирконий", "", 50 * GP, 0},
	//
	{"Amber", "Янтарь", "янтарем", 100 * GP, 0},
	{"Alexandrite", "Александрит", "александритом", 100 * GP, 0},
	{"Amethyst", "Аметист", "аметистом", 100 * GP, 0},
	{"Aquamarine", "Аквамарин", "аквамарином", 500 * GP, 0},
	{"Chrysoberyl", "Хризоберилл", "хризобериллом", 100 * GP, 0},
	{"Coral", "Корал", "коралом", 100 * GP, 0},
	{"Garnet", "Гранат", "гранатом", 300 * GP, 0},
	{"Jade", "Нефрит", "нефритом", 100 * GP, 0},
	{"Jet", "Черный янтарь", "черным янтарем", 100 * GP, 0},
	{"Pearl", "Жемчужина", "жемчужиной", 250 * GP, 0},
	{"Peridot", "Перидот", "перидотом", 500 * GP, 0},
	{"Spinel", "Шпинель", "шпинелью", 200 * GP, 0},
	{"Topaz", "Топаз", "топазом", 500 * GP, 0},
	{"Tourmaline", "Турмалин", "турмалином", 100 * GP, 0},
	//
	{"Black Opal", "Черный опал", "черным опалом", 1000 * GP, 0},
	{"Black Sapphire", "Черный сапфир", "черным сапфиром", 5000 * GP, 0},
	{"Diamond", "Бриллиант", "бриллиантом", 5000 * GP, 0},
	{"Emerald", "Изумруд", "изумрудом", 5000 * GP, 0},
	{"Fire Opal", "Огненный опал", "огненным опалом", 1000 * GP, 0},
	{"Jacinth", "Гиацинт", "гиацинтом", 5000 * GP, 0},
	{"Opal", "Опал", "опалом", 1000 * GP, 0},
	{"Oriental Amethyst", "Тейский аметист", "тейским аметистом", 1000 * GP, 0},
	{"Oriental Emerald", "Тейский изумруд", "тейским изумрудом", 5000 * GP, 0},
	{"Oriental Topaz", "Тейский топаз", "тейским топазом", 1000 * GP, 0},
	{"Ruby", "Рубин", "рубином", 5000 * GP, 0},
	{"Sapphire", "Сапфир", "сапфиром", 1000 * GP, 0},
	{"Star Ruby", "Звездный рубин", "звездным рубином", 5000 * GP, 0},
	{"Star Sapphire", "Звездный сапфир", "звездным сапфиром", 5000 * GP, 0},
};
assert_enum(itemi, LastItem);
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

static int compare(const void* p1, const void* p2) {
	return strcmp(getstr(*((item_s*)p1)), getstr(*((item_s*)p2)));
}

char* item::getdescription(char* result, const char* result_maximum, aref<item> source) {
	item_s undefiened[64] = {};
	result[0] = 0;
	auto ps = undefiened;
	auto pe = ps + sizeof(undefiened) / sizeof(undefiened[0]);
	for(auto& e : source) {
		if(e.identify >= KnownHistory)
			continue;
		if(ps < pe)
			*ps++ = e.type;
	}
	if(ps == undefiened)
		return result;
	qsort(undefiened, ps - undefiened, sizeof(undefiened[0]), compare);
	auto ep = NoItem;
	auto count = 0;
	auto pt = result;
	for(auto e : undefiened) {
		if(ep == NoItem) {
			ep = e;
			count = 1;
			continue;
		}
		else if(ep == e) {
			count++;
			continue;
		}
		if(pt != result) {
			zcat(pt, ", ");
			pt = zend(pt);
		}
		grammar::get(pt, result_maximum, getstr(ep), count);
		szlower(pt);
		pt = zend(pt);
		ep = e;
		count = 1;
		if(e == NoItem)
			break;
	}
	return result;
}