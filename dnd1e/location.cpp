#include "main.h"

static action tavern[] = {
	{"�������� � �������� � ������� �����.", PickPockets, Duration1Turn, 0, {}, {"%����� �� ����%�� ������� ������ ������� � ������� �����."}},
	{"����� ������ ������.", GoAway, Duration1Round, 0, {}, {"�� ����� ������."}},
};
static struct location_i {
	const char*		name;
	aref<action>	actions;
} location_data[] = {
	{""},
	{"�� ���� � ������������ ����. ������� ������� ������� ������ � ����."},
	{"����� ����� ��� ��������� ���� � ����������. �� ����� ����������� � ������."},
	{"�� ���������� � ��������� �������, �������� 4 �� 4 �����."},
	{"�� ���� � �������� ����, ������ ���������� ��������."},
	{"� ������� ������� ����� ������� � ���� ����� �����, ������ ����."},
	{"�� ����� ����� �������� ������."},
};
assert_enum(location, WildCampfire);
getstr_enum(location);

aref<action> scene::getactions(location_s id) {
	return location_data[id].actions;
}