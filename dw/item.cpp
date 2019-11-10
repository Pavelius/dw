#include "main.h"

itemi bsmeta<itemi>::elements[] = {{"Empthy", "Пусто"},
// Оружие
{"RaggedBow", "Потрепанный лук", 15, 2, Moderate, Weapons, {}, {Near}, 0, 0, 0, 0, NoItem, Arrows},
{"FineBow", "Хороший лук", 60, 2, Wealthy, Weapons, {}, {Near, Far}, 0, 0, 0, 0, NoItem, Arrows},
{"HuntersBow", "Охотничий лук", 100, 1, Wealthy, Weapons, {}, {Near, Far}, 0, 0, 0, 0, NoItem, Arrows},
{"Crossbow", "Арбалет", 35, 3, Rich, Weapons, {Reloaded}, {Near}, 0, 1},
{"BundleOfArrows", "Стрелы", 1, 1, Moderate, Weapons, {}, {}, 3, 0, 0, 0, Arrows},
{"ElvenArrows", "Эльфийские стрелы", 20, 1, Rich, Weapons, {}, {}, 4, 0, 0, 0, Arrows},
{"Club", "Дубинка", 1, 2, Moderate, Weapons, {}, {Close}},
{"Staff", "Посох", 1, 1, Moderate, Weapons, {TwoHanded}, {Close}},
{"Knife", "Нож", 2, 1, Moderate, Weapons, {}, {Hand}},
{"ThrowingDagger", "Метательный нож", 2, 0, Moderate, Weapons, {Thrown}, {Near}},
{"ShortSword", "Короткий меч", 8, 1, Moderate, Weapons, {}, {Close}},
{"Mace", "Булава", 8, 1, Moderate, Weapons, {}, {Close}},
{"Warhammer", "Молот", 8, 1, Moderate, Weapons, {}, {Close}},
{"Spear", "Копье", 5, 1, Moderate, Weapons, {Thrown}, {Reach, Near}},
{"LongSword", "Длинный меч", 15, 2, Wealthy, Weapons, {}, {Close}, 0, 1},
{"Halberd", "Алебарда", 9, 2, Rich, Weapons, {TwoHanded}, {Reach}, 0, 1},
{"Rapier", "Рапира", 25, 1, Wealthy, Weapons, {Precise}, {Close}},
{"DuelingRapier", "Рапира дулянта", 50, 2, Rich, Weapons, {Precise}, {Close}, 0, 0, 0, 1},
//
{"FineClothing", "Роскошная одежда", 10, 1, Wealthy, Weapons, {}, {}},
{"Leather", "Кожанная броня", 10, 1, Moderate, Weapons, {}, {}, 0, 0, 1},
{"Chainmail", "Кольчуга", 10, 1, Wealthy, Weapons, {}, {}, 0, 0, 1},
{"Scalemail", "Чешуйчатый доспех", 50, 3, Wealthy, Weapons, {Clumsy}, {}, 0, 0, 2},
{"Plate", "Латный доспех", 350, 4, Rich, Weapons, {Clumsy}, {}, 0, 0, 3},
{"Shield", "Щит", 15, 2, Moderate, Weapons, {}, {}, 0, 0, 1},
//
{"AdventuringGear", "Снаряжение для приключений", 20, 1, Poor, Tools, {}, {}, 5},
{"Bandages", "Бинты", 5, 0, Poor, Tools, {Slow}, {}, 3},
{"Herbs", "Травы и припарки", 10, 1, Poor, Species, {Slow}, {}, 2},
{"HealingPotion", "Лечебное зелье", 50, 0, Wealthy, Potions},
{"KegOfDwarvenStout", "Боченок Дварфийского Алкоголя", 10, 4, Rich, Species},
{"BagOfBooks", "Сумка с книгами", 10, 2, Wealthy, Tools, {}, {}, 5},
{"Antitoxin", "Антитоксин", 10, 0, Rich, Potions},
//
{"DungeonRation", "Сухпаек", 3, 1, Poor, Foods, {Ration}, {}, 5},
{"PersonalFeast", "Шикарная еда", 10, 1, Wealthy, Foods, {Ration}, {}, 1},
{"DwarvenHardtack", "Сухари дварфов", 3, 1, Wealthy, Foods, {Ration}, {}, 7},
{"ElvenBread", "Эльфийский хлеб", 10, 1, Wealthy, Foods, {Ration}, {}, 7},
{"HalflingPipeleaf", "Пирог хоббитов", 5, 0, Rich, Foods, {}, {}, 6},
//
{"Mandoline", "Мандолина", 40, 0, Rich, Tools},
{"Lute", "Лютня", 40, 0, Rich, Tools},
{"Pipes", "Свирель", 40, 0, Rich, Tools},
//
{"HolySymbol", "Святой символ", 5, 0, Wealthy, Tools},
{"SpellBook", "Книга заклинаний", 5, 0, Wealthy, Tools},
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
{"SilverCoins", "Серебрянные Монеты", 1, 0, Dirt, Gems},
{"GoldCoins", "Золотые Монеты", 10, 0, Dirt, Gems},
};
assert_enum(item, GoldCoins);

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
	return bsmeta<itemi>::elements[type].uses;
}

int item::getdamage() const {
	auto r = bsmeta<itemi>::elements[type].damage;
	if(is(Spiked))
		r++;
	if(is(SerratedEdges))
		r++;
	return r;
}

int item::getweight() const {
	int r = bsmeta<itemi>::elements[type].weight;
	if(is(Spiked))
		r++;
	if(is(WellCrafted))
		r--;
	return imax(r, 0);
}

int item::getarmor() const {
	return bsmeta<itemi>::elements[type].armor;
}

int item::getcost() const {
	return bsmeta<itemi>::elements[type].cost;
}

int item::getsellcost(int charisma) const {
	return bsmeta<itemi>::elements[type].cost / 2;
}

bool item::is(distance_s value) const {
	if(distance.is(value))
		return true;
	for(auto e : bsmeta<itemi>::elements[type].distance) {
		if(value == e)
			return true;
	}
	return false;
}

void item::set(item_s value) {
	clear();
	type = value;
	uses = bsmeta<itemi>::elements[type].uses;
	for(auto v : bsmeta<itemi>::elements[value].distance)
		set(v);
	for(auto v : bsmeta<itemi>::elements[value].tags)
		set(v);
}

void item::set(distance_s value) {
	distance.add(value);
}

void item::set(tag_s value) {
	tags.add(value);
}

void item::use() {
	if((--uses) == 0)
		type = NoItem;
}

void item::getname(stringbuilder& sb, bool description, bool tolower) const {
	auto p = sb.get();
	if(iscoins() && uses)
		sb.add("%1i %-2", getuses() + 1, getstr(type));
	else
		sb.add(getstr(type));
	if(description) {
		sb.add("[~");
		getdescription(sb);
		sb.add("]");
	}
	if(tolower)
		szlower(p);
}

bool item::iscoins() const {
	return type >= SilverCoins;
}

bool item::isammo() const {
	return bsmeta<itemi>::elements[type].ammo != NoItem;
}

bool item::isammo(item_s value) const {
	return bsmeta<itemi>::elements[type].ammo == value;
}

item_s item::getammo() const {
	return bsmeta<itemi>::elements[type].use_ammo;
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
	auto r = bsmeta<itemi>::elements[type].piercing;
	if(is(Sharp))
		r += 2;
	return r;
}

static void addtag(stringbuilder& sb, distance_s value) {
	sb.adds(getstr(value));
}

static void addtag(stringbuilder& sb, tag_s value) {
	sb.adds(getstr(value));
}

static void addtag(stringbuilder& sb, const char* name, int count, bool plus_minus = false, bool test_zero = true) {
	if(test_zero && !count)
		return;
	if(plus_minus)
		sb.adds("%1%+2i", name, count);
	else
		sb.adds("%2i %1", name, count);
}

void item::getdescription(stringbuilder& sb) const {
	for(auto t = Awkward; t <= WellCrafted; t = (tag_s)(t + 1)) {
		if(is(t))
			addtag(sb, t);
	}
	addtag(sb, "броня", getarmor());
	addtag(sb, "пробивание", getpiercing());
	if(isweapon()) {
		for(auto d = Hand; d <= Far; d = (distance_s)(d + 1)) {
			if(is(d))
				addtag(sb, d);
		}
	}
	if(getmaxuses()) {
		if(bsmeta<itemi>::elements[type].ammo)
			addtag(sb, "боезапас", uses);
		else
			addtag(sb, "использований", uses);
	}
	addtag(sb, "урон", getdamage(), true);
	addtag(sb, "вес", getweight(), false, true);
}

prosperty_s	item::getprosperty() const {
	return bsmeta<itemi>::elements[type].prosperty;
}

resource_s item::getresource() const {
	return bsmeta<itemi>::elements[type].resource;
}