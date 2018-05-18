#include "main.h"

struct landscape_i {
	const char*		id;
	const char*		name;
	char			encounter[Night + 1];
	const char*		movement;
} landscape_data[] = {
	{"Plain", "Равнина", {1, 0, 1, 0, 1, 0}, {"Вы двигались по красивой равнине."}},
	{"Brush", "Лесостепь", {1, 0, 1, 1, 0, 1}, {"Вы двигались по равнине, которая переодически менялась редкими перелесками и зарослями кустарника."}},
	{"Forest", "Лес", {2, 2, 2, 2, 2, 2}, {"Вы двигались по темному лесу."}},
	{"Desert", "Пустыня", {1, 0, 0, 1, 0, 1}},
	{"Hills", "Холмы", {0, 2, 0, 2, 0, 2}},
	{"Mountains", "Горы", {3, 0, 0, 3, 3, 0}},
	{"Swamp", "Болото", {4, 4, 4, 4, 4, 4}},
	{"Jungle", "Джунгли", {3, 3, 3, 3, 3, 0}},
	{"Ocean", "Океан", {0, 1, 0, 0, 1, 0}},
	{"Arctic", "Мерзлота", {0, 0, 1, 1, 0, 0}},
};
assert_enum(landscape, Arctic);
getstr_enum(landscape);

const char* game::getencounterchance(landscape_s id) {
	return landscape_data[id].encounter;
}

const char* game::getstrmovement(landscape_s id) {
	return landscape_data[id].movement;
}