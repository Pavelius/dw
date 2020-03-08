#include "main.h"

backgroundi bsmeta<backgroundi>::elements[] = {{},
{"Acolyte", "������", {Insight, Religion}, 2, {}, {Book, HolySymbol}},
{"Criminal", "����������", {Deception, Stealth}, 0, {GamingProficiency, TheifToolsProficiency}, {Crowbar}, 15},
{"Folk Hero", "�������� �����", {AnimalHandling, Survival}, 0, {RidingProficiency}, {}},
{"Noble", "�����", {History, Persuasion}, 1, {GamingProficiency}},
{"Sage", "������", {Arcana, History}, 2},
{"Soldier", "������", {Athletics, Intimidation}, 0, {GamingProficiency, RidingProficiency}},
};
assert_enum(background, Soldier);

void creature::apply(background_s id, bool interactive) {
	set(bsmeta<backgroundi>::elements[id].skills[0]);
	set(bsmeta<backgroundi>::elements[id].skills[0]);
}