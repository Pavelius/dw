#include "main.h"

static quest quests[] = {
	{ArkhamAsylum, "� ������� ����� �� ������������� �������� ��������, ������������� ��� \"������������������� ����\". ������ ���?", {Lore, -1}, {
		{"������ �� ���������."},
		{"��� �������� ������ �������� � �������� �������, � ������� �� ������ ��������� ������ �������.", {AddSpell}},
	}},
	{ArkhamAsylum, "�� ������� ����. ����� �� ��������� ������ ����� ������ � ����� ��������� ������������, ��� ��������� ��������� ����� ������! �� ����������� ����������� � ������������ �������, ���������� ���-�� � ��������� ��������.", {Lore, -2}, {
		{"�� ������� ���� ��� �� ��� �� ������ ����������� ���������� �� ��� � ������ �����, ����� ��� ��� ������ �����.", {Lose1Stamina}},
		{"������ �� ������ � ��� �� �������.", {Add1Clue}},
	}},
};