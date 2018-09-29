#include "main.h"

background_info background_data[] = {{},
{"acolyte", "������", {Insight, Religion}, {2}},
{"criminal", "����������", {Deception, Stealth}},
{"folk hero", "�������� �����", {AnimalHandling, Survival}},
{"noble", "�����", {History, Persuasion}, {1}},
{"sage", "������", {Arcana, History}, {0, 2}},
{"soldier", "������", {Athletics, Intimidation}},
};
assert_enum(background, Soldier);
getstr_enum(background);

void creature::apply(background_s id, bool interactive) {
	set(background_data[id].skills[0]);
	set(background_data[id].skills[0]);
}