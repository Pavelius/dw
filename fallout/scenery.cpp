#include "main.h"

sceneryi bsmeta<sceneryi>::elements[] = {{"�����"},
{"����", Male, "��������� ��������� ���� �� ����� ������"},
{"�����", Female, "�������� ���������� �����"},
{"������", Male, "������ ������, ������� � �����"},
};
assert_enum(scenery, Passage);

//const char* geti(char* result, const char* result_maximum, const char* format, scenery_s id) {
//	char temp[260];
//	return szprints(result, result_maximum, format, grammar::of(temp, zendof(temp), scenery_data[id].name));
//}