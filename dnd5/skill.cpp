#include "main.h"

struct skill_info {
	const char*			id;
	const char*			name;
} skill_data[] = {{"No skill", "��� ������"},
{"Athletics", "��������"},
{"Acrobatics", "����������"},
{"Sleight of hands", "�������� ���"},
{"Stealth", "����������"},
{"Arcana", "������ ������"},
{"History", "�������"},
{"Investigation", "������"},
{"Nature", "�������"},
{"Religion", "�������"},
{"Animal handling", "�����������"},
{"Insight", "��������"},
{"Medicine", "��������"},
{"Perception", "����������"},
{"Survival", "���������"},
{"Deception", "�����"},
{"Intimidation", "�����������"},
{"Performance", "�������������"},
{"Persuasion", "���������"},
};
assert_enum(skill, Persuasion);
getstr_enum(skill);