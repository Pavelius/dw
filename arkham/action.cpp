#include "main.h"

static struct action_info {
	stat_s			stat;
	int				count;
	void			(hero::*set)(stat_s stat, card_s card, location_s location, int count, bool interactive);
	card_s			card;
	location_s		location;
} action_data[] = {{},
{Clue, 1, &hero::add},
{Clue, 2, &hero::add},
{Clue, 3, &hero::add},
{Clue, 4, &hero::add},
{Clue, 5, &hero::add},
{Clue, -1, &hero::add},
{Clue, -2, &hero::add},
{Clue, -3, &hero::add},
{Clue, -4, &hero::add},
{Clue, -5, &hero::add},
{Money, 1, &hero::add},
{Money, 2, &hero::add},
{Money, 3, &hero::add},
{Money, 4, &hero::add},
{Money, 5, &hero::add},
{Money, 6, &hero::add},
{Money, 7, &hero::add},
{Money, 8, &hero::add},
{Money, 9, &hero::add},
{Money, 10, &hero::add},
{Money, -1, &hero::add},
{Money, -2, &hero::add},
{Money, -3, &hero::add},
{Money, -4, &hero::add},
{Money, -5, &hero::add},
{Sanity, 1, &hero::add},
{Sanity, 2, &hero::add},
{Sanity, 3, &hero::add},
{Sanity, -1, &hero::add},
{Sanity, -2, &hero::add},
{Sanity, -3, &hero::add},
{Stamina, 1, &hero::add},
{Stamina, 2, &hero::add},
{Stamina, 3, &hero::add},
{Stamina, -1, &hero::add},
{Stamina, -2, &hero::add},
{Stamina, -3, &hero::add},
{Movement, 1, &hero::restoreall},
{Movement, 1, &hero::skipturn},
{Movement, 1, &hero::leaveoutside},
{Movement, 1, &hero::arrested},
{Movement, 1, &hero::losememory},
{Fight, 1, &hero::monsterappear},
{Blessed, 1, &hero::monsterappear},
{Ally, 1, &hero::addally, AnnaKaslow},
{Ally, 1, &hero::addally, JohnLegrasse},
{Blessed, -1, &hero::addmagic},
{Blessed, 1, &hero::addmagic},
{Blessed, 1, &hero::addmagic},
{Blessed, -1, &hero::addmagic},
{CommonItem, 1, &hero::choose},
{CommonItem, 2, &hero::choose},
{UniqueItem, 1, &hero::choose},
{Skill, 1, &hero::choose},
{Spell, 1, &hero::choose},
{Spell, 2, &hero::chooseone},
{},
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
} case_data[] = {{Clue, "�������� [%3i] [%2].", "�������� [%3i] [%2].", {"����", "�����", "�����"}},
{Money, "�������� [%3i] [%2].", "�������� [%3i] [%2].", {"��������", "������", "�������"}},
{Sanity, "�������� [%3i] [%2].", "�������� [%3i] [%2].", {"��������", "��������", "��������"}},
{Stamina, "�������� [%3i] [%2].", "�������� [%3i] [%2].", {"��������", "��������", "��������"}},
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
		(this->*e.set)(e.stat, e.card, e.location, e.count, interactive);
	if(discard)
		*discard = (id == Discard);
}

void hero::add(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	count = getcount(stat, count);
	auto& e = getcase(stat);
	if(count >= 0)
		logs::add(1, e.increment, getstr(stat), e.get(count), count);
	else
		logs::add(1, e.decrement, getstr(stat), e.get(-count), -count);
	auto result = logs::input(interactive, false, "��� ������ ������?");
	switch(result) {
	case 1:
		auto value = get(stat) + count;
		if(value < 0)
			value = 0;
		set(stat, value);
		break;
	}
}

void hero::restoreall(stat_s stat, card_s card, location_s location, int value, bool interactive) {
	logs::add(1, "����������� �������� � ������� �� ���������.");
	logs::input(interactive, false, "��� ������ ������?");
	set(Stamina, get(StaminaMaximum));
	set(Sanity, get(SanityMaximum));
}

void hero::skipturn(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	logs::add(1, "���������� ��������� ���");
	logs::input(interactive, false, "��� ������?");
	stats[TurnToSkip]++;
}

void hero::leaveoutside(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	logs::add(1, "����� ������");
	logs::input(interactive, false, "��� ������?");
	position = location_data[position].neightboard[0];
}

void hero::arrested(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	logs::add(1, "����������� � ����������� �������");
	logs::input(interactive, false, "��� ������?");
	stats[TurnToSkip]++;
	set(Money, get(Money) / 2);
	position = PoliceStation;
}

void hero::losememory(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	if(get(Clue)>=4)
		logs::add(1, "�������� [4] �����");
	if(getspells() >= 2)
		logs::add(2, "�������� [2] ����������");
	if(getskills() >= 1)
		logs::add(3, "�������� [1] �����");
	card_s item;
	switch(logs::input(interactive, false, "��� ������?")) {
	case 1:
		set(Clue, get(Clue) - 4);
		break;
	case 2:
		for(int i = 0; i < 2; i++) {
			item = chooseexist("����� ���������� ��������?", BindMonster, Wither, interactive);
			if(cards[item]>0)
				cards[item]--;
		}
		break;
	case 3:
		item = chooseexist("����� ����� ��������?", SkillBarvery, SkillLuck, interactive);
		if(cards[item]>0)
			cards[item]--;
		break;
	}
}

void hero::monsterappear(stat_s stat, card_s card, location_s location, int count, bool interactive) {
}

void hero::addally(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	char temp[512];
	if(get(card)) {
		switch(card) {
		case JohnLegrasse:
			break;
		}
		return;
	}
	logs::driver driver;
	driver.gender = Male;
	driver.name = getstr(card);
	driver.prints(temp, zendof(temp), "��� ���%� [%�����] � %��� �����%� �������������� � ���.");
	logs::add(temp);
	logs::next(interactive);
	cards[card] = 1;
}

void hero::chooselocation(stat_s stat, card_s card, location_s location, int count, bool interactive) {
}

card_s hero::chooseexist(const char* text, card_s from, card_s to, bool interactive) const {
	for(auto i = from; i <= to; i = (card_s)(i + 1)) {
		if(get(i) == 0)
			continue;
		logs::add(i, getstr(i));
	}
	if(!logs::getcount())
		return NoItem;
	logs::sort();
	return (card_s)logs::input(interactive, false, text);
}

void hero::addmagic(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	auto value = get(Blessed) + count;
	if(value < -1 || value > 1) {
		logs::next();
		return;
	}
	switch(value) {
	case 1:
		logs::add(1, "�������� �������������");
		break;
	case -1:
		logs::add(1, "�������� ���������");
		break;
	default:
		if(get(Blessed)>0)
			logs::add(1, "����� �������������");
		else
			logs::add(1, "����� ���������");
		break;
	}
	logs::input(interactive, false, "��� ������?");
	set(Blessed, value);
}

void hero::choose(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	auto draw_count = count;
	auto draw_bottom = 0;
	if(is(Scrounge)) {
		if(stat == CommonItem || stat == UniqueItem || stat == Spell)
			draw_bottom++;
	}
	choose(stat, count, draw_count, draw_bottom, interactive);
}

void hero::chooseone(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	auto draw_count = 1;
	auto draw_bottom = 0;
	if(is(Scrounge)) {
		if(stat == CommonItem || stat == UniqueItem || stat == Spell)
			draw_bottom++;
	}
	choose(stat, count, draw_count, draw_bottom, interactive);
}