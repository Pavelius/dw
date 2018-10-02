#include "main.h"

background_info background_data[] = {{},
{"Acolyte", "Аколит", {Insight, Religion}, {2}, {Book, HolySymbol}},
{"Criminal", "Преступник", {Deception, Stealth}, {}, {}, {TheifToolsProficiency, GamingSet}, 15},
{"Folk Hero", "Народный герой", {AnimalHandling, Survival}},
{"Noble", "Знать", {History, Persuasion}, {1}},
{"Sage", "Мудрец", {Arcana, History}, {0, 2}},
{"Soldier", "Солдат", {Athletics, Intimidation}},
};
assert_enum(background, Soldier);
getstr_enum(background);

void creature::apply(background_s id, bool interactive) {
	set(background_data[id].skills[0]);
	set(background_data[id].skills[0]);
}