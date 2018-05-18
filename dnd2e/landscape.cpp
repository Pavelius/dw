#include "main.h"

struct landscape_i {
	const char*		id;
	const char*		name;
	char			encounter[Night + 1];
	const char*		movement;
} landscape_data[] = {
	{"Plain", "�������", {1, 0, 1, 0, 1, 0}, {"�� ��������� �� �������� �������."}},
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

const char* game::getencounterchance(landscape_s id) {
	return landscape_data[id].encounter;
}

const char* game::getstrmovement(landscape_s id) {
	return landscape_data[id].movement;
}