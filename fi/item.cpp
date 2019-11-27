#include "main.h"

static_assert(sizeof(item) == 4, "sizeof(item) is greater that sizeof(int)");

itemi bsmeta<itemi>::elements[] = {{"Hand", "����", 0, Hand, 0, {Arm, 0, 1}, {Blunt}},
{"Knife", "���", 1, Hand, 1, {Arm, 1, 1, KnifeFighter}, {Light, Pointed}},
{"Dagger", "������", 2, Hand, 1, {Arm, 1, 1, KnifeFighter}, {Light, Edged, Pointed}},
{"Falchion", "������", 4, Hand, 1, {Arm, 1, 2, KnifeFighter}, {Edged, Pointed}},
{"Shortsword", "�������� ���", 6, Hand, 2, {Arm, 1, 1, SwordFighter}, {Edged, Pointed, Parrying}},
{"Broadsword", "���", 10, Hand, 2, {Arm, 1, 2, SwordFighter}, {Edged, Pointed, Parrying}},
{"Longsword", "������� ���", 18, Hand, 2, {Arm, 1, 2, SwordFighter}, {Heavy, Edged, Pointed, Parrying}},
{"TwoHandedSword", "��������� ���", 40, Hand, 2, {Arm, 2, 3, SwordFighter}, {Heavy, Edged, Pointed, Parrying}},
{"Scimitar", "�����", 8, Hand, 1, {Arm, 1, 2, SwordFighter}, {Edged, Pointed, Hook, Parrying}},
{"Handaxe", "�����", 2, Hand, 2, {Arm, 1, 2, AxeFighter}, {Edged, Hook}},
{"Battleaxe", "������ �����", 6, Hand, 2, {Arm, 1, 2, AxeFighter}, {Heavy, Edged, Hook}},
{"TwoHandedAxe", "��������� �����", 18, Hand, 2, {Arm, 2, 3, AxeFighter}, {Heavy, Edged, Hook}},
{"Mace", "������", 4, Hand, 2, {Arm, 1, 1, HammerFighter}, {Blunt}},
{"Morningstar", "��������", 8, Hand, 2, {Arm, 1, 2, HammerFighter}, {Blunt}},
{"Warhammer", "������ �����", 12, Hand, 2, {Arm, 1, 2, HammerFighter}, {Blunt, Hook}},
{"Flail", "���", 16, Hand, 1, {Arm, 1, 2, HammerFighter}, {Blunt}},
{"WoodenClub", "������", 1, Hand, 1, {Arm, 1, 1, HammerFighter}, {Blunt}},
{"LargeWoodenClub", "������� ������", 2, Hand, 1, {Arm, 2, 2, HammerFighter}, {Heavy, Blunt}},
{"HeavyHammer", "������� �����", 22, Hand, 2, {Arm, 2, 3, HammerFighter}, {Heavy, Blunt, Hook}},
{"Staff", "�����", 1, Hand, 1, {Near, 2, 1, HammerFighter}, {Blunt, Hook, Parrying}},
{"ShortSpear", "�����", 2, Hand, 1, {Near, 1, 1, SpearFighter}, {Pointed}},
{"LongSpear", "������� �����", 4, Hand, 2, {Near, 2, 1, SpearFighter}, {Pointed}},
{"Pike", "����", 12, Hand, 2, {Near, 2, 2, SpearFighter}, {Heavy, Pointed}},
{"Halberd", "��������", 30, Hand, 2, {Near, 2, 2, SpearFighter}, {Heavy, Pointed, Edged, Hook}},
{"Trident", "��������", 6, Hand, 1, {Near, 2, 2, SpearFighter}, {Pointed, Hook}},
//
{"Rock", "������", 0, Hand, 0, {Short, 1, 1}, {Light}},
{"ThrovingKnife", "����������� ���", 1, Hand, 1, {Short, 1, 1}, {Light}},
{"ThrovingAxe", "����������� �����", 2, Hand, 1, {Short, 1, 2}, {}},
{"ThrovingSpear", "����������� �����", 3, Hand, 2, {Short, 1, 1}, {}},
{"Sling", "�����", 1, Hand, 1, {Short, 1, 1}, {Light}},
{"ShortBow", "���", 6, Hand, 2, {Short, 2, 1}, {Light}},
{"LongBow", "������� ���", 12, Hand, 2, {Long, 2, 1}, {}},
{"LightCrossbow", "�������", 24, Hand, 1, {Long, 2, 2}, {Reload}},
{"HeavyCrossbow", "������� �������", 40, Hand, 1, {Long, 2, 3}, {Light, Reload}},
//
{"LeatherArmor", "�������� �����", 3, Body, 2, {}, {Light}},
{"StuddedLeather", "��������� �����", 5, Body, 3, {}, {}},
{"Chainmail", "��������", 24, Body, 6, {}, {Heavy, PointedVulnerable}},
{"Platemail", "����", 80, Body, 8, {}, {Heavy, MovePenalty}},
{"StuddedLeatherCap", "��������� ����", 2, Head, 1, {}, {Light}},
{"OpenHelmet", "�������� ����", 8, Head, 2, {}, {Light}},
{"ClosedHelmet", "�������� ����", 18, Head, 3, {}, {}},
{"GreatHelm", "������ ����", 30, Head, 4, {}, {ScoutPenalty}},
{"SmallShield", "���", 6, LeftHand, 1, {}, {Light}},
{"LargeShield", "������� ���", 16, LeftHand, 2, {}, {}},
//
{"Arrows", "", 16, Quiver, 2, {}, {}},
{"GrapplingHook", "", 0, Gear, 0, {}, {}},
{"Rope", "", 0, Gear, 0, {}, {}},
{"TallonCandle", "", 0, Gear, 0, {}, {}},
{"OilLamp", "", 0, Gear, 0, {}, {}},
{"Lantern", "", 0, Gear, 0, {}, {}},
{"Torches", "", 0, Gear, 0, {}, {}},
{"Waterskin", "", 0, Gear, 0, {}, {}},
{"Bandages", "", 0, Gear, 0, {}, {}},
{"LampOil", "", 0, Gear, 0, {}, {}},
{"InkAndQuil", "", 0, Gear, 0, {}, {}},
{"Parchment", "", 0, Gear, 0, {}, {}},
{"Blanket", "", 0, Gear, 0, {}, {}},
{"SleepingFur", "", 0, Gear, 0, {}, {}},
{"FlintAndSteel", "", 0, Gear, 0, {}, {}},
{"FieldRations", "", 0, Gear, 0, {}, {}},
{"Lute", "", 0, Gear, 0, {}, {}},
{"Flute", "", 0, Gear, 0, {}, {}},
//
{"CooperPiece", "", 0, Gear, 0, {}, {}},
{"SilverPiece", "", 1, Gear, 0, {}, {}},
{"GoldPiece", "", 10, Gear, 0, {}, {}},
};
assert_enum(item, GoldPiece);

item::item(item_s t) : type(t), resource(D6), count(0) {
	bonus = bsmeta<itemi>::elements[type].bonus;
	origin_bonus = bsmeta<itemi>::elements[type].bonus;
}

item::item(item_s t, unsigned char count) : type(t), resource(D6), count(count) {
	bonus = bsmeta<itemi>::elements[type].bonus;
	origin_bonus = bsmeta<itemi>::elements[type].bonus;
}

int	item::getcost() const {
	return bsmeta<itemi>::elements[type].cost;
}

bool item::is(feature_s v) const {
	return bsmeta<itemi>::elements[type].flags.is(v);
}

slot_s item::getslot() const {
	return bsmeta<itemi>::elements[type].slot;
}

void item::repair(int value) {
	if(value == 0)
		return;
	if(bonus + value < 0)
		bonus = 0;
	else if(bonus + value > origin_bonus)
		bonus = origin_bonus;
	else
		bonus += value;
}

int	item::getartifact() const {
	static int artifact_dice[] = {0, 8, 10, 12};
	return artifact_dice[magic];
}

const char* item::getname() const {
	return bsmeta<itemi>::elements[type].name;
}