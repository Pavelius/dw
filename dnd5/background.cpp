#include "main.h"

background_info background_data[] = {{},
{"Acolyte", "������", {Insight, Religion}, 2, {}, {Book, HolySymbol}},
{"Criminal", "����������", {Deception, Stealth}, 0, {GamingProficiency, TheifToolsProficiency}, {Crowbar}, 15},
{"Folk Hero", "�������� �����", {AnimalHandling, Survival}, 0, {RidingProficiency}, {}},
{"Noble", "�����", {History, Persuasion}, 1, {GamingProficiency}},
{"Sage", "������", {Arcana, History}, 2},
{"Soldier", "������", {Athletics, Intimidation}, 0, {GamingProficiency, RidingProficiency}},
};
assert_enum(background, Soldier);
getstr_enum(background);

void creature::apply(background_s id, bool interactive) {
	set(background_data[id].skills[0]);
	set(background_data[id].skills[0]);
}