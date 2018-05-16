#include "logs\aref.h"
#include "logs\archive.h"
#include "logs\cflags.h"
#include "logs\crt.h"
#include "logs\dice.h"
#include "logs\logs.h"
#include "logs\bsdata.h"
#include "logs\string.h"
#include "logs\grammar.h"

#pragma once

#define metadc_enum(e) \
bsreq e##_type[] = {\
	BSREQ(e##_info, id),\
	BSREQ(e##_info, name),\
{}}; BSMETA(e)

#define BSENUM(e, i)\
getstr_enum(e);\
assert_enum(e, i);\
metadc_enum(e)

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
enum gender_s : unsigned char {
	NoGender, Male, Female
};
enum distance_s : unsigned char {
	Hand, Close, Reach, Near, Far,
};
enum tag_s : unsigned char {
	Awkward, Clumsy, Messy, Ration, Reloaded, Precise, Slow, Thrown, TwoHanded,
	Spiked, Sharp, PerfectlyWeighted, SerratedEdges, Glows, HugeWeapon, Versatile, WellCrafted,
};
enum class_s : unsigned char {
	Bard, Cleric, Druid, Fighter, Paladin, Ranger, Theif, Wizard,
};
enum race_s : unsigned char {
	Human, Elf, Dwarf, Halfling,
};
enum alignment_s : unsigned char {
	Good, Lawful, Neutral, Chaotic, Evil,
};
enum stat_s : unsigned char {
	Strenght, Dexterity, Constitution, Intellegence, Wisdow, Charisma,
};
enum god_s : unsigned char {
	Bane, Mystra, Tor, Tempus
};
enum result_s : unsigned char {
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
	HackAndSlash, Volley,
	DefyDangerStreght, DefyDangerDexterity, DefyDangerConstitution, DefyDangerIntellegence, DefyDangerWisdow, DefyDangerCharisma,
	Parley, SpoutLore, DiscernRealities, Supply,
	//// Paladins special moves (remove when quest completed)
	//InvulnerabilityToArrows, InvulnerabilityToFireOrCold, InvulnerabilityToEnchantment,
	//SenceDirectionToQuestTarget, SenceThatPierceLie, VoiceThatTranscendLanguages, FreedomFromHungerThirstAndSleep,
	//// Paladins vows
	//Honor, Temperance, Piety, Valor, Truth, Hospitality,
};
enum dungeon_move_s : unsigned char {
	Charsheet, ExamineFeature, GoBack, GoNext, GoHiddenPass, GoHiddenPassBack, MakeCamp, RunAway,
};
enum quest_s : unsigned char {
	NoQuest,
	SlayAGreatBlightOfTheLand, DefendFromTheIniquitesThatBesetThem, DiscoverTheTruth,
};
enum forward_s : unsigned char {
	AnyRoll, CombatRoll, DamageRoll, DefyDangerRoll,
	LastForward = DefyDangerRoll,
};
enum monster_s : unsigned char {
	Bandit, Goblin, Kobold, Zombie,
	LastMonster = Zombie,
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
	Foods, Tools, Weapons, Potions, Species, Gems, Clues,
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
	SpellGuidance, SpellLight, SpellPrestidigitation, SpellSanctify, SpellUnseenServant,
	SpellBless, SpellCauseFear, SpellContactSpirits, SpellCureLightWounds, SpellDetectAlignment, SpellDetectMagic, SpellTelepathy, SpellCharmPerson, SpellInvisibility, SpellMagicMissile, SpellMagicWeapon, SpellSanctuary, SpellSpeakWithDead, SpellAlarm,
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
enum duration_s : unsigned char {
	Instantaneous,
	Duration1Minute, Duration10Minute, Duration30Minute,
	Duration1Hour, Duration8Hour,
	Duration1Day,
	Permanent
};
enum target_s : unsigned char {
	Self, Hero, Monster,
};
enum effect_s : unsigned char {
	NoEffect,
	Damage, DamageAllParty, DamageIA, DamageAllPartyIA,
	Regroup, Summon,
	Heal, HealParty, BonusForward,
	LooseItem, LooseMoney,
	Debility, DebilityParty,
};
enum size_s : unsigned char {
	Tiny, Small, Medium, Large, Huge
};
enum monster_tag_s : unsigned char {
	NoMonsterTag,
	Amorphous, Cautions, Construct, Devious, Hoarder,
	Intellegent, Magical, Organized, Planar, Stealthy, Undead,
	Terrifing,
};
enum organization_s : unsigned char {
	Horde, Group, Solitary
};
enum tid_s : unsigned char {
	Moves,
	Actions, Alignments, Classes, DungeonMoves, Items, ItemTags, Results, Spells,
};

struct steading;
struct spell_state;

typedef cflags<alignment_s> alignmenta;
typedef cflags<god_s>		goda;
typedef adat<monster_s, 8>	monster_a;
typedef cflags<race_s>		race_a;
typedef cflags<resource_s>	resource_a;
typedef adat<steading*, 7>	steading_a;

namespace logs {
struct printer : stringcreator {
	gender_s				gender;
	const char*				name;
	constexpr printer(const char* name, gender_s gender) : name(name), gender(gender) {}
	void					parseidentifier(char* result, const char* result_max, const char* identifier) override;
};
}
struct tid {
	tid_s					type;
	unsigned char			value;
	constexpr tid(spell_s v) : type(Spells), value(v) {}
	constexpr tid(move_s v) : type(Moves), value(v) {}
	constexpr tid(dungeon_move_s v) : type(DungeonMoves), value(v) {}
	constexpr tid(class_s v) : type(Classes), value(v) {}
	constexpr tid(alignment_s v) : type(Alignments), value(v) {}
	constexpr tid(item_s v) : type(Items), value(v) {}
	constexpr tid(result_s v) : type(Results), value(v) {}
	constexpr tid(tid_s type, unsigned char v) : type(type), value(v) {}
	constexpr tid(int v) : type(tid_s(v >> 8)), value(v & 0xFF) {}
	constexpr operator unsigned short() const { return ((type << 8) | (value)); }
};
struct targetinfo {
	struct hero*			hero;
	struct monster*			monster;
	constexpr targetinfo() : hero(0), monster(0) {}
	constexpr targetinfo(struct monster& v) : hero(0), monster(&v) {}
	constexpr targetinfo(struct hero& v) : hero(&v), monster(0) {}
};
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
	char*					getname(char* result, bool description, bool tolower = false) const;
	int						getpiercing() const;
	prosperty_s				getprosperty() const;
	resource_s				getresource() const;
	int						getsellcost(int charisma = 0) const;
	int						getweight() const;
	int						getuses() const;
	bool					is(distance_s value) const;
	bool					is(tag_s value) const { return tags.is(value); }
	bool					isammo() const;
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
	void					use();
	static bsreq			metadata[];
private:
	cflags<tag_s>			tags;
	unsigned char			uses;
	cflags<distance_s, unsigned char> distance;
};
struct lootinfo {
	item_s					items[6];
	short unsigned			coins;
	operator bool() const { return coins || items[0]; }
	void					add(item_s type);
	void					clear();
	void					generate(int hoard);
	char*					getitems(char* result, bool description) const;
	bool					pickup();
};
struct mastermove {
	struct defyinfo {
		const char*			text;
		stat_s				stat;
		operator bool() const { return text != 0; }
	};
	const char*				text;
	effect_s				effect;
	dice					count;
	defyinfo				defy;
	operator bool() const { return effect != 0; }
};
struct monster {
	monster_s				type;
	distance_s				distance;
	char					count, hp;
	effect_s				effect;
	monster() = default;
	monster(monster_s type);
	operator bool() const { return count > 0 && hp > 0 && !effect; }
	void					act(const char* format, ...) const;
	int						getarmor() const;
	dice					getdamage() const;
	gender_s				getgender() const;
	int						getharm() const;
	int						getmaxhits() const;
	aref<mastermove>		getmoves() const;
	const char*				getname() const;
	char*					getname(char* result) const;
	const char*				getweapon() const;
	bool					is(distance_s id) const;
	bool					is(monster_tag_s id) const;
	void					set(monster_s value);
	void					regroup();
};
struct hero : npc {
	item				weapon, shield, armor, gear[8];
	god_s				diety;
	char				hp;
	char				experience;
	hero();
	void				act(const char* format, ...) const;
	void				add(spell_s id);
	int					addbonus(forward_s id);
	static void			addcoins(int count, bool interactive = false);
	void				apply(effect_s id, int value, monster* enemy);
	bool				apply(aref<mastermove> moves, monster* enemy);
	void				apply(mastermove& m, monster* enemy);
	void				apply(lootinfo& loot);
	result_s			cast(spell_s value, monster* te);
	void				clear();
	void				create(bool interactive);
	void				create(bool interactive, class_s value, gender_s gender);
	result_s			defydanger(stat_s stat);
	result_s			discernrealities();
	int					get(stat_s stat) const;
	int					get(forward_s stat) const;
	int					getarmor() const;
	static int			getcoins();
	dice				getdamage() const;
	static int			getdamage(class_s value);
	int					getencumbrance() const;
	char*				getequipment(char* result, const char* title) const;
	int					getharm() const;
	static int			gethits(class_s value);
	item*				getitem(item_s type);
	int					getlevel(spell_s value) const;
	int					getload() const;
	static int			getload(class_s value);
	int					getmaxhits() const;
	int					getpreparedlevels() const;
	int					getongoing() const;
	int					getraw(stat_s id) const { return stats[id]; }
	stat_s				getstat(move_s move) const;
	int					getspellpenalty() const;
	unsigned			getspells(spell_s* source, unsigned maximum);
	item*				getweapon(distance_s distance);
	void				hackandslash(monster& enemy);
	void				healharm(int count);
	void				hunger();
	void				inflictharm(monster& enemy, int value);
	bool				is(move_s value) const;
	static bool			is(spell_s id);
	bool				isalive() const;
	bool				isallow(effect_s id, int value, monster* enemy) const;
	bool				isallow(item_s id) const;
	bool				isallow(tag_s id) const;
	bool				isallow(tid id) const;
	bool				isammo(item_s value) const;
	bool				iscaster() const { return type == Wizard || type == Cleric; }
	bool				iscombatable() const;
	bool				isclumsy() const;
	bool				isdebilities(stat_s value) const { return (debilities & (1 << value)) != 0; }
	bool				isequipment() const;
	bool				isknown(spell_s value) const;
	bool				isprepared(spell_s value) const;
	static bsreq		metadata[];
	result_s			parley();
	void				preparespells(bool interactive);
	bool				prepareweapon(monster& enemy);
	bool				remove(item it);
	static void			remove(spell_s id);
	result_s			roll(int bonus, int* result = 0, bool show_result = true);
	result_s			roll(move_s id);
	void				say(const char* format, ...) const;
	bool				set(item value);
	void				set(move_s value, bool interactive);
	void				set(forward_s id, char value);
	void				setdebilities(stat_s value, bool state);
	void				setraw(stat_s id, int v) { stats[id] = v; }
	void				setknown(spell_s value, bool state);
	void				setprepared(spell_s value, bool state);
	unsigned			select(spell_state** result, spell_state** result_maximum) const;
	result_s			sell(prosperty_s prosperty);
	void				sheet();
	result_s			spoutlore();
	void				sufferharm(int value, bool ignore_armor = false);
	static void			supply(item* items, unsigned count);
	void				turnundead(monster& enemy);
	bool				use(tag_s id, bool interactive);
	bool				use(item_s id, bool interactive);
	bool				useammo(item_s value, bool run, bool interactive);
	void				volley(monster& enemy);
	int					whatdo(bool clear_text = true);
private:
	char				stats[Charisma - Strenght + 1];
	char				forward[LastForward + 1];
	unsigned char		debilities;
	unsigned char		spells_known[1 + LastSpell / 8];
	unsigned char		spells_prepared[1 + LastSpell / 8];
	unsigned			moves[4];
	adat<spell_s, 2>	prodigy;
	char				castpenalty;
	item				signature_weapon;
};
struct steading {
	steading();
	steading(steading_type_s type);
	operator bool() const { return names[0] != 0; }
	//
	void				addfeature();
	void				addproblem();
	void				adventure();
	void				clear();
	void				correct();
	void				create(steading_type_s type);
	static void			createworld();
	void				getmarket(resource_a& result);
	char*				getname(char* temp) const;
	bool				isoath(const steading* value) const;
	bool				isemnity(const steading* value) const;
	bool				istrade(const steading* value) const;
	void				lookaround();
	void				set(steading* owner);
	void				setenmity();
	void				setguild() {}
	void				sethistory() {}
	void				setlawless() {}
	void				setmarket() {}
	void				setoath();
	void				setoathme();
	void				setrandomname();
	void				setresource();
	void				setsafe() {}
	void				settrade();
private:
	steading_type_s		type;
	prosperty_s			prosperty;
	population_s		population;
	defence_s			defence;
	goda				religions;
	monster_a			blight;
	steading_a			emnity;
	steading_a			trade;
	race_s				habbitants;
	npc					personage;
	steading*			oath;
	resource_a			resources;
	resource_a			need;
	resource_a			exotic;
	unsigned char		names[4];
};
struct site {
	site_s				type;
	steading*			location; // Место находится рядом с этим поселением
	landscape_s			landscape;
	unsigned			distance; // В часах пути по дикой местности
};
struct spell_state {
	unsigned			date;
	spell_s				spell;
	hero*				caster;
	operator bool() const { return caster != 0; }
	void clear() { memset(this, 0, sizeof(*this)); }
	void remove();
};
namespace game {
hero*					choose(move_s id);
bool					combat(monster& enemy);
bool					combat(monster_s id, distance_s distance = Far, int count = 0);
void					dungeon();
void					eatrations(int count);
unsigned				get(duration_s v);
unsigned				getround();
hero*					getplayer();
bool					isallow(tid id);
bool					isgameover();
void					journey();
void					makecamp();
void					partyrest(bool forfree);
void					passtime(duration_s id);
void					pickup(item value);
unsigned				select(hero** result, unsigned maximum, tid id, bool alive);
void					sheets();
bool					useparty(tag_s id, bool run, bool interactive);
bool					useparty(item_s id, bool run, bool interactive);
int						whatdo(bool clear_text = true);
hero*					whodo(const char* format, ...);
hero*					whodo(stat_s stat, hero** exclude, const char* format, ...);
}
namespace logs {
struct state {
	struct site*		site;
	struct steading*	steading;
	struct monster*		monster;
	state();
	~state();
};
}
extern logs::state		logc;
extern hero				players[8];
extern site				sites[256];
extern adat<spell_state, 48> spell_state_data;
extern steading			steadings[64];

BSDECLENUM(alignment)
BSDECLENUM(class)
BSDECLENUM(distance)
BSDECLENUM(item)
BSDECLENUM(gender)
BSDECLENUM(god)
BSDECLENUM(monster)
BSDECLENUM(prosperty)
BSDECLENUM(population)
BSDECLENUM(race)
BSDECLENUM(stat)
BSDECLENUM(tag)
// Special metadata cases
template<> struct bsgetmeta<item> { static constexpr const bsreq* value = item::metadata; };
// Metadata special cflags
template<class T, class DT> struct bsgetsubtype<cflags<T, DT>> { static constexpr const char* value = "cflags"; };
template<class T, class DT> struct bsgetmeta<cflags<T, DT>> { static constexpr const bsreq* value = bsgetmeta<T>::value; };