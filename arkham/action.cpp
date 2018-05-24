#include "main.h"

static struct action_i {
	const char*		id;
	const char*		name;
	stat_s			stat;
	int				count;
	void			(hero::*set)(stat_s id, int count, bool interactive);
} action_data[] = {
	{"", ""},
	{"gain 1 clue", "�������� 1 �����", Clue, 1, &hero::add},
	{"gain 2 clues", "�������� 2 �����", Clue, 2, &hero::add},
	{"gain 3 clues", "�������� 3 �����", Clue, 3, &hero::add},
	{"gain 4 clues", "�������� 4 �����", Clue, 4, &hero::add},
	{"gain 5 clues", "�������� 5 ����", Clue, 5, &hero::add},
	{"lose 1 clue", "�������� 1 �����", Clue, 1, &hero::add},
	{"lose 2 clues", "�������� 2 �����", Clue, 2, &hero::add},
	{"lose 3 clues", "�������� 3 �����", Clue, 3, &hero::add},
	{"lose 4 clues", "�������� 4 �����", Clue, 4, &hero::add},
	{"lose 5 clues", "�������� 5 ����", Clue, 5, &hero::add},
	{"gain 1 dollar", "�������� 1 ������", Money, 1, &hero::add},
	{"gain 2 dollars", "�������� 2 �������", Money, 2, &hero::add},
	{"gain 3 dollars", "�������� 3 �������", Money, 3, &hero::add},
	{"gain 4 dollars", "�������� 4 �������", Money, 4, &hero::add},
	{"gain 5 dollars", "�������� 5 ��������", Money, 5, &hero::add},
	{"gain 6 dollars", "�������� 6 ��������", Money, 6, &hero::add},
	{"gain 7 dollars", "�������� 7 ��������", Money, 7, &hero::add},
	{"gain 8 dollars", "�������� 8 ��������", Money, 8, &hero::add},
	{"gain 9 dollars", "�������� 9 ��������", Money, 9, &hero::add},
	{"gain 10 dollars", "�������� 10 ��������", Money, 10, &hero::add},
	{"lose 1 dollar", "�������� 1 ������", Money, 1, &hero::add},
	{"lose 2 dollars", "�������� 2 �������", Money, 2, &hero::add},
	{"lose 3 dollars", "�������� 3 �������", Money, 3, &hero::add},
	{"lose 4 dollars", "�������� 4 �������", Money, 4, &hero::add},
	{"lose 5 dollars", "�������� 5 ��������", Money, 5, &hero::add},
	{"gain 1 sanity", "�������� 1 ��������", Sanity, 1, &hero::add},
	{"gain 2 sanity", "�������� 2 ��������", Sanity, 2, &hero::add},
	{"gain 3 sanities", "�������� 3 ��������", Sanity, 3, &hero::add},
	{"lose 1 sanity", "�������� 1 ��������", Sanity, 1, &hero::add},
	{"lose 2 sanity", "�������� 2 ��������", Sanity, 2, &hero::add},
	{"lose 3 sanities", "�������� 3 ��������", Sanity, 3, &hero::add},
	{"gain 1 stamina", "�������� 1 �����", Stamina, 1, &hero::add},
	{"gain 2 staminas", "�������� 2 �����", Stamina, 2, &hero::add},
	{"gain 3 staminas", "�������� 3 �����", Stamina, 3, &hero::add},
	{"lose 1 stamina", "�������� 1 �����", Stamina, 1, &hero::add},
	{"lose 2 staminas", "�������� 2 �����", Stamina, 2, &hero::add},
	{"lose 3 staminas", "�������� 3 �����", Stamina, 3, &hero::add},
	{"gain common item", "�������� ������� �������", CommonItem, 1, &hero::choose},
	{"gain 2 common items", "�������� 2 ������� ��������", CommonItem, 2, &hero::choose},
	{"gain unique item", "�������� ���������� �������", UniqueItem, 1, &hero::choose},
	{"gain skill", "�������� �����", Skill, 1, &hero::choose},
	{"gain spell", "�������� ����������", Spell, 1, &hero::choose},
	{"discard", "��������"},
};
assert_enum(action, Discard);

static struct case_info {
	stat_s		id;
	const char*	increment;
	const char*	decrement;
	const char*	numbers[3];
	const char*	get(int count) const {
		if(!numbers[0])
			return "";
		switch(count) {
		case 1: return numbers[1];
		case 2: case 3: case 4: return numbers[2];
		default: return numbers[0];
		}
	}
} case_data[] = {{Clue, "%����� �������%� [%3i] [%2]", "%����� �������%� [%3i] [%2]", {"����", "�����", "�����"}},
{Money, "%����� �������%� [%3i] [%2]", "%����� �������%� [%3i] [%2]", {"��������", "������", "�������"}},
{Sanity, "%����� �������%� [%3i] [%2]", "%����� �������%� [%3i] [%2]", {"��������", "��������", "��������"}},
{Stamina, "%����� �������%� [%3i] [%2]", "%����� �������%� [%3i] [%2]", {"��������", "��������", "��������"}},
{Skill, "%����� ������ ����� [%1]", "%����� ����� ����� [%1]"},
};

case_info& getcase(stat_s id) {
	for(auto& e : case_data) {
		if(e.id == id)
			return e;
	}
	return case_data[0];
}

char hero::getcount(stat_s id, char value) const {
	switch(value) {
	case Half: return get(id) / 2;
	case All: return get(id);
	case OneDice: return 1 + rand() % 6;
	case TwoDice: return 2 + rand() % 6 + rand() % 6;
	default: return value;
	}
}

void hero::apply(action_s id, bool interactive, bool* discard) {
	if(!id)
		return;
	auto& e = action_data[id];
	if(e.set)
		(this->*e.set)(e.stat, e.count, interactive);
	if(discard)
		*discard = (id == Discard);
}

void hero::add(stat_s id, int count, bool interactive) {
	auto value = get(id) + count;
	if(value < 0)
		value = 0;
	if(interactive) {
		auto& e = getcase(id);
		if(count >= 0)
			act(e.increment, getstr(id), count, e.get(count));
		else
			act(e.decrement, getstr(id), -count, e.get(-count));
		logs::next();
	}
}