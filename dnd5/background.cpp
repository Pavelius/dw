#include "main.h"

background_info background_data[] = {{},
{"acolyte", "аколит", {Insight, Religion}, {2}},
{"criminal", "преступник", {Deception, Stealth}},
{"folk hero", "народный герой", {AnimalHandling, Survival}},
{"noble", "знать", {History, Persuasion}, {1}},
{"sage", "мудрец", {Arcana, History}, {0, 2}},
{"soldier", "солдат", {Athletics, Intimidation}},
};
assert_enum(background, Soldier);
getstr_enum(background);

void creature::apply(background_s id, bool interactive) {
	set(background_data[id].skills[0]);
	set(background_data[id].skills[0]);
}