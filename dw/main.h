#include "adat.h"
#include "crt.h"
#include "dice.h"
#include "grammar.h"
#include "logs.h"

#pragma once

#define assert_enum(e, last) static_assert(sizeof(e##_data) / sizeof(e##_data[0]) == last + 1, "Invalid count of " #e " elements")
#define getstr_enum(e) template<> const char* getstr<e##_s>(e##_s value) { return e##_data[value].name; }
#define maptbl(t, id) (t[imax(0, imin(id, (int)(sizeof(t)/sizeof(t[0])-1)))])
#define lenghtof(t) (sizeof(t)/sizeof(t[0]))

enum item_s : unsigned char {
	NoItem,
	RaggedBow, FineBow, HuntersBow, Crossbow,
	Arrows, ElvenArrows,
	Club, Staff,
	Knife, ThrowingDagger,
	SwordShort, Mace, Warhammer, Spear, SwordLong, Halberd, Rapier, DuelingRapier,
	FineClothing, LeatherArmour, ChainMail, ScaleMail, PlateMail, Shield,
	AdventuringGear, Bandages, Herbs, HealingPotion, KegOfDwarvenStout,
	BagOfBooks, Antitoxin,
	DungeonRation, PersonalFeats, DwarvenHadrdtack, ElvenBread, HalflingPipeleaf,
	Mandoline, Lute, Pipes,
	HolySymbol, SpellBook,
	Bloodstone, Chrysoprase, Iolite, Jasper, Moonstone, Onyx, // Мелкие драгоценности
	Map, Note, Journal, // Улики
	Alexandrite, Aquamarine, BlackPearl, Topaz, // Драгоценности
	Poison,
	SilverCoins, GoldCoins
};
enum distance_s : char {
	Hand, Close, Reach, Near, Far,
};
enum tag_s : char {
	Awkward, Clumsy, Messy, Ration, Reloaded, Precise, Slow, Thrown, TwoHanded,
	Spiked, Sharp, PerfectlyWeighted, SerratedEdges, Glows, HugeWeapon, Versatile, WellCrafted,
};
enum class_s : char {
	Bard, Cleric, Druid, Fighter, Paladin, Ranger, Theif, Wizard,
};
enum race_s : char {
	Human, Elf, Dwarf, Halfling,
};
enum gender_s : char {
	NoGender, Male, Female
};
enum alignment_s : char {
	Good, Lawful, Neutral, Chaotic, Evil,
};
enum stat_s : char {
	Strenght, Dexterity, Constitution, Intellegence, Wisdow, Charisma,
};
enum state_s : char {
	Escape,
};
enum god_s : char {
	Bane, Mystra, Tor, Tempos
};
enum result_s : char {
	Fail, PartialSuccess, Success
};
enum move_s : unsigned char {
	ArcaneArt, BardicLore, CharmingAndOpen, PortInTheStorm,
	Deity, DivineGuidance, TurnUndead, Commune, CastASpell,
	BornOfTheSoil, ByNatureSustained, SpiritTongue, Shapeshifter, StudiedEssence,
	BendBarsLiftGates, Armored, SignatureWeapon,
	LayOnHands, IAmTheLaw, Quest,
	HuntAndTrack, CalledShot, AnimalCompanion, Command,
	TrapExpert, TricksOfTheTrade, Backstab, FlexibleMorals, Poisoner,
	Spellbook, PrepareSpells, SpellDefense, Ritual,
	// Fighter
	Merciless, Heirloom, ImprovedWeapon,
	SeeingRed, Interrogator, ScentOfBlood, IronHide, Blacksmith, SuperiorWarrior,
	// Wizard
	Prodigy, EmpoweredMagic, FountOfKnowledge, KnownItAll, ExpandedSpellbook,
	Enchanter, Logical, ArcaneWard, Counterspell, QuickStudy,
	//
	HackAndSlash,
	DefyDangerStreght, DefyDangerDexterity, DefyDangerConstitution, DefyDangerIntellegence, DefyDangerWisdow, DefyDangerCharisma,
	Parley, SpoutLore, DiscernRealities, Supply,
	MakeCamp, ExamineFeature, GoBack, GoNext, Charsheet,
};
enum monster_s : unsigned char {
	Goblin, Kobold, Bandit,
};
enum prosperty_s : char {
	Dirt, Poor, Moderate, Wealthy, Rich,
};
enum population_s : char {
	Exodus, Shrinking, Steady, Growing, Booming,
};
enum defence_s : char {
	NoDefence, Militia, Watch, Guard, Garrison, Battalion, Legion,
};
enum resource_s : char {
	Foods, Tools, Weapons, Dress, Potions, Species, Gems, Clues,
	Wood, Furs, Ore,
	Heroes,
};
enum steading_type_s : char {
	Village, Town, Keep, City,
};
enum landscape_s : char {
	Plain, Woods, Hills, Swamp, River, Mountain, Coast, Ocean,
};
enum site_s : char {
	Cave, Ruins, Camp,
};
enum spell_s : unsigned char {
	SpellLight, SpellUnseenServant, SpellPrestidigitation,
	SpellContactSpirits, SpellDetectMagic, SpellTelepathy, SpellCharmPerson, SpellInvisibility, SpellMagicMissile, SpellAlarm,
	SpellDispelMagic, SpellVisionsThroughTime, SpellFireball, SpellMimic, SpellMirrorImage, SpellSleep,
	SpellCage, SpellContactOtherPlane, SpellPolymorph, SpellSummonMonster,
	SpellDominate, SpellTrueSeeing, SpellShadowWalk, SpellContingency, SpellCloudkill,
	SpellAntipathy, SpellAlert, SpellSoulGem, SpellShelter, SpellPerfectSummons,
	FirstSpell = SpellLight, LastSpell = SpellPerfectSummons,
};
enum school_s : unsigned char {
	NoSchool,
	Divination, Enchantment, Evocation, Illusion, Summoning,
};
enum target_s : char {
	TargetSelf, TargetEnemy, TargetAlly,
	TargetLocation,
};
enum duration_s : unsigned char {
	Instantaneous,
	Duration1Minute, Duration10Minute, Duration30Minute,
	Duration1Hour,
	Duration1Day,
};
enum time_s {
	Hour = 1, Day = Hour * 24, Month = Day * 30, Year = Month * 12,
};

struct steading;

template<class T, class TC = unsigned>
struct flags {
	inline operator TC() const { return data; }
	inline void				clear() { data = 0; }
	inline bool				is(T value) const { return (data & (1 << value)) != 0; }
	inline void				set(T value) { data |= 1 << value; }
	inline void				remove(T value) { data &= ~(1 << value); }
private:
	TC						data;
};

typedef adat<alignment_s, 4> alignmenta;
typedef adat<god_s, 4>		goda;
typedef adat<monster_s, 8>	monster_a;
typedef adat<race_s, 5>		race_a;
typedef adat<resource_s, 4>	resource_a;
typedef adat<steading*, 7>	steading_a;

struct npc {
	class_s					type;
	race_s					race;
	gender_s				gender;
	alignment_s				alignment;
	unsigned char			level;
	unsigned char			name;
	operator bool() const { return gender != NoGender; }
	//
	void					create(class_s value);
	static gender_s			choosegender(bool interactive);
	static race_s			chooserace(const race_a& source, bool interactive);
	static class_s			chooseclass(bool interactive);
	static alignment_s		choosealignment(const alignmenta& source, bool interactive);
	const char*				getA() const;
	const char*				getAS() const;
	const char*				getLA() const;
	const char*				getname() const;
	static unsigned char	getrandomname(race_s race, gender_s gender);
	static unsigned char	getrandomname(class_s type, race_s race, gender_s gender);
	bool					isdwarf() const { return race == Dwarf; }
};
struct item {
	item_s					type;
	item();
	item(item_s type);
	operator bool() const { return type != NoItem; }
	void					clear();
	int						getarmor() const;
	item_s					getammo() const;
	int						getcost() const;
	int						getdamage() const;
	char*					getdescription(char* result) const;
	int						getmaxuses() const;
	char*					getname(char* result, bool description) const;
	int						getpiercing() const;
	prosperty_s				getprosperty() const;
	resource_s				getresource() const;
	int						getsellcost(int charisma = 0) const;
	int						getweight() const;
	int						getuses() const;
	bool					is(distance_s value) const;
	bool					is(tag_s value) const { return (tags&(1 << value)) != 0; }
	bool					isammo(item_s type) const;
	bool					isarmor() const;
	bool					isclumsy() const;
	bool					iscoins() const;
	bool					isgems() const;
	bool					isprecise() const;
	bool					isshield() const;
	bool					isweapon() const;
	void					set(distance_s value);
	void					set(item_s value);
	void					set(tag_s value);
	bool					use();
private:
	unsigned				tags;
	unsigned char			uses;
	flags<distance_s, unsigned char> distance;
};
struct loot_i {
	item_s					item[4];
	short unsigned			coins;
	operator bool() const { return coins || item[0]; }
	void					add(item_s type);
	void					clear();
	char*					getitems(char* result, bool description) const;
};
struct monster {
	monster_s				type;
	distance_s				distance;
	char					count, hp;
	monster();
	monster(monster_s type);
	operator bool() const { return count > 0; }
	const char*				getA() const { return ""; }
	const char*				getLA() const;
	void					getloot(loot_i& loot) const;
	int						getarmor() const;
	int						getharm() const;
	int						getmaxhits() const;
	const char*				getname() const;
	char*					getname(char* result) const;
	dice					getdamage() const;
	bool					is(distance_s id) const;
	bool					isalive() const { return count && hp > 0; }
	void					set(monster_s value);
};
struct targetinfo {
	struct monster*			enemy;
	struct npc*				npc;
	struct hero*			ally;
	struct site*			location;
	struct steading*		nearby;
	constexpr targetinfo() : enemy(0), npc(0), ally(0), nearby(0), location(0) {}
	constexpr targetinfo(monster* v) : enemy(v), npc(0), ally(0), nearby(0), location(0) {}
};
struct hero : npc {
	item					weapon, shield, armor;
	god_s					diety;
	char					hp;
	char					experience;
	hero();
	void					act(const char* format, ...) const;
	static void				addcoins(int count, bool interactive = false);
	void					apply(loot_i& loot);
	void					ask(spell_s value);
	void					cast(spell_s value, targetinfo ti);
	void					cast(targetinfo& ti);
	void					clear();
	void					create(bool interactive);
	void					create(bool interactive, class_s value, gender_s gender);
	result_s				defydanger(stat_s stat);
	result_s				discernrealities();
	int						get(stat_s stat) const;
	int						getarmor() const;
	int						getcoins() const;
	dice					getdamage() const;
	static int				getdamage(class_s value);
	int						getencumbrance() const;
	char*					getequipment(char* result, const char* title) const;
	int						getharm() const;
	item*					getitem(item_s type);
	int						getlevel(spell_s value) const;
	int						getload() const;
	static int				getload(class_s value);
	static int				gethits(class_s value);
	int						getmaxhits() const;
	static hero*			getplayer();
	int						getpreparedlevels() const;
	int						getraw(stat_s id) const { return stats[id]; }
	stat_s					getstat(move_s move) const;
	int						getspellpenalty() const;
	unsigned				getspells(spell_s* source, unsigned maximum, targetinfo& ti);
	item*					getweapon(distance_s distance);
	void					hackandslash(monster& enemy);
	void					healharm(int count);
	void					hunger();
	void					inflictharm(monster& enemy, int value);
	bool					is(move_s value) const;
	bool					is(state_s value) const;
	bool					isalive() const;
	bool					isammo(item_s value) const;
	bool					iscaster() const { return type == Wizard || type == Cleric; }
	bool					iscombatable() const;
	bool					isclumsy() const;
	bool					isequipment() const;
	bool					isknown(spell_s value) const;
	bool					isprepared(spell_s value) const;
	result_s				parley();
	void					preparespells();
	bool					prepareweapon(monster& enemy);
	bool					remove(item it);
	void					remove(state_s value);
	result_s				roll(int bonus, int* result = 0, bool show_result = true);
	bool					set(item value);
	void					set(move_s value, bool interactive);
	void					set(state_s value);
	void					setraw(stat_s id, int v) { stats[id] = v; }
	void					setknown(spell_s value, bool state);
	void					setprepared(spell_s value, bool state);
	result_s				sell(prosperty_s prosperty);
	result_s				spoutlore();
	void					sufferharm(int value);
	result_s				supply(item* source, int count);
	bool					use(tag_s id);
	bool					useammo(item_s value, bool interactive);
	bool					volley(monster& enemy, bool run);
	int						whatdo(bool clear_text = true);
private:
	struct effect {
		spell_s				type;
		targetinfo			target;
	};
	char					stats[Charisma - Strenght + 1];
	item					gear[8];
	unsigned char			spells_known[1 + LastSpell / 8];
	unsigned char			spells_prepared[1 + LastSpell / 8];
	unsigned				moves[4];
	unsigned				state;
	adat<spell_s, 2>		prodigy;
	char					castpenalty;
	adat<effect, 8>			ongoing;
	item					signature_weapon;
};
struct steading {
	steading();
	steading(steading_type_s type);
	operator bool() const { return names[0] != 0; }
	//
	void					addfeature();
	void					addproblem();
	void					adventure();
	void					clear();
	void					correct();
	void					create(steading_type_s type);
	static void				createworld();
	void					getmarket(resource_a& result);
	char*					getname(char* temp) const;
	bool					isoath(const steading* value) const;
	bool					isemnity(const steading* value) const;
	bool					istrade(const steading* value) const;
	void					lookaround();
	static int				select(item* source, unsigned maximum, prosperty_s prosperty, resource_a* resources = 0);
	void					set(steading* owner);
	void					setenmity();
	void					setguild() {}
	void					sethistory() {}
	void					setlawless() {}
	void					setmarket() {}
	void					setoath();
	void					setoathme();
	void					setrandomname();
	void					setresource();
	void					setsafe() {}
	void					settrade();
private:
	steading_type_s			type;
	prosperty_s				prosperty;
	population_s			population;
	defence_s				defence;
	goda					religions;
	monster_a				blight;
	steading_a				emnity;
	steading_a				trade;
	race_s					habbitants;
	npc						personage;
	steading*				oath;
	resource_a				resources;
	resource_a				need;
	resource_a				exotic;
	unsigned char			names[4];
};
struct site {
	site_s					type;
	steading*				location;
	landscape_s				landscape;
	unsigned				distance; // in hours
};
namespace game {
	hero*					choose(move_s id);
	void					combat(monster& enemy);
	void					combat(monster_s id, distance_s distance = Far, int count = 0);
	void					dungeon();
	void					eatrations(int count);
	hero*					getplayer();
	bool					isgameover();
	bool					isnoplayer(move_s id);
	void					journey();
	void					makecamp();
	void					partyrest();
	void					passtime(int round);
	void					pickup(item value);
	bool					useparty(tag_s id);
	hero*					whodo(const char* format, ...);
	hero*					whodo(stat_s stat, hero** exclude, const char* format, ...);
}
extern hero					players[8];
extern site					sites[256];
extern steading				steadings[64];