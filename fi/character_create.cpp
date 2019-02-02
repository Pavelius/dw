#include "main.h"

static gender_s choose_gender(bool interactive) {
	logs::add(Male, getstr(Male));
	logs::add(Female, getstr(Female));
	return (gender_s)logs::input(interactive, true, "Кто вы?");
}

static race_s choose_race(bool interactive) {
	for(auto i = Dwarf; i <= Wolfkin; i = (race_s)(i + 1))
		logs::add(i, getstr(i));
	logs::sort();
	return (race_s)logs::input(interactive, true, "Откуда вы?");
}

profession_s character::choose_profession(bool interactive) const {
	for(auto i = Druid; i <= Sorcerer; i = (profession_s)(i + 1))
		logs::add(i, getpriority(race, i), getstr(i));
	logs::sort();
	return (profession_s)logs::input(interactive, true, "Чем вы занимаетесь?");
}

static void add_type(race_s race, gender_s gender, profession_s profession) {
	logs::add("Итак, вы %-1 %-2 %-3.", getstr(race), getstr(gender), getstr(profession));
}

static void add_attributes(const char* source) {
	for(auto i = Strenght; i <= Empathy; i = (ability_s)(i + 1)) {
		if(i != Strenght)
			logs::add(", ");
		logs::add("%1: [%2i]", getstr(i), source[i]);
	}
}

static void add_skills(const char* source, const char* title) {
	auto p = logs::getptr();
	for(auto i = Might; i <= AnimalHandling; i = (skill_s)(i + 1)) {
		auto v = source[i];
		if(!v)
			continue;
		if(p == logs::getptr())
			logs::add("%1: ", title);
		else
			logs::add(", ");
		logs::add("%1:%2i", getstr(i), v);
	}
	if(p != logs::getptr())
		logs::add(".");
}

void character::choose_attributes(int points, bool interactive) {
	for(auto i = Strenght; i <= Empathy; i = (ability_s)(i + 1)) {
		ability[i] = getminimum(i);
		points -= ability[i];
	}
	while(points > 0) {
		add_type(race, gender, profession);
		logs::add("Определите ваши способности.\n");
		add_attributes(ability);
		for(auto i = Strenght; i <= Empathy; i = (ability_s)(i + 1)) {
			auto v = get(i);
			if(v >= getmaximum(i))
				continue;
			logs::add(i, getpriority(i), "Увеличить %1 до [%2i]", getstr(i), v + 1);
		}
		auto r = (ability_s)logs::input(interactive, true, "Осталось еще (%1i очков)", points);
		ability[r] += 1;
		points -= 1;
	}
}

void character::choose_skills(int points, bool interactive) {
	while(points > 0) {
		add_type(race, gender, profession); logs::add("\n");
		add_attributes(ability); logs::add("\n");
		add_skills(skills, "Навыки");
		for(auto i = Might; i <= AnimalHandling; i = (skill_s)(i + 1)) {
			auto v = get(i);
			if(v >= getmaximum(i))
				continue;
			logs::add(i, getmaximum(i), getstr(i));
		}
		auto r = (skill_s)logs::input(interactive, true, "Выбирайте навык (еще [%1i])", points);
		skills[r] += 1;
		points -= 1;
	}
}

void character::create(bool interactive) {
	clear();
	gender = choose_gender(interactive);
	race = choose_race(interactive);
	profession = choose_profession(interactive);
	choose_attributes(15, interactive);
	choose_skills(8, interactive);
}