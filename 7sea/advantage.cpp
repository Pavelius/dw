#include "main.h"

struct advantage_i {
	const char*				id;
	const char*				name;
	char					cost;
	adat<skill_s, 4>		skills;
	adat<advantage_s, 4>	deny;
} advantage_data[] = {{"Able drinker", "����������� ����", 1},
{"Academy", "������� ��������", 4},
{"Appearance", "���������", 5},
{"Castillian Education", "����������� �����������", 10},
{"Citation", "�������", 4, {}, {Scoundrel}},
{"Combat Reflexes", "������ ��������", 3},
{"Commissions", "������� ������", 4},
{"Dangerous beauty", "������������ �������", 5},
{"Dracheneisen", "�����������", 20},
{"Foul Weather Jack", "���� ������ ������", 5},
{"Indomitable will", "�������� ����", 3},
{"Keen Sences", "������ �������", 2},
{"Large", "�������", 5, {}, {Small}},
{"Linguist", "��������", 2},
{"Noble", "��������", 10},
{"Ordained", "�������� ���", 4, {Scholar}},
{"Scoundrel", "�������", 3, {Streetwise}, {Citation}},
{"Small", "������", 2, {}, {Large}},
{"Toughness", "�������", 5},
{"University", "�����������", 3},
};
assert_enum(advantage, LastAdvantage);
getstr_enum(advantage);

int	hero::getcost(advantage_s id) const {
	switch(id) {
	case DracheneisenNoble: return (nation == Eisen) ? advantage_data[id].cost : 0;
	case CastilliansEducation: return (nation == Castille) ? advantage_data[id].cost : 0;
	case Noble: return issorcery() ? 5 : 10;
	default: return advantage_data[id].cost;
	}
}

void hero::set(advantage_s value, bool interactive, char* skills) {
	advantages[value]++;
	for(auto e : advantage_data[value].skills)
		set(e, interactive, skills);
}