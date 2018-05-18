#include "main.h"

struct skill {
	const char*			id;
	const char*			name;
	classa				allowed;
	testinfo			test;
} skill_data[] = {
	{"Pick Pockets", "������� �������", {Theif, Bard}, {TestSkill}},
	{"Open Locks", "���������� �����", {Theif}, {TestSkill}},
	{"Find/Remove Traps", "�������� �������", {Theif}, {TestSkill}},
	{"Move Silently", "��������� ����", {Theif, Ranger}, {TestSkill}},
	{"Hide in Shadows", "��������� � �����", {Theif, Ranger}, {TestSkill}},
	{"Detect Noise", "��������� �����", {Theif, Bard}, {TestSkill}},
	{"Climb Walls", "������ �� ������", {Theif, Bard}, {TestSkill}},
	{"Read Languages", "������ �����", {Theif, Bard}, {TestSkill}},
	//
	{"Open door", "������� �����",{},{TestSkill}},
	{"Getting lost", "���� ����������"},
	//
	{"Herbalism", "�������������", {Mage, Cleric, Druid}, {TestAbility, Wisdow}},
	{"Hunting", "�����", {Fighter, Paladin, Ranger}, {TestAbility, Wisdow}},
	{"Tracking", "������������", {Ranger}, {TestAbility, Wisdow}},
	//
	{"Go away", "����� ������"},
	{"Go inside", "����� ������"},
};
assert_enum(skill, GoInside);
getstr_enum(skill);

const classa& character::getclasses(skill_s id) {
	return skill_data[id].allowed;
}

const testinfo& character::getinfo(skill_s id) {
	return skill_data[id].test;
}