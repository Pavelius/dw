#include "main.h"

static gender_s choose_gender(bool interactive) {
	an.add(Male, getstr(Male));
	an.add(Female, getstr(Female));
	return (gender_s)an.choose(interactive, true, "Кто вы?");
}

static race_s choose_race(bool interactive) {
	for(auto i = Dwarf; i <= Wolfkin; i = (race_s)(i + 1))
		an.add(i, getstr(i));
	an.sort();
	return (race_s)an.choose(interactive, true, "Откуда вы?");
}

profession_s character::choose_profession(bool interactive) const {
	for(auto i = Druid; i <= Sorcerer; i = (profession_s)(i + 1))
		an.addv(i, getpriority(race, i), getstr(i), 0);
	an.sort();
	return (profession_s)an.choose(interactive, true, "Чем вы занимаетесь?");
}

static void add_type(stringbuilder& sb, race_s race, gender_s gender, profession_s profession) {
	sb.addn("Итак, вы %-1 %-2 %-3.", getstr(race), getstr(gender), getstr(profession));
}

static void add_attributes(stringbuilder& sb, const char* source) {
	if(!source[0])
		return;
	for(auto i = Strenght; i <= Empathy; i = (ability_s)(i + 1)) {
		if(i != Strenght)
			sb.add(", ");
		else
			sb.addn("Атрибуты: ");
		sb.add("%1:%2i", getstr(i), source[i]);
	}
}

static void add_skills(stringbuilder& sb, const char* source, const char* footer) {
	auto title = "Навыки";
	auto p = sb.get();
	for(auto i = Might; i <= AnimalHandling; i = (skill_s)(i + 1)) {
		auto v = source[i];
		if(!v)
			continue;
		if(sb.ispos(p))
			sb.addn("%1: ", title);
		else
			sb.add(", ");
		if(v >= 2)
			sb.add("%1:%2i", getstr(i), v);
		else
			sb.add("%1", getstr(i));
	}
	if(footer && !sb.ispos(p))
		sb.add(footer);
}

static void add_talents(stringbuilder& sb, const char* source, const char* footer) {
	auto title = "Таланты";
	auto p = sb.get();
	for(auto i = FirstTalent; i <= LastTalent; i = (talent_s)(i + 1)) {
		auto v = source[i];
		if(!v)
			continue;
		if(sb.ispos(p))
			sb.addn("%1: ", title);
		else
			sb.add(", ");
		if(v>=2)
			sb.add("%1:%2i", getstr(i), v);
		else
			sb.add("%1", getstr(i));
	}
	if(!sb.ispos(p) && footer)
		sb.add(footer);
}

void character::add_info(stringbuilder& sb) const {
	add_type(sb, race, gender, profession);
	add_attributes(sb, ability);
	add_skills(sb, skills, ".");
	add_talents(sb, talents, ".");
}

void character::choose_attributes(int points, bool interactive) {
	for(auto i = Strenght; i <= Empathy; i = (ability_s)(i + 1)) {
		ability[i] = getminimum(i);
		points -= ability[i];
	}
	while(points > 0) {
		add_info(sb);
		for(auto i = Strenght; i <= Empathy; i = (ability_s)(i + 1)) {
			auto v = get(i);
			if(v >= getmaximum(i))
				continue;
			an.addp(i, getpriority(i), "Увеличить %1 до [%2i].", getstr(i), v + 1);
		}
		auto r = (ability_s)an.choose(interactive, true, "Выберите атрибуты (еще [%1i]):", points);
		ability[r] += 1;
		points -= 1;
	}
}

void character::choose_skills(int points, bool interactive) {
	while(points > 0) {
		add_info(sb);
		for(auto i = Might; i <= AnimalHandling; i = (skill_s)(i + 1)) {
			auto v = get(i);
			if(v >= getmaximum(i))
				continue;
			an.addp(i, getmaximum(i), getstr(i));
		}
		an.sort();
		auto r = (skill_s)an.choose(interactive, true, "Выбирайте навык (еще [%1i]):", points);
		skills[r] += 1;
		points -= 1;
	}
}

void character::choose_talents(int points, const variant filter, bool interactive) {
	while(points > 0) {
		add_info(sb);
		for(auto i = FirstTalent; i <= LastTalent; i = (talent_s)(i + 1)) {
			if(getkey(i) != filter)
				continue;
			an.addp(i, 1, getstr(i));
		}
		an.sort();
		auto r = (talent_s)an.choose(interactive, true, "Выбирайте талант (еще [%1i]):", points);
		talents[r] += 1;
		points -= 1;
	}
}

void character::choose_talents(bool interactive) {
	add_info(sb);
	auto profession_talant = 1;
	auto general_talant = 1;
	an.add(1, "Я талантлив в своей професии. Это даст мне [%1i] профессиональных таланта, но [%2i] общих таланта.", profession_talant+1, general_talant - 1);
	an.add(2, "Я обычный специалист своего дела. Это даст мне [%1i] профессиональных таланта, но [%2i] общих таланта.", profession_talant, general_talant);
	switch(an.choose(interactive, true, "Теперь вам надо выбрать в чем вы талантливы.")) {
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
	pride = 1;
	choose_attributes(15, interactive);
	choose_skills(8, interactive);
	apply_talents();
	apply_equipment(interactive);
	choose_talents(interactive);
	name = getrandomname(race, gender);
}