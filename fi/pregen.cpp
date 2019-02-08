#include "main.h"

struct attack_context {
	attack_info*		attack;
	character*			monster;
	character*			enemy;
	int					value;
};
struct pregen_info {
	const char*			id;
	const char*			name;
	race_s				race;
	profession_s		profession;
	char				ability[4];
	adat<skill_set, 8>	skills;
	item_s				gear[8];
	char				movement;
	char				natural_armor;
	attack_info*		attacks;
};
static attack_info worm_attack[6] = {{"����� ��� ������ �������� ��� ������ � ������� ����� ��������� �� %�����.", SlashAttack | ThrowNear, 8, 2},
{"������ ������������ ��� ������ � ������ ������ ������ ���.", AffectNear | AffectAll | Fear, 5, 0},
{"���������� ����� ������� � ���� �������� ������ ����� �������� ������ � � ������ ����������� ����� �� ������ ������.", AffectAll | AffectNear | MoveSave | DropDown, 12, 1, DropDown},
{"���������� ����� ������ �������� ����� � ��������� ���������� %�����.", AffectStrongest | MoveSave | Devoure, 10, 1},
{"������ ������ ���������� ������� �������� ����� ������� ����� ���� ������ ������.", AffectAll | AffectNear | DropDown, 12, 1},
{"�������� ������ ����� ��������� � ����� ���� ��� �����. ����� ��� ������ ������ ������� ���� � ��� ����� � �������� ���.", AffectAll | AffectNear | Falling, 0, 0, 0, {2, 12}},
};
static attack_info dragon_attack[6] = {{"������ ��������� ����� � ��������� � ���� �� �����.", SlashAttack | AffectTwo, 10, 2},
{"������ ����� ��������������� ���, ������� ������ �� ������ ���������� ������.", AffectNear | AffectAll | Fear, 8, 0},
{"������ ����� �������� ������ ��������, ������ ������ �����.", AffectAll | AffectNear | NoDodge | DropDown, 8, 1},
{"������ ������� ��� � �������� ����� ���� �� ������ �������� �����.", AffectStrongest | AffectShort | FireAttack, 12, 1},
{"������ ����� ����������� ����� ���� ����� ������� �������.", AffectAll | AffectNear | DropDown, 8, 1},
{"������ ������� ��� ����� ��� � ����� �������� ��� �����. �� ����� �������� ����� ��������� �� - ������ ���� ������� �����.", AffectAll | AffectShort | FireAttack | SingleUse, 2, 12, 0, {2, 12}},
};
pregen_info pregen_data[] = {{""},
{"Aliander", "����������", Human, Fighter, {3, 3, 3, 3}, {{Melee, 2}, {Move, 2}, {Marksmanship, 2}, {Healing, 1}}, {Shortsword, ShortBow}},
{"Frailer", "�������", HalfElf, Druid, {2, 3, 4, 4}, {{Lore, 2}, {Insight, 2}, {Manipulation, 2}}, {Dagger}},
{"Bear", "�������", Animal, Fighter, {6, 2}, {{Melee, 3}, {Scouting, 3}}},
{"Wolf", "����", Animal, Fighter, {4, 4}, {{Move, 3}, {Melee, 3}, {Scouting, 5}}},
//
{"YoungWorm", "������� �����", Monster, Fighter, {14, 2}, {}, {}, 1, 0, worm_attack},
{"OldWorm", "������� �����", Monster, Fighter, {18, 2}, {}, {}, 1, 0, worm_attack},
{"Dragon", "������", Monster, Fighter, {32, 4, 4, 2}, {{Scouting, 2}, {Lore, 2}, {Insight, 2}, {Manipulation, 2}}, {}, 3, 8, dragon_attack},
{"LargeDragon", "�������� ������", Monster, Fighter, {48, 4, 6, 2}, {{Scouting, 3}, {Lore, 3}, {Insight, 4}, {Manipulation, 3}}, {}, 3, 12, dragon_attack},
};
assert_enum(pregen, LargeDragon);

void character::create(pregen_s id) {
	clear();
	race = pregen_data[id].race;
	profession = pregen_data[id].profession;
	memcpy(ability, pregen_data[id].ability, sizeof(ability));
	memcpy(ability_damage, ability, sizeof(ability));
	for(auto& e : pregen_data[id].skills)
		set(e.type, e.value);
}