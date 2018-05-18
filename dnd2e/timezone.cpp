#include "main.h"

static struct timezone_i {
	const char*	id;
	const char*	name;
	const char*	become;
} timezone_data[] = {
	{"Morning", "����", "��������� ����."},
	{"Noon", "�������", "�������� �������."},
	{"Afternoon", "����� �����", "�������� ����."},
	{"Evening", "�����", "������� �����."},
	{"Midnight", "�������", "������� �������."},
	{"Night", "�������� ����", "������ �������� ����."},
};