#include "main.h"

itemi bsmeta<itemi>::elements[] = {{"", ""},
{"Knife", "���", 25, 0, 5, Weapon, {0, 0, W1p0}, {}},
{"Dagger", "������", 30, 0, 20, Weapon, {0, 0, W1p1}, {}},
{"HeavyDagger", "������� ������", 35, 0, 30, Weapon, {0, 0, W1p2}, {}},
{"Rapier", "������", 90, 0, 60, Weapon, {0, 0, W1p3}, {}},
{"Staff", "�����", 150, 0, 25, Weapon, {0, 0, W1p1}, {}},
{"Club", "������", 80, 0, 1, Weapon, {0, 0, W1p1}, {}},
{"Mace", "������", 80, 0, 15, Weapon, {0, 0, W1p2}, {}},
{"Saber", "�����", 90, 0, 60, Weapon, {0, 0, W1p3}, {}},
{"AxeBattle", "������ �����", 90, 0, 50, Weapon, {0, 0, W1p4}, {}},
{"Sword", "���", 95, 0, 100, Weapon, {0, 0, W1p4}, {}},
{"SwordTwoHanded", "��������� ���", 155, 0, 180, Weapon, {0, 0, W2p4}, {}},
{"Bow", "", 0, 0, 0, Weapon, {0, 0, W1p0}, {}},
{"Crossbow", "", 0, 0, 0, Weapon, {0, 0, W1p0}, {}},
{"Arrows", "", 0, 0, 0, Weapon, {}, {}},
{"Bolts", "", 0, 0, 0, Weapon, {}, {}},
//
{"ClothingSilk", "������", 0, 0, 0, Armor, {}, {1}},
{"ClothingRobe", "����", 0, 0, 0, Armor, {}, {1}},
{"ClothingHard", "������", 0, 0, 0, Armor, {}, {2}},
{"ClothingWinter", "������ ������", 0, 0, 0, Armor, {}, {2}},
{"ArmourLeather", "������� ������", 0, 0, 0, Armor, {}, {3}},
{"ArmourChain", "��������", 0, 0, 0, Armor, {}, {4}},
{"ArmourScale", "���������� ������", 0, 0, 0, Armor, {}, {5}},
{"ArmourPlate", "����", 0, 0, 0, Armor, {}, {6}},
};
assert_enum(item, ArmourPlate);