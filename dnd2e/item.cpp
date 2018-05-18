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
	{"Empthy", "�����"},
	//
	{"Axe", "�����", "�������", 0, 0, {MeleeWeapon}, {0, {{1, 8}}, Slashing}},
	{"Club", "������", "�������", 0, 0, {MeleeWeapon}, {0, {{1, 6}}, Bludgeon}},
	{"Flail", "���", "�����", 0, 0, {MeleeWeapon}, {0, {{1, 6}}, Bludgeon}},
	{"Mace", "������", "�������", 0, 0, {MeleeWeapon}, {0, {{1, 6, 1}}}},
	{"Morningstar", "��������", "����������", 0, 0, {MeleeWeapon}, {0, {{2, 4}}}},
	{"Pick", "�����", "������", 0, 0, {MeleeWeapon}, {0, {{1, 6}}}},
	{"Hammer", "�����", "�������", 0, 0, {MeleeWeapon}, {0, {{1, 4, 1}}}},
	{"Spear", "�����", "������", 0, 0, {MeleeWeapon}, {0, {{1, 6}}, Piercing}},
	{"Staff", "�����", "�������", 0, 0, {MeleeWeapon}, {0, {{1, 6}}, Slashing}},
	{"Halberd", "��������", "���������", 0, 0, {MeleeWeapon}, {0, {{1, 10}}, Slashing}},
	//
	{"Dagger", "������", "��������", 0, 0, {MeleeWeapon, OffhandWeapon}, {0, {{1, 4}}, Piercing}},
	{"Short sword", "�������� ���", "�������� �����", 0, 0, {MeleeWeapon, OffhandWeapon}, {0, {{1, 6}}, Slashing}},
	{"Long sword", "������� ���", "������� �����", 0, 0, {MeleeWeapon}, {0, {{1, 8}}, Slashing}},
	{"Bastard sword", "���������� ���", "���������� �����", 0, 0, {MeleeWeapon}, {0, {{2, 4}}, Slashing}},
	{"Two-handed sword", "��������� ���", "��������� �����", 0, 0, {MeleeWeapon}, {0, {{1, 10}}, Slashing}},
	{"Scimitar", "�����", "������", 0, 0, {MeleeWeapon}, {0, {{1, 6}}, Slashing}},
	{"Short bow", "�������� ���", "�������� �����", 0, 0, {RangedWeapon}, {0, {{1, 6}}, Piercing}},
	{"Long bow", "������� ���", "������� �����", 0, 0, {RangedWeapon}, {0, {{1, 8}}, Piercing}},
	{"Crossbow", "�������", "���������", 0, 0, {RangedWeapon}, {0, {{1, 4, 1}}, Piercing}},
	{"Sling", "�����", "������", 0, 0, {RangedWeapon}, {0, {1, 6}}},
	//
	{"Banded armor", "�������� �����", "��������", 90 * GP, 0, {Armor}, {}, {6}},
	{"Chain armor", "��������", "���������", 75 * GP, 0, {Armor}, {}, {5}},
	{"Leather armor", "�������� �����", "������� ������", 5 * GP, 0, {Armor}, {}, {2}},
	{"Padded armor", "������ �����", "������", 4 * GP, 0, {Armor}, {}, {2}},
	{"Plate armor", "����", "������", 400 * GP, 0, {Armor}, {}, {7}},
	{"Ring armor", "��������� �����", "������", 30 * GP, 0, {Armor}, {}, {3}},
	{"Scale armor", "���������� �����", "���������", 45 * GP, 0, {Armor}, {}, {4}},
	{"Splinted armor", "������������ �����", "������", 80 * GP, 0, {Armor}, {}, {6}},
	{"Studded armor", "�������� �����", "�������� ������", 15 * GP, 0, {Armor}, {}, {3}},
	{"Shield", "���", "�����", 0, 0, {OffhandWeapon}, {}, {1}},
	//
	{"Stone", "������", "������"},
	{"Arrow", "������", "�������"},
	{"Bolt", "����", "������"},
	//
	{"Potion", "�����", "������"},
	{"Scroll", "������", "�������"},
	{"Ring", "������", "�������"},
	{"Rod", "������", "��������"},
	{"Wand", "�������", "��������"},
	{"Book", "�����", "������"},
	{"Tome", "���", "�����"},
	{"Necklage", "��������", "���������"},
	{"Cloack", "����", "������"},
	{"Robe", "����", "�����"},
	{"Boot", "������", "��������"},
	{"Glove", "��������", "����������"},
	{"Gridle", "����", "������"},
	{"Helm", "����", "������"},
	{"Bag", "�����", "������"},
	{"Bottle", "�������", "��������"},
	{"Dust", "����", "�����"},
	{"Flute", "������", "�������"},
	{"Guitar", "������", "�������"},
	//
	{"Rasbery", "������", "�������", 0, 0},
	{"Grain", "�����", "������", 0, 0},
	// Ornamental stones
	{"Azurite", "������", "��������", 10 * GP, 0},
	{"Banded Agate", "������������ ����", "����������� ������", 10 * GP, 0},
	{"Blue Quartz", "������� �����", "", 10 * GP, 0},
	{"Eye Agate", "������� ����", "������� ������", 10 * GP, 0},
	{"Hematite", "�������", "���������", 10 * GP, 0},
	{"Lapis Lazuli", "����� ������", "����� �������", 10 * GP, 0},
	{"Malachite", "�������", "���������", 10 * GP, 0},
	{"Moss Agate", "������� ����", "������� ������", 10 * GP, 0},
	{"Obsidian", "��������", "����������", 10 * GP, 0},
	{"Rhodochrosite", "����������", "������������", 10 * GP, 0},
	{"Tiger Eye Agate", "���� � �������� ����", "������ � �������� ����", 10 * GP, 0},
	{"Turquoise", "������", "�������", 10 * GP, 0},
	// Semi-Precious
	{"Bloodstone", "�������� ������", "�������� ������", 50 * GP, 0},
	{"Chalcedony", "��������", "����������", 50 * GP, 0},
	{"Chrysoprase", "���������", "�����������", 50 * GP, 0},
	{"Citrine", "������", "��������", 50 * GP, 0},
	{"Jasper", "�������", "���������", 50 * GP, 0},
	{"Moonstone", "������ ������", "������ ������", 50 * GP, 0},
	{"Onyx", "�����", "�������", 50 * GP, 0},
	{"Rock Crystal", "������ �������", "������ ���������", 50 * GP, 0},
	{"Sardonyx", "���������", "�����������", 50 * GP, 0},
	{"Smoky Quartz", "������ �����", "������ �������", 50 * GP, 0},
	{"Star Rose Quartz", "�������-������� �����", "�������-������� �������", 50 * GP, 0},
	{"Zircon", "��������", "", 50 * GP, 0},
	//
	{"Amber", "������", "�������", 100 * GP, 0},
	{"Alexandrite", "�����������", "�������������", 100 * GP, 0},
	{"Amethyst", "�������", "���������", 100 * GP, 0},
	{"Aquamarine", "���������", "�����������", 500 * GP, 0},
	{"Chrysoberyl", "�����������", "�������������", 100 * GP, 0},
	{"Coral", "�����", "�������", 100 * GP, 0},
	{"Garnet", "������", "��������", 300 * GP, 0},
	{"Jade", "������", "��������", 100 * GP, 0},
	{"Jet", "������ ������", "������ �������", 100 * GP, 0},
	{"Pearl", "���������", "����������", 250 * GP, 0},
	{"Peridot", "�������", "���������", 500 * GP, 0},
	{"Spinel", "�������", "��������", 200 * GP, 0},
	{"Topaz", "�����", "�������", 500 * GP, 0},
	{"Tourmaline", "��������", "����������", 100 * GP, 0},
	//
	{"Black Opal", "������ ����", "������ ������", 1000 * GP, 0},
	{"Black Sapphire", "������ ������", "������ ��������", 5000 * GP, 0},
	{"Diamond", "���������", "�����������", 5000 * GP, 0},
	{"Emerald", "�������", "���������", 5000 * GP, 0},
	{"Fire Opal", "�������� ����", "�������� ������", 1000 * GP, 0},
	{"Jacinth", "�������", "���������", 5000 * GP, 0},
	{"Opal", "����", "������", 1000 * GP, 0},
	{"Oriental Amethyst", "������� �������", "������� ���������", 1000 * GP, 0},
	{"Oriental Emerald", "������� �������", "������� ���������", 5000 * GP, 0},
	{"Oriental Topaz", "������� �����", "������� �������", 1000 * GP, 0},
	{"Ruby", "�����", "�������", 5000 * GP, 0},
	{"Sapphire", "������", "��������", 1000 * GP, 0},
	{"Star Ruby", "�������� �����", "�������� �������", 5000 * GP, 0},
	{"Star Sapphire", "�������� ������", "�������� ��������", 5000 * GP, 0},
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