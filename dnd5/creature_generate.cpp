#include "main.h"

static void add_count(stringbuilder& sb, int count) {
	if(count < 2)
		return;
	sb.add(" (осталось %1i)", count);
}

static void add_ability(stringbuilder& sb, char* ability, bool name = false) {
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
		if(!ability[i])
			continue;
		if(sb)
			sb.add(", ");
		sb.add(name ? "%1 %2i" : "%2i", getstr(i), ability[i]);
	}
}

static void add_variant(variant v) {
	auto pi = v.getinfo();
	auto ps = getstr(v);
	if(pi && pi[0])
		an.add(v, "[%+1]. %2", ps, pi);
	else
		an.add(v, ps);
}

static void add_value(variant v) {
	auto pi = v.getinfo();
	auto ps = getstr(v);
	if(pi && pi[0])
		an.add(v.value, "[%+1]. %2", ps, pi);
	else
		an.add(v.value, ps);
}

gender_s creature::choose_gender(bool interactive) {
	an.add(Male, getstr(Male));
	an.add(Female, getstr(Female));
	return (gender_s)an.choose(interactive, true, "Кто вы?");
}

class_s creature::choose_class(bool interactive) {
	for(auto e = Cleric; e <= Wizard; e = (class_s)(e + 1))
		an.add(e, getstr(e));
	an.sort();
	return (class_s)an.choose(interactive, true, "Чем вы занимаетесь?");
}

background_s creature::choose_background(bool interactive) {
	for(auto e = Acolyte; e <= Soldier; e = (background_s)(e + 1))
		an.add(e, getstr(e));
	an.sort();
	return (background_s)an.choose(interactive, true, "Кем вы были раньше?");
}

race_s creature::choose_race(bool interactive) {
	for(auto e = Dwarf; e <= Human; e = (race_s)(e + 1))
		add_value(e);
	an.sort();
	return (race_s)an.choose(interactive, true, "Откуда вы родом?");
}

domain_s creature::choose_domain(bool interactive) {
	return LifeDomain;
}

race_s creature::choose_subrace(race_s race, bool interactive) {
	for(auto e = Dwarf; e <= HalflingStout; e = (race_s)(e + 1)) {
		if(race == bsmeta<racei>::elements[e].basic)
			add_value(e);
	}
	if(!an)
		return NoRace;
	an.sort();
	return (race_s)an.choose(interactive, true, "Какой именно вы [%1]?", getstr(race));
}

void creature::choose_ability(char* result, bool interactive) {
	char temp[260]; stringbuilder sb(temp);
	while(true) {
		random_ability(result);
		sb.clear(); add_ability(sb, result);
		an.add(1, "Взять эти атрибуты");
		an.add(2, "Перебросить");
		auto id = an.choose(interactive, true, "Вы выбросили: %1.", temp);
		if(id == 1)
			return;
	}
}

void creature::show_ability() {
	sb.add("Способности: ");
	add_ability(sb, ability, true);
	sb.add(".\n");
}

void creature::place_ability(char* result, char* ability, bool interactive) {
	memset(result, 0, 6);
	for(auto s = 0; s < 6; s++) {
		for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
			if(result[i])
				continue;
			an.add(i, getstr(i));
		}
		if(!an)
			break;
		auto id = (ability_s)an.choose(interactive, true, "Куда хотиет распределить [%1i]?", ability[s]);
		result[id] = ability[s];
	}
}

void creature::choose_skills(class_s type, bool interactive) {
	char temp[260]; stringbuilder sb(temp);
	sb.add("Как %1 выберите навыки", getstr(type));
	apply(bsmeta<classi>::elements[type].skills, temp, bsmeta<classi>::elements[type].start_skills, interactive);
}

item_s creature::choose_absent_item(feat_s feat, const char* title, bool interactive) const {
	for(auto it = NoItem; it <= LastItem; it = (item_s)(it + 1)) {
		if(!item(it).is(feat))
			continue;
		if(!isproficient(it))
			continue;
		if(has(it))
			continue;
		an.add(it, getstr(it));
	}
	if(!an)
		return NoItem;
	an.sort();
	return (item_s)an.choose(interactive, false, title);
}

void creature::apply(const aref<variant>& elements, const char* title, int count, bool interactive) {
	char temp[260]; stringbuilder sb(temp);
	while(count > 0) {
		for(auto it : elements) {
			if(!isallow(it))
				continue;
			add_variant(it);
		}
		if(!an)
			break;
		an.sort();
		sb.clear();
		sb.add(title);
		add_count(sb, count);
		auto result = (variant)an.choose(interactive, false, temp);
		set(result);
		count--;
	}
}

void creature::apply(variant v1, variant v2, const char* title, int count, bool interactive) {
	adat<variant, 256> elements;
	for(auto v = v1; v.value != v2.value; v.value++)
		elements.add(v);
	apply(elements, title, count, interactive);
}

creature* creature::generate(bool interactive) {
	char random[6] = {10, 10, 10, 10, 10, 10};
	char ability[6] = {10, 10, 10, 10, 10, 10};
	auto gender = choose_gender(interactive);
	auto race = choose_race(interactive);
	auto subrace = choose_subrace(race, interactive);
	auto background = choose_background(interactive);
	auto type = choose_class(interactive);
	choose_ability(random, interactive);
	place_ability(ability, random, interactive);
	if(subrace)
		race = subrace;
	return new creature(race, gender, type, background, ability, interactive);
}