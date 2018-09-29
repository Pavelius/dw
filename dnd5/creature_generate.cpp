#include "main.h"

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

creature* creature::generate(bool interactive) {
	static feat_s weapon_style[] = {StyleArchery, StyleDefense, StyleDueling, StyleGreatWeaponFighting, StyleProtection, StyleTwoWeaponFighting};
	auto gender = choose_gender(interactive);
	auto race = choose_race(interactive);
	auto subrace = choose_subrace(race, interactive);
	auto type = choose_class(interactive);
	auto background = choose_background(interactive);
	auto p = new creature(race, gender, type, background, interactive);
	return p;
}

void creature::apply(aref<feat_s> elements, const char* title, bool interactive) {
	for(auto e : elements) {
		if(is(e))
			continue;
		logs::add(e, getstr(e));
	}
	auto result = (feat_s)logs::input(interactive, true, title);
	set(result);
}