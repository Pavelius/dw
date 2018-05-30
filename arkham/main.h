#include "logs/adat.h"
#include "logs/aref.h"
#include "logs/crt.h"
#include "logs/cflags.h"
#include "logs/grammar.h"
#include "logs/logs.h"
#include "logs/logs_driver.h"
#include "logs/stringcreator.h"

#pragma once

enum stat_s : unsigned char {
	NoStat,
	Speed, Sneak, Fight, Will, Lore, Luck,
	Sanity, Stamina,
	Clue, Money, Focus, TurnToSkip, Blessed,
	StaminaMaximum, SanityMaximum,
	// Special checks
	CombatCheck, EvadeCheck, HorrorCheck, SkillCheck, SpellCheck,
	// Calculated values
	Movement, TestOneDie, TestTwoDie,
	// Item groups
	CommonItem, UniqueItem, Spell, Skill,
};
enum action_s : unsigned char {
	NoAction,
	Add1Clue, Add2Clue, Add3Clue, Add4Clue, Add5Clue,
	Lose1Clue, Lose2Clue, Lose3Clue, Lose4Clue, Lose5Clue,
	Add1Money, Add2Money, Add3Money, Add4Money, Add5Money, Add6Money, Add7Money, Add8Money, Add9Money, Add10Money,
	Lose1Money, Lose2Money, Lose3Money, Lose4Money, Lose5Money,
	Add1Sanity, Add2Sanity, Add3Sanity,
	Lose1Sanity, Lose2Sanity, Lose3Sanity,
	Add1Stamina, Add2Stamina, Add3Stamina,
	Lose1Stamina, Lose2Stamina, Lose3Stamina,
	SkipTurn, LeaveOutside, Arrested, LoseMemory,
	AddCurse, LoseCurse, AddBless, LoseBless,
	AddCommonItem, Add2CommonItem,
	AddUniqueItem,
	AddSkill,
	AddSpell,
	Discard
};
enum number_s : unsigned char {
	All=100, Half, OneDice, TwoDice,
};
enum location_s : unsigned char {
	AnyLocation,
	AdministrationBuilding, ArkhamAsylum, BankOfArkham, BlackCave, CuriositieShoppe,
	GeneralStore, Graveyard, HibbsRoadhouse, HistoricalSociety, IndependenceSquare,
	Library, MasBoardingHouse, Newspaper, PoliceStation, RiverDocks,
	ScienceBuilding, SilverTwilightLodge, SouthChurch, StMarysHospital, TheUnnamable,
	TheWitchHouse, TrainStation, UnvisitedIsle, VelmasDiner, Woods, YeOldeMagickShoppe
};
enum tag_s : unsigned char {
	Tome, PhysicalWeapon, MagicalWeapon,
	CantStealOrLoose, CombatBonusTwoHand, ExhaustToRerollDie, ExhaustToEffect,
	CombatBonusVsUndead, DiscardAfterUse, SixDoubleSuccess, MarkTokenToDiscard,
	OneHanded, TwoHanded,
};
enum item_s : unsigned char {
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
	AlienStatue, AncientTablet, BlueWatcherOfThePyramid, CamillasRuby,
	CarcosanPage, CryptozoologyCollection, CrystalOfTheElderThings, DragonsEye,
	ElderSign, EnchantedBlade, EnchantedJewelry, EnchantedKnife, FluteOfTheOuterGods,
	GateBox, HealingStone, HolyWater, LampOfAlhazred, NamelessCults,
	Necronomicon, ObsidianStatue, PallidMask, PowderOfIbnGhazi, RubyOfRlyeh,
	SilverKey, SwordOfGlory, TheKingInYellow, WardingStatue,
	//
	AllyDuke,
	LastItem = AllyDuke
};
enum tid_s : unsigned char {
	Actions, Stats, Items,
};
enum special_s : unsigned char {
	Hunches, Scrounge,
};
enum monster_flag_s : unsigned char {
	Ambush, Undead,
};
enum monster_s : unsigned char {
	Byakhee, Chthonian,
	Zombie
};
struct tid {
	tid_s			type;
	unsigned char	value;
	constexpr tid() : type(Actions), value(NoAction) {}
	constexpr tid(item_s v) : type(Items), value(v) {}
	constexpr tid(stat_s v) : type(Stats), value(v) {}
	constexpr tid(tid_s type, unsigned char v) : type(type), value(v) {}
	constexpr tid(int v) : type(tid_s(v >> 8)), value(v & 0xFF) {}
	constexpr operator unsigned short() const { return ((type << 8) | (value)); }
};
struct roll_info {
	stat_s			id;
	char			bonus;
	char			difficult;
	bool			optional;
	char*			getname(char* result, const char* result_maximum) const;
};
struct quest {
	struct action {
		operator bool() const { return text != 0; }
		const char*	text;
		action_s	results[4];
	};
	location_s		type;
	const char*		text;
	roll_info		roll;
	action			results[4];
	operator bool() const { return text != 0; }
};
struct deck : adat<item_s, 128> {
	void			add(item_s id);
	void			create(stat_s	group);
	static void		discard(item_s id);
	item_s			draw();
	item_s			drawb();
	void			draw(deck& source, int count);
	void			drawb(deck& source, int count);
	static deck&	getdeck(stat_s id);
	static stat_s	getgroup(item_s id);
	static void		initialize();
};
struct monster {
	monster() = default;
	monster(monster_s type) : type(type), position() {}
	char			get(stat_s id);
	const char*		getname() const;
	bool			is(monster_flag_s id) const;
private:
	monster_s		type;
	location_s		position;
};
struct hero {
	operator bool() const { return name != 0; }
	void			act(const char* format, ...) const;
	void			add(item_s id) { if(id) cards[id]++; }
	void			add(stat_s id, int value, bool interactive);
	void			addmagic(stat_s id, int value, bool interactive);
	void			apply(action_s id, bool interactive = false, bool* discard = 0);
	void			clear();
	bool			combat(monster& e);
	item_s			changeweapon() const;
	void			changeweapon(item_s& w1, item_s& w2);
	void			choose(stat_s id, int count, bool interactive);
	void			choose(stat_s id, int count, int draw_count, int draw_bottom, bool interactive);
	void			chooselocation(stat_s id, int count, bool interactive);
	void			create(const char* id);
	void			discard(item_s id);
	bool			before(monster& e, int round = 0);
	void			focusing();
	char			get(stat_s id) const;
	char			get(item_s id) const;
	char			getbonus(item_s i, stat_s id);
	char			getcount(stat_s id, char value) const;
	gender_s		getgender() const { return gender; }
	location_s		getlocation() const { return position; }
	const char*		getname() const { return name; }
	static quest&	getquest(location_s value, int index = -1);
	item_s			getwepon(int index) const { return weapons[index]; }
	bool			is(special_s v) const { return special == v; }
	bool			isready() const { return get(Sanity) && get(Stamina); }
	bool			remove(item_s e);
	int				roll(stat_s id, int bonus = 0, int difficult = 1, bool interactive = true);
	void			run(const quest& e);
	void			select(deck& result, stat_s group) const;
	void			set(location_s v) { position = v; }
	void			set(special_s id) { special = id; }
	void			set(stat_s id, int v) { stats[id] = v; }
	void			setname(const char* v) { name = v; }
	void			skipturn(stat_s id, int value, bool interactive);
	void			upkeep();
	int				whatdo();
private:
	const char*		name;
	gender_s		gender;
	special_s		special;
	char			stats[SanityMaximum + 1];
	char			focus[3];
	char			cards[LastItem];
	char			exhause[LastItem];
	location_s		position;
	item_s			weapons[2];
};
struct location {
	const char*		id;
	const char*		name;
	const char*		text; // When you look around
	char			clue;
	location_s		neightboard[4];
};
namespace item {
int					get(item_s i, stat_s id);
char*				getname(char* result, const char* result_maximum, item_s i);
int					gethands(item_s i);
bool				is(item_s i, tag_s value);
}
char*				getstr(char* result, const char* result_maximum, stat_s id, int bonus);
extern hero			player;
extern location		location_data[YeOldeMagickShoppe + 1];