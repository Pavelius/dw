#include "main.h"

itemi bsmeta<itemi>::elements[] = {{"", ""},
{"Knife", "Нож", 25, 0, 5, {Weapon, Adventurer, Magician, Warrior, Elf, Dwarf}, {0, 0, W1p0}, {}},
{"Dagger", "Кинжал", 30, 0, 20, {Weapon, Adventurer, Warrior, Elf, Dwarf}, {0, 0, W1p1}, {}},
{"HeavyDagger", "Тяжелый кинжал", 35, 0, 30, {Weapon, Adventurer, Warrior, Elf, Dwarf}, {0, 0, W1p2}, {}},
{"Rapier", "Рапира", 90, 0, 60, {Weapon, Adventurer, Warrior, Elf}, {0, 0, W1p3}, {}},
{"Staff", "Посох", 150, 0, 25, {Weapon, TwoHanded, Adventurer, Magician, Warrior, Elf}, {0, 0, W1p1}, {}},
{"Club", "Дубина", 80, 0, 1, {Weapon, Adventurer, Magician, Warrior, Elf, Dwarf}, {0, 0, W1p1}, {}},
{"Mace", "Булава", 80, 0, 15, {Weapon, Adventurer, Warrior, Elf, Dwarf}, {0, 0, W1p2}, {}},
{"Saber", "Сабля", 90, 0, 60, {Weapon, Adventurer, Warrior, Elf, Dwarf}, {0, 0, W1p3}, {}},
{"AxeBattle", "Боевой топор", 90, 0, 50, {Weapon, Adventurer, Warrior, Dwarf}, {0, 0, W1p4}, {}},
{"Sword", "Меч", 95, 0, 100, {Weapon, Adventurer, Warrior, Elf}, {0, 0, W1p4}, {}},
{"SwordTwoHanded", "Двуручный меч", 155, 0, 180, {Weapon, TwoHanded, Warrior}, {0, 0, W2p4}, {}},
{"Bow", "", 0, 0, 0, {Weapon, TwoHanded, Ranged, Adventurer, Elf, Warrior}, {0, 0, W1p0}, {}},
{"Crossbow", "", 0, 0, 0, {Weapon, TwoHanded, Ranged, Adventurer, Dwarf, Warrior}, {0, 0, W1p0}, {}},
{"Arrows", "", 0, 0, 0, {Weapon}, {}, {}},
{"Bolts", "", 0, 0, 0, {Weapon}, {}, {}},
//
{"ClothingSilk", "Одежда", 0, 0, 0, {Armor, Adventurer, Magician, Warrior, Elf, Dwarf}, {}, {1}},
{"ClothingRobe", "Роба", 0, 0, 0, {Armor, Adventurer, Magician, Warrior, Elf, Dwarf}, {}, {1}},
{"ClothingHard", "Ватник", 0, 0, 0, {Armor, Adventurer, Warrior, Elf, Dwarf}, {}, {2}},
{"ClothingWinter", "Зимняя одежда", 0, 0, 0, {Armor, Adventurer, Magician, Warrior, Elf, Dwarf}, {}, {2}},
{"ArmourLeather", "Кожаная куртка", 0, 0, 0, {Armor, Adventurer, Warrior, Elf, Dwarf}, {}, {3}},
{"ArmourChain", "Кольчуга", 0, 0, 0, {Armor, Adventurer, Warrior, Dwarf}, {}, {4}},
{"ArmourScale", "Чешуйчатый доспех", 0, 0, 0, {Armor, Warrior, Dwarf}, {}, {5}},
{"ArmourPlate", "Латы", 0, 0, 0, {Armor, Warrior}, {}, {6}},
};
assert_enum(item, ArmourPlate);

int	item::get(parameter_s v) const {
	switch(v) {
	case RS: return getinfo().armor.rs;
	default: return 0;
	}
}