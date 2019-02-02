#include "main.h"

static struct profession_info {
	const char*			id;
	const char*			name;
	ability_s			ability;
	skill_s				skills[5];
} profession_data[] = {{"Druid", "Друид", Wits, {Endurance, Survival, Insight, Healing, AnimalHandling}},
{"Fighter", "Боец", Strenght, {Might, Endurance, Melee, Crafting, Move}},
{"Hunter", "Охотник", Agility, {Stealth, Move, Marksmanship, Scouting, Survival}},
{"Minstrel", "Минестрель", Empathy, {Lore, Insight, Manipulation, Performance, Healing}},
{"Peddler", "Торговец", Empathy, {Crafting, SleightOfHand, Scouting, Insight, Manipulation}},
{"Rider", "Всадник", Agility, {Endurance, Melee, Marksmanship, Survival, AnimalHandling}},
{"Rogue", "Бродяга", Agility, {Melee, Stealth, SleightOfHand, Move, Manipulation}},
{"Sorcerer", "Волшебник", Wits, {Crafting, SleightOfHand, Lore, Insight, Manipulation}},
};
assert_enum(profession, Sorcerer);
getstr_enum(profession);

ability_s character::getkey(profession_s id) {
	return profession_data[id].ability;
}

int	character::getpriority(ability_s v) {
	auto min = 4;
	auto max = getmaximum(v);
	if(min == max)
		return 1;
	return (1 + (max - min)) * 2;
}

char character::getmaximum(skill_s v) const {
	for(auto e : profession_data[profession].skills) {
		if(e == v)
			return 3;
	}
	return 1;
}