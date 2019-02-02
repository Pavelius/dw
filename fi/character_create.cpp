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
	if(!source[0])
		return;
	for(auto i = Strenght; i <= Empathy; i = (ability_s)(i + 1)) {
		if(i != Strenght)
			logs::add(", ");
		logs::add("%1: [%2i]", getstr(i), source[i]);
	}
}

static void add_skills(const char* source, const char* footer) {
	auto p = logs::getptr();
	auto title = "Навыки";
	for(auto i = Might; i <= AnimalHandling; i = (skill_s)(i + 1)) {
		auto v = source[i];
		if(!v)
			continue;
		if(p == logs::getptr())
			logs::add("%1: ", title);
		else
			logs::add(", ");
		if(v >= 2)
			logs::add("%1:%2i", getstr(i), v);
		else
			logs::add("%1", getstr(i));
	}
	if(p != logs::getptr() && footer)
		logs::add(footer);
}

static void add_talents(const char* source, const char* footer) {
	auto p = logs::getptr();
	auto title = "Таланты";
	for(auto i = FirstTalent; i <= LastTalent; i = (talent_s)(i + 1)) {
		auto v = source[i];
		if(!v)
			continue;
		if(p == logs::getptr())
			logs::add("%1: ", title);
		else
			logs::add(", ");
		if(v>=2)
			logs::add("%1:%2i", getstr(i), v);
		else
			logs::add("%1", getstr(i));
	}
	if(p != logs::getptr() && footer)
		logs::add(".");
}

void character::add_info() const {
	add_type(race, gender, profession); logs::add("\n");
	add_attributes(ability); logs::add("\n");
	add_skills(skills, ".\n");
	add_talents(talents, ".\n");
}

void character::choose_attributes(int points, bool interactive) {
	for(auto i = Strenght; i <= Empathy; i = (ability_s)(i + 1)) {
		ability[i] = getminimum(i);
		points -= ability[i];
	}
	while(points > 0) {
		add_info();
		for(auto i = Strenght; i <= Empathy; i = (ability_s)(i + 1)) {
			auto v = get(i);
			if(v >= getmaximum(i))
				continue;
			logs::add(i, getpriority(i), "Увеличить %1 до [%2i]", getstr(i), v + 1);
		}
		auto r = (ability_s)logs::input(interactive, true, "Выберите ваши атрибуты (осталось еще %1i)", points);
		ability[r] += 1;
		points -= 1;
	}
}

void character::choose_skills(int points, bool interactive) {
	while(points > 0) {
		add_info();
		for(auto i = Might; i <= AnimalHandling; i = (skill_s)(i + 1)) {
			auto v = get(i);
			if(v >= getmaximum(i))
				continue;
			logs::add(i, getmaximum(i), getstr(i));
		}
		logs::sort();
		auto r = (skill_s)logs::input(interactive, true, "Выбирайте навык (еще [%1i])", points);
		skills[r] += 1;
		points -= 1;
	}
}

void character::choose_talents(int points, const variant filter, bool interactive) {
	while(points > 0) {
		add_info();
		for(auto i = FirstTalent; i <= LastTalent; i = (talent_s)(i + 1)) {
			if(getkey(i) != filter)
				continue;
			logs::add(i, 1, getstr(i));
		}
		logs::sort();
		auto r = (talent_s)logs::input(interactive, true, "Выбирайте талант (еще [%1i])", points);
		talents[r] += 1;
		points -= 1;
	}
}

void character::choose_talents(bool interactive) {
	add_info();
	auto profession_talant = 1;
	auto general_talant = 1;
	logs::add(1, "Я талантлив в своей професии. Это даст мне [%1i] профессиональных таланта, но [%2i] общих таланта.", profession_talant+1, general_talant - 1);
	logs::add(2, "Я обычный специалист своего дела. Это даст мне [%1i] профессиональных таланта, но [%2i] общих таланта.", profession_talant, general_talant);
	switch(logs::input(interactive, true, "Теперь вам надо выбрать в чем вы талантливы.")) {
	case 1: profession_talant++; general_talant--; break;
	}
	choose_talents(profession_talant, profession, interactive);
	choose_talents(general_talant, variant(), interactive);
}

void character::create(bool interactive) {
	clear();
	gender = choose_gender(interactive);
	race = choose_race(interactive);
	profession = choose_profession(interactive);
	choose_attributes(15, interactive);
	choose_skills(8, interactive);
	apply_talents();
	choose_talents(interactive);
}