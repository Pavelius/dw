#include "main.h"

itemi bsmeta<itemi>::elements[] = {{"Empthy", "�����"},
// ������
{"RaggedBow", "����������� ���", 15, 2, Moderate, Weapons, {}, {Near}, 0, 0, 0, 0, NoItem, Arrows},
{"FineBow", "������� ���", 60, 2, Wealthy, Weapons, {}, {Near, Far}, 0, 0, 0, 0, NoItem, Arrows},
{"HuntersBow", "��������� ���", 100, 1, Wealthy, Weapons, {}, {Near, Far}, 0, 0, 0, 0, NoItem, Arrows},
{"Crossbow", "�������", 35, 3, Rich, Weapons, {Reloaded}, {Near}, 0, 1},
{"BundleOfArrows", "������", 1, 1, Moderate, Weapons, {}, {}, 3, 0, 0, 0, Arrows},
{"ElvenArrows", "���������� ������", 20, 1, Rich, Weapons, {}, {}, 4, 0, 0, 0, Arrows},
{"Club", "�������", 1, 2, Moderate, Weapons, {}, {Close}},
{"Staff", "�����", 1, 1, Moderate, Weapons, {TwoHanded}, {Close}},
{"Knife", "���", 2, 1, Moderate, Weapons, {}, {Hand}},
{"ThrowingDagger", "����������� ���", 2, 0, Moderate, Weapons, {Thrown}, {Near}},
{"ShortSword", "�������� ���", 8, 1, Moderate, Weapons, {}, {Close}},
{"Mace", "������", 8, 1, Moderate, Weapons, {}, {Close}},
{"Warhammer", "�����", 8, 1, Moderate, Weapons, {}, {Close}},
{"Spear", "�����", 5, 1, Moderate, Weapons, {Thrown}, {Reach, Near}},
{"LongSword", "������� ���", 15, 2, Wealthy, Weapons, {}, {Close}, 0, 1},
{"Halberd", "��������", 9, 2, Rich, Weapons, {TwoHanded}, {Reach}, 0, 1},
{"Rapier", "������", 25, 1, Wealthy, Weapons, {Precise}, {Close}},
{"DuelingRapier", "������ �������", 50, 2, Rich, Weapons, {Precise}, {Close}, 0, 0, 0, 1},
//
{"FineClothing", "��������� ������", 10, 1, Wealthy, Weapons, {}, {}},
{"Leather", "�������� �����", 10, 1, Moderate, Weapons, {}, {}, 0, 0, 1},
{"Chainmail", "��������", 10, 1, Wealthy, Weapons, {}, {}, 0, 0, 1},
{"Scalemail", "���������� ������", 50, 3, Wealthy, Weapons, {Clumsy}, {}, 0, 0, 2},
{"Plate", "������ ������", 350, 4, Rich, Weapons, {Clumsy}, {}, 0, 0, 3},
{"Shield", "���", 15, 2, Moderate, Weapons, {}, {}, 0, 0, 1},
//
{"AdventuringGear", "���������� ��� �����������", 20, 1, Poor, Tools, {}, {}, 5},
{"Bandages", "�����", 5, 0, Poor, Tools, {Slow}, {}, 3},
{"Herbs", "����� � ��������", 10, 1, Poor, Species, {Slow}, {}, 2},
{"HealingPotion", "�������� �����", 50, 0, Wealthy, Potions},
{"KegOfDwarvenStout", "������� ������������ ��������", 10, 4, Rich, Species},
{"BagOfBooks", "����� � �������", 10, 2, Wealthy, Tools, {}, {}, 5},
{"Antitoxin", "����������", 10, 0, Rich, Potions},
//
{"DungeonRation", "�������", 3, 1, Poor, Foods, {Ration}, {}, 5},
{"PersonalFeast", "�������� ���", 10, 1, Wealthy, Foods, {Ration}, {}, 1},
{"DwarvenHardtack", "������ �������", 3, 1, Wealthy, Foods, {Ration}, {}, 7},
{"ElvenBread", "���������� ����", 10, 1, Wealthy, Foods, {Ration}, {}, 7},
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
	addtag(sb, "�����", getarmor());
	addtag(sb, "����������", getpiercing());
	if(isweapon()) {
		for(auto d = Hand; d <= Far; d = (distance_s)(d + 1)) {
			if(is(d))
				addtag(sb, d);
		}
	}
	if(getmaxuses()) {
		if(bsmeta<itemi>::elements[type].ammo)
			addtag(sb, "��������", uses);
		else
			addtag(sb, "�������������", uses);
	}
	addtag(sb, "����", getdamage(), true);
	addtag(sb, "���", getweight(), false, true);
}

prosperty_s	item::getprosperty() const {
	return bsmeta<itemi>::elements[type].prosperty;
}

resource_s item::getresource() const {
	return bsmeta<itemi>::elements[type].resource;
}