#include "main.h"

static quest quests[] = {{},
{StMarysHospital, "����� �� ��� �� ��������� � ��� ��������� ����� ������ ������������.", {Luck, -1}, {{"�� ������������� ���� � �������� ��������. ����� ����� �� �������� �� �����.", {Lose2Sanity, LeaveOutside}},
{"� ��������� ��������� �� ��������, ��� ������ �������� �������� �� ���� �� �������, ����������� ���������������� �����. �� ����� ��������� �� �������� ���. ����� ���� �������� ��� �������, ������� �� ���� ��������� ����.", {Add3Money, Add2Sanity}},
}},
{StMarysHospital, "����� ���� ����������, ��������� ����� ��� - �� ������ ��� � ����.", {Sneak, -1}, {{"���� ������� ��� � ������ �������� � ��� �����-�� ��������� ������ ��������� �������� ��������."},
{"�� ������ �������� ������� ��� ���� ����� ������. ����� �� ���������� ��� ��� ��� ��������� ������.", {AddSpell}},
}},
{StMarysHospital, "���� �� ������� �������� ������� ��� �����. ��� ����� ����������� ������� ��� ������.", {}, {{0, {Lose1Clue}},
}},
{StMarysHospital, "�� ������������ ����, �� �����������, �� ��� �� ���������. � ������ ����� ������� �������������� ����.", {Fight, -1}, {{"����� ��������� ��� ������ ������ �������� �� �����.", {Lose1Sanity, LeaveOutside}},
{"�� ������� �����, ���� ������� ����������.", {Lose1Sanity}},
}},
{StMarysHospital, "������ ���������� ��� ���� ������� ������������ ������, ���������� �� ����������. �������� ������� � ������.", {Will, -1}, {{"� ������ �� �������� ������ �������� �� �����.", {Lose1Sanity, LeaveOutside}},
{"������������ ������� ���� �� ���������� ����� ����������.", {AddUniqueItem}},
}},
{StMarysHospital, "�� ����������� ������ ���� ������������������ �������.", {}, {{0, {Add1_3Stamina}},
}},
{StMarysHospital, "��� ������� ��������� � ����� ������������ �� ���� ��������, ������� ���� ������� ����������.", {Lore, 0}, {{"�� ������ ������ �� �� ������ ������."},
{"�� ������ � ������ �������� ���-��� �����.", {Add1Clue}},
}},
{Library, "������ ������, �� ������, ��� ��� ���� � ������������ ����� ������� ������� ������.", {Will, -1}, {{"�� ������� ����� ������ � ��� ��������� ��� �� �����.", {LeaveOutside}},
{"��� ��������� ����� �������, ��� �������� ��� ��� ����� ������ �����.", {AddUniqueItemTome}},
}},
{Library, "�����, ������� �� �������, �������� ����� ��������� ���.", {Lore, -2}, {{"����� ������ �������� ���.", {Lose2Sanity, Lose2Stamina}},
{"�� ���������� ������ ������ ������ ������.", {AddDClue}},
}},
{Library, "����� �� ������ ������ ����� �� ��������� � ��� ��������� ������ ���. �� ���� � ������ ����.", {}, {{0, {EncounterDreamland}},
}},
{Library, "�� ������� ������ �����.", {Luck, -2}, {{"� ��� ������ ������ �����������."},
{"����� �� ����� �� ������� �� ����� �������� ������.", {Add5Money}},
}},
{Library, "��� �������� ����� �� �������� �����.", {Money, 4}, {{"��� ������� �� �����.", {LeaveOutside}},
{"�������� ����� �� �������� � ����������."},
}},
{Library, "� ��� ������� �������������, ������� ������ � ���-�� �������� ���������.", {Will}, {{"� ����� ��������������� ������� ���������� ��� �� �����.", {LeaveOutside}},
{"� ����� ��� ������� ��� � �������� ����� ����������, ��� �� �������� ��������� �������.", {AddSpell1of2}},
{"� ����� ��� ��������� ��� �������� ������������ ��������.", {AddUniqueItem}},
}},
{Library, "����� � ������ ���� ���������� �������� ������� ��� ������� ����.", {}, {{0, {Lose1Sanity}},
}},
{UnvisitedIsle, "��� �������� �� �����, �������� �� �� ��������.", {Will, -2}, {{"�� ��������� � ��� ��������� ��������� ���� ������� �������� � ������ �� �� �������.", {Lose3Sanity}},
{"������� ���� �� ������ ���� ��������� � ����������� ��������� ������."},
}},
{UnvisitedIsle, "��� ����� �������� ��� �� ���������� ����� ������������ ������. C���� �������� �� ��������� ������.", {}, {{0, {Lose1Sanity, AddSpell}},
}},
{UnvisitedIsle, "����� - �� ������� ������� ������ �����. � �� ��������� ������� � ���� ���������.", {Sneak, -1}, {{"������� ��������� ��� ����� ����� ������ ������� � ���� ��������."},
{"������� ��� ������� ������ ������������� ���������� �������������.", {AddAllyLegrase}},
}},
{UnvisitedIsle, "��������� ��� �� ����� ���������� �������. �� �������� ��������������� ���� ���� ������. �� ��������������, �� ������������ ������ ��� �����.", {Will, -1}, {{"�� ���������� �� �������� ����� � �������� ���� �� ����.", {Lose1Stamina, Lose1Sanity}},
{"�� ���������� � ��� ������� ���� �� ����.", {Lose1Stamina}},
}},
{UnvisitedIsle, "������ ���������� ��������� �� ������ � �������� ����� �� �������. ����������, � ��� ��� �������...", {Sneak, -1}, {{"������ �������� �� �������."},
{"�� �������� ������ ����������.", {Add2Clue}},
}},
{UnvisitedIsle, "��� ������� �� ������, �� ��������� � ������� ����� � �������� �������� ����. ����� ����������� ������ ������������ ���.", {Will, -1}, {{"�������� ��������� ���������� �� ���.", {AddCurse}},
{"�� ������ ���������� �����."},
}},
{UnvisitedIsle, "����� � ������ ���� ��� ��������, �� ������ ���������� ���������. ����� ���������� ������ ������!", {}, {{0, {Lose1Sanity, Add1Clue}},
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
	if(q->roll.id == Money) {
		if(get(Money) < q->roll.bonus)
			logs::add("� ��� �� ������� �����.");
		else if(logs::yesno(true, "������ ������� [%1i$]?", q->roll.bonus)) {
			set(Money, get(Money) - q->roll.bonus);
			result = 1;
		}
	} else {
		if(q->roll.optional) {
			char skill_temp[128]; q->roll.getname(skill_temp, zendof(skill_temp));
			if(!logs::yesno(true, "������ ������ ������ [%1]?", skill_temp))
				return;
		}
		if(q->roll.id)
			result = roll(q->roll.id, q->roll.bonus, q->roll.difficult, true);
	}
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