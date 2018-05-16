#include "main.h"

static struct prosperty_info {
	const char*		id;
	const char*		name;
	const char*		text;
} prosperty_data[] = {{"Dirt", "�����", "������ ��� ���������� ������� � ������ ������, ��������� �� ���������� �����."},
{"Poor", "������", "� �������� �� ������ ������ ������, ��������� �� ���������� ���������, ���� ������� ���������� ������� ����."},
{"Moderate", "�������", "������ ���� ����������� ��������� ����, � ���������� ���������."},
{"Wealth", "������������", "������ ���� ����������� ����, ��������� �� ��� ���� ������������ ��� ������ �����������."},
{"Rich", "�������", "� �������� ����� ���� ����������� ���� � ������� ������� � ������� �� �������� ���������. ��������� ������, ������� ������� � ������� ����� ��� �������� � ������� �������� ����������."},
};
assert_enum(prosperty, Rich);
getstr_enum(prosperty);
bsreq prosperty_type[] = {
	BSREQ(prosperty_info, id),
	BSREQ(prosperty_info, name),
	BSREQ(prosperty_info, text),
{}}; BSMETA(prosperty);

const char*	game::get(prosperty_s v) {
	return prosperty_data[v].text;
}