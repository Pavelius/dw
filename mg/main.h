#include "crt.h"
#include "logs.h"

#pragma once

using namespace logs;

enum distace_s : unsigned char {
	DistanceNormal, DistanceSpear, DistanceThrown, DistanceMissile
};
enum item_s : unsigned char {
	NoItem,
	Axe, Bow, Halberd, HookAndLine, Knife, Shield, Sling, Spear, Staff, Sword,
	LightArmor, HeavyArmor,
	Herbs, Nuts, Grains, Roots,
	LastItem = Roots,
};
enum skill_s : unsigned char {
	Nature, Will, Health, Resources, Circles,
	Administrator, Apiarist, Archivist, Armorer, Baker,
	Boatcrafter, Brewer, Carpenter, Cartographer, Cook,
	Deceiver, Fighter, Glazier, Haggler, Harvester,
	Healer, Hunter, Insectrist, Instructor, Laborer,
	Loremouse, Militarist, Miller, Orator, Pathfinder,
	Persuader, Potter, Scientist, Scout, Smith,
	Stonemason, Survivalist, WeatherWatcher, Weaver,
	FirstSkill = Administrator, LastSkill = Weaver,
};
enum condition_s : unsigned char {
	Healthy, HungerAndThirsty, Angry, Tired, Injured, Sick, Dead,
};
enum trait_s : unsigned char {
	Bigpaw, Bitter, Bodyguard, Bold, Brave,
	Calm, Clever, Compassionate, Cunning, Curious,
	DeepEar, Defender, Determined, Driven, EarlyRiser,
	Extrovert, Fat, Fearful, Fearless, Fiery,
	Generous, Graceful, GuardsHonor, Innocent, Jaded,
	Leader, Longtail, Lost, NaturalBearings, Nimble,
	Nocturnal, Oldfur, QuickWitted, Quiet, Scarred,
	SharpEyed, Sharptooth, Short, Skeptical, Skinny,
	Stoic, Stubborn, Suspicious, Tall, Thoughtful,
	Tough, WeatherSense, Wise, WolfsSnout, Young,
	Alert, HardWorker, Independent, OpenMinded, SteadyPaw, Inquisitive, Rational,
	FirstTraits = Bigpaw, LastTraits = Rational,
};
enum landscape_s : unsigned char {
	NoLandscape,
	Coast, Forest, Lake, Rocks, Swamp, TallGrass
};
enum location_s : unsigned char {
	NoLocation,
	Barkstone, Cooperwood, Elmoss, Ivydale, Lockhaven, PortSumac, Shaleburrow, Sprucetuck, // Eight most knowed locations
};
enum location_size_s : unsigned char {
	Village, Towm, City,
};
enum animal_s : unsigned char {
	NoAnimal,
	Badger, Bear, Crab, Deer, Fox, Frog, Hawk, Moose, Mouse, Owl, Racoon, Snake, Squirrel, Turtle, Weasel, Wolf,
};
enum rang_s : unsigned char {
	Tenderpaws, Guardmouse, PatrolGuard, PatrolLeader, GuardCapitan,
};
enum wise_s : unsigned char {
	BirdsWise, BurrowWise, MammalsWise, PredatorWise,
	CoastWise, ForestWise, LakeWise, RockyTerrainWise, SwampWise, TallGrassWise,
	CraftWise, CrimeWise, GovernorWise, GuardmouseWise,
	RainWise, ClearWeatherWise, SnowWise,
	BarkstoneWise, CooperwoodWise, DarkHeatherWise, ElmossWise, IvydaleWise, LockhavenWise, PortSumacWise, ShaleburrowWise, SprucetuckWise,
	FirstWise = BirdsWise, LastWise = SprucetuckWise
};
enum conflict_s : unsigned char {
	FightConflict,
};
enum action_s : unsigned char {
	Attack, Defend, Feint, Maneuver
};
enum roll_type_s : unsigned char {
	StandartRoll, ConflictRoll, RecoveryRoll,
};
enum action_roll_s : unsigned char {
	NoRoll, IndependedRoll, VersusRoll,
};
enum maneuver_s : unsigned char {
	Impende, GainPosition, Disarm,
	FirstManeuver = Impende, LastManeuver = Disarm
};
enum season_s : unsigned char {
	Spring, Summer, Autum, Winter,
};
enum weather_s : unsigned char {
	ClearAndWarm, SpringSnow, SpringRain, SpringStorms, SpringUnseasonablyCold, SpringUnseasonablyWarm,
	WarmAndHumid, SummerRain, Thunderstorms, HeatWaves,
	AutumStorms, ColdRain, AutumUnseasonablyCold, AutumUnseasonablyWarm,
	ClearAndCold, Snow, Blizzard, ColdSnap, IceStorm, WinterUnseasonablyWarm,
	FirstWeather = ClearAndWarm, LastWeather = WinterUnseasonablyWarm,
};
enum variant_s : unsigned char {
	NoVariant,
	Action, Condition, Season, Skill, Weather,
};
struct variant {
	variant_s					type;
	unsigned char				value;
	constexpr variant() : type(NoVariant), value(0) {}
	constexpr variant(action_s v) : type(Action), value(v) {}
	constexpr variant(condition_s v) : type(Condition), value(v) {}
	constexpr variant(season_s v) : type(Season), value(v) {}
	constexpr variant(skill_s v) : type(Skill), value(v) {}
	constexpr variant(weather_s v) : type(Weather), value(v) {}
};
typedef flagable<1>				conditiona;
typedef adat<skill_s, 8>		skilla;
typedef adat<trait_s, 8>		traita;
typedef adat<wise_s, 4>			wisea;
struct actioni {
	const char*					id;
	const char*					name;
	const char*					nameby;
	action_roll_s				rolls[Maneuver + 1];
};
struct animali {
	const char*					id;
	const char*					name;
	gender_s					gender;
	char						nature;
	wise_s						wise;
};
struct wisei {
	const char*					id;
	const char*					name;
};
struct traiti {
	const char*					id;
	const char*					name;
	skill_s						bonus[4];
};
struct seasoni {
	const char*					id;
	const char*					name;
	char						obstacle;
};
struct weatheri {
	const char*					id;
	const char*					name;
	const char*					now_text;
	const char*					start_text;
	char						chance;
	season_s					season;
	season_s					season_link;
	conditiona					conditions;
	bool						weather_factor_for_outdoor;
	char						obstacle_for_tired;
	char						obstacle_for_sick;
	skilla						skills;
	weather_s					getid() const;
};
struct conditioni {
	const char*					id;
	const char*					name;
	const char*					text;
	skilla						skills;
	skilla						recover;
	char						recover_ob;
};
struct itemcni {
	char						bonus[4];
	char						success[4];
	bool						use_two_hands;
	bool						thrown;
	char						heavy;
	bool						heavy_skill_penalty;
};
struct skilli {
	const char*					id;
	const char*					name;
	skilla						help;
};
struct conflicti {
	const char*					id;
	const char*					name;
	skill_s						skills[2][4];
};
struct maneuveri {
	const char*					id;
	const char*					name;
	int							cost;
};
struct itemi {
	const char*					id;
	const char*					name;
	char						ob;
	itemcni						conflict;
};
class item {
	item_s						type;
	unsigned char				disarmed : 1;
	unsigned char				used : 1; // Light armor or Thrown weapon
public:
	constexpr item(item_s type = NoItem) : type(type), disarmed(0), used(0) {}
	explicit operator bool() const { return type != NoItem; }
	int							getbonus(action_s value) const;
	void						getbonus(stringbuilder& sb, action_s action, const char* prefix = " (", const char* postfix = ")") const;
	int							getcost() const;
	const itemi&				getitem() const { return bsmeta<itemi>::elements[type]; }
	const char*					getname() const { return getitem().name; }
	int							getsuccess(action_s value) const;
	const char*					gettext(action_s value) const;
	bool						isready() const { return disarmed == 0 && used == 0; }
	bool						istwohanded() const;
	void						setdisarm(int v) { disarmed = v; }
};
struct locationi {
	const char*					id;
	const char*					name;
	const char*					nameof;
	skilla						skills;
	traita						traits;
	wise_s						wise;
	location_size_s				size;
};
struct landscapei {
	const char*					id;
	const char*					name;
	wise_s						wise;
};
struct rangi {
	struct skillset {
		skill_s					key;
		char					value;
	};
	const char*					id;
	const char*					name;
	unsigned char				age[2];
	skillset					skills[16];
	char						talented;
	char						convice;
	char						mentors;
	char						specialization;
	char						wises;
	char						trait_tender;
	char						trait_leader;
};
class nameable {
	short unsigned				name;
public:
	animal_s					getanimal() const;
	const char*					getname() const;
	gender_s					getgender() const;
};
class hero {
	unsigned char				name;
	char						checks, fate, persona;
	char						skills[LastSkill + 1];
	char						traits[LastTraits + 1];
	char						traits_used[LastTraits + 1];
	char						fail[LastSkill + 1];
	char						pass[LastSkill + 1];
	char						wises[LastWise + 1];
	unsigned char				conditions;
	//
	void						tallyskills();
	void						tallywises();
public:
	animal_s					type;
	rang_s						rang;
	unsigned char				age;
	skill_s						specialization;
	location_s					homeland;
	gender_s					gender;
	item						weapon, armor, gears[4];
	hero*						family;
	hero*						friends[3];
	hero*						enemies[3];
	//
	hero() = default;
	hero(animal_s type);
	hero(animal_s type, gender_s gender, skill_s skill, location_s homeland);
	hero(rang_s rang, item_s weapon, bool interactive = false, bool isplayer = true);
	void* operator new(unsigned size);
	operator bool() const { return type != NoAnimal; }
	//
	void						act(const char* format, ...) const;
	void						buyeqipment();
	bool						canhelp(skill_s value, skill_s* result = 0) const;
	void						clear();
	static hero*				choose(skill_s skill);
	static hero*				choose(bool interactive, bool (hero::*proc)() const);
	void						choosename(bool interactive);
	static rang_s				chooserang(bool interactive);
	static void					fight(animal_s type);
	static action_roll_s		get(action_s player, action_s opposition);
	int							get(skill_s value) const;
	int							get(trait_s value) const { return traits[value]; }
	int							get(wise_s value) const { return wises[value]; }
	static void					get(adat<condition_s, 8>& conditions, skill_s skill);
	const char*					getA() const;
	animal_s					getanimal() const { return type; }
	void						getinfo(stringbuilder& sb) const;
	const char*					getLA() const;
	static char*				getmembers(char* result, hero** helps);
	const char*					getname() const;
	static const char*			getnameby(action_s value);
	hero*						getparent() const { return family; }
	static int					getobstacle(season_s value);
	static season_s				getseason();
	static weather_s			getweather();
	static void					gonext();
	bool						is(condition_s value) const;
	bool						isalive() const { return !is(Dead); }
	bool						isanimal() const { return type != Mouse; }
	static bool					isbonus(trait_s base, skill_s value);
	bool						ischeck() const { return checks >= 1; }
	bool						ischeck2() const { return checks >= 2; }
	bool						isconditions() const;
	static bool					isfactor(weather_s object, skill_s value);
	bool						isfreegear() const;
	static bool					ismatch(landscape_s id, wise_s value);
	static bool					ismatch(location_s value, wise_s wise);
	static bool					ismatch(animal_s value, wise_s wise);
	static bool					ismatch(bool (hero::*proc)() const);
	bool						isplayer() const;
	static bool					passtest(skill_s skill, int obstacle);
	static void					quest(const char* name);
	int							roll(skill_s value, int obstacle, int bonus_dices = 0, int bonus_success = 0, bool interactive = true, roll_type_s roll_type = StandartRoll, hero* opponent = 0, hero** allies = 0, hero** helpers = 0, skill_s opponent_skill = Nature, int opponent_bonus_dices = 0, int opponent_success = 0);
	bool						rollresource(int obstacle, bool interactive = true);
	void						recover();
	void						recover(condition_s value);
	void						remove(condition_s value);
	void						set(condition_s value);
	void						set(rang_s rang);
	void						set(skill_s value, int number);
	void						set(trait_s value, int number) { traits[value] = number; }
	void						set(wise_s value, int number);
	static void					setyearweather();
	static void					playersturn();
	static void					twistconditions(bool interactive, skill_s skill, hero** helps);
	static void					twistweather(bool interactive, skill_s skill, hero** helps);
	void						use(trait_s value);
	static void					weatherwatch();
};
struct order {
	action_s					action;
	hero*						actor;
	item*						weapon;
};
struct parcipants : adat<hero*, 7> {
	void						act(const char* format, ...) const;
};
inline int						d100() { return rand() % 100; }
extern hero*					players[4];
DECLENUM(action);
DECLENUM(animal);
DECLENUM(location);
DECLENUM(maneuver);
DECLENUM(rang);
DECLENUM(skill);
DECLENUM(trait);
DECLENUM(wise);