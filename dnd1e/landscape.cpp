#include "main.h"

static action plain[] = {
	{"��������� ������, ����������� ���� ����.", GettingLost, Duration4Hours, 0, {"�� ��������� � ������ �����������."}, {"���� �� ����� �� �� ������� � ������������."}},
	{"���������� ����������� �� ����.", Hunting, Duration4Hours, 0, {"%����� ������%� ������� ����."}, {"%����� �� �����%� ����� ����."}},
};
struct landscape_i {
	const char*		id;
	const char*		name;
	char			encounter[Night + 1];
	const char*		movement;
	aref<action>	actions;
} landscape_data[] = {
	{"Plain", "�������", {1, 0, 1, 0, 1, 0}, {"�� ��������� �� �������� �������."}, plain},
	{"Brush", "���������", {1, 0, 1, 1, 0, 1}, {"�� ��������� �� �������, ������� ������������ �������� ������� ����������� � ��������� ����������."}},
	{"Forest", "���", {2, 2, 2, 2, 2, 2}, {"�� ��������� �� ������� ����."}},
	{"Desert", "�������", {1, 0, 0, 1, 0, 1}},
	{"Hills", "�����", {0, 2, 0, 2, 0, 2}},
	{"Mountains", "����", {3, 0, 0, 3, 3, 0}},
	{"Swamp", "������", {4, 4, 4, 4, 4, 4}},
	{"Jungle", "�������", {3, 3, 3, 3, 3, 0}},
	{"Ocean", "�����", {0, 1, 0, 0, 1, 0}},
	{"Arctic", "��������", {0, 0, 1, 1, 0, 0}},
};
assert_enum(landscape, Arctic);
getstr_enum(landscape);

const char* scene::getencounterchance(landscape_s id) {
	return landscape_data[id].encounter;
}

const char* scene::getstrmovement(landscape_s id) {
	return landscape_data[id].movement;
}

aref<action> scene::getactions(landscape_s id) {
	return landscape_data[id].actions;
}