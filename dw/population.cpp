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
bsreq population_type[] = {
	BSREQ(population_info, id),
	BSREQ(population_info, name),
	BSREQ(population_info, text),
{}}; BSMETA(population);