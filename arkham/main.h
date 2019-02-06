#include "logs/collection.h"
#include "logs/crt.h"
#include "logs/grammar.h"
#include "logs/logs.h"
#include "logs/logs_driver.h"

#pragma once

const int ItemUse = 2000;
const int SpecialUse = 1000;

enum stat_s : unsigned char {
	NoStat,
	Speed, Sneak, Fight, Will, Lore, Luck,
	Sanity, Stamina,
	Clue, Money, Focus, TurnToSkip, Blessed, Movement,
	StaminaMaximum, SanityMaximum,
	// Special checks
	CombatCheck, EvadeCheck, HorrorCheck, SkillCheck, SpellCheck,
	// Calculated values
	TestOneDie, TestTwoDie,
	// Item groups
	Ally, CommonItem, Monster, Skill, Spell, UniqueItem,
};
enum myth_s : unsigned char {
	NoMyth, StrangePlague, AlienTechnology, AnEvilFog, NotWork,
};
enum action_s : unsigned char {
	NoAction,
	Add1Clue, Add2Clue, Add3Clue, Add4Clue, Add5Clue, AddDClue,
	Lose1Clue, Lose2Clue, Lose3Clue, Lose4Clue, Lose5Clue,
	Add1Money, Add2Money, Add3Money, Add4Money, Add5Money, Add6Money, Add7Money, Add8Money, Add9Money, Add10Money,
	Lose1Money, Lose2Money, Lose3Money, Lose4Money, Lose5Money,
	Add1Sanity, Add2Sanity, Add3Sanity,
	Lose1Sanity, Lose2Sanity, Lose3Sanity, LoseDSanity,
	Add1Stamina, Add2Stamina, Add3Stamina, Add1_3Stamina,
	Lose1Stamina, Lose2Stamina, Lose3Stamina, LoseDStamina,
	Lose1Movement, Lose2Movement, Lose3Movement,
	RestoreAll, RestoreStamina, RestoreSanity, SkipTurn, LeaveOutside, Arrested, LoseMemory,
	MonsterAppear, MonsterAppearCursed,
	EncounterAbbys, EncounterArkhamAsylum, EncounterDreamland, EncounterArkhem, Encounter1of2Woods, Encounter1of2BlackCave, EncounterInRandomLocationAndMove,
	AddAllyAnnaKaslow, AddAllyDuke, AddAllyLegrase, AddAllyArmitage,
	AddCurse, LoseCurse, AddBless, LoseBless,
	AddRetainer,
	AddCommonItem, Add2CommonItem,
	BuyCommonItem, BuyCommonItem1Expence, BuyUniqueItem1of3, Buy3CommonAnd1Unique,
	AddUniqueItem, AddUniqueItemTome,
	AddSkill,
	AddSpell, AddSpell1of2, AddSpellOr3Clue,
	AddWhiskey,
	UsePart, Discard
};
enum number_s : unsigned char {
	All = 100, Half, OneDice, OneDiceMinus, HalfDiceOrNone, TwoDice,
};
enum location_s : unsigned char {
	AnyLocation,
	AdministrationBuilding, ArkhamAsylum, BankOfArkham, BlackCave, CuriositieShoppe,
	GeneralStore, Graveyard, HibbsRoadhouse, HistoricalSociety, IndependenceSquare,
	Library, MasBoardingHouse, Newspaper, PoliceStation, Jail, RiverDocks,
	ScienceBuilding, SilverTwilightLodge, SouthChurch, StMarysHospital, TheUnnamable,
	TheWitchHouse, TrainStation, UnvisitedIsle, VelmasDiner, Woods, YeOldeMagickShoppe,
	// Streets
	Easttown, Downtown, FrenchHill, MerchantDistrict, MiskatonicUniversity, Northside, Rivertown, SouthSide, Uptown,
	// Other words
	Abyss, AnotherDimension, CityOfTheGreatRace, GreatHallOfCeleano, PlateauOfLeng,
	Rlyeh, TheDreamlands, Yuggoth,
	// Special location
	Outskirt, Sky, Cup, InvestigatorTrophy,
};
enum feature_s : unsigned char {
	Tome, PhysicalWeapon, MagicalWeapon,
	CantStealOrLoose, CombatBonusTwoHand, ExhaustToRerollDie, ExhaustToEffect,
	CombatBonusVsUndead, DiscardAfterUse, SixDoubleSuccess,
	AutoCombatCheck, AutoGateCheck,
	OneHanded, TwoHanded,
};
enum card_s : unsigned char {
	NoItem,
	// Common items
	PistolDerringer18, PistolRevolver38, PistolAutomatic45,
	AncientTome, Axe, Bullwhip, CavalrySaber, Cross, DarkCloak, Dynamite, Food, Knife,
	Lantern, LuckyCigaretteCase, MapOfArkham, Motorcycle, OldJournal, ResearchMaterials, Rifle,
	Shotgun, TommyGun, Whiskey,
	// Skills
	SkillBarvery, SkillExpertOccultist, SkillMarksman,
	SkillSpeed, SkillSneak, SkillFight, SkillWill, SkillLore, SkillLuck,
	// Spells
	BindMonster, DreadCurseOfAzathoth, EnchantWeapon, FindGate,
	FleshWard, Heal, MistOfReleh, RedSignOfShuddleMell,
	Shrivelling, VoiceOfRa, Wither,
	// Unique items
	AlienStatue, AncientTablet, BlueWatcherOfThePyramid, BookOfDzyan,
	CabalaOfSaboth, CultesDesGoules, DragonsEye,
	ElderSign, EnchantedBlade, EnchantedJewelry, EnchantedKnife, FluteOfTheOuterGods,
	GateBox, HealingStone, HolyWater, LampOfAlhazred, NamelessCults,
	Necronomicon, ObsidianStatue, PallidMask, PowderOfIbnGhazi, RubyOfRlyeh,
	SilverKey, SwordOfGlory, TheKingInYellow, WardingStatue,
	//
	AnnaKaslow, Duke, EricColt, JohnLegrasse, ProfessorArmitage,
	RichardUptonPickman, RubyStandish, RyanDean, SirWilliamBrinton, ThomasFMalone,
	TomMountainMurphy, LastItem = TomMountainMurphy,
	//
	Byakhee, Chthonian, Cultist, DarkYoung, Dhole, DimensionShambler, ElderThing, FireVampire,
	FlyingPolyp, FormlessSpawn, Ghost, Ghoul, GodOfTheBloodyTongue, Gug, HaunterOfTheDark,
	HighPriest, HoundOfTindalos, Maniac, MiGo, Nightgaunt, Shoggoth,
	StarSpawn, TheBlackMan, TheBloatedWoman, TheDarkPharoah, Vampire, Warlock, Witch,
	Zombie
};
enum ancient_s : unsigned char {
	Azathoth, Cthulhu, Hastur, Ithaqua, Nyarlathotep, ShubNiggurath, Yig, YogSothoth
};
enum special_s : unsigned char {
	Hunches, Scrounge,
};
enum monster_color_s : unsigned char {
	Normal, Stationary, Fast, Unique, Flying,
};
enum monster_flag_s : unsigned char {
	Ambush, Endless, MagicalResistance, NightmarishI, OvervelmingI, PhysicalImmunity, PhysicalResistance, Undead,
};
struct roll_info {
	stat_s			id;
	char			bonus;
	char			difficult;
	bool			optional;
	//
	char*			getname(char* result, const char* result_maximum) const;
};
struct quest {
	struct action {
		operator bool() const { return text != 0; }
		const char*	text;
		action_s	results[6];
		quest*		next;
	};
	location_s		type;
	const char*		text;
	roll_info		roll;
	action			results[4];
	operator bool() const { return text != 0; }
};
typedef adat<quest*, 32> questa;
struct deck : adat<card_s, 128> {
	void			add(card_s id);
	void			create(stat_s group);
	static void		discard(card_s id);
	card_s			draw();
	card_s			draw(feature_s filter);
	void			draw(deck& source, int count);
	void			draw(deck& source, int count, feature_s filter);
	card_s			drawb();
	void			drawb(deck& source, int count);
	static deck&	getdeck(stat_s id);
	static void		initialize();
};
struct monster {
	monster() = default;
	constexpr monster(card_s type) : type(type), position(), owner() {}
	explicit operator bool() const { return type != NoItem; }
	void			discard();
	char			get(stat_s id);
	monster_color_s getcolor() const;
	static monster*	getfromcup();
	card_s			getid() const { return type; }
	const char*		getname() const;
	location_s		getposition() const { return position; }
	const char*		gettext() const;
	struct hero*	gettrophy() const { return owner; }
	static void		initialize();
	bool			is(monster_flag_s id) const;
	static int		remove(location_s id);
	static unsigned select(monster** result, monster** result_maximum, location_s value);
	void			set(location_s value) { position = value; }
	void			trophy(hero* owner);
private:
	card_s			type;
	location_s		position;
	struct hero*	owner;
};
struct hero {
	operator bool() const { return name != 0; }
	void			act(const char* format, ...) const;
	void			add(card_s id) { if(id) cards[id]++; }
	void			add(stat_s stat, card_s card, location_s location, int value, bool interactive);
	void			addally(stat_s stat, card_s card, location_s location, int value, bool interactive);
	void			addmagic(stat_s stat, card_s card, location_s location, int value, bool interactive);
	void			addretainer(stat_s stat, card_s card, location_s location, int value, bool interactive);
	void			addtrophy(monster& e);
	void			apply(const action_s* actions, bool interactive, bool* discard = 0, bool* usepart = 0);
	void			apply(action_s id, bool interactive = false, bool* discard = 0, bool* usepart = 0);
	void			arrested(stat_s stat, card_s card, location_s location, int count, bool interactive);
	void			ask(card_s i, const char* custom = 0) const;
	bool			before(monster& e, int round = 0);
	void			buy(stat_s stat, card_s card, location_s location, int count, bool interactive);
	void			buy1expence(stat_s stat, card_s card, location_s location, int count, bool interactive);
	void			buy1ofX(stat_s stat, card_s card, location_s location, int count, bool interactive);
	void			buyXofXCU(stat_s stat, card_s card, location_s location, int count, bool interactive);
	void			clear();
	bool			combat(monster& e);
	card_s			changeweapon(bool interactive = true) const;
	void			changeweapons(bool interactive = true);
	void			choose(stat_s stat, card_s card, location_s location, int count, bool interactive);
	void			choose(stat_s id, int count, int draw_count, int draw_bottom, bool interactive, feature_s* filter = 0, bool buymode = false, int more_cost = 0);
	quest*			choosebest(questa& source, int count, bool interactive);
	card_s			chooseexist(const char* text, card_s from, card_s to, bool interactive) const;
	void			chooselocation(stat_s stat, card_s card, location_s location, int count, bool interactive);
	void			chooseone(stat_s stat, card_s card, location_s location, int count, bool interactive);
	void			choosespellorclue(stat_s stat, card_s card, location_s location, int count, bool interactive);
	void			choosetome(stat_s stat, card_s card, location_s location, int count, bool interactive);
	void			create(const char* id);
	void			discard(card_s id);
	void			encounter(stat_s stat, card_s card, location_s location, int value, bool interactive);
	void			encounter1ofX(stat_s stat, card_s card, location_s location, int value, bool interactive);
	void			encounterany(stat_s stat, card_s card, location_s location, int value, bool interactive);
	void			encounterandmove(stat_s stat, card_s card, location_s location, int value, bool interactive);
	void			exhausecard(card_s i);
	void			finditem(stat_s stat, card_s card, location_s location, int count, bool interactive);
	void			focusing();
	char			get(stat_s id) const;
	char			get(card_s id) const;
	char			getbonus(stat_s id) const;
	char			getbonus(monster& e, card_s i, stat_s id);
	char			getbonus(stat_s id, card_s from, card_s to) const;
	char			getcount(stat_s id, char value) const;
	char			getfocus(stat_s id) const;
	gender_s		getgender() const { return gender; }
	location_s		getlocation() const { return position; }
	char			getmark(card_s id) const { return counter[id]; }
	char			getmaximum(stat_s id) const;
	const char*		getname() const { return name; }
	static void		getquest(questa& result, location_s value);
	static const quest*	getquest(location_s value, int index = -1);
	int				getskills() const;
	int				getspells() const;
	char			getsuccess() const;
	char			gettrophy() const;
	card_s			getwepon(int index) const { return weapons[index]; }
	void			leaveoutside(stat_s stat, card_s card, location_s location, int count, bool interactive);
	bool			is(special_s v) const { return special == v; }
	bool			is(myth_s value) const;
	bool			isallow(action_s id) const;
	bool			isallow(const action_s* actions) const;
	bool			isexhause(card_s i) const { return exhause[i] && cards[i] <= exhause[i]; };
	bool			isready() const { return get(Sanity) > 0 && get(Stamina) > 0; }
	void			losememory(stat_s stat, card_s card, location_s location, int count, bool interactive);
	void			monsterappear(stat_s stat, card_s card, location_s location, int value, bool interactive);
	void			movement();
	void			play();
	bool			remove(card_s e);
	static void		required(char* result, const char* result_maximum, action_s id);
	static void		required(char* result, const char* result_maximum, const action_s* id);
	void			restoreall(stat_s stat, card_s card, location_s location, int value, bool interactive);
	int				roll(stat_s id, int bonus = 0, int difficult = 1, bool interactive = true);
	void			run(const quest* e, bool* discard = 0, bool* usepart = 0, bool* again = 0);
	void			select(deck& result, stat_s group) const;
	void			set(location_s v) { position = v; }
	void			set(special_s id) { special = id; }
	void			set(stat_s id, int v) { stats[id] = v; }
	void			setname(const char* v) { name = v; }
	void			skipturn(stat_s stat, card_s card, location_s location, int value, bool interactive);
	void			upkeep();
	void			use(card_s i);
	bool			usable(card_s i) const;
	int				whatdo(bool interactive = true, bool clear_text = true);
private:
	const char*		name;
	gender_s		gender;
	special_s		special;
	char			stats[SanityMaximum + 1];
	char			focus[3];
	char			cards[LastItem + 1];
	char			exhause[LastItem + 1];
	char			counter[LastItem + 1];
	location_s		position;
	card_s			weapons[2];
};
struct location {
	const char*		id;
	const char*		name;
	const char*		text; // When you look around
	location_s		neightboard[7];
	char			clue;
	location_s		gate;
	bool			sealed;
	//
	location_s		getid() const;
	bool			isarkham() const;
};
struct use_info {
	action_s		before[4];
	quest*			script;
	char			usable; // This is maximum use count
};
struct monster_info {
	monster_color_s	color;
	char			awareness;
	char			horror[2];
	char			toughness;
	char			combat[2];
	cflags<monster_flag_s> flags;
	const char*		text;
};
struct game_info {
	ancient_s		ancient;
	short			day;
	char			doom;
	char			doom_maximum;
	char			terror;
	hero			players[1];
	//
	void			addterror();
	void			awakening();
	void			create(ancient_s i);
	void			finalbattle();
	int				getcombat() const;
	int				getmonsters() const;
	int				getsealcost() const;
	bool			is(ancient_s value) const { return ancient == value; }
	bool			is(myth_s value) const;
	void			monsterappear(location_s position);
	void			mything();
	void			opengate(location_s position);
	void			upkeep();
};
namespace item {
int					get(card_s i, stat_s id);
char				getcost(card_s i);
char				getcount(card_s i);
char*				getname(char* result, const char* result_maximum, card_s i, bool description = true, bool exhaused = false, char use = 0, bool price = false, int more_cost = 0);
stat_s				getgroup(card_s id);
int					gethands(card_s i);
char				getmark(card_s i);
const use_info&		getuse(card_s i);
bool				is(card_s i, feature_s value);
}
extern game_info	game;
char*				getstr(char* result, const char* result_maximum, stat_s id, int bonus);
extern location		location_data[Yuggoth + 1];