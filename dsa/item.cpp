#include "main.h"

itemi bsmeta<itemi>::elements[] = {{"", ""},
{"Knife", "���", 25, 0, 5, {Weapon, Adventurer, Magician, Warrior, Elf, Dwarf}, {0, 0, W1p0}, {}},
{"Dagger", "������", 30, 0, 20, {Weapon, Adventurer, Warrior, Elf, Dwarf}, {0, 0, W1p1}, {}},
{"HeavyDagger", "������� ������", 35, 0, 30, {Weapon, Adventurer, Warrior, Elf, Dwarf}, {0, 0, W1p2}, {}},
{"Rapier", "������", 90, 0, 60, {Weapon, Adventurer, Warrior, Elf}, {0, 0, W1p3}, {}},
{"Staff", "�����", 150, 0, 25, {Weapon, TwoHanded, Adventurer, Magician, Warrior, Elf}, {0, 0, W1p1}, {}},
{"Club", "������", 80, 0, 1, {Weapon, Adventurer, Magician, Warrior, Elf, Dwarf}, {0, 0, W1p1}, {}},
{"Mace", "������", 80, 0, 15, {Weapon, Adventurer, Warrior, Elf, Dwarf}, {0, 0, W1p2}, {}},
{"Saber", "�����", 90, 0, 60, {Weapon, Adventurer, Warrior, Elf, Dwarf}, {0, 0, W1p3}, {}},
{"AxeBattle", "������ �����", 90, 0, 50, {Weapon, Adventurer, Warrior, Dwarf}, {0, 0, W1p4}, {}},
{"Sword", "���", 95, 0, 100, {Weapon, Adventurer, Warrior, Elf}, {0, 0, W1p4}, {}},
{"SwordTwoHanded", "��������� ���", 155, 0, 180, {Weapon, TwoHanded, Warrior}, {0, 0, W2p4}, {}},
{"Bow", "", 0, 0, 0, {Weapon, TwoHanded, Ranged, Adventurer, Elf, Warrior}, {0, 0, W1p0}, {}},
{"Crossbow", "", 0, 0, 0, {Weapon, TwoHanded, Ranged, Adventurer, Dwarf, Warrior}, {0, 0, W1p0}, {}},
{"Arrows", "", 0, 0, 0, {Weapon}, {}, {}},
{"Bolts", "", 0, 0, 0, {Weapon}, {}, {}},
//
{"ClothingSilk", "������", 0, 0, 0, {Armor, Adventurer, Magician, Warrior, Elf, Dwarf}, {}, {1}},
{"ClothingRobe", "����", 0, 0, 0, {Armor, Adventurer, Magician, Warrior, Elf, Dwarf}, {}, {1}},
{"ClothingHard", "������", 0, 0, 0, {Armor, Adventurer, Warrior, Elf, Dwarf}, {}, {2}},
{"ClothingWinter", "������ ������", 0, 0, 0, {Armor, Adventurer, Magician, Warrior, Elf, Dwarf}, {}, {2}},
{"ArmourLeather", "������� ������", 0, 0, 0, {Armor, Adventurer, Warrior, Elf, Dwarf}, {}, {3}},
{"ArmourChain", "��������", 0, 0, 0, {Armor, Adventurer, Warrior, Dwarf}, {}, {4}},
{"ArmourScale", "���������� ������", 0, 0, 0, {Armor, Warrior, Dwarf}, {}, {5}},
{"ArmourPlate", "����", 0, 0, 0, {Armor, Warrior}, {}, {6}},
};
assert_enum(item, ArmourPlate);

int	item::get(parameter_s v) const {
	switch(v) {
	case RS: return getinfo().armor.rs;
	default: return 0;
	}
}