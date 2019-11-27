#include "crt.h"
#include "logs.h"

#pragma once

using namespace logs;

const unsigned character_max = 4;

enum ability_s : unsigned char {
	Strenght, Agility, Wits, Empathy,
};
enum race_s : unsigned char {
	Dwarf, Halfling, Human, Goblin, Elf, HalfElf, Orc, Wolfkin,
	Animal, Monster,
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
	Personal, Arm, Near, Short, Long, Distant,
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
	Hand, LeftHand, Body, Head, Quiver,
	Gear, LastGear = Gear + 15,
	LastSlot = LastGear,
};
enum magic_s : unsigned char {
	Mundane, Mighty, Epic, Legendary
};
enum reaction_s : unsigned char {
	Neutral, Friendly, Hostile,
};
enum used_s : unsigned char {
	QuarterDayAction,
	ActionSlow, ActionFast,
	ActionDodge, ActionParry,
	ActionSingleUse,
};
enum attack_effect_s {
	AffectTwo = 1, AffectAll = 2, AffectNear = 4, AffectStrongest = 8,
	Fear = 16, Dirty = 32, Weapon = 64,
	DropDown = 128, ThrowNear = 256, ThrowShort = 256 * 2,
	ApplyCold = 256 * 4, ApplyPoisonParalized = 256 * 8, ApplyPoisonLethal = 256 * 16,
	SlashAttack = 256 * 32, DoPoint = 256 * 64,
	MoveSave = 256 * 128, Devoure = 256 * 256, Falling = 256 * 256 * 2,
	CanParry = 256 * 256 * 4, NoDodge = 256 * 256 * 8, FireAttack = 256 * 256 * 16,
	AffectShort = 256 * 256 * 32, SingleUse = 256 * 256 * 64,
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
	Arrows, GrapplingHook, Rope,
	TallonCandle, OilLamp, Lantern, Torches,
	Waterskin, Bandages, LampOil,
	InkAndQuil, Parchment, Blanket, SleepingFur, FlintAndSteel,
	FieldRations,
	Lute, Flute,
	CooperPiece, SilverPiece, GoldPiece,
};
enum action_s : unsigned char {
	Hike, LeadTheWay, KeepWatch, Forage, Hunt, Fish,
	MakeCamp, Rest, Sleep, Explore,
	Slash, Stab, Punch, Kick, Bite,
	Grapple, GrappleAttack, BreakFree,
	Run, Flee,
	DodgeStand, DodgeProne, ParryWeapon, ParryShield,
	DrawWeapon, SwingWeapon, GetUp, Shove, Disarm, Feint, Retreat,
	ReadyWeapon, Aim, Shoot,
	Persuade, Taunt,
};
enum zone_kind_s : unsigned char {
	Open, Rought,
};
enum variant_s : unsigned char {
	NoVariant,
	Actions, Attributes, Category, Items, Professions, Races, Skills, Talents,
};
enum wound_s : unsigned char {
	NoWound,
	LethalPoison, ParalizedPoison,
};
enum state_s : unsigned char {
	Prone, ArmsHand, RunSlowAction, ImmunePhysicalWeapon,
};
enum pregen_s : unsigned char {
	NoPregen,
	Aliander, Frailer,
	Bear, Wolf,
	YoungWorm, OldWorm, Dragon, LargeDragon,
};
enum resource_s : unsigned char {
	D6, D8, D10, D12,
};
enum scene_s : unsigned {
	CommonScene, Dungeon,
};
class scene;
class character;
struct featurei;
struct scene_info;
struct variant {
	variant_s			type;
	unsigned char		subtype;
	char				value;
	constexpr bool operator==(const variant& e) const { return e.type == type && e.subtype == subtype; }
	constexpr bool operator!=(const variant& e) const { return e.type != type || e.subtype != subtype; }
	constexpr variant() : type(NoVariant), subtype(0), value(0) {}
	constexpr variant(ability_s v) : type(Attributes), subtype(v), value(0) {}
	constexpr variant(action_s v) : type(Actions), subtype(v), value(0) {}
	constexpr variant(profession_s v) : type(Professions), subtype(v), value(0) {}
	constexpr variant(race_s v) : type(Races), subtype(v), value(0) {}
	constexpr variant(skill_s v) : type(Skills), subtype(v), value(0) {}
	constexpr variant(talent_s v) : type(Talents), subtype(v), value(0) {}
	constexpr variant(variant_s v) : type(Category), subtype(v), value(0) {}
	const char*			getname() const;
};
struct genderi {
	const char*			id;
	const char*			name;
};
struct equipmenti {
	resource_s			food;
	resource_s			water;
	resource_s			silver;
	char				goods;
	item_s				standart[4];
	item_s				custom[2][2];
	char				one_handed_weapon;
};
struct professioni {
	const char*			id;
	const char*			name;
	ability_s			ability;
	skill_s				skills[5];
	equipmenti			equipment;
};
struct racei {
	const char*			id;
	const char*			name;
	ability_s			ability;
	talent_s			talent;
	int					priority;
	profession_s		professions[3];
};
struct skilli {
	const char*			id;
	const char*			name;
	ability_s			attribute;
};
struct abilityi {
	const char*			id;
	const char*			name;
	const char*			nameof;
};
struct talenti {
	const char*			id;
	const char*			name;
	variant				type;
	variant				affect;
};
struct attack_info {
	const char*			name;
	unsigned			flags;
	char				base;
	char				count;
	unsigned			fail;
	char				value[2];
};
struct skill_set {
	skill_s				type;
	char				value;
};
struct attack_context {
	attack_info*		attack;
	character*			monster;
	character*			enemy;
	int					value;
};
struct pregeni {
	const char*			id;
	const char*			name;
	race_s				race;
	profession_s		profession;
	char				ability[4];
	adat<skill_set, 8>	skills;
	item_s				gear[8];
	char				movement;
	char				natural_armor;
	attack_info*		attacks;
};
struct action_context;
struct actioni {
	typedef bool(*callback)(action_context& e, bool run, bool interactive);
	const char*			id;
	const char*			name;
	used_s				type;
	variant				use;
	const char*			text_success;
	const char*			text_fail;
	callback			proc_roll;
	aref<variant>		reaction;
	callback			proc_effect;
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
struct itemi {
	struct weaponi {
		range_s			range;
		char			grip;
		char			damage;
		talent_s		talent;
	};
	const char*			id;
	const char*			name;
	int					cost;
	slot_s				slot;
	char				bonus;
	weaponi				weapon;
	cflags<feature_s>	flags;
};
class item {
	item_s				type;
	//
	magic_s				magic : 2;
	unsigned char		bonus : 3;
	unsigned char		origin_bonus : 3;
	//
	resource_s			resource : 2;
	//
	unsigned char		count;
public:
	constexpr item() : type(NoItem), bonus(0), origin_bonus(0), magic(Mundane), resource(D6), count(0) {}
	constexpr item(item_s t, resource_s r) : type(t), bonus(0), origin_bonus(0), magic(Mundane), resource(r), count(0) {}
	constexpr explicit operator bool() const { return type != NoItem; }
	item(item_s t);
	item(item_s t, unsigned char count);
	int					getartifact() const;
	int					getbonus() const { return bonus; }
	int					getcost() const;
	int					getcount() const { return count; }
	const char*			getname() const;
	slot_s				getslot() const;
	item_s				gettype() const { return type; }
	bool				is(feature_s v) const;
	bool				is(magic_s v) const { return magic == v; }
	bool				isbroken() const { return bonus == 0; }
	void				repair(int value);
};
class wound {
	unsigned char		type;
	unsigned char		days;
	unsigned char		potency;
	unsigned char		flags;
public:
	wound() = default;
	int					getdays() const { return days; }
	int					getpotency() const { return potency; }
};
struct zone {
	zone_kind_s			type;
};
class character {
	const char*			name;
	char				ability[Empathy + 1], ability_damage[Empathy + 1];
	char				skills[AnimalHandling + 1];
	char				talents[Wanderer + 1];
	char				used[ActionParry + 1];
	char				pride;
	char				willpower;
	profession_s		profession;
	gender_s			gender;
	race_s				race;
	reaction_s			reaction;
	item				wears[LastSlot + 1];
	wound				wounds[8];
	zone*				position;
	character*			grappler;
	attack_info*		monster_attacks;
	cflags<state_s, unsigned char> states;
	unsigned			cooper_piece;
	//
	void				add_info(stringbuilder& sb) const;
	void				apply_talents();
	void				apply_equipment(bool interactive);
	void				choose_attributes(int points, bool interactive);
	item_s				choose_item(const char* title, aref<item_s> source, bool interactive);
	profession_s		choose_profession(bool interactive) const;
	void				choose_skills(int points, bool interactive);
	void				choose_talents(bool interactive);
	void				choose_talents(int points, const variant filter, bool interactive);
public:
	character() = default;
	void				add(const item& it);
	void				addwill(int value);
	void				act(const char* format, ...) const { actv(format, xva_start(format)); }
	void				act(const character* opponent, const char* format, ...) const { actv(opponent, format, xva_start(format)); }
	void				actv(const char* format, const char* param) const;
	void				actv(const character* opponent, const char* format, const char* param) const;
	bool				activity(action_s a, character* opponent, scene* ps, bool run);
	void				clear();
	void				create(bool interactive);
	void				create(pregen_s id);
	void				damage(ability_s id, int value, bool interactive);
	bool				equip(const item& it);
	int					get(action_s v) const { return used[v]; }
	char				get(skill_s id) const { return skills[id]; }
	char				get(ability_s id) const { return ability[id]; }
	char				get(talent_s id) const { return talents[id]; }
	const item&			get(slot_s id) const { return wears[id]; }
	char				getdamage(ability_s v) const { return ability_damage[v]; }
	const character*	getgrapler() const { return grappler; }
	static variant		getkey(talent_s id);
	static ability_s	getkey(race_s id);
	static ability_s	getkey(profession_s id);
	static ability_s	getkey(skill_s id);
	const char*			getname() const { return name; }
	static const char*	getrandomname(race_s kin, gender_s gender);
	char				getmaximum(ability_s) const;
	char				getmaximum(skill_s) const;
	char				getminimum(ability_s) const;
	reaction_s			getopposed() const { return getopposed(getreaction()); }
	static reaction_s	getopposed(reaction_s v);
	int					getpriority(ability_s id);
	static int			getpriority(race_s id);
	static int			getpriority(race_s id, profession_s v);
	range_s				getrange(action_s id) const;
	range_s				getrange(const character* opponent) const;
	reaction_s			getreaction() const { return reaction; }
	int					getwill() const { return willpower; }
	int					getuse(action_s v) const;
	zone*				getzone() const { position; }
	bool				is(action_s v) const { return get(v) == 0; }
	bool				is(talent_s id, int level) const { return get(id) <= level; }
	bool				is(state_s id) const { return states.is(id); }
	bool				isbroke(ability_s id) const { return ability_damage[id] >= ability[id]; }
	bool				isbroken() const { return isbroke(Strenght) || isbroke(Agility); }
	bool				iscontrolled() const { return getreaction() == Friendly; }
	bool				isgrappled() const { return grappler != 0; }
	bool				isready() const { return !isbroken() && !isbroke(Wits); }
	bool				isshield() const { return wears[LeftHand].getslot() == LeftHand; }
	bool				isstance() const { return !is(Prone); }
	void				react(const aref<variant>& source, character* opponent, int& result, bool run);
	bool				react(action_s a, character* opponent, int& result, bool run);
	void				remove(state_s v) { states.remove(v); }
	void				roll(diceroll& r, ability_s id, int base, int skill, int equipment, int artifact_dice);
	int					roll(skill_s id, int modifier, item* pi = 0);
	static int			roll(resource_s i);
	void				set(used_s i, int v) { used[i] = v; }
	void				set(reaction_s v) { reaction = v; }
	void				set(skill_s i, int v) { skills[i] = v; }
	void				set(state_s v) { states.add(v); }
	void				set(zone* v) { position = v; }
	void				setgrappler(character* v) { grappler = v; }
};
struct featurei {
	scene_s				type;
	gender_s			gender;
	const char*			name;
	const char*			look;
};
class feature {
	featurei*			type;
	unsigned char		position;
public:
	constexpr feature() : type(0), position(0) {}
	constexpr explicit operator bool() const { return type != 0; }
	void				clear();
	void				create(featurei* v, unsigned char position);
	const char*			getlook() const;
	const char*			getname() const;
	int					getposition() const { return position; }
};
class scene {
	scene_info*			type;
	unsigned char		size;
	character*			players[character_max];
	feature				features[8];
public:
	constexpr scene() : size(1), players(), features(), type() {}
	void				add(character* p);
	void				combat();
	void				clear();
	void				create();
	bool				isenemy() const;
	void				look(stringbuilder& sb);
	character*			get(reaction_s value) const;
	int					getplayercount() const;
	void				remove(const character* p);
};
DECLENUM(ability);
DECLENUM(action);
DECLENUM(gender);
DECLENUM(item);
DECLENUM(profession);
DECLENUM(race);
DECLENUM(skill);
DECLENUM(talent);