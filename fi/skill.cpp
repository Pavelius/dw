#include "main.h"

static struct skill_info {
	const char*			id;
	const char*			name;
	ability_s			attribute;
} skill_data[] = {{"Might", "����", Strenght},
{"Endurance", "������������", Strenght},
{"Melee", "����������", Strenght},
{"Crafting", "��������", Strenght},
{"Stealth", "����������", Agility},
{"SleightOfHand", "�������� ���", Agility},
{"Move", "��������", Agility},
{"Marksmanship", "��������", Agility},
{"Scouting", "��������", Wits},
{"Lore", "������", Wits},
{"Survival", "���������", Wits},
{"Insight", "����������������", Wits},
{"Manipulation", "�����������", Empathy},
{"Performance", "�����������", Empathy},
{"Healing", "�������", Empathy},
{"AnimalHandling", "��������� � ���������", Empathy},
};
getstr_enum(skill);
assert_enum(skill, AnimalHandling);