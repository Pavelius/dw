#include "main.h"

static struct item_i {
	const char*			id;
	const char*			name;
	int					cost;
	unsigned char		weight;
	prosperty_s			prosperty;
	resource_s			resource;
	adat<tag_s, 4>		tags;
	adat<distance_s, 2>	distance;
	unsigned char		uses;
	unsigned char		damage;
	unsigned char		armor;
	unsigned char		piercing;
	item_s				ammo;
	item_s				use_ammo;
} item_data[] = {
	{"Empthy", "Пусто"},
	// Оружие
	{"Ragged bow", "Потрепанный лук", 15, 2, Moderate, Weapons, {}, {{Near}, 1}, 0, 0, 0, 0, NoItem, Arrows},
	{"Fine bow", "Хороший лук", 60, 2, Wealthy, Weapons, {}, {{Near, Far}, 2}, 0, 0, 0, 0, NoItem, Arrows},
	{"Hunter's bow", "Охотничий лук", 100, 1, Wealthy, Weapons, {}, {{Near, Far}, 2}, 0, 0, 0, 0, NoItem, Arrows},
	{"Crossbow", "Арбалет", 35, 3, Rich, Weapons, {{Reloaded}, 1}, {{Near}, 1}, 0, 1},
	{"Bundle of Arrows", "Стрелы", 1, 1, Moderate, Weapons, {}, {}, 3, 0, 0, 0, Arrows},
	{"Elven arrows", "Эльфийские стрелы", 20, 1, Rich, Weapons, {}, {}, 4, 0, 0, 0, Arrows},
	{"Club", "Дубинка", 1, 2, Moderate, Weapons, {}, {{Close}, 1}},
	{"Staff", "Посох", 1, 1, Moderate, Weapons, {{TwoHanded}, 1}, {{Close}, 1}},
	{"Knife", "Нож", 2, 1, Moderate, Weapons, {}, {{Hand}, 1}},
	{"Throwing Dagger", "Метательный нож", 2, 0, Moderate, Weapons, {{Thrown}, 1}, {{Near}, 1}},
	{"Short sword", "Короткий меч", 8, 1, Moderate, Weapons, {}, {{Close}, 1}},
	{"Mace", "Булава", 8, 1, Moderate, Weapons, {}, {{Close}, 1}},
	{"Warhammer", "Молот", 8, 1, Moderate, Weapons, {}, {{Close}, 1}},
	{"Spear", "Копье", 5, 1, Moderate, Weapons, {{Thrown}, 1}, {{Reach, Near}, 2}},
	{"Long sword", "Длинный меч", 15, 2, Wealthy, Weapons, {}, {{Close}, 1}, 0, 1},
	{"Halberd", "Алебарда", 9, 2, Rich, Weapons, {{TwoHanded}, 1}, {{Reach}, 1}, 0, 1},
	{"Rapier", "Рапира", 25, 1, Wealthy, Weapons, {{Precise}, 1}, {{Close}, 1}},
	{"Dueling Rapier", "Рапира дулянта", 50, 2, Rich, Weapons, {{Precise}, 1}, {{Close}, 1}, 0, 0, 0, 1},
	//
	{"Fine Clothing", "Роскошная одежда", 10, 1, Wealthy, Weapons, {}, {}},
	{"Leather", "Кожанная броня", 10, 1, Moderate, Weapons, {}, {}, 0, 0, 1},
	{"Chainmail", "Кольчуга", 10, 1, Wealthy, Weapons, {}, {}, 0, 0, 1},
	{"Scalemail", "Чешуйчатый доспех", 50, 3, Wealthy, Weapons, {{Clumsy}, 1}, {}, 0, 0, 2},
	{"Plate", "Латный доспех", 350, 4, Rich, Weapons, {{Clumsy}, 1}, {}, 0, 0, 3},
	{"Shield", "Щит", 15, 2, Moderate, Weapons, {}, {}, 0, 0, 1},
	//
	{"Adventuring Gear", "Снаряжение для приключений", 20, 1, Poor, Tools, {}, {}, 5},
	{"Bandages", "Бинты", 5, 0, Poor, Tools, {{Slow}, 1}, {}, 3},
	{"Herbs", "Травы и припарки", 10, 1, Poor, Species, {{Slow}, 1}, {}, 2},
	{"Healing Potion", "Лечебное зелье", 50, 0, Wealthy, Potions},
	{"Keg of Dwarven Stout", "Боченок Дварфийского Алкоголя", 10, 4, Rich, Species},
	{"Bag of Books", "Сумка с книгами", 10, 2, Wealthy, Tools, {}, {}, 5},
	{"Antitoxin", "Антитоксин", 10, 0, Rich, Potions},
	//
	{"Dungeon Ration", "Сухпаек", 3, 1, Poor, Foods, {{Ration}, 1}, {}, 5},
	{"Personal Feast", "Шикарная еда", 10, 1, Wealthy, Foods, {{Ration}, 1}, {}, 1},
	{"Dwarven Hardtack", "Сухари дварфов", 3, 1, Wealthy, Foods, {{Ration}, 1}, {}, 7},
	{"Elven Bread", "Эльфийский хлеб", 10, 1, Wealthy, Foods, {{Ration}, 1}, {}, 7},
	{"Halfling Pipeleaf", "Пирог хоббитов", 5, 0, Rich, Foods, {}, {}, 6},
	//
	{"Mandoline", "Мандолина", 40, 0, Rich, Tools},
	{"Lute", "Лютня", 40, 0, Rich, Tools},
	{"Pipes", "Свирель", 40, 0, Rich, Tools},
	//
	{"Holy Symbol", "Святой символ", 5, 0, Wealthy, Tools},
	{"Spell Book", "Книга заклинаний", 5, 0, Wealthy, Tools},
	//
	{"Bloodstone", "Кроваый камень", 5, 0, Moderate, Gems},
	{"Chrysoprase", "Хризопраз", 5, 0, Moderate, Gems},
	{"Iolite", "Иолит", 5, 0, Moderate, Gems},
	{"Jasper", "Джаспер", 5, 0, Moderate, Gems},
	{"Moonstone", "Лунный камень", 5, 0, Moderate, Gems},
	{"Onyx", "Оникс", 5, 0, Moderate, Gems},
	// Улики
	{"Map", "Карта", 5, 0, Moderate, Clues},
	{"Note", "Заметки", 5, 0, Moderate, Clues},
	{"Journal", "Дневник", 5, 0, Moderate, Clues},
	// Драгоценности
	{"Alexandrite", "Александрит", 5, 0, Rich, Gems},
	{"Aquamarine", "Аквамарин", 5, 0, Rich, Gems},
	{"Black Pearl", "Черная жемчужина", 5, 0, Rich, Gems},
	{"Topaz", "Топаз", 5, 0, Rich, Gems},
	//
	{"Poison", "Яд", 5, 0, Wealthy, Potions},
	//
	{"Silver Coins", "Серебрянные Монеты", 1, 0, Dirt, Gems},
	{"Gold Coins", "Золотые Монеты", 10, 0, Dirt, Gems},
};
assert_enum(item, GoldCoins);
getstr_enum(item);

struct tag_i {
	const char*			id;
	const char*			name;
} tag_data[] = {
	{"awkward", "опасное"},
	{"clumsy", "неуклюжее"},
	{"messy", "кровавое"},
	{"ration", "паек"},
	{"reloaded", "перезарядка"},
	{"precise", "точное"},
	{"slow", "медленно"},
	{"thrown", "метательное"},
	{"two-handed", "двуручное"},
	//
	{"spiked", "шипастое"},
	{"sharp", "острое"},
	{"perfectly weighted", "отлично сбалансированное"},
	{"serrated edge", "зазубренное"},
	{"glows", "светится"},
	{"huge", "огромное"},
	{"versatile", "разностороннее"},
	{"well crafted", "отлично сделанное"},
};
assert_enum(tag, WellCrafted);
getstr_enum(tag);

item::item() {
	clear();
}

item::item(item_s type) {
	set(type);
}

void item::clear() {
	memset(this, 0, sizeof(*this));
}

int	item::getuses() const {
	return uses;
}

int item::getmaxuses() const {
	return item_data[type].uses;
}

int item::getdamage() const {
	auto r = item_data[type].damage;
	if(is(Spiked))
		r++;
	if(is(SerratedEdges))
		r++;
	return r;
}

int item::getweight() const {
	int r = item_data[type].weight;
	if(is(Spiked))
		r++;
	if(is(WellCrafted))
		r--;
	return imax(r, 0);
}

int item::getarmor() const {
	return item_data[type].armor;
}

int item::getcost() const {
	return item_data[type].cost;
}

int item::getsellcost(int charisma) const {
	return item_data[type].cost / 2;
}

bool item::is(distance_s value) const {
	if(distance&(1 << value))
		return true;
	for(auto e : item_data[type].distance) {
		if(value == e)
			return true;
	}
	return false;
}

void item::set(item_s value) {
	clear();
	type = value;
	uses = item_data[type].uses;
	for(auto v : item_data[value].distance)
		set(v);
	for(auto v : item_data[value].tags)
		set(v);
}

void item::set(distance_s value) {
	distance |= (1 << value);
}

void item::set(tag_s value) {
	tags |= (1 << value);
}

void item::use() {
	if((--uses) == 0)
		type = NoItem;
}

char* item::getname(char* result, bool description, bool tolower) const {
	if(iscoins() && uses) {
		szprint(result, "%1i %2", getuses() + 1, getstr(type));
		szlower(result);
	} else
		zcpy(result, getstr(type));
	if(description)
		getdescription(result);
	if(tolower)
		szlower(result, zlen(result));
	return result;
}

bool item::iscoins() const {
	return type >= SilverCoins;
}

bool item::isammo() const {
	return item_data[type].ammo != NoItem;
}

bool item::isammo(item_s value) const {
	return item_data[type].ammo == value;
}

item_s item::getammo() const {
	return item_data[type].use_ammo;
}

bool item::isarmor() const {
	return type >= FineClothing && type <= PlateMail;
}

bool item::isweapon() const {
	return type >= RaggedBow && type <= DuelingRapier;
}

bool item::isshield() const {
	return type == Shield;
}

bool item::isgems() const {
	return (type >= Bloodstone && type <= Onyx)
		|| (type >= Alexandrite && type <= Topaz);
}

bool item::isclumsy() const {
	return is(Clumsy);
}

bool item::isprecise() const {
	return is(Precise) || is(PerfectlyWeighted);
}

int item::getpiercing() const {
	auto r = item_data[type].piercing;
	if(is(Sharp))
		r += 2;
	return r;
}

static char* addsep(char* result) {
	if(result[0])
		zcat(result, ", ");
	else
		zcat(result, " (");
	return zend(result);
}

static void addtag(char* result, distance_s value) {
	zcat(addsep(result), getstr(value));
}

static void addtag(char* result, tag_s value) {
	zcat(addsep(result), getstr(value));
}

static void addtag(char* result, const char* name, int count, bool plus_minus = false, bool test_zero = true) {
	if(test_zero && !count)
		return;
	if(plus_minus)
		szprint(addsep(result), "%1%+2i", name, count);
	else
		szprint(addsep(result), "%2i %1", name, count);
}

char* item::getdescription(char* result) const {
	auto p = zend(result);
	for(auto t = Awkward; t <= WellCrafted; t = (tag_s)(t + 1)) {
		if(is(t))
			addtag(p, t);
	}
	addtag(p, "броня", getarmor());
	addtag(p, "пробивание", getpiercing());
	if(isweapon()) {
		for(auto d = Hand; d <= Far; d = (distance_s)(d + 1)) {
			if(is(d))
				addtag(p, d);
		}
	}
	if(getmaxuses()) {
		if(item_data[type].ammo)
			addtag(p, "боезапас", uses);
		else
			addtag(p, "использований", uses);
	}
	addtag(p, "урон", getdamage(), true);
	addtag(p, "вес", getweight(), false, true);
	if(p[0])
		zcat(p, ")");
	return result;
}

prosperty_s	item::getprosperty() const {
	return item_data[type].prosperty;
}

resource_s item::getresource() const {
	return item_data[type].resource;
}