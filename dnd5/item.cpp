#include "main.h"

item_info item_data[] = {{"No item", "��� ��������"},
//
{"Club", "������", 1 * SP, 2, {MeleeWeapon, OffhandWeapon}, {SimpleWeaponProficiency}, {}, {1, 8, 0, Bludgeon}},
{"Dagger", "������", 2 * GP, 1, {MeleeWeapon, OffhandWeapon}, {SimpleWeaponProficiency}, {Finesse, Thrown}, {1, 4, 0, Pierce}},
{"Greatclub", "������", 2 * SP, 10, {MeleeWeapon}, {SimpleWeaponProficiency}, {TwoHanded}, {1, 8, 0, Bludgeon}},
{"Handaxe", "�����", 5 * GP, 2, {MeleeWeapon, OffhandWeapon}, {SimpleWeaponProficiency}, {}, {1, 6, 0, Slashing}},
{"Javelin", "������", 5 * SP, 2, {MeleeWeapon}, {SimpleWeaponProficiency}, {Thrown}, {1, 6, 0, Pierce}},
{"Light Hammer", "�������", 2 * SP, 2, {MeleeWeapon, OffhandWeapon}, {SimpleWeaponProficiency}, {Thrown}, {1, 4, 0, Bludgeon}},
{"Mace", "������", 5 * GP, 4, {MeleeWeapon}, {SimpleWeaponProficiency}, {}, {1, 6, 0, Bludgeon}},
{"Quaterstaff", "�����", 2 * SP, 4, {MeleeWeapon}, {SimpleWeaponProficiency}, {Versatile}, {1, 6, 0, Bludgeon}},
{"Spear", "�����", 1 * GP, 3, {MeleeWeapon}, {SimpleWeaponProficiency}, {Versatile}, {1, 6, 0, Pierce}},
//
{"Light Crossbow", "������ �������", 25 * GP, 5, {RangedWeapon}, {SimpleWeaponProficiency}, {TwoHanded, Loading}, {1, 8, 0, Pierce}},
{"Dart", "����", 5 * �P, 1, {RangedWeapon}, {SimpleWeaponProficiency}, {Finesse, Thrown}, {1, 4, 0, Pierce}},
{"Shortbow", "�������� ���", 25 * GP, 2, {RangedWeapon}, {SimpleWeaponProficiency, ElfWeaponTrain}, {TwoHanded}, {1, 6, 0, Pierce}},
{"Sling", "�����", 1 * SP, 0, {RangedWeapon}, {SimpleWeaponProficiency}, {}, {1, 4, 0, Bludgeon}},
//
{"Battleaxe", "������ �����", 10 * GP, 4, {MeleeWeapon}, {MartialWeaponProfiency}, {Versatile}, {1, 8, 0, Slashing}},
{"Flail", "���", 10 * GP, 2, {MeleeWeapon}, {MartialWeaponProfiency}, {}, {1, 8, 0, Bludgeon}},
{"Greataxe", "������", 30 * GP, 7, {MeleeWeapon}, {MartialWeaponProfiency}, {Heavy, TwoHanded}, {1, 12, 0, Slashing}},
{"Halberd", "��������", 20 * GP, 6, {MeleeWeapon}, {MartialWeaponProfiency}, {Heavy, TwoHanded, Reach}, {1, 10, 0, Slashing}},
{"Lance", "������������� ����", 10 * GP, 6, {MeleeWeapon}, {MartialWeaponProfiency}, {Reach}, {1, 12, 0, Pierce}},
{"Longsword", "������� ���", 15 * GP, 3, {MeleeWeapon}, {MartialWeaponProfiency, ElfWeaponTrain}, {Versatile}, {1, 8, 0, Slashing}},
{"Maul", "����", 10 * GP, 10, {MeleeWeapon}, {MartialWeaponProfiency}, {Heavy, TwoHanded}, {2, 6, 0, Bludgeon}},
{"Morningstar", "��������", 15 * GP, 4, {MeleeWeapon}, {MartialWeaponProfiency}, {}, {1, 8, 0, Pierce}},
{"Pike", "����", 5 * GP, 18, {MeleeWeapon}, {MartialWeaponProfiency}, {Heavy, Reach, TwoHanded}, {1, 10, 0, Pierce}},
{"Rapier", "������", 25 * GP, 2, {MeleeWeapon}, {MartialWeaponProfiency}, {Finesse}, {1, 8, 0, Pierce}},
{"Scimitar", "��������", 25 * GP, 3, {MeleeWeapon, OffhandWeapon}, {MartialWeaponProfiency}, {Finesse}, {1, 6, 0, Slashing}},
{"Shortsword", "�������� ���", 10 * GP, 2, {MeleeWeapon, OffhandWeapon}, {MartialWeaponProfiency, ElfWeaponTrain}, {Finesse}, {1, 6, 0, Pierce}},
{"Trident", "��������", 5 * GP, 4, {MeleeWeapon}, {MartialWeaponProfiency}, {Versatile, Thrown}, {1, 6, 0, Pierce}},
{"Warhammer", "������ �����", 15 * GP, 2, {MeleeWeapon}, {MartialWeaponProfiency}, {Versatile}, {1, 8, 0, Bludgeon}},
{"Whip", "����", 2 * GP, 3, {MeleeWeapon}, {MartialWeaponProfiency}, {Finesse, Reach}, {1, 4, 0, Slashing}},
//
{"Crossbow Heavy", "������� �������", 50 * GP, 18, {RangedWeapon}, {MartialWeaponProfiency}, {Heavy, Loading, TwoHanded}, {1, 10, 0, Pierce}},
{"Longbow", "������� ���", 50 * GP, 18, {RangedWeapon}, {MartialWeaponProfiency, ElfWeaponTrain}, {Heavy, TwoHanded}, {1, 8, 0, Pierce}},
{"Net", "����", 1 * GP, 3, {RangedWeapon}, {MartialWeaponProfiency}, {Thrown}},
//
{"Arrow", "������", 1 * GP, 1, {Ammunition}},
{"Bolts", "�����", 1 * GP, 2, {Ammunition}},
{"Stones", "�����", 4 * �P, 2, {Ammunition}},
//
{"Leather armor", "������� �����", 10 * GP, 10, {Armor}, {LightArmorProficiency}, {}, {}, {1, 10}},
{"Padded Armor", "�������� �����", 5 * GP, 8, {Armor}, {LightArmorProficiency}, {}, {}, {1, 10, 0, Stealth}},
{"Studded Leather armor", "��������� ������� �����", 45 * GP, 13, {Armor}, {LightArmorProficiency}, {}, {}, {2, 10}},
//
{"Hide", "�����", 10 * GP, 12, {Armor}, {MediumArmorProficiency}, {}, {}, {2, 2}},
{"Breastplate", "���������", 400 * GP, 20, {Armor}, {MediumArmorProficiency}, {}, {}, {4, 2}},
{"Half Plate", "����-����", 750 * GP, 40, {Armor}, {MediumArmorProficiency}, {}, {}, {5, 2, 0, Stealth}},
{"Chain Shirt", "���������� ������", 50 * GP, 20, {Armor}, {MediumArmorProficiency}, {}, {}, {3, 2}},
{"Scale Mail", "���������� ������", 50 * GP, 45, {Armor}, {MediumArmorProficiency}, {}, {}, {4, 2, 0, Stealth}},
//
{"Ring Mail", "��������� ������", 30 * GP, 40, {Armor}, {HeavyArmorProficiency}, {}, {}, {4, 0, 0, Stealth}},
{"Plate", "����", 1500 * GP, 65, {Armor}, {HeavyArmorProficiency}, {}, {}, {8, 0, 15, Stealth}},
{"Chain Mail", "���������� ������", 75 * GP, 55, {Armor}, {HeavyArmorProficiency}, {}, {}, {6, 0, 13, Stealth}},
{"Splint Mail", "��������� ������", 200 * GP, 60, {Armor}, {HeavyArmorProficiency}, {}, {}, {7, 0, 15, Stealth}},
//
{"Shield", "���", 10 * GP, 6, {OffhandWeapon}, {ShieldProficiency}, {}, {}, {2}},
{"Helmet", "����", 10 * GP, 1, {Head}},
{"Bracers", "��������", 10 * GP, 1, {Elbow}},
{"Ring", "������", 10 * GP, 0, {LeftFinger, RightFinger}},
{"Necklage", "��������", 10 * GP, 0, {Neck}},
//
{"Bedroll", "���������� ��������������", 1 * GP, 7},
{"Book", "�����", 5 * GP, 2},
{"Component's pounch", "������� � ������������", 1 * GP, 1},
{"Crowbar", "�����", 2 * GP, 5},
{"Holy symbol", "��������� ������", 1 * SP, 1},
{"Map", "�����", 2 * GP, 0},
{"Parchment", "���������", 1 * SP, 0, {}, {}, {}, {}, {}, 10},
{"Ration", "��������", 2 * SP, 4, {}, {}, {}, {}, {}, 20},
{"Rope", "�������", 1 * GP, 10},
{"Spellbook", "����� ����������", 10 * GP, 2},
{"Torches", "������", 5 * �P, 2, {}, {}, {}, {}, {}, 5},
{"Waterskin", "������", 2 * SP, 5, {}, {}, {}, {}, {}, 20},
//
{"Dices", "������", 1 * SP},
{"Playing cards", "��������� �����", 5 * SP},
//
{"Flute", "", 2 * GP, 1},
{"Lute", "", 35 * GP, 2},
//
{"Alchemist's supplies", "", 50 * GP, 8},
{"Brewer's supplies", "", 20 * GP, 9},
{"Calligrapher's supplies", "", 10 * GP, 5},
{"Carpenter's tools", "", 8 * GP, 6},
{"Cartographer's tools", "", 15 * GP, 6},
{"Cobbler's tools", "", 5 * GP, 5},
{"Cook's utensils", "", 1 * GP, 8},
{"Glassblower's tools", "", 30 * GP, 5},
{"Jeweler's tools", "", 25 * GP, 2},
{"Leatherworker's tools", "", 5 * GP, 5},
{"Mason's tools", "", 10 * GP, 8},
{"Painter's supplies", "", 10 * GP, 5},
{"Potter's tools", "", 10 * GP, 3},
{"Smith's tools", "", 20 * GP, 8},
{"Tinker's tools", "", 50 * GP, 10},
{"Weaver's tools", "", 1 * GP, 5},
{"Woodcarver's tools", "", 1 * GP, 5},
//
{"Disguise kit", "����� ��� ����������", 25 * GP, 3},
{"Forgery kit", "����� ��� �������� ����������", 15 * �P, 5},
{"Herbalism kit", "����� ��������", 5 * GP, 3},
{"Navigator's tools", "����������� ����������", 25 * GP, 2},
{"Poisoner's tools", "����������� ����������", 50 * GP, 2},
{"Theif's Tools", "��������� �����������", 2 * GP, 5},
};
getstr_enum(item);
assert_enum(item, LastItem);

const char* item::getnameof(char* result, const char* result_maximum) const {
	return grammar::of(result, result_maximum, item_data[type].name);
}

const char* item::getnameby(char* result, const char* result_maximum) const {
	return grammar::by(result, result_maximum, item_data[type].name);
}

bool item::is(feat_s id) const {
	for(auto e : item_data[type].proficiency) {
		if(e == id)
			return true;
	}
	return false;
}

bool item::is(item_feat_s id) const {
	for(auto e : item_data[type].feats) {
		if(e == id)
			return true;
	}
	return false;
}

bool item::is(wear_s id) const {
	return item_data[type].wears[0] == id
		|| item_data[type].wears[1] == id;
}

bool item::islight() const {
	return item_data[type].wears[0] == MeleeWeapon
		&& item_data[type].wears[1] == OffhandWeapon;
}

int item::getac() const {
	return item_data[type].armor.ac;
}

const dice& item::getattack() const {
	return item_data[type].attack;
}

bool creature::isproficient(item_s it) const {
	if(item_data[it].proficiency[0] == NoFeat)
		return true;
	for(auto e : item_data[it].proficiency) {
		if(!e)
			break;
		if(is(e))
			return true;
	}
	return false;
}