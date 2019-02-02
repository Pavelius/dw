#include "main.h"

static struct skill_info {
	const char*			id;
	const char*			name;
} skill_data[] = {{"Might", "����"},
{"Endurance", "������������"},
{"Melee", "����������"},
{"Crafting", "��������"},
{"Stealth", "����������"},
{"SleightOfHand", "�������� ���"},
{"Move", "��������"},
{"Marksmanship", "��������"},
{"Scouting", "��������"},
{"Lore", "������"},
{"Survival", "���������"},
{"Insight", "����������������"},
{"Manipulation", "�����������"},
{"Performance", "�����������"},
{"Healing", "�������"},
{"AnimalHandling", "��������� � ���������"},
};
getstr_enum(skill);
assert_enum(skill, AnimalHandling);
