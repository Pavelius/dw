#include "adat.h"
#include "crt.h"
#include "logs.h"
#include "dice.h"

#pragma once

#define assert_enum(name, last) static_assert(sizeof(name##_data) / sizeof(name##_data[0]) == last + 1,\
	"Invalid count of " #name " elements")
#define getstr_enum(ename) template<> const char* getstr<ename##_s>(ename##_s value) { return ename##_data[value].name[1]; }
#define maptbl(t, id) (t[imax(0, imin(id, (int)(sizeof(t)/sizeof(t[0])-1)))])

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
	Coin
};
enum distance_s : char {
	Hand, Close, Reach, Near, Far,
};
enum tag_s : char {
	Ammo, Awkward, Clumsy, Messy, Ration, Reloaded, Precise, Slow, Thrown, TwoHanded,
};
enum enchantment_s : char {
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
	HackAndSlash, DefyDanger, Parley, SpoutLore, DiscernRealities,
	Supply,
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

struct steading;

template<class T, class TC = unsigned>
struct flags
{
	inline operator TC() const { return data; }
	inline void				clear() { data = 0; }
	inline bool				is(T value) const { return (data & (1 << value)) != 0; }
	inline void				set(T value) { data |= 1 << value; }
	inline void				remove(T value) { data &= ~(1 << value); }
private:
	TC						data;
};

typedef adat<alignment_s, 4>	alignment_a;
typedef adat<god_s, 4>			god_a;
typedef adat<monster_s, 8>		monster_a;
typedef adat<race_s, 5>			race_a;
typedef adat<resource_s, 4>		resource_a;
typedef adat<steading*, 7>		steading_a;

struct item
{
	item_s									type;
	unsigned char							uses;
	flags<distance_s, unsigned char>		distance;
	flags<tag_s, short unsigned>			tags;
	flags<enchantment_s, short unsigned>	enchant;
	item();
	item(item_s type);
	operator bool() const { return type != NoItem; }
	void					clear();
	int						getarmor() const;
	int						getcost() const;
	int						getdamage() const;
	int						getmaxuses() const;
	char*					getname(char* result, bool description) const;
	char*					getdescription(char* result) const;
	int						getpiercing() const;
	prosperty_s				getprosperty() const;
	resource_s				getresource() const;
	int						getsellcost(int charisma = 0) const;
	int						getweight() const;
	bool					is(distance_s value) const;
	bool					is(tag_s value) const;
	bool					is(enchantment_s value) const;
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
	void					set(enchantment_s value);
	bool					use();
};
struct monster
{
	monster_s				type;
	item					weapon;
	distance_s				distance;
	char					count, hp;
	monster();
	monster(monster_s type);
	operator bool() const { return count > 0; }
	const char*				getA() const { return ""; }
	int						getarmor() const;
	int						getharm() const;
	int						getmaxhits() const;
	const char*				getname() const;
	char*					getname(char* result) const;
	dice					getdamage() const;
	bool					isalive() const { return hp > 0; }
	void					set(monster_s value);
};
struct targetinfo
{
	struct monster*			enemy;
	struct npc*				npc;
	struct hero*			ally;
	struct site*			location;
	struct steading*		nearby;
	targetinfo() : enemy(0), npc(0), ally(0), nearby(0), location(0) {}
};
struct spell_effect
{
	spell_s					type;
	targetinfo				target;
};
struct npc
{
	class_s					type;
	race_s					race;
	gender_s				gender;
	alignment_s				alignment;
	unsigned char			level;
	unsigned char			name;
	operator bool() const { return gender != NoGender; }
	//
	void					create(class_s value);
	static void				choose(gender_s& value, bool interactive);
	static void				choose(race_s& value, const race_a& source, bool interactive);
	static void				choose(class_s& value, bool interactive);
	static void				choose(alignment_s& value, const alignment_a& source, bool interactive);
	const char*				getA() const;
	const char*				getLA() const;
	const char*				getname() const;
};
struct hero : npc
{
	item					weapon, shield, armor;
	char					stats[Charisma - Strenght + 1];
	item					gear[8];
	god_s					diety;
	char					hp;
	char					experience;
	char					actions;
	hero();
	void					addcoins(int count);
	result_s				cast(spell_s value, targetinfo& ti);
	result_s				cast(targetinfo& ti);
	void					clear();
	void					create();
	void					create(class_s value);
	static hero*			chooseplayer(const char* format, ...);
	static hero*			chooseplayer(stat_s stat, const char* format, ...);
	void					choosemoves(bool interactive);
	result_s				defydanger(stat_s stat);
	result_s				discernrealities();
	result_s				hackandslash(monster& enemy);
	void					healharm(int count);
	int						get(stat_s stat) const;
	int						getarmor() const;
	dice					getdamage() const;
	int						getcoins() const;
	char*					getequipment(char* result, const char* title) const;
	int						getharm() const;
	item*					getitem(item_s type);
	int						getlevel(spell_s value) const;
	int						getload() const;
	int						getmaxhits() const;
	int						getpreparedlevels() const;
	int						getspellpenalty() const;
	unsigned				getspells(spell_s* source, unsigned maximum, targetinfo& ti);
	item*					getweapon(distance_s distance);
	void					inflictharm(monster& enemy, int value);
	bool					is(move_s value) const;
	bool					isalive() const;
	bool					isammo() const;
	bool					iscaster() const { return type == Wizard || type == Cleric; }
	bool					isclumsy() const;
	bool					isequipment() const;
	bool					isknown(spell_s value) const;
	bool					isongoing(spell_s value) const;
	bool					isprepared(spell_s value) const;
	void					makecamp();
	result_s				parley();
	void					preparespells();
	bool					prepareweapon(monster& enemy);
	bool					remove(item it);
	result_s				roll(int bonus, int* result = 0, bool show_result = true);
	bool					set(item value);
	void					set(move_s value);
	void					setknown(spell_s value, bool state);
	void					setprepared(spell_s value, bool state);
	result_s				sell(prosperty_s prosperty);
	result_s				spoutlore();
	void					sufferharm(int value);
	result_s				supply(item* source, int count);
	bool					useammo();
	bool					useration();
	void					volley(monster& enemy);
	int						whatdo(bool clear_text = true);
private:
	unsigned char			spells_known[1 + LastSpell / 8];
	unsigned char			spells_prepared[1 + LastSpell / 8];
	unsigned				moves[4];
	adat<spell_s, 2>		prodigy;
	char					castpenalty;
	adat<spell_effect, 8>	ongoing;
	item					signature_weapon;
};
struct steading
{
	steading_type_s			type;
	prosperty_s				prosperty;
	population_s			population;
	defence_s				defence;
	god_a					religions;
	resource_a				resources;
	resource_a				need;
	resource_a				exotic;
	monster_a				blight;
	steading*				oath;
	steading_a				emnity;
	steading_a				trade;
	race_s					habbitants;
	npc						personage;
	//
	steading();
	steading(steading_type_s type);
	operator bool() const { return name != 0; }
	//
	void					addfeature();
	void					addproblem();
	void					adventure();
	void					clear();
	void					correct();
	void					create(steading_type_s type);
	void					getmarket(resource_a& result);
	const char*				getname() const;
	bool					isoath(const steading* value) const;
	bool					isemnity(const steading* value) const;
	bool					istrade(const steading* value) const;
	void					lookaround();
	void					set(steading* owner);
	void					setenmity();
	void					setguild() {}
	void					sethistory() {}
	void					setlawless() {}
	void					setmarket() {}
	void					setoath();
	void					setoathme();
	void					setresource();
	void					settrade();
	void					setsafe() {}
private:
	const char*				name;
};
struct site
{
	site_s					type;
	steading*				location;
	landscape_s				landscape;
	unsigned				distance; // in hours
};
namespace game
{
	void					combat(monster& enemy);
	void					clearactions();
	void					createworld();
	bool					isgameover();
	hero*					getplayer();
	int						getdamage(class_s value);
	int						gethits(class_s value);
	int						getload(class_s value);
	unsigned char			getrandomname(race_s race, gender_s gender);
	unsigned char			getrandomname(class_s type, race_s race, gender_s gender);
	int						select(item* source, unsigned maximum, prosperty_s prosperty, resource_a* resources = 0);
}
extern hero					players[8];
extern site					sites[256];
extern steading				steadings[64];