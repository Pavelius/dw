#include "main.h"

monstermovei bsmeta<monstermovei>::elements[] = {{HackAndSlash, Kobold, "������� ������� ����� ���� ������."},
{HackAndSlash, Kobold, "����� ������� ����� ���� ������ ����� �����."},
};
DECLFULL(monstermovei);

//static mastermove kobold_moves[] = {
//	{"%����� �������%��� � ������%� � ������ ��������������� �������� ������.", Damage, {2, 6}, {"������ �������, ��� � �� ������ %����� - � ��������� ������ %��� ���������� � �������.", Dexterity}},
//	{"��������, ���������� �������� ��������� � �������� �� ����. ������ ����� ��� ��������� ���-�� ��������.", Regroup},
//	{"������� ������������� ������� ������� � ������� � ��-�� �������� ����� ����� �������� ��� ���� ������� � ������������� � �����.", Summon, {1}},
//};
//static mastermove goblin_moves[] = {
//	{"\n- ����� ���!!! ��� ����!! - ������ ���� ������, ����� ������� ������.\n�� ������� ������� ��������� ��� ���� �������� ��������.", Summon, {2}},
//	{"\n- ����������!! - ������� ������� � ���������� ���� ����� �� ������ �� ���������� %�����.", Damage, {1, 10, 1}, 0},
//	{"\n- ��������!!! ��� �����, ������� �� ����� � �������� ��!! - ������� ������� � �������� �� ����.\n- ������� ��?? - ���������� ����������� %�����.", Regroup},
//};
//static mastermove bandit_moves[] = {
//	{"������ ����, ����� ������� ���� ��������, ������ ������� %����� � �������� � %��� ������� � ������������ ��������.", LooseMoney, {2, 6}},
//};
//static mastermove zombi_moves[] = {
//	{"�������� ���� �� ����������� ����� ����� ����.", Summon, {1}},
//	{"����� ������ %����� � ���� � ������ ����� �� �����.", Damage, {1, 10}},
//};
//monsteri bsmeta<monsteri>::elements[] = {
//	{"Bandit", "������", Horde, Small, {Intellegent, Organized}, 1, "������", {1, 6}, 3, {Close}, bandit_moves},
//	{"Goblin", "������", Horde, Small, {Intellegent, Organized}, 1, "�����", {1, 6}, 3, {Close, Reach}, goblin_moves},
//	{"Kobold", "�������", Horde, Small, {Stealthy, Intellegent, Organized}, 1, "�����", {1, 6}, 3, {Close, Reach}, kobold_moves},
//	{"Zombie", "�����", Horde, Small, {Undead}, 0, "����� �� �����", {1, 6}, 11, {Close}, zombi_moves},
//};
//assert_enum(monster, LastMonster);

static char regrouping[LastMonster + 1];

static int add_regrouping(monster_s type) {
	auto r = regrouping[type];
	regrouping[type] = 0;
	return r;
}