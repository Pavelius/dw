#include "main.h"

itemi bsmeta<itemi>::elements[] = {{"NoItem", "��� ��������"},
//
{"Club", "������", "", 1 * SP, 2, OffhandWeapon, {SimpleWeaponProficiency}, {}, {1, 8, 0, Bludgeon}},
{"Dagger", "������", "", 2 * GP, 1, OffhandWeapon, {SimpleWeaponProficiency}, {Finesse, Thrown}, {1, 4, 0, Pierce}},
{"Greatclub", "������", "", 2 * SP, 10, MeleeWeapon, {SimpleWeaponProficiency}, {TwoHanded}, {1, 8, 0, Bludgeon}},
{"Handaxe", "�����", "", 5 * GP, 2, OffhandWeapon, {SimpleWeaponProficiency}, {}, {1, 6, 0, Slashing}},
{"Javelin", "������", "", 5 * SP, 2, MeleeWeapon, {SimpleWeaponProficiency}, {Thrown}, {1, 6, 0, Pierce}},
{"LightHammer", "�������", "", 2 * SP, 2, MeleeWeapon, {SimpleWeaponProficiency}, {Thrown}, {1, 4, 0, Bludgeon}},
{"Mace", "������", "", 5 * GP, 4, MeleeWeapon, {SimpleWeaponProficiency}, {}, {1, 6, 0, Bludgeon}},
{"Quaterstaff", "�����", "", 2 * SP, 4, MeleeWeapon, {SimpleWeaponProficiency}, {Versatile}, {1, 6, 0, Bludgeon}},
{"Spear", "�����", "", 1 * GP, 3, MeleeWeapon, {SimpleWeaponProficiency}, {Versatile}, {1, 6, 0, Pierce}},
//
{"Light Crossbow", "������ �������", "", 25 * GP, 5, RangedWeapon, {SimpleWeaponProficiency}, {TwoHanded, Loading}, {1, 8, 0, Pierce}},
{"Dart", "����", "", 0, 1, RangedWeapon, {SimpleWeaponProficiency}, {Finesse, Thrown}, {1, 4, 0, Pierce}},
{"Shortbow", "�������� ���", "", 25 * GP, 2, RangedWeapon, {SimpleWeaponProficiency, ElfWeaponTrain}, {TwoHanded}, {1, 6, 0, Pierce}},
{"Sling", "�����", "", 1 * SP, 0, RangedWeapon, {SimpleWeaponProficiency}, {}, {1, 4, 0, Bludgeon}},
//
{"Battleaxe", "������ �����", "", 10 * GP, 4, MeleeWeapon, {MartialWeaponProfiency}, {Versatile}, {1, 8, 0, Slashing}},
{"Flail", "���", "", 10 * GP, 2, MeleeWeapon, {MartialWeaponProfiency}, {}, {1, 8, 0, Bludgeon}},
{"Greataxe", "������", "", 30 * GP, 7, MeleeWeapon, {MartialWeaponProfiency}, {Heavy, TwoHanded}, {1, 12, 0, Slashing}},
{"Halberd", "��������", "", 20 * GP, 6, MeleeWeapon, {MartialWeaponProfiency}, {Heavy, TwoHanded, Reach}, {1, 10, 0, Slashing}},
{"Lance", "������������� ����", "", 10 * GP, 6, MeleeWeapon, {MartialWeaponProfiency}, {Reach}, {1, 12, 0, Pierce}},
{"Longsword", "������� ���", "", 15 * GP, 3, MeleeWeapon, {MartialWeaponProfiency, ElfWeaponTrain}, {Versatile}, {1, 8, 0, Slashing}},
{"Maul", "����", "", 10 * GP, 10, MeleeWeapon, {MartialWeaponProfiency}, {Heavy, TwoHanded}, {2, 6, 0, Bludgeon}},
{"Morningstar", "��������", "", 15 * GP, 4, MeleeWeapon, {MartialWeaponProfiency}, {}, {1, 8, 0, Pierce}},
{"Pike", "����", "", 5 * GP, 18, MeleeWeapon, {MartialWeaponProfiency}, {Heavy, Reach, TwoHanded}, {1, 10, 0, Pierce}},
{"Rapier", "������", "", 25 * GP, 2, MeleeWeapon, {MartialWeaponProfiency}, {Finesse}, {1, 8, 0, Pierce}},
{"Scimitar", "��������", "", 25 * GP, 3, OffhandWeapon, {MartialWeaponProfiency}, {Finesse}, {1, 6, 0, Slashing}},
{"Shortsword", "�������� ���", "", 10 * GP, 2, OffhandWeapon, {MartialWeaponProfiency, ElfWeaponTrain}, {Finesse}, {1, 6, 0, Pierce}},
{"Trident", "��������", "", 5 * GP, 4, MeleeWeapon, {MartialWeaponProfiency}, {Versatile, Thrown}, {1, 6, 0, Pierce}},
{"Warhammer", "������ �����", "", 15 * GP, 2, MeleeWeapon, {MartialWeaponProfiency}, {Versatile}, {1, 8, 0, Bludgeon}},
{"Whip", "����", "", 2 * GP, 3, MeleeWeapon, {MartialWeaponProfiency}, {Finesse, Reach}, {1, 4, 0, Slashing}},
//
{"CrossbowHeavy", "������� �������", "", 50 * GP, 18, RangedWeapon, {MartialWeaponProfiency}, {Heavy, Loading, TwoHanded}, {1, 10, 0, Pierce}},
{"Longbow", "������� ���", "", 50 * GP, 18, RangedWeapon, {MartialWeaponProfiency, ElfWeaponTrain}, {Heavy, TwoHanded}, {1, 8, 0, Pierce}},
{"Net", "����", "", 1 * GP, 3, RangedWeapon, {MartialWeaponProfiency}, {Thrown}},
//
{"Arrow", "������", "", 1 * GP, 1, Ammunition},
{"Bolts", "�����", "", 1 * GP, 2, Ammunition},
{"Stones", "�����", "", 0, 2, Ammunition},
//
{"LeatherArmor", "������� �����", "", 10 * GP, 10, Armor, {LightArmorProficiency}, {}, {}, {1, 10}},
{"PaddedArmor", "�������� �����", "", 5 * GP, 8, Armor, {LightArmorProficiency}, {}, {}, {1, 10, 0, Stealth}},
{"StuddedLeatherArmor", "��������� ������� �����", "", 45 * GP, 13, Armor, {LightArmorProficiency}, {}, {}, {2, 10}},
//
{"Hide", "�����", "", 10 * GP, 12, Armor, {MediumArmorProficiency}, {}, {}, {2, 2}},
{"Breastplate", "���������", "", 400 * GP, 20, Armor, {MediumArmorProficiency}, {}, {}, {4, 2}},
{"HalfPlate", "����-����", "", 750 * GP, 40, Armor, {MediumArmorProficiency}, {}, {}, {5, 2, 0, Stealth}},
{"ChainShirt", "���������� ������", "", 50 * GP, 20, Armor, {MediumArmorProficiency}, {}, {}, {3, 2}},
{"ScaleMail", "���������� ������", "", 50 * GP, 45, Armor, {MediumArmorProficiency}, {}, {}, {4, 2, 0, Stealth}},
//
{"RingMail", "��������� ������", "", 30 * GP, 40, Armor, {HeavyArmorProficiency}, {}, {}, {4, 0, 0, Stealth}},
{"Plate", "����", "", 1500 * GP, 65, Armor, {HeavyArmorProficiency}, {}, {}, {8, 0, 15, Stealth}},
{"ChainMail", "���������� ������", "", 75 * GP, 55, Armor, {HeavyArmorProficiency}, {}, {}, {6, 0, 13, Stealth}},
{"SplintMail", "��������� ������", "", 200 * GP, 60, Armor, {HeavyArmorProficiency}, {}, {}, {7, 0, 15, Stealth}},
//
{"Shield", "���", "", 10 * GP, 6, OffhandWeapon, {ShieldProficiency}, {}, {}, {2}},
{"Helmet", "����", "", 10 * GP, 1, Head},
{"Bracers", "��������", "", 10 * GP, 1, Elbow},
{"Ring", "������", "", 10 * GP, 0, RightFinger},
{"Necklage", "��������", "", 10 * GP, 0, Neck},
//
{"Bedroll", "���������� ��������������", "", 1 * GP, 7},
{"Book", "�����", "", 5 * GP, 2},
{"ComponentsPounch", "������� � ������������", "", 1 * GP, 1},
{"Crowbar", "�����", "", 2 * GP, 5},
{"HolySymbol", "��������� ������", "", 1 * SP, 1},
{"Map", "�����", "", 2 * GP, 0},
{"Parchment", "���������", "", 1 * SP, 0, {}, {}, {}, {}, {}},
{"Ration", "��������", "", 2 * SP, 4, {}, {}, {}, {}, {}},
{"Rope", "�������", "", 1 * GP, 10},
{"Spellbook", "����� ����������", "", 10 * GP, 2},
{"Torches", "������", "", 1 * SP, 2, {}, {}, {}, {}, {}},
{"Waterskin", "������", "", 2 * SP, 5, {}, {}, {}, {}, {}},
//
{"Dices", "������", "", 1 * SP},
{"PlayingCards", "��������� �����", "", 5 * SP},
//
{"Flute", "������", "", 2 * GP, 1},
{"Lute", "�����", "", 35 * GP, 2},
//
{"AlchemistSupplies", "������������ ����������", "", 50 * GP, 8},
{"BrewerSupplies", "�������", "", 20 * GP, 9},
{"CalligrapherSupplies", "���������", "", 10 * GP, 5},
{"CarpenterTools", "����������� ��������", "", 8 * GP, 6},
{"CartographerTools", "", "", 15 * GP, 6},
{"CobblerTools", "", "", 5 * GP, 5},
{"CookUtensils", "��������", "", 1 * GP, 8},
{"GlassblowerTools", "", "", 30 * GP, 5},
{"JewelerTools", "����", "", 25 * GP, 2},
{"LeatherworkerTools", "", "", 5 * GP, 5},
{"MasonTools", "������", "", 10 * GP, 8},
{"PainterSupplies", "�������� � ������", "", 10 * GP, 5},
{"PotterTools", "", "", 10 * GP, 3},
{"SmithTools", "�������", "", 20 * GP, 8},
{"TinkerTools", "�����", "", 50 * GP, 10},
{"WeaverTools", "���� � �����", "", 1 * GP, 5},
{"WoodcarverTools", "�����", "", 1 * GP, 5},
//
{"DisguiseKit", "��������� ����", "", 25 * GP, 3},
{"ForgeryKit", "���� � ��������", "", 15 * GP, 5},
{"HerbalismKit", "������� � �������", "", 5 * GP, 3},
{"NavigatorTools", "������", "", 25 * GP, 2},
{"PoisonerTools", "����� �������� �����������", "", 50 * GP, 2},
{"TheifTools", "������� � ����", "", 2 * GP, 5},
//
{"ScrollOfBless", "������", "", 20 * GP, 0, Readable, {}, {}, {}, {}},
{"PotionOfHealing", "�����", "�������", 25 * GP, 5, Drinkable, {}, {}, {}, {}},
};
assert_enum(item, LastItem);

void item::addname(stringbuilder& sb) const {
	sb.add(bsmeta<itemi>::elements[type].name);
}

void item::addnameby(stringbuilder& sb) const {
	sb.addby(bsmeta<itemi>::elements[type].name);
}

void item::addnamewh(stringbuilder& sb) const {
	sb.addby(bsmeta<itemi>::elements[type].name);
}

bool item::is(feat_s id) const {
	return bsmeta<itemi>::elements[type].proficiency.is(id);
}

bool item::is(item_feat_s id) const {
	return getei().feats.is(id);
}

bool item::is(wear_s id) const {
	return getei().wears == id;
}

bool item::islight() const {
	return getei().wears == OffhandWeapon;
}

int	item::getcost() const {
	return getei().cost;
}

const dice& item::getattack() const {
	return getei().attack;
}

bool creature::isproficient(item_s it) const {
	if(feats.is(bsmeta<itemi>::elements[it].proficiency))
		return true;
	return false;
}

int item::getcount() const {
	if(iscountable())
		return 1 + charges;
	return 1;
}

void item::setcount(int v) {
	if(!v)
		clear();
	else if(iscountable()) {
		if(v > 32)
			v = 32;
		charges = v - 1;
	}
}

void item::consume() {
	auto& ei = getei();
	if(ischargeable()) {
		if(charges == 1) {
			charges = 0;
			if(d100() < 5)
				clear();
		} else {
		}
	} else if(iscountable())
		setcount(getcount() - 1);
}

void item::clear() {
	memset(this, 0, sizeof(*this));
}