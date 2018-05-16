#include "main.h"

static struct item_info {
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
	{"Empthy", "�����"},
	// ������
	{"RaggedBow", "����������� ���", 15, 2, Moderate, Weapons, {}, {{Near}, 1}, 0, 0, 0, 0, NoItem, Arrows},
	{"FineBow", "������� ���", 60, 2, Wealthy, Weapons, {}, {{Near, Far}, 2}, 0, 0, 0, 0, NoItem, Arrows},
	{"HuntersBow", "��������� ���", 100, 1, Wealthy, Weapons, {}, {{Near, Far}, 2}, 0, 0, 0, 0, NoItem, Arrows},
	{"Crossbow", "�������", 35, 3, Rich, Weapons, {{Reloaded}, 1}, {{Near}, 1}, 0, 1},
	{"BundleOfArrows", "������", 1, 1, Moderate, Weapons, {}, {}, 3, 0, 0, 0, Arrows},
	{"ElvenArrows", "���������� ������", 20, 1, Rich, Weapons, {}, {}, 4, 0, 0, 0, Arrows},
	{"Club", "�������", 1, 2, Moderate, Weapons, {}, {{Close}, 1}},
	{"Staff", "�����", 1, 1, Moderate, Weapons, {{TwoHanded}, 1}, {{Close}, 1}},
	{"Knife", "���", 2, 1, Moderate, Weapons, {}, {{Hand}, 1}},
	{"ThrowingDagger", "����������� ���", 2, 0, Moderate, Weapons, {{Thrown}, 1}, {{Near}, 1}},
	{"ShortSword", "�������� ���", 8, 1, Moderate, Weapons, {}, {{Close}, 1}},
	{"Mace", "������", 8, 1, Moderate, Weapons, {}, {{Close}, 1}},
	{"Warhammer", "�����", 8, 1, Moderate, Weapons, {}, {{Close}, 1}},
	{"Spear", "�����", 5, 1, Moderate, Weapons, {{Thrown}, 1}, {{Reach, Near}, 2}},
	{"LongSword", "������� ���", 15, 2, Wealthy, Weapons, {}, {{Close}, 1}, 0, 1},
	{"Halberd", "��������", 9, 2, Rich, Weapons, {{TwoHanded}, 1}, {{Reach}, 1}, 0, 1},
	{"Rapier", "������", 25, 1, Wealthy, Weapons, {{Precise}, 1}, {{Close}, 1}},
	{"DuelingRapier", "������ �������", 50, 2, Rich, Weapons, {{Precise}, 1}, {{Close}, 1}, 0, 0, 0, 1},
	//
	{"FineClothing", "��������� ������", 10, 1, Wealthy, Weapons, {}, {}},
	{"Leather", "�������� �����", 10, 1, Moderate, Weapons, {}, {}, 0, 0, 1},
	{"Chainmail", "��������", 10, 1, Wealthy, Weapons, {}, {}, 0, 0, 1},
	{"Scalemail", "���������� ������", 50, 3, Wealthy, Weapons, {{Clumsy}, 1}, {}, 0, 0, 2},
	{"Plate", "������ ������", 350, 4, Rich, Weapons, {{Clumsy}, 1}, {}, 0, 0, 3},
	{"Shield", "���", 15, 2, Moderate, Weapons, {}, {}, 0, 0, 1},
	//
	{"AdventuringGear", "���������� ��� �����������", 20, 1, Poor, Tools, {}, {}, 5},
	{"Bandages", "�����", 5, 0, Poor, Tools, {{Slow}, 1}, {}, 3},
	{"Herbs", "����� � ��������", 10, 1, Poor, Species, {{Slow}, 1}, {}, 2},
	{"HealingPotion", "�������� �����", 50, 0, Wealthy, Potions},
	{"KegOfDwarvenStout", "������� ������������ ��������", 10, 4, Rich, Species},
	{"BagOfBooks", "����� � �������", 10, 2, Wealthy, Tools, {}, {}, 5},
	{"Antitoxin", "����������", 10, 0, Rich, Potions},
	//
	{"DungeonRation", "�������", 3, 1, Poor, Foods, {{Ration}, 1}, {}, 5},
	{"PersonalFeast", "�������� ���", 10, 1, Wealthy, Foods, {{Ration}, 1}, {}, 1},
	{"DwarvenHardtack", "������ �������", 3, 1, Wealthy, Foods, {{Ration}, 1}, {}, 7},
	{"ElvenBread", "���������� ����", 10, 1, Wealthy, Foods, {{Ration}, 1}, {}, 7},
	{"HalflingPipeleaf", "����� ��������", 5, 0, Rich, Foods, {}, {}, 6},
	//
	{"Mandoline", "���������", 40, 0, Rich, Tools},
	{"Lute", "�����", 40, 0, Rich, Tools},
	{"Pipes", "�������", 40, 0, Rich, Tools},
	//
	{"HolySymbol", "������ ������", 5, 0, Wealthy, Tools},
	{"SpellBook", "����� ����������", 5, 0, Wealthy, Tools},
	//
	{"Bloodstone", "������� ������", 5, 0, Moderate, Gems},
	{"Chrysoprase", "���������", 5, 0, Moderate, Gems},
	{"Iolite", "�����", 5, 0, Moderate, Gems},
	{"Jasper", "�������", 5, 0, Moderate, Gems},
	{"Moonstone", "������ ������", 5, 0, Moderate, Gems},
	{"Onyx", "�����", 5, 0, Moderate, Gems},
	// �����
	{"Map", "�����", 5, 0, Moderate, Clues},
	{"Note", "�������", 5, 0, Moderate, Clues},
	{"Journal", "�������", 5, 0, Moderate, Clues},
	// �������������
	{"Alexandrite", "�����������", 5, 0, Rich, Gems},
	{"Aquamarine", "���������", 5, 0, Rich, Gems},
	{"Black Pearl", "������ ���������", 5, 0, Rich, Gems},
	{"Topaz", "�����", 5, 0, Rich, Gems},
	//
	{"Poison", "��", 5, 0, Wealthy, Potions},
	//
	{"SilverCoins", "����������� ������", 1, 0, Dirt, Gems},
	{"GoldCoins", "������� ������", 10, 0, Dirt, Gems},
};
assert_enum(item, GoldCoins);
getstr_enum(item);
bsreq item_type[] = {
	BSREQ(item_info, id),
	BSREQ(item_info, name),
	BSREQ(item_info, cost),
	BSREQ(item_info, weight),
	BSREQ(item_info, uses),
	BSREQ(item_info, damage),
	BSREQ(item_info, armor),
	BSREQ(item_info, piercing),
	BSREQ(item_info, ammo),
	BSREQ(item_info, use_ammo),
{}};
BSMETA(item);
bsreq item::metadata[] = {
	BSREQ(item, type),
	BSREQ(item, tags),
	BSREQ(item, uses),
	BSREQ(item, distance),
{}};

struct tag_info {
	const char*			id;
	const char*			name;
} tag_data[] = {
	{"Awkward", "�������"},
	{"Clumsy", "���������"},
	{"Messy", "��������"},
	{"Ration", "����"},
	{"Reloaded", "�����������"},
	{"Precise", "������"},
	{"Slow", "��������"},
	{"Thrown", "�����������"},
	{"TwoHanded", "���������"},
	//
	{"Spiked", "��������"},
	{"Sharp", "������"},
	{"PerfectlyWeighted", "������� ����������������"},
	{"SerratedEdge", "�����������"},
	{"Glows", "��������"},
	{"Huge", "��������"},
	{"Versatile", "��������������"},
	{"WellCrafted", "������� ���������"},
};
BSENUM(tag, WellCrafted);

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
	if(distance.is(value))
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
	distance.set(value);
}

void item::set(tag_s value) {
	tags.set(value);
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
	addtag(p, "�����", getarmor());
	addtag(p, "����������", getpiercing());
	if(isweapon()) {
		for(auto d = Hand; d <= Far; d = (distance_s)(d + 1)) {
			if(is(d))
				addtag(p, d);
		}
	}
	if(getmaxuses()) {
		if(item_data[type].ammo)
			addtag(p, "��������", uses);
		else
			addtag(p, "�������������", uses);
	}
	addtag(p, "����", getdamage(), true);
	addtag(p, "���", getweight(), false, true);
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