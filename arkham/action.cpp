#include "main.h"

static struct action_i {
	const char*		id;
	const char*		name;
	stat_s			stat;
	int				count;
	void			(hero::*set)(stat_s id, int count, bool interactive);
} action_data[] = {
	{"", ""},
	{"gain 1 clue", "получить 1 улику", Clue, 1, &hero::add},
	{"gain 2 clues", "получить 2 улики", Clue, 2, &hero::add},
	{"gain 3 clues", "получить 3 улики", Clue, 3, &hero::add},
	{"gain 4 clues", "получить 4 улики", Clue, 4, &hero::add},
	{"gain 5 clues", "получить 5 улик", Clue, 5, &hero::add},
	{"lose 1 clue", "потерять 1 улику", Clue, 1, &hero::add},
	{"lose 2 clues", "потерять 2 улики", Clue, 2, &hero::add},
	{"lose 3 clues", "потерять 3 улики", Clue, 3, &hero::add},
	{"lose 4 clues", "потерять 4 улики", Clue, 4, &hero::add},
	{"lose 5 clues", "потерять 5 улик", Clue, 5, &hero::add},
	{"gain 1 dollar", "получить 1 доллар", Money, 1, &hero::add},
	{"gain 2 dollars", "получить 2 доллара", Money, 2, &hero::add},
	{"gain 3 dollars", "получить 3 доллара", Money, 3, &hero::add},
	{"gain 4 dollars", "получить 4 доллара", Money, 4, &hero::add},
	{"gain 5 dollars", "получить 5 долларов", Money, 5, &hero::add},
	{"gain 6 dollars", "получить 6 долларов", Money, 6, &hero::add},
	{"gain 7 dollars", "получить 7 долларов", Money, 7, &hero::add},
	{"gain 8 dollars", "получить 8 долларов", Money, 8, &hero::add},
	{"gain 9 dollars", "получить 9 долларов", Money, 9, &hero::add},
	{"gain 10 dollars", "получить 10 долларов", Money, 10, &hero::add},
	{"lose 1 dollar", "потерять 1 доллар", Money, 1, &hero::add},
	{"lose 2 dollars", "потерять 2 доллара", Money, 2, &hero::add},
	{"lose 3 dollars", "потерять 3 доллара", Money, 3, &hero::add},
	{"lose 4 dollars", "потерять 4 доллара", Money, 4, &hero::add},
	{"lose 5 dollars", "потерять 5 долларов", Money, 5, &hero::add},
	{"gain 1 sanity", "получить 1 рассудок", Sanity, 1, &hero::add},
	{"gain 2 sanity", "получить 2 рассудка", Sanity, 2, &hero::add},
	{"gain 3 sanities", "получить 3 рассудка", Sanity, 3, &hero::add},
	{"lose 1 sanity", "потерять 1 рассудок", Sanity, 1, &hero::add},
	{"lose 2 sanity", "потерять 2 рассудка", Sanity, 2, &hero::add},
	{"lose 3 sanities", "потерять 3 рассудка", Sanity, 3, &hero::add},
	{"gain 1 stamina", "получить 1 жизнь", Stamina, 1, &hero::add},
	{"gain 2 staminas", "получить 2 жизни", Stamina, 2, &hero::add},
	{"gain 3 staminas", "получить 3 жизни", Stamina, 3, &hero::add},
	{"lose 1 stamina", "потерять 1 жизнь", Stamina, 1, &hero::add},
	{"lose 2 staminas", "потерять 2 жизни", Stamina, 2, &hero::add},
	{"lose 3 staminas", "потерять 3 жизни", Stamina, 3, &hero::add},
	{"gain common item", "получить обычный предмет", CommonItem, 1, &hero::choose},
	{"gain 2 common items", "получить 2 обычных предмета", CommonItem, 2, &hero::choose},
	{"gain unique item", "получить уникальный предмет", UniqueItem, 1, &hero::choose},
	{"gain skill", "получить навык", Skill, 1, &hero::choose},
	{"gain spell", "получить заклинание", Spell, 1, &hero::choose},
	{"discard", "сбросить"},
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
} case_data[] = {{Clue, "%герой получил%а [%3i] [%2]", "%герой потерял%а [%3i] [%2]", {"улик", "улика", "улики"}},
{Money, "%герой получил%а [%3i] [%2]", "%герой потерял%а [%3i] [%2]", {"долларов", "доллар", "доллара"}},
{Sanity, "%герой получил%а [%3i] [%2]", "%герой потерял%а [%3i] [%2]", {"рассудка", "рассудок", "рассудка"}},
{Stamina, "%герой получил%а [%3i] [%2]", "%герой потерял%а [%3i] [%2]", {"здоровья", "здоровье", "здоровья"}},
{Skill, "%герой изучил навык [%1]", "%герой забыл навык [%1]"},
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