#include "main.h"

struct skill_info {
	const char*			id;
	const char*			name;
} skill_data[] = {{"athletics", "��������"},
{"acrobatics", "����������"},
{"sleight of hands", "�������� ���"},
{"stealth", "����������"},
{"arcana", "������"},
{"history", "�������"},
{"investigation", "�������������"},
{"nature", "�������"},
{"religion", "�������"},
{"animal handling", "���������� ��������"},
{"insight", "����������������"},
{"medicine", "��������"},
{"perception", "����������"},
{"survival", "���������"},
{"deception", "�����"},
{"intimidation", "�����������"},
{"performance", "���������"},
{"persuasion", "���������"},
};
assert_enum(skill, Persuasion);
getstr_enum(skill);