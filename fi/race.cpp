#include "main.h"

static struct race_info {
	const char*			id;
	const char*			name;
	ability_s			ability;
	adat<skill_s, 12>	skills;
} race_data[] = {{"druid", "�����", Wits, {Endurance, Survival, Insight, Healing, AnimalHandling}},
{"fighter", "����", Strenght, {Might, Endurance, Melee, Crafting, Move}},
};
getstr_enum(race);