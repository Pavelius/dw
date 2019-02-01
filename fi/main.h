#include "logs\archive.h"
#include "logs\crt.h"
#include "logs\dice.h"
#include "logs\logs.h"
#include "logs\logs_driver.h"
//#include "logs\string.h"
#include "logs\grammar.h"

#pragma once

enum ability_s : unsigned char {
	Strenght, Agility, Wits, Empathy,
};
enum race_s : unsigned char {
	Dwarf, Halfling, Human, Goblin, Elf, HalfElf, Orc, Wolfkin,
};
enum profession_s : unsigned char {
	Druid, Fighter, Hunter, Minstrel, Peddler, Rider, Rogue, Sorcerer
};
enum skill_s : unsigned char {
	Might, Endurance, Melee, Crafting, Stealth,
	SleightOfHand, Move, Marksmanship, Scouting, Lore,
	Survival, Insight, Manipulation, Performance, Healing,
	AnimalHandling
};
enum variant_s : unsigned char {
	NoVariant, Skill, Profession, Race, Ability,
};
struct variant {
	variant_s			type;
	union {
		skill_s			skill;
		profession_s	profession;
		race_s			race;
	};
	constexpr variant() : type(NoVariant), skill(Might) {}
	constexpr variant(skill_s v) : type(Skill), skill(v) {}
	constexpr variant(profession_s v) : type(Profession), profession(v) {}
};

class character {
	char			ability[Empathy + 1];
	char			skills[AnimalHandling + 1];
	profession_s	profession;
	gender_s		gender;
	race_s			race;
public:
	character() = default;
	void			create(bool interactive);
	char			get(skill_s id) const { return skills[id]; }
	char			get(ability_s id) const { return skills[id]; }
};
