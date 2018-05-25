#include "main.h"

static struct action_i {
	stat_s			stat;
	int				count;
	void			(hero::*set)(stat_s id, int count, bool interactive);
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
{Movement, 1, &hero::skipturn},
{Movement, 1, &hero::skipturn},
{Movement, 1, &hero::skipturn},
{Movement, 1, &hero::skipturn},
{Blessed, -1, &hero::addmagic},
{Blessed, 1, &hero::addmagic},
{Blessed, 1, &hero::addmagic},
{Blessed, -1, &hero::addmagic},
{CommonItem, 1, &hero::choose},
{CommonItem, 2, &hero::choose},
{UniqueItem, 1, &hero::choose},
{Skill, 1, &hero::choose},
{Spell, 1, &hero::choose},
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
} case_data[] = {{Clue, "Получить [%3i] [%2].", "Потерять [%3i] [%2].", {"улик", "улику", "улики"}},
{Money, "Получить [%3i] [%2].", "Потерять [%3i] [%2].", {"долларов", "доллар", "доллара"}},
{Sanity, "Получить [%3i] [%2].", "Потерять [%3i] [%2].", {"рассудка", "рассудок", "рассудка"}},
{Stamina, "Получить [%3i] [%2].", "Потерять [%3i] [%2].", {"здоровья", "здоровье", "здоровья"}},
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
	auto& e = getcase(id);
	if(count >= 0)
		logs::add(1, e.increment, getstr(id), e.get(count), count);
	else
		logs::add(1, e.decrement, getstr(id), e.get(-count), -count);
	auto result = logs::input(interactive, false, "Что будете делать?");
	switch(result) {
	case 1:
		auto value = get(id) + count;
		if(value < 0)
			value = 0;
		break;
	}
}

void hero::skipturn(stat_s id, int count, bool interactive) {
	logs::add(1, "Пропустить следующий ход");
	logs::input(interactive, false, "Что делать?");
	stats[TurnToSkip]++;
}

void hero::chooselocation(stat_s id, int count, bool interactive) {
}

void hero::addmagic(stat_s id, int count, bool interactive) {
	auto value = get(Blessed) + count;
	if(value < -1 || value > 1) {
		logs::next();
		return;
	}
	switch(value) {
	case 1:
		logs::add(1, "Получить благословение");
		break;
	case -1:
		logs::add(1, "Получить проклятие");
		break;
	default:
		if(get(Blessed)>0)
			logs::add(1, "Снять благословение");
		else
			logs::add(1, "Снять проклятие");
		break;
	}
	logs::input(interactive, false, "Что делать?");
	set(Blessed, value);
}