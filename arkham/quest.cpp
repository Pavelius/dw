#include "main.h"

static quest quests[] = {
	{ArkhamAsylum, "� ������� ����� �� ������������� �������� ��������, ������������� ��� \"������������������� ����\". ������ ���?", {Lore, -1, 0, true}, {
		{"������ �� ���������."},
		{"��� �������� ������ �������� � �������� �������, � ������� �� ������ ��������� ������ �������.", {AddSpell}},
	}},
	{ArkhamAsylum, "�� ������� ����. ����� �� ��������� ������� ����� ������ � ����� ��������� ������������, ��� ��������� ��������� ������ ������! �� ����������� ����������� � ������������ �������, ���������� ���-�� � ��������� ��������.", {Lore, -2}, {
		{"�� ������� ���� ��� �� ��� �� ������ ����������� ���������� �� ��� � ������ �����, ����� ��� ��� ������ �����.", {Lose1Stamina}},
		{"������ �� ������ � ��� �� �������.", {Add1Clue}},
	}},
};

quest& hero::getquest(location_s value) {
	adat<quest*, 32> result;
	for(auto& q : quests) {
		if(q.type == value)
			result.add(&q);
	}
	if(result.count)
		return *result.data[rand() % result.count];
	return quests[0];
}

void hero::run(const quest& e) {
	logs::clear(true);
	logs::add(e.text);
	auto result = 0;
	if(e.roll.optional) {
		char skill_temp[128]; e.roll.getname(skill_temp, zendof(skill_temp));
		if(!logs::yesno(true, "������ ������ ������ [%1]?", skill_temp))
			return;
	}
	switch(e.roll.action.type) {
	case Stats:
		result = roll((stat_s)e.roll.action.value, e.roll.bonus, e.roll.difficult, true);
		break;
	}
	auto result_maximum = zlen(e.results);
	if(!result_maximum)
		return;
	if(result >= result_maximum)
		result = result_maximum - 1;
	bool discard = false;
	for(auto a : e.results[result].results)
		apply(a, &discard);
}