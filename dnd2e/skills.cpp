#include "main.h"

struct skill {
	const char*		id;
	const char*		name;
	classa			allowed;
} skill_data[] = {
	{"Pick Pockets", "������� �������", {Theif}},
	{"Open Locks", "���������� �����", {Theif}},
	{"Find/Remove Traps", "�������� �������", {Theif}},
	{"Move Silently", "��������� ����", {Theif, Ranger}},
	{"Hide in Shadows", "��������� � �����", {Theif, Ranger}},
	{"Detect Noise", "��������� �����", {Theif}},
	{"Climb Walls", "������ �� ������", {Theif}},
	{"Read Languages", "������ �����", {Theif}},
	//
	{"Open door", "������� �����"},
	{"Open locked door", "������ �������� �����"},
	{"Find secret doors", "����� ��������� �����"},
	{"Learn spell", "������� ����������", {MagicUser}},
};
assert_enum(skill, LearnSpell);
getstr_enum(skill);

const classa& character::getclasses(skill_s id) {
	return skill_data[id].allowed;
}