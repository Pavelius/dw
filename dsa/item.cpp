#include "main.h"

itemi bsmeta<itemi>::elements[] = {{"", ""},
{"Knife", "���", 25, 0, 5, Weapon, {0, 0, {1}}, {}},
{"Dagger", "������", 30, 0, 20, Weapon, {0, 0, {1, 1}}, {}},
{"HeavyDagger", "������� ������", 35, 0, 30, Weapon, {0, 0, {1, 2}}, {}},
{"Rapier", "������", 90, 0, 60, Weapon, {0, 0, {1, 3}}, {}},
{"Staff", "�����", 150, 0, 25, Weapon, {0, 0, {1,1}}, {}},
{"Club", "������", 80, 0, 1, Weapon, {0, 0, {1, 1}}, {}},
{"Mace", "������", 80, 0, 15, Weapon, {0, 0, {1, 2}}, {}},
{"Saber", "�����", 90, 0, 60, Weapon, {0, 0, {1, 3}}, {}},
{"AxeBattle", "������ �����", 90, 0, 50, Weapon, {0, 0, {1, 4}}, {}},
{"Sword", "���", 95, 0, 100, Weapon, {0, 0, {1, 4}}, {}},
{"SwordTwoHanded", "��������� ���", 155, 0, 180, Weapon, {0, 0, {2, 4}}, {}},
{"Bow", "", 0, 0, 0, Weapon, {0, 0, {1}}, {}},
{"Crossbow", "", 0, 0, 0, Weapon, {0, 0, {1}}, {}},
{"Arrows", "", 0, 0, 0, Weapon, {}, {}},
{"Bolts", "", 0, 0, 0, Weapon, {}, {}},
};
assert_enum(item, Bolts);