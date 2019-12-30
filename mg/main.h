#include "crt.h"
#include "logs.h"

#pragma once

using namespace logs;

const unsigned short Blocked = 0xFFFF;

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
	Tough, WeatherSense, WiseTrait, WolfsSnout, Young,
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
enum special_s : unsigned char {
	Bonus, Penalty, Success,
};
enum tag_s : unsigned char {
	Absorb, Armor, Bulky, CloseRanks, Clumsy, Deadly, GentleThrashing, Handy,
	Fast, Fragile, Heavy, Hooked, LongRange,
	MediumRange, Missile, Protection, ShortAndQuick, Slow,
	Thrown, TwoHanded, HeavySkillPenalty, Useful, Unwieldy,
	Versatile,
	LastTag = Versatile,
};
enum wear_s : unsigned char {
	Hands, Offhand, Body,
	FirstGear, LastGear = FirstGear + 3,
};
enum roll_flag_s : unsigned char {
	MarkExperience, RecoveryTest, ActWithNature,
};
enum variant_s : unsigned char {
	NoVariant,
	Action, Animal, Condition, Conflict, Landscape, Location,
	Season, Skill, Special, Tag, Variant, Wise, Weather,
};
struct variant {
	variant_s					type;
	unsigned char				value;
	constexpr variant() : type(NoVariant), value(0) {}
	constexpr variant(action_s v) : type(Action), value(v) {}
	constexpr variant(animal_s v) : type(Animal), value(v) {}
	constexpr variant(condition_s v) : type(Condition), value(v) {}
	constexpr variant(conflict_s v) : type(Conflict), value(v) {}
	constexpr variant(landscape_s v) : type(Landscape), value(v) {}
	constexpr variant(location_s v) : type(Location), value(v) {}
	constexpr variant(season_s v) : type(Season), value(v) {}
	constexpr variant(skill_s v) : type(Skill), value(v) {}
	constexpr variant(special_s v) : type(Special), value(v) {}
	constexpr variant(tag_s v) : type(Tag), value(v) {}
	constexpr variant(variant_s v) : type(Variant), value(v) {}
	constexpr variant(wise_s v) : type(Wise), value(v) {}
	constexpr variant(weather_s v) : type(Weather), value(v) {}
	explicit constexpr operator bool() const { return type != NoVariant; }
	constexpr bool operator==(const variant& e) const { return type == e.type && value == e.value; }
	constexpr bool operator!=(const variant& e) const { return type != e.type || value != e.value; }
};
typedef flagable<Dead>			conditiona;
typedef flagable<ActWithNature>	rollf;
typedef adat<skill_s, 8>		skilla;
typedef adat<trait_s, 8>		traita;
typedef flagable<LastWise>		wisea;
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
	variant						subject;
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
	weather_s					epic;
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
	//
	weather_s					getid() const;
	constexpr bool				nonseason() const { return season != season_link; }
};
struct conditioni {
	const char*					id;
	const char*					name;
	const char*					text;
	skilla						skills;
	skilla						recover;
	char						recover_ob;
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
	flagable<LastTag>			tags;
};
class item {
	item_s						type;
	//
	unsigned char				disarmed : 1;
	unsigned char				useful_used : 1;
	action_s					useful : 2;
	unsigned char				charge : 4; // Light armor or Thrown weapon
public:
	constexpr item(item_s type = NoItem) : type(type), disarmed(0), useful_used(0), useful(Attack), charge(1) {}
	explicit operator bool() const { return type != NoItem; }
	int							getbonus(action_s value) const;
	void						getbonus(stringbuilder& sb, action_s action, const char* prefix = " (", const char* postfix = ")") const;
	int							getcost() const;
	const itemi&				getitem() const { return bsmeta<itemi>::elements[type]; }
	const char*					getname() const { return getitem().name; }
	int							getsuccess(action_s value) const;
	const char*					gettext(action_s value) const;
	bool						is(tag_s v) const { return getitem().tags.is(v); }
	bool						isready() const { return disarmed == 0 && charge > 0; }
	void						set(action_s v) { useful = v; }
	void						setdisarm(int v) { disarmed = v; }
	void						setuseful(int v) { useful_used = v; }
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
class nameable : variant {
	short unsigned				name;
public:
	constexpr nameable() : variant(), name() {}
	constexpr nameable(variant v) : variant(v), name() {}
	explicit constexpr operator bool() const { return type != NoVariant; }
	void						act(const char* format, ...) const;
	void						actv(stringbuilder& sb, const char* format, const char* format_param) const;
	animal_s					getanimal() const { return (animal_s)value; }
	const char*					getname() const;
	gender_s					getgender() const;
	bool						isanimal() const { return type == Animal && value != Mouse; }
	void						setkind(variant object);
	void						setname(gender_s gender);
};
class hero;
class heroa : public adat<hero*, 4> {
public:
	void						act(const char* format, ...) const;
	void						actv(stringbuilder& sc, const char* format, const char* format_param) const;
	void						add(hero* p);
	void						addn(stringbuilder& sb) const;
	void						select();
};
class hero : public nameable {
	char						checks, fate, persona;
	unsigned char				conditions;
	char						skills[LastSkill + 1];
	char						traits[LastTraits + 1];
	flagable<LastTraits>		trait_used;
	char						fail[LastSkill + 1];
	char						pass[LastSkill + 1];
	wisea						wises;
	item						wears[LastGear + 1];
	unsigned short				family_id;
	unsigned char				age;
	rang_s						rang;
	skill_s						specialization;
	location_s					homeland;
	//
	void						tallyskills();
public:
	void						addplayer();
	void						buyeqipment();
	bool						canhelp(skill_s value, skill_s* result = 0) const;
	static hero*				choose(skill_s skill);
	static hero*				choose(bool interactive, bool (hero::*proc)() const);
	static rang_s				chooserang(bool interactive);
	void						create(animal_s type);
	void						create(animal_s type, gender_s gender, skill_s specialization, location_s homeland);
	void						create(rang_s rang, bool interactive);
	static void					fight(animal_s type);
	static action_roll_s		get(action_s player, action_s opposition);
	int							get(skill_s value) const;
	int							get(trait_s value) const { return traits[value]; }
	static void					get(adat<condition_s, 8>& conditions, skill_s skill);
	item&						get(wear_s v) { return wears[v]; }
	void						getinfo(stringbuilder& sb) const;
	location_s					gethomeland() const { return homeland; }
	static const char*			getnameby(action_s value);
	hero*						getparent() const { return (family_id==Blocked) ? 0 : bsmeta<hero>::elements + family_id; }
	skill_s						getspecial() const { return specialization; }
	static int					getobstacle(season_s value);
	static void					gonext();
	bool						is(condition_s value) const;
	bool						is(wise_s v) const { return wises.is(v); }
	bool						isalive() const { return !is(Dead); }
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
	int							roll(skill_s value, int obstacle, int bonus_dices = 0, int bonus_success = 0, bool interactive = true);
	int							roll(roll_type_s roll_type, heroa& allies, heroa& helpers, bool interactive, skill_s value, int obstacle, int bonus_dices = 0, int bonus_success = 0, hero* opponent = 0, skill_s opponent_skill = Nature, int opponent_bonus_dices = 0, int opponent_bonus_success = 0);
	bool						rollresource(int obstacle, bool interactive = true);
	void						recover();
	void						recover(condition_s value);
	void						remove(condition_s value);
	void						set(condition_s value);
	void						set(wear_s i, item v) { wears[i] = v; }
	void						set(rang_s rang);
	void						set(skill_s value, int number);
	void						set(trait_s value, int number) { traits[value] = number; }
	void						set(wise_s v) { wises.set(v); }
	void						setfamily(const hero* v);
	void						sethomeland(location_s v) { homeland = v; }
	void						setspecial(skill_s v) { specialization = v; }
	static void					playersturn();
	static void					twistconditions(bool interactive, skill_s skill, heroa& helps);
	static void					twistweather(bool interactive, skill_s skill, heroa& helps);
	void						use(trait_s value);
	static void					weatherwatch();
};
struct order {
	action_s					action;
	hero*						actor;
	item*						weapon;
};
union idu {
	int							i;
	struct {
		unsigned char			a, b, c, d;
	};
	struct {
		short					s1, s2;
	};
	constexpr idu(int i) : i(i) {}
	constexpr idu(unsigned char a, unsigned char b, unsigned char c = 0, unsigned char d = 0) : a(a), b(b), c(c), d(c) {}
	constexpr operator int() { return i; }
};
struct twisti {
	variant						conditions[6];
	const char*					text;
};
typedef adat<twisti*, 31>		twista;
class squadi : public heroa {
	short unsigned				year;
	short unsigned				year_index;
	static season_s				year_cicle[14];
	weather_s					year_weather[14];
	variant						location;
	hero*						opposition;
	//
	bool						stage();
public:
	void						addweather();
	void						clear();
	short unsigned				getnext() const { return (year_index + 1) % (sizeof(year_cicle) / sizeof(year_cicle[0])); }
	season_s					getseason() const { return year_cicle[year_index]; }
	static season_s				getseason(short unsigned i) { return year_cicle[i]; }
	weather_s					getweather() const { return year_weather[year_index]; }
	short unsigned				getyear() const { return year; }
	bool						match(const twisti& e) const;
	bool						match(wise_s v) const;
	void						play();
	bool						play(const twisti& e);
	void						set(variant v);
	void						set(short unsigned index, weather_s v) { year_weather[index] = v; }
	void						setopponent(hero* v) { opposition = v; }
	void						setyearweather();
};
inline int						d100() { return rand() % 100; }
extern squadi					party;
DECLENUM(action);
DECLENUM(animal);
DECLENUM(location);
DECLENUM(maneuver);
DECLENUM(rang);
DECLENUM(skill);
DECLENUM(trait);
DECLENUM(wise);