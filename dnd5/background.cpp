#include "main.h"

background_info background_data[] = {{},
{"Acolyte", "������", {Insight, Religion}, {2}, {Book, HolySymbol}},
{"Criminal", "����������", {Deception, Stealth}, {}, {}, {TheifToolsProficiency, GamingSet}, 15},
{"Folk Hero", "�������� �����", {AnimalHandling, Survival}},
{"Noble", "�����", {History, Persuasion}, {1}},
{"Sage", "������", {Arcana, History}, {0, 2}},
{"Soldier", "������", {Athletics, Intimidation}},
};
assert_enum(background, Soldier);
getstr_enum(background);

void creature::apply(background_s id, bool interactive) {
	set(background_data[id].skills[0]);
	set(background_data[id].skills[0]);
}