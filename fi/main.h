#include "logs\archive.h"
#include "logs\crt.h"
#include "logs\dice.h"
#include "logs\logs.h"
#include "logs\logs_driver.h"
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
enum range_s : unsigned char {
	Personal, Arm, Near, Short, Long,
};
enum talent_s : unsigned char {
	Adaptive, InnerPeace, PsychicPower, TrueGrit, HardToCatch,
	HuntingInstinct, Unbreakable, Sneaky,
	PathOfHealing, PathOfShiftingShapes, PathOfSight,
	PathOfBlade, PathOfShield,
	PathOfArrow, PathOfBeast, PathOfForest,
	PathOfHymn, PathOfSong, PathOfWarcry,
	PathOfGold, PathOfLies, PathOfManyThings,
	PathOfCompanion, PathOfKnight, PathOfPlains,
	PathOfFace, PathOfKiller, PathOfPoison,
	PathOfBlood, PathOfDeath, PathOfSigns, PathOfStone,
	Ambidexterous, AxeFighter, Berserker, Bowyer, Brawler,
	Builder, Chef, ColdBlooded, Defender, Dragonslayer,
	Executioner, FastFootwork, FastShooter, Fearless, FirmGrip,
	Fisher, HammerFighter, Herbalist, HorsebackFighter, Incorruptible,
	KnifeFighter, LightingFast, Lockpicker, Lucky, MasterOfTheHunt,
	MeleeCharge, PackRat, PathFinder, Poisoner, QuarterMaster,
	QuickDraw, Sailor, Sharpshooter, SharpTongue, ShieldFighter,
	SixthSense, Smith, SpearFighter, SteadyFeet, SwordFighter,
	Tailor, Tanner, Threatening, ThrowingArm, Wanderer,
	FirstTalent = Adaptive, LastTalent = Wanderer,
};
enum feature_s : unsigned char {
	Blunt, Edged, Pointed,
	Light, Heavy,
	Parrying, Hook, Reload,
};
enum item_s : unsigned char {
	NoItem,
	Knife, Dagger, Falchion,
	Shortsword, Broadsword, Longsword, TwoHandedSword, Scimitar,
	Handaxe, Battleaxe, TwoHandedAxe,
	Mace, Morningstar, Warhammer, Flail, WoodenClub, LargeWoodenClub, HeavyHammer,
	Staff, ShortSpear, LongSpear, Pike, Halberd, Trident,
	//
	Rock, ThrovingKnife, ThrovingAxe, ThrovingSpear, Sling,
	ShortBow, LongBow,
	LightCrossbow, HeavyCrossbow,
};
enum variant_s : unsigned char {
	NoVariant,
	Ability, Profession, Race, Skill, Talent,
};
struct variant {
	variant_s			type;
	union {
		ability_s		ability;
		profession_s	profession;
		race_s			race;
		skill_s			skill;
		talent_s		talent;
	};
	constexpr bool operator==(const variant& e) const { return e.type == type && e.talent == talent; }
	constexpr bool operator!=(const variant& e) const { return e.type != type || e.talent != talent; }
	constexpr variant() : type(NoVariant), skill(Might) {}
	constexpr variant(ability_s v) : type(Ability), ability(v) {}
	constexpr variant(profession_s v) : type(Profession), profession(v) {}
	constexpr variant(race_s v) : type(Race), race(v) {}
	constexpr variant(skill_s v) : type(Skill), skill(v) {}
	constexpr variant(talent_s v) : type(Talent), talent(v) {}
};
struct item {
	item_s			type;
	unsigned char	bonus : 3;
	unsigned char	origin_bonus : 3;
	constexpr item() : type(NoItem), bonus(0), origin_bonus(0) {}
	bool			is(feature_s v) const;
	bool			isbroken() const { return bonus == 0; }
};
class character {
	char			ability[Empathy + 1];
	char			skills[AnimalHandling + 1];
	char			talents[Wanderer + 1];
	profession_s	profession;
	gender_s		gender;
	race_s			race;
	//
	void			add_info() const;
	void			apply_talents();
	void			choose_attributes(int points, bool interactive);
	profession_s	choose_profession(bool interactive) const;
	void			choose_skills(int points, bool interactive);
	void			choose_talents(bool interactive);
	void			choose_talents(int points, const variant filter, bool interactive);
	static ability_s getkey(race_s id);
	static ability_s getkey(profession_s id);
	int				getpriority(ability_s id);
	static int		getpriority(race_s id);
	static int		getpriority(race_s id, profession_s v);
	static variant	getkey(talent_s id);
public:
	character() = default;
	void			clear();
	void			create(bool interactive);
	char			get(skill_s id) const { return skills[id]; }
	char			get(ability_s id) const { return ability[id]; }
	char			get(talent_s id) const { return talents[id]; }
	char			getmaximum(ability_s) const;
	char			getmaximum(skill_s) const;
	char			getminimum(ability_s) const;
	bool			is(talent_s id, int level) const { return get(id) <= level; }
};