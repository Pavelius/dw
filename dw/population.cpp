#include "main.h"

static struct population_info {
	const char*		id;
	const char*		name;
	const char*		text;
} population_data[] = {{"Exodus", "�����������", "����������� ����� ��������� ����������� � ������ ����� � ��� ����� �� ���."},
{"Shrinking", "�������", "������ ���� ���� ���������."},
{"Steady", "����������", ""},
{"Growing", "��������", "�� ����� ���� ����� ������."},
{"Booming", "�������������", "����� ���� ����� ����� ������. ��������� ������� � ������ ��������� ����� - � ��� ���� ����."},
};
assert_enum(population, Booming);
getstr_enum(population);