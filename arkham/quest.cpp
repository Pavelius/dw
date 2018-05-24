#include "main.h"

static quest quests[] = {{ArkhamAsylum, "� �������� ������� �� ����� ����� � �������� ������� ���������.", {Lore}, {{"������ ���������, �� ������ �� ����� ������ ����������.", {Add1Clue, Lose1Sanity}},
{"�� ���� ������ ��������� �����������.", {Add2Clue}},
{"�� ���� ������ ��������� �����������.", {Add2Clue}},
{"���� ������ �������� �������� ������ ������.", {Add3Clue}},
}},
{ArkhamAsylum, "������ ����� ����! ���� ���������.", {Speed, -1}, {{"��� ���������� ��� ���.", {LeaveOutside}},
{"� �������� ������ ��� ���-�� ��������.", {AddUniqueItem}},
}},
{ArkhamAsylum, "������ ����� �������� ����� ��� ����������. ������ ��������������, ����� �� ������?", {Fight, -2, 0, true}, {{"�� ������� ��� �������.", {Add2Sanity, SkipTurn}},
{"������ �� ���������."},
}},
{ArkhamAsylum, "\"��� ����� ������,\" - ������� ��� ������� � �������� �����. �� ��� �� ������ ���������. ����������, �� ������� ��� �� ���� � ������. �����������, �� �� ������-�� ���� ������ ������ � ������.", {}, {{0, {Add3Sanity}},
}},
{ArkhamAsylum, "� ������� ����� �� ������������� �������� ��������, ������������� ��� \"������������������� ����\". ������ ���?", {Lore, -1, 0, true}, {{"������ �� ���������."},
{"��� �������� ������ �������� � �������� �������, � ������� �� ������ ��������� ������ �������.", {AddSpell}},
}},
{ArkhamAsylum, "�� ������� ����. ����� �� ��������� ������� ����� ������ � ����� ��������� ������������, ��� ��������� ��������� ������ ������! �� ����������� ����������� � ������������ �������, ���������� ���-�� � ��������� ��������.", {Lore, -2}, {{"�� ������� ���� ��� �� ��� �� ������ ����������� ���������� �� ��� � ������ �����, ����� ��� ��� ������ �����.", {Lose1Stamina}},
{"������ �� ������ � ��� �� �������.", {Add1Clue}},
}},
};

quest& hero::getquest(location_s value, int index) {
	adat<quest*, 32> result;
	for(auto& q : quests) {
		if(q.type == value)
			result.add(&q);
	}
	if(result.count) {
		if(index == -1)
			index = rand() % result.count;
		if(index >= (int)result.count)
			index = result.count - 1;
		return *result.data[index];
	}
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
	if(result_maximum < 1)
		result_maximum = 1;
	if(result >= result_maximum)
		result = result_maximum - 1;
	bool discard = false;
	auto apply_actions = 0;
	if(e.results[result].text)
		logs::add(e.results[result].text);
	for(auto a : e.results[result].results) {
		if(!a)
			break;
		apply(a, &discard);
		apply_actions++;
	}
	if(!apply_actions)
		logs::next();
}