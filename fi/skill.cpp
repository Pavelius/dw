#include "main.h"

skilli bsmeta<skilli>::elements[] = {{"Might", "����", Strenght},
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
assert_enum(skill, AnimalHandling);

ability_s character::getkey(skill_s id) {
	return bsmeta<skilli>::elements[id].attribute;
}