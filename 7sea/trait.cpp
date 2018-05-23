#include "main.h"

static struct trait_i {
	const char*		id;
	const char*		name;
	const char*		text;
} trait_data[] = {{"Brawn", "����", "�������� ���� � ������������ ���������."},
{"Finesse", "����������", "�������� ����������� �������� ��������� � ��� �����������."},
{"Resolve", "���������", "�������� ���� ���� ���������."},
{"Wits", "�����", "���������� ��, ��������� ������ ����� ����� ������, �������� � ����������� ���������."},
{"Panache", "��������", "��� �� \"����� ���������\", �� ��� �������� ����� �� �����."},
};
assert_enum(trait, Panache);
getstr_enum(trait);
getinf_enum(trait);