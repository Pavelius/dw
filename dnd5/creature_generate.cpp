#include "main.h"

static void add_count(char* result, const char* result_maximum, int count) {
	if(count < 2)
		return;
	szprints(zend(result), result_maximum, " (осталось %1i)", count);
}

static const char* print_ability(char* result, const char* result_maximum, char* ability, bool name = false) {
	result[0] = 0;
	auto p = result;
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
		if(!ability[i])
			continue;
		if(p != result) {
			szprints(p, result_maximum, ", ");
			p = zend(result);
		}
		szprints(p, result_maximum, name ? "%1 %2i" : "%2i", getstr(i), ability[i]);
		p = zend(result);
	}
	p[0] = 0;
	return result;
}

gender_s creature::choose_gender(bool interactive) {
	logs::add(Male, getstr(Male));
	logs::add(Female, getstr(Female));
	return (gender_s)logs::input(interactive, true, "Кто вы?");
}

class_s creature::choose_class(bool interactive) {
	for(auto e = Cleric; e <= Wizard; e = (class_s)(e + 1))
		logs::add(e, getstr(e));
	logs::sort();
	return (class_s)logs::input(interactive, true, "Чем вы занимаетесь?");
}

background_s creature::choose_background(bool interactive) {
	for(auto e = Acolyte; e <= Soldier; e = (background_s)(e + 1))
		logs::add(e, getstr(e));
	logs::sort();
	return (background_s)logs::input(interactive, true, "Кем вы были раньше?");
}

race_s creature::choose_race(bool interactive) {
	for(auto e = Dwarf; e <= Human; e = (race_s)(e + 1))
		logs::add(e, getstr(e));
	logs::sort();
	return (race_s)logs::input(interactive, true, "Откуда вы родом?");
}

domain_s creature::choose_domain(bool interactive) {
	return LifeDomain;
}

race_s creature::choose_subrace(race_s race, bool interactive) {
	for(auto e = Dwarf; e <= HalflingStout; e = (race_s)(e + 1)) {
		if(race == race_data[e].basic)
			logs::add(e, getstr(e));
	}
	if(logs::getcount() == 0)
		return NoRace;
	logs::sort();
	return (race_s)logs::input(interactive, true, "Какой именно вы [%1]?", getstr(race));
}

void creature::choose_ability(char* result, bool interactive) {
	char temp[260];
	while(true) {
		random_ability(result);
		print_ability(temp, zendof(temp), result);
		logs::add(1, "Взять эти атрибуты");
		logs::add(2, "Перебросить");
		auto id = logs::input(interactive, true, "Вы выбросили: %1.", temp);
		if(id == 1)
			return;
	}
}

void creature::show_ability() {
	char temp[512];
	szprints(temp, zendof(temp), "Способности: ");
	print_ability(zend(temp), zendof(temp), ability, true);
	szprints(zend(temp), zendof(temp), ".\n");
	logs::add(temp);
}

void creature::place_ability(char* result, char* ability, bool interactive) {
	memset(result, 0, 6);
	for(auto s = 0; s < 6; s++) {
		for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
			if(result[i])
				continue;
			logs::add(i, getstr(i));
		}
		if(logs::getcount() == 0)
			break;
		auto id = (ability_s)logs::input(interactive, true, "Куда хотиет распределить [%1i]?", ability[s]);
		result[id] = ability[s];
	}
}

void creature::choose_skills(class_s type, bool interactive) {
	char temp[260]; szprints(temp, zendof(temp), "Как %1 выберите навыки", getstr(type));
	apply(class_data[type].skills, temp, class_data[type].start_skills, interactive);
}

item_s creature::choose_absent_item(feat_s feat, const char* title, bool interactive) const {
	for(auto it = NoItem; it <= LastItem; it = (item_s)(it + 1)) {
		if(!item(it).is(feat))
			continue;
		if(!isproficient(it))
			continue;
		if(has(it))
			continue;
		logs::add(it, getstr(it));
	}
	if(logs::getcount() == 0)
		return NoItem;
	logs::sort();
	return (item_s)logs::input(interactive, false, title);
}

void creature::apply(const aref<variant>& elements, const char* title, int count, bool interactive) {
	char temp[260];
	while(count > 0) {
		for(auto it : elements) {
			if(!isallow(it))
				continue;
			logs::add(it, getstr(it));
		}
		if(!logs::getcount())
			break;
		logs::sort();
		szprints(temp, zendof(temp), title);
		add_count(temp, zendof(temp), count);
		auto result = (variant)logs::input(interactive, false, temp);
		set(result);
		count--;
	}
}

void creature::apply(variant v1, variant v2, const char* title, int count, bool interactive) {
	adat<variant, 256> elements;
	for(auto v = v1; v.number != v2.number; v.number++)
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