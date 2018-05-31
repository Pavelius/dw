#include "main.h"

static quest quests[] = {{},
{UnvisitedIsle, "������ ���������� ��������� �� ������ � �������� ����� �� �������. ����������, � ��� ��� �������...", {Sneak, -1}, {{"������ �������� �� �������."},
{"�� �������� ������ ����������.", {Add2Clue}},
}},
{UnvisitedIsle, "��� ������� �� ������, �� ��������� � ������� ����� � �������� �������� ����. ����� ����������� ������ ������������ ���.", {Will, -1}, {{"�������� ��������� ���������� �� ���.", {AddCurse}},
{"�� ������ ���������� �����."},
}},
{ArkhamAsylum, "� �������� ������� �� ����� ����� � �������� ������� ���������.", {Lore}, {{"������ ���������, �� ������ �� ����� ������ ����������.", {Add1Clue, Lose1Sanity}},
{"�� ���� ������ ��������� �����������.", {Add2Clue}},
{"�� ���� ������ ��������� �����������.", {Add2Clue}},
{"���� ������ �������� �������� ������ ������.", {Add3Clue}},
}},
{ArkhamAsylum, "��� ������� �� ��������, �������� ������ ���� ����� ������ �������� � ���� ��� �������������.", {Will, -1, 2}, {{"�� �� ��������� ������������ � �������� ������.", {LoseMemory}},
{"������������ ����������� ��������� �� ����� ������������.", {AddSkill}},
}},
{ArkhamAsylum, "��������� ����������, ��� �� ���������� �� ���������� ���������.", {Sneak, -1}, {{"��� ������� ��� � ����� �������.", {Arrested}},
{"��� �������. �� ������ ����������� ���� ��� �� �����.", {LeaveOutside}},
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

const quest* hero::getquest(location_s value, int index) {
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
		return result.data[index];
	}
	return 0;
}

void hero::run(const quest* q) {
	if(!q)
		return;
	if(!isready())
		return;
	logs::clear(true);
	logs::add(q->text);
	auto result = 0;
	if(q->roll.optional) {
		char skill_temp[128]; q->roll.getname(skill_temp, zendof(skill_temp));
		if(!logs::yesno(true, "������ ������ ������ [%1]?", skill_temp))
			return;
	}
	if(q->roll.id)
		result = roll(q->roll.id, q->roll.bonus, q->roll.difficult, true);
	auto result_maximum = zlen(q->results);
	if(result_maximum < 1)
		result_maximum = 1;
	if(result >= result_maximum)
		result = result_maximum - 1;
	bool discard = false;
	auto apply_actions = 0;
	if(q->results[result].text)
		logs::add(q->results[result].text);
	for(auto a : q->results[result].results) {
		if(!isready())
			break;
		if(!a)
			break;
		apply(a, &discard);
		apply_actions++;
	}
	if(!apply_actions)
		logs::next();
}