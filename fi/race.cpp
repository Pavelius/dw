#include "main.h"

static struct race_info {
	const char*		id;
	const char*		name;
	ability_s		ability;
	talent_s		talent;
	int				priority;
	profession_s	professions[3];
} race_data[] = {{"Dwarf", "Гном", Strenght, TrueGrit, 1, {Fighter, Minstrel, Peddler}},
{"Halfling", "Хоббит", Empathy, HardToCatch, 1, {Minstrel, Peddler, Rogue}},
{"Human", "Человек", Empathy, Adaptive, 3},
{"Goblin", "Гоблин", Agility, Sneaky, 1, {Fighter, Rider, Rogue}},
{"Elf", "Эльф", Agility, InnerPeace, 1, {Druid, Minstrel, Hunter}},
{"HalfElf", "Полу-Эльф", Wits, PsychicPower, 1, {Druid, Rogue, Sorcerer}},
{"Orc", "Орк", Strenght, Unbreakable, 1, {Fighter, Hunter, Rogue}},
{"Wolfkin", "Волкулак", Agility, HuntingInstinct, 1, {Druid, Fighter, Hunter}},
};
assert_enum(race, Wolfkin);
getstr_enum(race);

int character::getpriority(race_s id, profession_s v) {
	const int a = 4;
	const int b = 1;
	auto& e = race_data[id];
	if(e.professions[0] == e.professions[1])
		return a;
	if(e.professions[0] == v || e.professions[1] == v || e.professions[2] == v)
		return a;
	return b;
}

int character::getpriority(race_s id) {
	return race_data[id].priority;
}

ability_s character::getkey(race_s id) {
	return race_data[id].ability;
}
