#include "main.h"

template<> resourcei bsmeta<resourcei>::elements[] = {
	{"Foods", "Еда"},
	{"Tools", "Инструменты"},
	{"Weapons", "Оружие"},
	{"Potions", "Зелья"},
	{"Species", "Специи"},
	{"Gems", "Драгоценности"},
	{"Clues", "Улики"},
	//
	{"Wood", "Дерево"},
	{"Furs", "Меха"},
	{"Ore", "Руда"},
};
assert_enum(resource, Ore);