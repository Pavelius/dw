#include "main.h"

background_info background_data[] = {{},
{"Acolyte", "Аколит", {Insight, Religion}, 2, {}, {Book, HolySymbol}},
{"Criminal", "Преступник", {Deception, Stealth}, 0, {GamingProficiency, TheifToolsProficiency}, {Crowbar}, 15},
{"Folk Hero", "Народный герой", {AnimalHandling, Survival}, 0, {RidingProficiency}, {}},
{"Noble", "Знать", {History, Persuasion}, 1, {GamingProficiency}},
{"Sage", "Мудрец", {Arcana, History}, 2},
{"Soldier", "Солдат", {Athletics, Intimidation}, 0, {GamingProficiency, RidingProficiency}},
};
assert_enum(background, Soldier);
getstr_enum(background);

void creature::apply(background_s id, bool interactive) {
	set(background_data[id].skills[0]);
	set(background_data[id].skills[0]);
}