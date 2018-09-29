#include "main.h"

item_info item_data[] = {{"No item", "��� ��������"},
//
{"Club", "������", 1 * SP, 2, {MeleeWeapon, OffhandWeapon}, {SimpleWeaponProficiency}, {}, {{1, 8}, Bludgeon}},
{"Dagger", "������", 2 * GP, 1, {MeleeWeapon, OffhandWeapon}, {SimpleWeaponProficiency}, {Finesse, Thrown}, {{1, 4}, Pierce}},
{"Greatclub", "������", 2 * SP, 10, {MeleeWeapon}, {SimpleWeaponProficiency}, {TwoHanded}, {{1, 8}, Bludgeon}},
{"Handaxe", "�����", 5 * GP, 2, {MeleeWeapon, OffhandWeapon}, {SimpleWeaponProficiency}, {}, {{1, 6}, Slashing}},
{"Javelin", "������", 5 * SP, 2, {MeleeWeapon}, {SimpleWeaponProficiency}, {Thrown}, {{1, 6}, Pierce}},
{"Light Hammer", "�������", 2 * SP, 2, {MeleeWeapon, OffhandWeapon}, {SimpleWeaponProficiency}, {Thrown}, {{1, 4}, Bludgeon}},
{"Mace", "������", 5 * GP, 4, {MeleeWeapon}, {SimpleWeaponProficiency}, {}, {{1, 6}, Bludgeon}},
{"Quaterstaff", "", 2 * SP, 4, {MeleeWeapon}, {SimpleWeaponProficiency}, {Versatile}, {{1, 6}, Bludgeon}},
{"Spear", "", 1 * GP, 3, {MeleeWeapon}, {SimpleWeaponProficiency}, {Versatile}, {{1, 6}, Pierce}},
//
{"Light Crossbow", "", 25 * GP, 5, {RangedWeapon}, {SimpleWeaponProficiency}, {TwoHanded, Loading}, {{1, 8}, Pierce}},
{"Dart", "����", 5 * �P, 1, {RangedWeapon}, {SimpleWeaponProficiency}, {Finesse, Thrown}, {{1, 4}, Pierce}},
{"Shortbow", "�������� ���", 25 * GP, 2, {RangedWeapon}, {SimpleWeaponProficiency}, {TwoHanded}, {{1, 6}, Pierce}},
{"Sling", "�����", 1 * SP, 0, {RangedWeapon}, {SimpleWeaponProficiency}, {}, {{1, 4}, Bludgeon}},
//
{"Battleaxe", "������ �����", 10 * GP, 4, {MeleeWeapon}, {MartialWeaponProfiency}, {Versatile}, {{1, 8}, Slashing}},
{"Flail", "���", 10 * GP, 2, {MeleeWeapon}, {MartialWeaponProfiency}, {}, {{1, 8}, Bludgeon}},
{"Greataxe", "������", 30 * GP, 7, {MeleeWeapon}, {MartialWeaponProfiency}, {Heavy, TwoHanded}, {{1, 12}, Slashing}},
{"Halberd", "������", 20 * GP, 6, {MeleeWeapon}, {MartialWeaponProfiency}, {Heavy, TwoHanded, Reach}, {{1, 10}, Slashing}},
{"Lance", "����", 10 * GP, 6, {MeleeWeapon}, {MartialWeaponProfiency}, {Reach}, {{1, 12}, Pierce}},
{"Longsword", "������� ���", 15 * GP, 3, {MeleeWeapon}, {MartialWeaponProfiency}, {Versatile}, {{1, 8}, Slashing}},
{"Maul", "����", 10 * GP, 10, {MeleeWeapon}, {MartialWeaponProfiency}, {Heavy, TwoHanded}, {{2, 6}, Bludgeon}},
{"Morningstar", "��������", 15 * GP, 4, {MeleeWeapon}, {MartialWeaponProfiency}, {}, {{1, 8}, Pierce}},
{"Pike", "����", 5 * GP, 18, {MeleeWeapon}, {MartialWeaponProfiency}, {Heavy, Reach, TwoHanded}, {{1, 10}, Pierce}},
{"Rapier", "������", 25 * GP, 2, {MeleeWeapon}, {MartialWeaponProfiency}, {Finesse}, {{1, 8}, Pierce}},
{"Scimitar", "��������", 25 * GP, 3, {MeleeWeapon, OffhandWeapon}, {MartialWeaponProfiency}, {Finesse}, {{1, 6}, Slashing}},
{"Shortsword", "�������� ���", 10 * GP, 2, {MeleeWeapon, OffhandWeapon}, {MartialWeaponProfiency}, {Finesse}, {{1, 6}, Pierce}},
{"Trident", "��������", 5 * GP, 4, {MeleeWeapon}, {MartialWeaponProfiency}, {Versatile, Thrown}, {{1, 6}, Pierce}},
{"Warhammer", "������ �����", 15 * GP, 2, {MeleeWeapon}, {MartialWeaponProfiency}, {Versatile}, {{1, 8}, Bludgeon}},
{"Whip", "����", 2 * GP, 3, {MeleeWeapon}, {MartialWeaponProfiency}, {Finesse, Reach}, {{1, 4}, Slashing}},
//
{"Crossbow Heavy", "������� �������", 50 * GP, 18, {RangedWeapon}, {MartialWeaponProfiency}, {Heavy, Loading, TwoHanded}, {{1, 10}, Pierce}},
{"Longbow", "������� ���", 50 * GP, 18, {RangedWeapon}, {MartialWeaponProfiency}, {Heavy, TwoHanded}, {{1, 8}, Pierce}},
{"Net", "����", 1 * GP, 3, {RangedWeapon}, {MartialWeaponProfiency}, {Thrown}},
//
{"Arrow", "������", 1 * GP, 1, {Ammunition}},
{"Bolts", "�����", 1 * GP, 2, {Ammunition}},
{"Stones", "�����", 4 * �P, 2, {Ammunition}},
//
{"Leather armor", "�������� �����", 10 * GP, 10, {Armor}, {LightArmorProficiency}, {}, {}, {1, 10}},
{"Padded Armor", "������ �����", 5 * GP, 8, {Armor}, {LightArmorProficiency}, {}, {}, {1, 10, 0, Stealth}},
{"Studded Leather armor", "��������� �������� �����", 45 * GP, 13, {Armor}, {LightArmorProficiency}, {}, {}, {2, 10}},
//
{"Hide", "�����", 10 * GP, 12, {Armor}, {MediumArmorProficiency}, {}, {}, {2, 2}},
{"Breastplate", "���������", 400 * GP, 20, {Armor}, {MediumArmorProficiency}, {}, {}, {4, 2}},
{"Half Plate", "��������", 750 * GP, 40, {Armor}, {MediumArmorProficiency}, {}, {}, {5, 2, 0, Stealth}},
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
};
getstr_enum(item);
assert_enum(item, Necklage);

bool item::is(item_feat_s id) const {
	return item_data[type].feats[0] == id
		|| item_data[type].feats[1] == id
		|| item_data[type].feats[2] == id;
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

const damage_info& item::getattack() const {
	return item_data[type].attack;
}

bool creature::isproficient(item_s it) const {
	if(item_data[it].proficiency[0] == NoFeat)
		return false;
	for(auto e : item_data[it].proficiency) {
		if(!e)
			break;
		if(is(e))
			return true;
	}
	return false;
}