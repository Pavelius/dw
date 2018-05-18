#include "logs/adat.h"
#include "logs/aref.h"
#include "logs/bsdata.h"
#include "logs/crt.h"
#include "logs/dice.h"
#include "logs/logs.h"
#include "logs/logs_driver.h"
#include "logs/point.h"

#pragma once

#define metadc_enum(e) \
bsreq e##_type[] = {\
	BSREQ(e##_info, id),\
	BSREQ(e##_info, name),\
{}}; BSMETA(e)

extern bsreq class_type[];
extern bsreq damage_type[];
extern bsreq dice_type[];
extern bsreq gender_type[];
extern bsreq group_type[];
extern bsreq itemi_type[];
extern bsreq monster_type[];

enum item_s : unsigned char {
	NoItem,
	Axe, BattleAxe, Mace, MorningStar, Hammer,
	Spear, Staff, Halberd,
	Dagger, ShortSword, LongSword, BastardSword, TwoHandedSword, Scimitar,
	ShortBow, LongBow, Crossbow, Sling,
	LeatherArmor, StuddedLeatherArmor, ChainMail, ScaleMail, Brigandine, PlateMail, RingMail, SplintMail, BandedMail, FieldPlate, FullPlate,
	Shield,
	Stone, Arrow, Bolt,
	Potion, Scroll, Ring, Rod, Wand, Book, Tome, Necklage, Cloack, Robe, Boot, Glove, Gridle,
	Helm, Bag, Bottle, Dust,
	Flute, Guitar,
	Raspberry, Grain,
	// Gems
	Azurite, BandedAgate, BlueQuartz, EyeAgate, Hematite, LapisLazuli, Malachite, MossAgate, Obsidian, Rhodochrosite, TigerEyeAgate, Turquoise,
	Bloodstone, Chalcedony, Chrysoprase, Citrine, Jasper, Moonstone, Onyx, RockCrystal, Sardonyx, SmokyQuartz, StarRoseQuartz, Zircon,
	Amber, Alexandrite, Amethyst, Aquamarine, Chrysoberyl, Coral, Garnet, Jade, Jet, Pearl, Peridot, Spinel, Topaz, Tourmaline,
	BlackOpal, BlackSapphire, Diamond, Emerald, FireOpal, Jacinth, Opal, OrientalAmethyst, OrientalEmerald, OrientalTopaz, Ruby, Sapphire, StarRuby, StarSapphire,
	FirstWeapon = Axe, LastWeapon = Sling,
	FirstArmor = LeatherArmor, LastArmor = Shield,
	FirstGem = Azurite, LastGem = StarSapphire,
	LastItem = StarSapphire
};
enum class_s : unsigned char {
	NoClass,
	Bard, Cleric, Druid, Fighter, Mage, Paladin, Ranger, Theif,
	FighterCleric, FighterMage, FighterTheif,
	ClericMage, MageTheif,
	FighterClericMage, FighterMageTheif,
};
enum race_s : unsigned char {
	NoRace,
	Human, Dwarf, Elf, Gnome, HalfElf, Halfling,
};
enum alignment_s : unsigned char {
	AnyAlignment,
	LawfulGood, NeutralGood, ChaoticGood,
	LawfulNeutral, TrueNeutral, ChaoticNeutral,
	LawfulEvil, NeutralEvil, ChaoticEvil
};
enum ability_s : unsigned char {
	Strenght, Dexterity, Constitution, Intellegence, Wisdow, Charisma,
};
enum god_s : unsigned char {
	Bane, Mystra, Tor, Tempos
};
enum group_s : unsigned char {
	GeneralGroup,
	Warriors, Priests, Rogues, Wizards
};
enum skill_s : unsigned char {
	PickPockets, OpenLocks, FindRemoveTraps, MoveSilently, HideInShadows, DetectNoise, ClimbWalls, ReadLanguages,
	OpenDoor, GettingLost,
	Herbalism, Hunting, Tracking,
	GoAway, GoInside,
};
enum skill_type_s : unsigned char {
	NoTest,
	TestSkill, TestAbility,
};
enum monster_s : unsigned char {
	Character, Orc, Rogue,
};
enum landscape_s : unsigned  char {
	Plain, Brush, Forest, Desert, Hills, Mountains, Swamp, Jungle, Ocean, Arctic,
};
enum wear_s : unsigned char {
	Head, Neck, Armor, MeleeWeapon, OffhandWeapon, RangedWeapon, GridleWear, Legs,
	FirstWear = Head, LastWear = Legs
};
enum school_s : unsigned char {
	NoSchool,
	Abjuration, Alteration, Charm, Conjuration, Divination, Enchantment,
	Invocation, Necromantic,
	Summoning,
};
enum distance_s : unsigned char {
	Self, Touch, Range1, Range3, Range6, Range12,
};
enum duration_s : unsigned char {
	Instantaneous, Concetration, Hour, Day, Month, Year,
	Duration1Round, Duration1RoundPerLevel, Duration1RoundPerLevelPlus1, Duration1RoundPerLevelPlus2, Duration1RoundPerLevelPlus3, Duration1RoundPerLevelPlus1d3, Duration1RoundPerLevelPlus1d4,
	Duration1d10Rounds, Duration2d20Rounds,
	Duration2RoundPerLevel, Duration2RoundPlus1RoundPerLevel,
	Duration4RoundPlus1RoundPerLevel,
	Duration5RoundPerLevel,
	Duration6Round,
	Duration1Turn, Duration1TurnPerLevel, Duration1TurnPlus1Per2Level,
	Duration3Turn,
	Duration5Turn,
	Duration6TurnPlus1PerLevel,
	Duration4Hours,
	Duration10Hours,
	Duration1DayPerLevel,
	Permanent,
};
enum feat_s : unsigned char {
	NoFeat,
	Darkvision,
	BonusSaveVsPoison, BonusSaveVsWands, BonusSaveVsSpells,
	DetectSecretDoors, DetectUndegroundPassages, CharmResistance,
	ElfWeaponTraining, DwarfCombatTactic, SmallSizeCombatAdvantage, LightSteps,
};
enum reaction_s : unsigned char {
	Indifferent, Friendly, Flight, Cautions, Threatening, Hostile,
};
enum location_s : unsigned char {
	NoLocation,
	DeepForest,
	DungeonEntrance, SmallRoom, LargeRoom, Tavern,
	WildCampfire,
};
enum side_s : unsigned char {
	PartySide, EnemySide,
};
enum save_s : unsigned char {
	SaveVsParalization, SaveVsPoison, SaveVsDeath,
	SaveVsWands,
	SaveVsPetrification, SaveVsPolymorph,
	SaveVsBreathWeapon,
	SaveVsSpells,
};
enum save_result_s : unsigned char {
	NoSave, Negate, Half,
};
enum damage_s : unsigned char {
	Bludgeon, Piercing, Slashing,
	Acid, Cold, Electricity, Fire,
};
enum size_s : unsigned char {
	Small, Medium, Large,
};
enum timezone_s : unsigned char {
	Morning, Noon, Afternoon, Evening, Midnight, Night,
};
enum magic_item_s : unsigned char {
	Any,
	Potions, Oils, Scrolls, Armors, Shields, Weapons, Rings, Rods, Staves, Wands,
	Books, Tomes, Jewels, Jewelry, Cloacks, Robes, Boots, Gloves,
	Gridles, Helms, Bags, Bottles, Dusts, Stones, Tools,
	MusicalInstruments, WeirdStuffs,
};
enum spell_s : unsigned char {
	NoSpell,
	// 1 - level cleric
	SpellBless, SpellCommand, SpellCreateWater, SpellCureLightWounds, SpellDetectEvil,
	SpellDetectMagic, SpellLight, SpellProtectionFromEvil, SpellPurifyFoodDrink, SpellRemoveFear,
	SpellResistCold, SpellSanctuary,
	// 2 - level cleric
	SpellAugury, SpellChant, SpellDetectCharm, SpellFindTraps, SpellHoldPerson,
	SpellKnowAlignment, SpellResistFire, SpellSilence15Radius, SpellSlowPoison, SpellSnakeCharm,
	SpellSpeakWithAnimals, SpellSpiritualHammer,
};
enum magic_power_s : unsigned char {
	NoMagicPower,
	// Potions
	AnimalControl, Clairaudience, Clairvoyance, Climbing, Delusion, Diminution, DragonControl,
	Health, Madness, Youth, ESP, ExtraHealing, FireBreath, FireResistance, Flying, GaseousForm,
	GiantControl, GiantStrength, Growth, HealingPower, Heroism, HumanControl, Invisibility,
	Invulnerability, Levitation, Longevity,
	AcidResistance, Disenchantment, ElementalInvulnerability,
	Etherealness, FieryBurning, Fumbling, Impact, Slipperiness,
	Timelessness, Glibness, Love, Persuasiveness, StammeringAndStuttering,
	PlantControl, Poison, Polymorph, RainbowHues, Speed, SuperHeroism,
	SweetWater, TreasureFinding, UndeadControl, VentriloquismPower, Vitality, WaterBreathing,
	// Rings
	Blinking, ChameleonPower, Clumsiness, Contrariness, DjinniSummoning, ElementalControl, FeatherFalling,
	FreeAction, JumpingPower, MindShielding, Protection,
	Ram, Regeneration, ShockingGrasp, ShootingStars, SpellStoring, SpellTurning,
	Sustenance, SwimmingPower, Telekinesis, Truth, Warmth, WaterWalking, Weakness, Wizardry, DarkvisionPower,
	// Character status non magic
	Surprised, Blessed, Lighted,
};
enum movement_s : unsigned char {
	NoChange,
	MoveForward, MoveAway, MoveInside,
};

const unsigned CP = 1; // One cooper coin
const unsigned SP = 10; // One silver coin
const unsigned GP = 100; // One gold coin
const unsigned PP = 500; // One platinum or electra coin

const unsigned RRound = 1;
const unsigned RTurn = RRound * 10;
const unsigned RHour = RTurn * 6;
const unsigned RDay = 24 * RHour;
const unsigned RMonth = 30 * RDay;
const unsigned RYear = 12 * 30 * RDay;

struct character;
struct history;
struct scene;

typedef alignment_s			alignmenta[8];
typedef race_s				racea[8];
typedef feat_s				feata[8];
typedef class_s				classa[3];

struct saveinfo {
	save_s					save;
	save_result_s			type;
	char					bonus;
};
struct damageinfo {
	damage_s				type;
	dice					damage, damage_large;
	const dice&				getdamage(size_s value) const;
};
struct testinfo {
	skill_type_s			type;
	ability_s				ability;
	char					bonus;
};
struct attackinfo : damageinfo {
	char					thac0;
	char					attacks_per_two_rounds;
	char					critical;
	char					multiplier;
	struct item*			weapon;
	attackinfo() { clear(); }
	void					clear();
};
struct itemweight {
	item_s					key;
	short					weight;
	static int				compare(const void* p1, const void* p2);
};
struct item {
	enum state_s : unsigned char {
		Mundane, Cursed, Magic, Artifact
	};
	enum identify_s : unsigned char {
		Unknown, KnownMagic, KnownHistory, KnownPowers
	};
	item_s					type;
	unsigned char			quality : 2;
	unsigned char			fashion : 2; // All mundane items have 0. Some magical and all object of arts have 1-3. Do not modify price. Give random fashion and look to item.
	state_s					state : 2;
	identify_s				identify : 2;
	magic_power_s			power;
	unsigned char			charges;
	item() = default;
	constexpr item(item_s type) : type(type), quality(0), fashion(0), state(Mundane), identify(Unknown), power(NoMagicPower), charges(0) {}
	constexpr operator bool() const { return type != NoItem; }
	void					clear();
	static item_s			get(magic_item_s type);
	int						getAC() const;
	bool					getattack(attackinfo& e) const;
	static aref<char>		getbonus(magic_item_s type);
	unsigned				getcost() const;
	const char*				getname() const;
	const char*				getnameby() const;
	constexpr magic_power_s	getpower() const { return ismagical() && type != Scroll ? power : NoMagicPower; }
	static aref<magic_power_s> getpowers(magic_item_s type);
	static aref<item_s>		gettypes(magic_item_s type);
	bool					is(wear_s value) const;
	constexpr bool			isgem() const { return type >= FirstGem && type <= LastGem; }
	constexpr bool			ismagical() const { return state != Mundane; }
private:
	int						getbonus() const;
};
struct treasure {
	int						cp, sp, gp, pp, gems, art, magic;
	item					items[64];
	treasure();
	void					add(item value);
	void					add(magic_item_s type);
	void					addarts(int count);
	void					addgems(int count);
	void					addmagic(int count);
	static item				anyart();
	static item_s			anygem();
	static magic_item_s		anymagic();
	static item				anymagic(magic_item_s type, char level = 0, class_s usable = NoClass);
	void					clear();
	void					generate(char symbol);
	void					generate(const char* type);
	static item				gemquality(item_s type);
};
struct character {
	struct variable {
		const char*			id;
		const char*			name;
		int					(character::*proc)() const;
		const char*			present;
	};
	character();
	character(race_s race, gender_s gender, class_s type, const char* abilities, bool party_member);
	character(bool interactive);
	character(monster_s type);
	operator bool() const { return name != 0; }
	void					act(const char* format, ...) const;
	void					actvs(const character& e, const char* format, ...) const;
	bool					add(item value);
	void					add(magic_power_s id, unsigned count_rounds = 10);
	void					addexp(bool interactive, unsigned value);
	void					addmoney(int count);
	void					attack(bool interactive, character& enemy, wear_s weapon, bool flatfooted = false);
	void					clear();
	void					charsheet();
	static void				checkstates();
	static void				chooseability(bool interactive, char* abilities);
	static class_s			chooseclass(bool interactive, race_s race, char* abilities);
	static character*		chooseplayer(bool interactive);
	static race_s			chooserace(bool interactive, char* abilities);
	void					create(bool interactive, race_s race, gender_s gender, class_s type, const char* abilities, bool party_member);
	void					damage(bool interactive, int value);
	bool					get(attackinfo& result, wear_s weapon) const;
	int						get(ability_s id) const;
	int						get(class_s id) const;
	int						get(save_s id) const;
	int						get(skill_s id) const;
	item					get(wear_s id) const { return wears[id]; }
	character*				get(aref<character*> parcipants, bool (character::*)(const character*) const) const;
	static alignment_s		getalignment(monster_s id);
	static dice				getappearing(monster_s id);
	int						getAC(bool flatfooted) const;
	int						getAC() const { return getAC(false); }
	static const char*		getadjustment(race_s value);
	static class_s			getclass(class_s value);
	static const classa&	getclasses(class_s value);
	static const classa&	getclasses(skill_s value);
	unsigned				getcount() const;
	character*				getenemy(aref<character*> parcipants) const { return get(parcipants, &character::isenemy); }
	int						getexperience() const { return experience; }
	static const feata&		getfeats(race_s value);
	gender_s				getgender() const { return gender; }
	static group_s			getgroup(class_s value);
	int						getHD() const { return levels[0]; }
	static int				getHD(group_s value);
	static int				getHD(class_s value) { getHD(getgroup(value)); }
	int						gethp() const { return hp; }
	static const char*		getinfo(race_s value);
	static const testinfo&	getinfo(skill_s id);
	int						getinitiative() const { return initiative; }
	aref<item_s>			getitems(class_s type) const;
	int						getmaxclasses() const;
	int						getmaxhp() const;
	static char*			getmaximum(race_s value);
	static char*			getminimum(class_s value);
	static char*			getminimum(race_s value);
	int						getmoney() const { return coopers; }
	const char*				getname() const;
	char*					getname(char* result, const char* result_maximum) const;
	static aref<character*>	getparty(character** result);
	race_s					getrace() const { return race; }
	static const racea&		getraces(class_s value);
	static short unsigned	getrandomname(race_s race, gender_s gender, class_s type);
	static reaction_s		getreaction(reaction_s start, int bonus = 0);
	side_s					getside() const { return side; }
	size_s					getsize() const { return Medium; }
	static char*			getskills(race_s);
	int						getspeed() const { return 12; }
	int						getstrenght() const;
	int						getsurprise() const;
	int						getsurpriseother() const;
	static aref<variable>	getvariables();
	const item*				getwear(item_s type) const;
	bool					is(group_s value) const;
	bool					is(feat_s value) const { return (feats & (1 << value)) != 0; }
	bool					is(magic_power_s id) const;
	bool					isallow(skill_s id) const;
	bool					isenemy(const character* p) const;
	bool					isplayer() const;
	bool					isready() const { return this && hp > 0; }
	bool					isuse(item_s value) const;
	static bsreq			metadata[];
	void					raiselevel(bool interactive, class_s type);
	void					say(const char* format, ...) const;
	void					set(class_s value);
	void					set(feat_s value);
	void					set(side_s value) { side = value; }
	void					set(race_s value) { race = value; }
	void					setcount(int value) { count = value; }
	void					setinitiative(char value) { initiative = value; }
	bool					surprise(int bonus = 0);
	void					use(bool interactive, item& e);
private:
	gender_s				gender;
	alignment_s				alignment;
	class_s					type;
	race_s					race;
	monster_s				monster;
	char					abilities[Charisma + 1];
	short					hp, hp_maximum;
	char					initiative;
	unsigned				feats;
	side_s					side;
	char					strenght_percent;
	short unsigned			name;
	point					position;
	char					levels[3];
	item					wears[Legs + 1];
	int						coopers;
	int						experience;
	short unsigned			count;
	//
	void					addweapons(int count);
	void					equip();
	void					finish(bool party_member);
	const char*				find(class_s value) const;
	int						getbonus(int(item::*)() const) const;
	char*					getmonstername(char* result, const char* result_maximum) const;
	void					setmonsterhp();
};
struct lair {
	monster_s				monster;
	unsigned				count;
};
struct effect {
	const char*				text;
	constexpr operator bool() const { return text!=0; }
};
struct action {
	const char*				text;
	skill_s					type;
	duration_s				duration;
	short unsigned			exp;
	effect					success;
	effect					fail;
	//
	void					addhistory(const character* player) const;
	const char*				getskill() const;
	history*				gethistory(const character* player) const;
	bool					isallow(const character* player) const;
	bool					useonce() const;
};
struct history {
	unsigned				when;
	const character*		who;
	const action*			what;
};
struct outcome {
	bool					success;
	char					result, difficult, bonus;
	constexpr outcome() : success(), result(), difficult(), bonus() {}
	constexpr operator bool() const { return success; }
};
struct scene {
	landscape_s				enviroment;
	character*				player;
	constexpr scene(landscape_s type) : player(), enviroment(type) {}
	//
	static unsigned			adventure(landscape_s type);
	void					ask(aref<action> source) const;
	void					ask(action& a) const;
	void					askencounter() const;
	void					charsheet();
	void					change(bool interactive, timezone_s& timezone);
	static void				combat(bool interactive, aref<character*> parcipants);
	static void				combat(bool interactive, character& enemy);
	static void				combat(bool interactive, monster_s type, unsigned count);
	void					encounter();
	void					encounter(character& monsters);
	static unsigned			get(duration_s value, int level = 1);
	static aref<action>		getactions(location_s id);
	static aref<action>		getactions(landscape_s id);
	static int				getday();
	static const char*		getencounterchance(landscape_s id);
	static int				gethour();
	static int				getmonth();
	static const char*		getstrmovement(landscape_s id);
	static int				getminimum(int (character::*proc)() const);
	static int				getmoverate();
	static unsigned			getround();
	static int				getspeed();
	static timezone_s		getzone();
	static int				getyear();
	bool					isallow(const action& e) const;
	bool					isallow(const effect& e) const;
	static bool				isparty(feat_s value);
	static bool				isparty(magic_power_s value);
	static bool				isparty(bool (character::*proc)() const);
	void					lookaround() const;
	void					loosemoney();
	void					makecamp();
	static void				passtime(bool interactive, unsigned rounds);
	inline void				passtime(bool interactive, duration_s value) { passtime(interactive, get(value, 0)); }
	void					pickpockets();
	static reaction_s		reduce(reaction_s id);
	outcome					resolve();
	void					resolve(const effect& e);
	outcome					resolve(const action& a);
};
namespace logs {
	struct state {
		const char*			information;
		int					width;
		state();
		~state();
	};
}
extern bsreq				alignment_type[];
extern bsreq				race_type[];
extern bsreq				gender_type[];
extern logs::state			logc;
extern adat<character*, 8>	party;
extern adat<character, 128> characters;