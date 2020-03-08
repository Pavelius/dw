#include "main.h"

backgroundi bsmeta<backgroundi>::elements[] = {{},
{"Acolyte", "Аколит", {Insight, Religion}, 2, {}, {Book, HolySymbol}},
{"Criminal", "Преступник", {Deception, Stealth}, 0, {GamingProficiency, TheifToolsProficiency}, {Crowbar}, 15},
{"Folk Hero", "Народный герой", {AnimalHandling, Survival}, 0, {RidingProficiency}, {}},
{"Noble", "Знать", {History, Persuasion}, 1, {GamingProficiency}},
{"Sage", "Мудрец", {Arcana, History}, 2},
{"Soldier", "Солдат", {Athletics, Intimidation}, 0, {GamingProficiency, RidingProficiency}},
};
assert_enum(background, Soldier);

void creature::apply(background_s id, bool interactive) {
	set(bsmeta<backgroundi>::elements[id].skills[0]);
	set(bsmeta<backgroundi>::elements[id].skills[0]);
}