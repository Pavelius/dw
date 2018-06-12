#include "logs/collection.h"
#include "logs/crt.h"
#include "logs/dice.h"
#include "logs/grammar.h"
#include "logs/logs.h"
#include "logs/point.h"

#pragma once

enum item_s : unsigned char {
	NoItem,
	Axe, Club, Flail, Mace, MorningStar, Pick, Hammer,
	Spear, Staff, Halberd,
	Dagger, ShortSword, LongSword, BastardSword, TwoHandedSword, Scimitar,
	ShortBow, LongBow, Crossbow, Sling,
	BandedArmor, ChainArmor, LeatherArmor, PaddedArmor, PlateArmor, RingArmor, ScaleArmor, SplintedArmor, StuddedArmor,
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
	Cleric, Druid, Fighter, Paladin, Ranger, MagicUser, Illusionist, Theif,
};
enum race_s : unsigned char {
	NoRace,
	Human, Dwarf, Elf, Gnome, HalfElf, Halfling, HalfOrc,
};
enum gender_s : unsigned char {
	NoGender,
	Male, Female
};
enum alignment_s : unsigned char {
	Neutral,
	LawfulGood, NeutralGood, ChaoticGood,
	LawfulNeutral, ChaoticNeutral,
	LawfulEvil, NeutralEvil, ChaoticEvil
};
enum ability_s : unsigned char {
	Strenght, Dexterity, Constitution, Intellegence, Wisdow, Charisma,
};
enum god_s : unsigned char {
	Bane, Mystra, Tor, Tempos
};
enum skill_s : unsigned char {
	PickPockets, OpenLocks, FindRemoveTraps, MoveSilently, HideInShadows, DetectNoise, ClimbWalls, ReadLanguages,
	ForceDoor, ForceLockedDoor, FindSecretDoors, LearnSpell, Tracking,
};
enum action_s : unsigned char {
	Charsheet, MakeCamp, GoBack, GoNext, GoAway, GoInside, TakeAll, ExamineFeature,
};
enum magic_power_s : unsigned char {
	NoMagicPower,
	// Potions
	AnimalControl, Clairaudience, Clairvoyance, Climbing, Delusion, Diminution, DragonControl,
	Health, Madness, Youth, ESP, ExtraHealing, FireBreath, FireResistance, Flying, GaseousForm,
	GiantControl, GiantStrength, Growth, Healing, Heroism, HumanControl, Invisibility,
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
enum monster_s : unsigned char {
	Character,
	AntGiant, Badger, Bandit, BeetleFire, DemonManes, DwarfFolk, EarSeeker, ElfFolk,
	GnomeFolk, Goblin, HalflingFolk, Hobgoblin, Kobold, Orc, Piercer, RatGiant, RotGrub, Shrieker,
	Skieleton, Zombie,
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
	Instantaneous, Concetration,
	Duration1Round, Duration1RoundPerLevel, Duration1RoundPerLevelPlus1, Duration1RoundPerLevelPlus2, Duration1RoundPerLevelPlus3, Duration1RoundPerLevelPlus1d3, Duration1RoundPerLevelPlus1d4,
	Duration1d10Rounds, Duration2d20Rounds,
	Duration2RoundPerLevel, Duration2RoundPlus1RoundPerLevel,
	Duration4RoundPlus1RoundPerLevel,
	Duration5RoundPerLevel,
	Duration6Round,
	Duration1Turn, Duration1TurnPerLevel, Duration1TurnPlus1Per2Level,
	Duration3Turn,
	Duration5Turn,
	Duration6Turn,
	Duration6TurnPlus1PerLevel,
	Duration4Hours,
	Duration10Hours,
	Duration1DayPerLevel,
	Duration1Month,
	Permanent,
};
enum feat_s : unsigned char {
	NoFeat,
	Animal,
	BonusSaveVsPoison, BonusSaveVsWands, BonusSaveVsSpells, BonusSaveVsLighting,
	Infravision,
	ImmuneCharmAndSleep,
	Alertness, Assasination, LightSteps,
	ElfWeaponTraining, DwarfCombatTactic, RangerCombatTactic,
	HolyGrace, DetectEvil, HolyHealth, LayOnHand,
	DetectSecretDoors, Mining,
	NatureKnowledge, NatureLanguage,
	UsePickPockets, UseOpenLocks, UseFindRemoveTraps, UseMoveSilently,
	UseHideInShadows, UseDetectNoise, UseClimbWalls, UseReadLanguages,
	TurnUndead, Backstab,
	ResistSlashingAndPierce, LooseInitiative,
	MagicWeaponToHit1, Undead,
};
enum reaction_s : unsigned char {
	Indifferent, Friendly, Flight, Cautions, Threatening, Hostile,
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
	// 1 - level cleric
	SpellBless, SpellCommand, SpellCreateWater, SpellCureLightWounds, SpellDetectEvil,
	SpellDetectMagic, SpellLight, SpellProtectionFromEvil, SpellPurifyFoodDrink, SpellRemoveFear,
	SpellResistCold, SpellSanctuary,
	// 2 - level cleric
	SpellAugury, SpellChant, SpellDetectCharm, SpellFindTraps, SpellHoldPerson,
	SpellKnowAlignment, SpellResistFire, SpellSilence15Radius, SpellSlowPoison, SpellSnakeCharm,
	SpellSpeakWithAnimals, SpellSpiritualHammer,
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

enum type_s : unsigned char {
	Action,
	Ability, Alignment, Class, Feat, Item, Monster, Power, Race, Reaction, Skill, Spell, Timezone,
};
// Compile-time tag generator
struct tag {
	type_s					type;
	unsigned char			value;
	constexpr tag() : type(Action), value(0) {}
	constexpr tag(ability_s value) : type(Ability), value(value) {}
	constexpr tag(action_s value) : type(Action), value(value) {}
	constexpr tag(alignment_s value) : type(Alignment), value(value) {}
	constexpr tag(class_s value) : type(Class), value(value) {}
	constexpr tag(item_s value) : type(Item), value(value) {}
	constexpr tag(feat_s value) : type(Feat), value(value) {}
	constexpr tag(magic_power_s value) : type(Power), value(value) {}
	constexpr tag(monster_s value) : type(Monster), value(value) {}
	constexpr tag(race_s value) : type(Race), value(value) {}
	constexpr tag(reaction_s value) : type(Reaction), value(value) {}
	constexpr tag(skill_s value) : type(Skill), value(value) {}
	constexpr tag(spell_s value) : type(Spell), value(value) {}
	constexpr tag(timezone_s value) : type(Timezone), value(value) {}
	constexpr tag(type_s type, unsigned char value) : type(type), value(value) {}
	constexpr tag(short unsigned value) : type((type_s)(value>>8)), value(value&0xFF) {}
	constexpr operator unsigned short() const { return (type << 8) | value; }
};
constexpr inline short unsigned tg(tag i) { return i; }
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
struct attackinfo : damageinfo {
	char					thac0;
	char					attacks_per_two_rounds;
	char					critical;
	char					multiplier;
	struct item*			weapon;
	attackinfo() { clear(); }
	void					clear();
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
	static char*			getdescription(char* result, const char* result_maximum, aref<item> source);
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
	item					getfirst();
};
// Dungeon encounter descriptor
struct dungeon_encounter {
	char					chance;
	monster_s				monster;
	unsigned char			count[2];
	const dungeon_encounter* child;
	const dungeon_encounter* roll() const;
};
struct character {
	struct variable {
		const char*			id;
		const char*			name;
		int					(character::*proc)() const;
		const char*			present;
	};
	character();
	~character();
	character(race_s race, gender_s gender, class_s type, const char* abilities, bool party_member);
	character(race_s race, gender_s gender, const class_s* type, const char* abilities, bool party_member);
	character(bool interactive);
	character(monster_s type);
	operator bool() const { return name != 0; }
	void					act(const char* format, ...) const;
	void					actvs(const character& e, const char* format, ...) const;
	bool					add(item value);
	void					add(magic_power_s id, unsigned count_rounds = 10);
	void					addcombat(side_s side);
	void					addexp(bool interactive, unsigned value);
	void					addmoney(int count);
	static void				addparty();
	void					attack(bool interactive, character& enemy, wear_s weapon, bool flatfooted = false);
	void					clear();
	void					charsheet();
	static void				checkstates();
	static void				chooseability(bool interactive, char* abilities);
	static const class_s*	chooseclass(bool interactive, race_s race, char* abilities);
	static race_s			chooserace(bool interactive, char* abilities);
	void					create(bool interactive, race_s race, gender_s gender, const class_s* type, const char* abilities, bool party_member);
	void					damage(bool interactive, int value);
	void					damage(bool interactive, int value, saveinfo& e);
	bool					get(attackinfo& result, wear_s weapon) const;
	int						get(ability_s id) const;
	int						get(class_s id) const;
	int						get(save_s id) const;
	int						get(skill_s id) const;
	item					get(wear_s id) const { return wears[id]; }
	character*				get(aref<character*> parcipants, bool (character::*proc)(const character* opponent) const) const;
	alignment_s				getalignment() const { return alignment; }
	static alignment_s		getalignment(monster_s id);
	static dice				getappearing(monster_s id);
	int						getAC(bool flatfooted) const;
	int						getAC() const { return getAC(false); }
	static int				getAC(monster_s value);
	static const char*		getadjustment(race_s value);
	class_s					getclass() const { return classes[0]; }
	static const classa&	getclasses(skill_s value);
	unsigned				getcount() const;
	character*				getenemy() const;
	int						getcostexp() const;
	int						getexperience() const { return experience; }
	static const feata&		getfeats(race_s value);
	gender_s				getgender() const { return gender; }
	int						getHD() const { return levels[0]; }
	static int				getHD(class_s value);
	int						gethp() const { return hp; }
	static const char*		getinfo(race_s value);
	int						getinitiative() const { return initiative; }
	static class_s			getkit(class_s value);
	int						getmaxclasses() const;
	int						getmaxhp() const;
	static char*			getmaximum(race_s value);
	static char*			getminimum(class_s value);
	static char*			getminimum(race_s value);
	int						getmoney() const { return coopers; }
	const char*				getname() const;
	char*					getname(char* result, const char* result_maximum) const;
	static const char*		getnameof(monster_s id);
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
	static aref<item_s>		getusablearmor(class_s value);
	static aref<item_s>		getusableweapon(class_s value);
	bool					is(feat_s value) const;
	bool					is(magic_power_s id) const;
	bool					is(class_s id) const { return classes[0] == id || classes[1] == id || classes[2] == id;	}
	bool					isallow(const tag id) const;
	bool					isenemy(const character* p) const;
	bool					isplayer() const;
	bool					isready() const { return this && hp > 0; }
	bool					isuse(item_s value) const;
	bool					isusearmor() const;
	static bool				isusearmor(class_s value);
	bool					isvulnerable(feat_s value) const { return false; }
	void					raiselevel(bool interactive, class_s type);
	bool					roll(tag id) const;
	bool					savingthrow(saveinfo& e) const;
	void					say(const char* format, ...) const;
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
	race_s					race;
	monster_s				monster;
	char					abilities[Charisma + 1];
	short					hp, hp_maximum;
	char					initiative;
	unsigned char			feats[8];
	side_s					side;
	char					strenght_percent;
	short unsigned			name;
	point					position;
	class_s					classes[3];
	char					levels[3];
	item					wears[Legs + 1];
	int						coopers;
	int						experience;
	short unsigned			count;
	//
	void					equip(class_s type);
	void					finish(bool party_member);
	const char*				find(class_s value) const;
	int						getbonus(int(item::*)() const) const;
	char*					getmonstername(char* result, const char* result_maximum) const;
	void					removepowers() const;
	void					setmonsterhp();
	friend struct archive;
};
namespace game {
	bool					attack(int thac0, int ac);
	void					charsheet();
	character*				choose(bool interactive);
	character*				choose(bool interactive, tag id);
	void					combat(bool interactive);
	void					combat(bool interactive, character& enemy);
	void					combat(bool interactive, monster_s type, unsigned count);
	void					dungeon();
	void					encounter();
	void					encounter(character& monsters);
	unsigned				get(duration_s value, int level = 1);
	int						getday();
	const dungeon_encounter* getdungeonencounter(int level);
	const char*				getencounterchance(landscape_s id);
	int						gethour();
	int						getmonth();
	character*				getplayer();
	const char*				getstrmovement(landscape_s id);
	int						getminimum(int (character::*proc)() const);
	int						getmoverate();
	inline int				getpartyspeed() { return getminimum(&character::getspeed); }
	character*				getplayer();
	unsigned				getround();
	timezone_s				getzone();
	int						getyear();
	bool					isallow(const tag id);
	bool					isallow(const tag id, character* player);
	bool					isparty(bool (character::*proc)() const);
	bool					ispartyready();
	void					passtime(bool interactive, unsigned rounds);
	inline void				passtime(bool interactive, duration_s value) { passtime(interactive, get(value, 0)); }
	template<typename T> T	random(const aref<T> source) { return source.data[rand() % source.count]; }
	reaction_s				reduce(reaction_s id);
	void					write(const char* name);
};
namespace logs {
	struct state {
		const char*			information;
		int					width;
		state();
		~state();
	};
}
extern logs::state			logc;
extern adat<character*, 8>	party;
extern adat<character, 128>	characters;