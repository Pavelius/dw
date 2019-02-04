#include "logs\archive.h"
#include "logs\crt.h"
#include "logs\logs.h"
#include "logs\logs_driver.h"
#include "logs\grammar.h"

#pragma once

const unsigned character_max = 10;

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
	Parrying, Hook, NeedReady, Reload, PointedVulnerable,
	MovePenalty, ScoutPenalty
};
enum slot_s : unsigned char {
	Hand, LeftHand, Body, Head,
	LastSlot = Head,
};
enum magic_s : unsigned char {
	Mundane, Mighty, Epic, Legendary
};
enum reaction_s : unsigned char {
	Neutral, Friendly, Hostile,
};
enum used_s : unsigned char {
	NoUsed,
	ActionSlow, ActionFast,
	ActionDodge, ActionParry,
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
	//
	LeatherArmor, StuddedLeather, Chainmail, Platemail,
	StuddedLeatherCap, OpenHelmet, ClosedHelmet, GreatHelm,
	SmallShield, LargeShield,
	//
	Arrows, Quiver, GrapplingHook, Rope,
	TallonCandle, OilLamp, Lantern, Torches,
	Sack, Backpack, Waterskin, Bandages, LampOil,
	InkAndQuil, Parchment, Blanket, SleepingFur, FlintAndSteel,
	FieldRations,
};
enum action_s : unsigned char {
	Hike, LeadTheWay, KeepWatch, Forage, Hunt, Fish,
	MakeCamp, Rest, Sleep, Explore,
	Slash, Stab, Punch, Kick, Bite, Grapple, BreakFree,
	Run, Flee,
	Dodge, Parry, DrawWeapon, SwingWeapon, GetUp, Shove, Disarm, Feint, Retreat,
	ReadyWeapon, Aim, Shoot,
	Persuade, Taunt,
};
enum variant_s : unsigned char {
	NoVariant,
	Actions, Attributes, Category, Items, Professions, Races, Skills, Talents,
};
enum wound_s : unsigned char {
	NoWound,
};
enum state_s : unsigned char {
	Prone, ArmsHand,
};
struct variant {
	variant_s			type;
	union {
		ability_s		ability;
		action_s		action;
		profession_s	profession;
		race_s			race;
		skill_s			skill;
		talent_s		talent;
		variant_s		category;
	};
	constexpr bool operator==(const variant& e) const { return e.type == type && e.talent == talent; }
	constexpr bool operator!=(const variant& e) const { return e.type != type || e.talent != talent; }
	constexpr variant() : type(NoVariant), skill(Might) {}
	constexpr variant(ability_s v) : type(Attributes), ability(v) {}
	constexpr variant(action_s v) : type(Actions), action(v) {}
	constexpr variant(profession_s v) : type(Professions), profession(v) {}
	constexpr variant(race_s v) : type(Races), race(v) {}
	constexpr variant(skill_s v) : type(Skills), skill(v) {}
	constexpr variant(talent_s v) : type(Talents), talent(v) {}
	constexpr variant(variant_s v) : type(Category), category(v) {}
};
struct dice {
	variant_s			type;
	char				border;
	char				result;
	char				multiplier;
};
struct diceroll : adat<dice, 64> {
	int					reroll;
	void				clear();
	int					getone(variant_s id) const;
	int					getreroll() const;
	int					getsix() const;
	void				print(stringbuilder& sb);
	void				pushroll();
	void				roll(variant_s type, int c, int d);
};
class item {
	item_s			type;
	magic_s			magic : 2;
	unsigned char	bonus : 3;
	unsigned char	origin_bonus : 3;
	unsigned char	prepared : 1;
public:
	constexpr item() : type(NoItem), bonus(0), origin_bonus(0), magic(Mundane), prepared(0) {}
	constexpr explicit operator bool() const { return type != NoItem; }
	int				getartifact() const;
	int				getbonus() const { return bonus; }
	slot_s			getslot() const;
	bool			is(feature_s v) const;
	bool			is(magic_s v) const { return magic == v; }
	bool			isbroken() const { return bonus == 0; }
	void			repair(int value);
};
struct wound {
	unsigned char	type;
	unsigned char	days;
	unsigned char	healed;
};
class character {
	char			ability[Empathy + 1], ability_damage[Empathy + 1];
	char			skills[AnimalHandling + 1];
	char			talents[Wanderer + 1];
	char			used[ActionParry + 1];
	char			pride;
	char			willpower;
	profession_s	profession;
	gender_s		gender;
	race_s			race;
	reaction_s		reaction;
	item			wears[LastSlot + 1];
	adat<wound, 8>	wounds;
	cflags<state_s, unsigned char> states;
	//
	void			add_info(stringbuilder& sb) const;
	void			apply_talents();
	void			attack(item& weapon, character* enemy);
	void			choose_attributes(int points, bool interactive);
	profession_s	choose_profession(bool interactive) const;
	void			choose_skills(int points, bool interactive);
	void			choose_talents(bool interactive);
	void			choose_talents(int points, const variant filter, bool interactive);
public:
	character() = default;
	void			addwill(int value);
	bool			activity(action_s a, character* opponent, bool run);
	void			clear();
	void			create(bool interactive);
	void			damage(ability_s id, int value, bool interactive);
	int				get(action_s v) const { return used[v]; }
	char			get(skill_s id) const { return skills[id]; }
	char			get(ability_s id) const { return ability[id]; }
	char			get(talent_s id) const { return talents[id]; }
	char			getdamage(ability_s v) const { return ability_damage[v]; }
	static variant	getkey(talent_s id);
	static ability_s getkey(race_s id);
	static ability_s getkey(profession_s id);
	static ability_s getkey(skill_s id);
	static const char* getnameof(ability_s id);
	char			getmaximum(ability_s) const;
	char			getmaximum(skill_s) const;
	char			getminimum(ability_s) const;
	reaction_s		getopposed() const { return getopposed(getreaction()); }
	static reaction_s getopposed(reaction_s v);
	int				getpriority(ability_s id);
	static int		getpriority(race_s id);
	static int		getpriority(race_s id, profession_s v);
	range_s			getrange(action_s id) const;
	range_s			getrange(const character* opponent) const;
	reaction_s		getreaction() const { return reaction; }
	int				getwill() const { return willpower; }
	int				getuse(action_s v) const;
	bool			is(action_s v) const { return get(v) == 0; }
	bool			is(talent_s id, int level) const { return get(id) <= level; }
	bool			is(state_s id) const { return states.is(id); }
	bool			isbroke(ability_s id) const { return ability_damage[id] >= ability[id]; }
	bool			isbroken() const { return isbroke(Strenght) || isbroke(Agility); }
	bool			iscontrolled() const { return getreaction() == Friendly; }
	bool			isready() const { return !isbroken() && !isbroke(Wits); }
	bool			isshield() const { return wears[LeftHand].getslot()==LeftHand; }
	bool			isstance() const { return !is(Prone); }
	bool			react(action_s a, character* opponent, bool run);
	void			remove(state_s v) { states.remove(v); }
	void			roll(diceroll& r, ability_s id, int base, int skill, int equipment, int artifact_dice);
	int				roll(skill_s id, int modifier, item* pi = 0);
	void			set(used_s i, int v) { used[i] = v; }
	void			set(reaction_s v) { reaction = v; }
	void			set(state_s v) { states.add(v); }
};
class scene {
	char			order[character_max];
	character*		players[character_max];
	int				outskirts;
public:
	constexpr scene() : players(), order(), outskirts(0) {}
	void			add(character* p);
	void			combat();
	void			initiative();
	bool			isenemy() const;
	character*		get(reaction_s value) const;
	int				getfree(int index = 0) const;
	int				getplayercount() const;
};