#include "main.h"

static struct race {
	const char*		id;
	const char*		name;
	char			minimum[Charisma + 1];
	char			maximum[Charisma + 1];
	char			adjustment[Charisma + 1];
	char			theive_skills[ReadLanguages + 1];
	feata			feats;
	const char*		info;
} race_data[] = {
	{"No race", "��� ����"},
	{"Human", "�������", {3, 3, 3, 3, 3, 3}, {18, 18, 18, 18, 18, 18}, {0, 0, 0, 0, 0, 0}, {0},
	{},
	"���� ���� � ���� AD&D ��������������� ��� ��������� ����, ��� ���������� �� ���� ��������������, ��������� � �������� ����. ������� ��������-������� ����� �������� ������ �������� ����������������, ������� ��������� ������."},
	{"Dwarf", "������", {8, 3, 12, 3, 3, 3}, {18, 17, 18, 18, 18, 17}, {0, 0, 1, 0, 0, -1}, {0, 10, 15, 0, 0, 0, -10, -5},
	{Infravision, BonusSaveVsPoison, BonusSaveVsSpells, BonusSaveVsWands, DwarfCombatTactic, Mining},
	"������� - ��� ���������, ���������� ��������, ������� ����� �������� �� �� ������� � �������� ����. �� ���� ���������� �������� 120-140 ��. � ��� ������� ����, ������ ����� � ������ ������. ������� � �������� ����� 350 ���."},
	{"Elf", "����", {3, 6, 7, 8, 3, 8}, {18, 18, 18, 18, 18, 18}, {0, 1, -1, 0, 0, 0}, {5, -5, 0, 5, 10, 5, 0, 0},
	{Infravision, ImmuneCharmAndSleep, ElfWeaponTraining, LightSteps},
	"�����, ��� �������, ��������� ���� � �������� ������� �����. �� ����� ������ ������ � ���������, ��� ������������� � ����������� �����������. ���� ��� � ������� �������� � �������, ������������� ���� ���� �������� � ������. ����� ������ ����� ����� 1200 ���, ���� ������� �� ����� ������� ��� ��������� ���������� �������� ��� ��������. ����������, ���� ��� ������, �� ��� ����������� ���������� �� ����."},
	{"Gnome", "����", {6, 3, 8, 6, 3, 3}, {18, 18, 18, 18, 18, 18}, {0, 0, 0, 1, -1, 0}, {0, 5, 10, 5, 5, 10, -15, 0},
	{BonusSaveVsSpells, BonusSaveVsWands, DwarfCombatTactic, Mining},
	"�������� � ������� � ���������, ����� ������� ������ ������, ��� �� ������� ������������. �����, ��� ����� ����� ����������, ��� ����� �������, ��� �������. ������ �� ���� ����������� ������. � ����������� ������ ������ ���������-���������� ��� ���������� ���� � ����� ������. �������� ���� ����� 350 ���."},
	{"Halfelf", "����-����", {3, 6, 6, 4, 3, 3}, {18, 18, 18, 18, 18, 18}, {0, 0, 0, 0, 0, 0}, {10, 0, 0, 0, 5, 0, 0, 0},
	{Infravision},
	"��������� - ��� �������� ���������������� ��������, ����������� � ��������� ����. �������������� � ������, ���������� ��� ����� ������������ ��������� �������: ������, ����� ������� �������� ���� � �����, � ����, �������� ���� ���������, ���� ���������� (����� ������� ������ ����� ���� ������ �����). ���� ����� ������� ������ �����, ��� ������, �������� �������� ���������, ���� ������� ������� ��� ������ ����� ��� ������, �������� �������� ����������."},
	{"Halfling", "������", {7, 7, 10, 6, 3, 3}, {18, 18, 18, 18, 17, 18}, {-1, 1, 0, 0, 0, 0}, {5, 5, 5, 10, 15, 5, -15, -5},
	{LightSteps},
	"������� - ��� ����������� ���������� ��������, ����� ������� �� ��������� �����. � ��� �������� ������� ����, ����� ������� ������ ������� ����. � �������� ������ ��������� ��������, � ������ ����� �� ��� ������� ������� ��������. ��� ������������ �� ������ �����, ��������� ��� ��������. �� ������������ ���� �����, �������� ���������� ����� 150 ���."},
	{"Halforc", "����-���", {7, 7, 10, 6, 3, 3}, {17, 17, 18, 17, 14, 14}, {1, 0, 1, 0, 0, -2}, {-5, 5, 5, 0, 0, 5, 5, -10},
	{},
	"����� ����� � �����. �� ����� �� ����������� � ����."},
};
assert_enum(race, HalfOrc);
getstr_enum(race);

char* character::getminimum(race_s value) {
	return race_data[value].minimum;
}

char* character::getmaximum(race_s value) {
	return race_data[value].maximum;
}

const char* character::getinfo(race_s value) {
	return race_data[value].info;
}

const char* character::getadjustment(race_s value) {
	return race_data[value].adjustment;
}

const feata& character::getfeats(race_s value) {
	return race_data[value].feats;
}

char* character::getskills(race_s id) {
	return race_data[id].theive_skills;
}