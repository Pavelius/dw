#include "main.h"

struct scenery_info {
	const char*		name;
	gender_s		gender;
	const char*		description;
} scenery_data[] = {{"�����"},
{"����", Male, "��������� ��������� ���� �� ����� ������"},
{"�����", Female, "�������� ���������� �����"},
{"������", Male, "������ ������, ������� � �����"},
};
assert_enum(scenery, Passage);
getstr_enum(scenery)

const char* geti(char* result, const char* result_maximum, const char* format, scenery_s id) {
	char temp[260];
	return szprints(result, result_maximum, format, grammar::of(temp, zendof(temp), scenery_data[id].name));
}