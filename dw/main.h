#include "adat.h"
#include "crt.h"
#include "logs.h"
#include "dice.h"

#pragma once

#define assert_enum(name, last) static_assert(sizeof(name##_data) / sizeof(name##_data[0]) == last + 1,\
	"Invalid count of " #name " elements")
#define getstr_enum(ename) template<> const char* getstr<ename##_s>(ename##_s value) { return ename##_data[value].name[1]; }

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
};
enum monster_s : unsigned char {
	Goblin, Kobold, Bandit,
};
enum prosperty_s : unsigned char {
	Dirt, Poor, Moderate, Wealthy, Rich,
};
enum population_s : unsigned char {
	Exodus, Shrinking, Steady, Growing, Booming,
};
enum defence_s : unsigned char {
	NoDefence, Militia, Watch, Guard, Garrison, Battalion, Legion,
};
enum resource_s : unsigned char {
	Foods, Potions, Weapons, Species, Dress, Gems, Tools, Clues,
	Wood, Furs, Ore,
};
enum steading_tag_s : unsigned char {
	Safe, Religion, Exotic, Resource, Need, Oath, Trade, Market, Enmity, History, Lawless,
};
enum steading_type_s : unsigned char {
	Village, Town, Keep, City,
};

typedef adat<race_s, 5>			race_a;
typedef adat<alignment_s, 4>	alignment_a;
typedef adat<resource_s, 4>		resource_a;

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
	char*					getname(char* result, bool description, int cost = 0) const;
	char*					getdescription(char* result, int cost = 0) const;
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
	static void				choose(gender_s& value, bool interactive);
	static void				choose(race_s& value, const race_a& source, bool interactive);
	static void				choose(class_s& value, bool interactive);
	static void				choose(alignment_s& value, const alignment_a& source, bool interactive);
	const char*				getname() const;
};
struct hero : npc
{
	item					weapon, shield, armor;
	item					signature_weapon;
	char					stats[Charisma - Strenght + 1];
	item					gear[8];
	god_s					diety;
	char					hp;
	char					experience;
	hero();
	void					addcoins(int count);
	void					clear();
	void					create();
	void					create(class_s value);
	void					choosemoves(bool interactive);
	result_s				defydanger(stat_s stat);
	result_s				discernrealities();
	result_s				hackandslash(monster& enemy);
	int						get(stat_s stat) const;
	const char*				getA() const;
	const char*				getLA() const;
	int						getarmor() const;
	dice					getdamage() const;
	int						getcoins() const;
	char*					getequipment(char* result, const char* title) const;
	int						getharm() const;
	item*					getitem(item_s type);
	int						getload() const;
	int						getmaxhits() const;
	item*					getweapon(distance_s distance);
	void					inflictharm(monster& enemy, int value);
	bool					is(move_s value) const;
	bool					isalive() const;
	bool					isammo() const;
	bool					isclumsy() const;
	bool					isequipment() const;
	result_s				parley();
	bool					prepareweapon(monster& enemy);
	bool					remove(item it);
	result_s				roll(int bonus, int* result = 0, bool show_result = true);
	bool					set(item value);
	void					set(move_s value);
	result_s				sell(prosperty_s prosperty);
	result_s				spoutlore();
	void					sufferharm(int value);
	result_s				supply(prosperty_s prosperty);
	result_s				supply(prosperty_s prosperty, resource_s resource);
	bool					useammo();
	void					volley(monster& enemy);
	int						whatdo(bool clear_text = true);
private:
	unsigned				moves[4];
};
struct steading
{
	steading_type_s			type;
	prosperty_s				prosperty;
	population_s			population;
	defence_s				defence;
	adat<god_s, 4>			religions;
	resource_a				resources;
	resource_a				need;
	resource_a				exotic;
	steading*				oath;
	adat<steading*, 4>		emnity;
	adat<steading*, 4>		trade;
	steading();
	operator bool() const { return name != 0; }
	void*					operator new(unsigned size);
	void					adventure();
	void					create(steading_type_s type);
	const char*				getname() const;
	void					clear();
	bool					is(steading_tag_s value) const;
	void					set(steading* owner);
	void					set(steading_tag_s value);
private:
	const char*				name;
	flags<steading_tag_s>	tags;
};
namespace game
{
	void					combat(monster& enemy);
	bool					isgameover();
	hero*					getplayer();
	int						getdamage(class_s value);
	int						gethits(class_s value);
	int						getload(class_s value);
	unsigned char			getrandomname(race_s race, gender_s gender);
	unsigned char			getrandomname(class_s type, race_s race, gender_s gender);
}
extern hero					players[8];