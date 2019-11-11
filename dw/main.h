#include "archive.h"
#include "dice.h"
#include "logs.h"

#pragma once

using namespace logs;

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
enum distance_s : unsigned char {
	Hand, Close, Reach, Near, Far,
};
enum tag_s : unsigned char {
	Awkward, Clumsy, Messy, Ration, Reloaded, Precise, Slow, Thrown, TwoHanded,
	Armor1, Armor2, Armor4,
	Damage1, Damage2,
	Pierce1, Pierce2,
	Weight1, Weight2, Weight4, Weight8,
	Use1, Use2, Use4,
	// Item upgrades
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
enum variant_s : unsigned char {
	Moves,
	Actions, Alignments, Classes, DungeonMoves, Items, ItemTags, Players, Results, Spells,
};

class hero;
struct steading;
struct spell_state;

typedef cflags<alignment_s, unsigned char> alignmenta;
typedef cflags<distance_s, unsigned char> distancea;
typedef cflags<god_s> goda;
typedef adat<monster_s, 8> monstera;
typedef cflags<race_s> racea;
typedef cflags<resource_s> resourcea;
typedef adat<steading*, 7> steadinga;

struct variant {
	variant_s				type;
	unsigned char			value;
	constexpr variant(spell_s v) : type(Spells), value(v) {}
	constexpr variant(move_s v) : type(Moves), value(v) {}
	constexpr variant(dungeon_move_s v) : type(DungeonMoves), value(v) {}
	constexpr variant(class_s v) : type(Classes), value(v) {}
	constexpr variant(alignment_s v) : type(Alignments), value(v) {}
	constexpr variant(item_s v) : type(Items), value(v) {}
	constexpr variant(result_s v) : type(Results), value(v) {}
	constexpr variant(variant_s type, unsigned char v) : type(type), value(v) {}
	constexpr variant(int v) : type(variant_s(v >> 8)), value(v & 0xFF) {}
	constexpr operator unsigned short() const { return ((type << 8) | (value)); }
	template<class T, variant_s V> T* get() const { return (type == V) ? &bsmeta<T>::elements[value] : 0 }
};
class taga {
	unsigned				data;
	int						get(tag_s i1, tag_s i2) const;
	void					set(tag_s i1, tag_s i2, int v);
public:
	constexpr taga() : data(0) {}
	constexpr taga(const std::initializer_list<tag_s>& list) : data() { for(auto e : list) set(e); }
	void					apply(const taga& e) { data |= e.data; }
	constexpr void			clear() { data = 0; }
	int						getarmor() const { return get(Armor1, Armor4); }
	int						getdamage() const;
	int						getpierce() const;
	int						getuses() const { return get(Use1, Use4); }
	int						getweight() const;
	constexpr bool			is(tag_s v) const { return (data & (1 << v)) != 0; }
	constexpr void			remove(tag_s v) { data &= ~(1 << v); }
	constexpr void			set(tag_s v) { data |= 1 << v; }
	void					setarmor(int v) { set(Armor1, Armor4, v); }
	void					setdamage(int v) { set(Damage1, Damage2, v); }
	void					setpierce(int v) { set(Pierce1, Pierce2, v); }
	void					setuses(int v) { set(Use1, Use4, v); }
	void					setweight(int v) { set(Weight1, Weight8, v); }
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
struct npc : taga {
	class_s					type;
	race_s					race;
	gender_s				gender;
	alignment_s				alignment;
	unsigned char			level;
	unsigned short			name;
	operator bool() const { return gender != NoGender; }
	void					act(const char* format, ...) const;
	void					actv(stringbuilder& sb, const char* format, ...) const;
	void					create(class_s value);
	static gender_s			choosegender(bool interactive);
	static race_s			chooserace(const racea& source, bool interactive);
	static class_s			chooseclass(bool interactive);
	static alignment_s		choosealignment(const alignmenta& source, bool interactive);
	const char*				getname() const;
	static unsigned char	getrandomname(race_s race, gender_s gender);
	static unsigned char	getrandomname(class_s type, race_s race, gender_s gender);
	bool					isdwarf() const { return race == Dwarf; }
	void					say(const char* format, ...) const;
};
struct stati {
	const char*				id;
	const char*				name;
};
struct alignmenti {
	const char*				id;
	const char*				name;
};
struct racei {
	const char*				id;
	const char*				name;
};
struct genderi {
	const char*				id;
	const char*				name;
};
struct spelli {
	const char*				id;
	const char*				name;
	char					level[2];
	target_s				target;
	bool					ongoing;
	dice					random;
	const char*				effect;
	const char*				remove;
};
struct populationi {
	const char*				id;
	const char*				name;
	const char*				text;
};
struct movei {
	const char*				id;
	const char*				name;
	stat_s					stat;
};
struct monsteri {
	const char*				id;
	const char*				name;
	organization_s			organization;
	size_s					size;
	monster_tag_s			tags[4];
	int						armor;
	const char*				weapon;
	dice					damage;
	char					hp;
	distance_s				distance[4];
	aref<mastermove>		moves;
};
struct godi {
	const char*				id;
	const char*				name;
};
struct tagi {
	const char*				id;
	const char*				name;
	char					value;
};
struct distancei {
	const char*				id;
	const char*				name;
};
struct itemi {
	const char*				id;
	const char*				name;
	int						cost;
	unsigned char			weight;
	prosperty_s				prosperty;
	resource_s				resource;
	taga					tags;
	distancea				distance;
	item_s					ammo;
	item_s					use_ammo;
};
class item : public taga {
	distancea				distance;
	item_s					type;
public:
	item();
	item(item_s type);
	explicit operator bool() const { return type != NoItem; }
	bool operator==(const item_s e) const { return type == e; }
	void					clear();
	item_s					getammo() const;
	int						getcost() const;
	void					getdescription(stringbuilder& sb) const;
	int						getmaxuses() const;
	void					getname(stringbuilder& sb, bool description, bool tolower = false) const;
	prosperty_s				getprosperty() const;
	resource_s				getresource() const;
	int						getsellcost(int charisma = 0) const;
	bool					is(distance_s value) const;
	bool					is(tag_s v) const { return taga::is(v); }
	bool					isammo() const;
	bool					isammo(item_s type) const;
	bool					isarmor() const;
	bool					isclumsy() const;
	bool					iscoins() const;
	bool					isgems() const;
	bool					isprecise() const;
	bool					isshield() const;
	bool					isweapon() const;
	void					set(distance_s v);
	void					set(item_s v);
	void					set(tag_s v) { taga::set(v); }
	void					use();
};
struct looti {
	item_s					items[6];
	short unsigned			coins;
	operator bool() const { return coins || items[0]; }
	void					add(item_s type);
	void					clear();
	void					generate(int hoard);
	void					getitems(stringbuilder& sb, bool description) const;
	bool					pickup();
};
struct classi {
	const char*				id;
	const char*				name;
	racea					race;
	alignmenta				alignment;
	char					load; // Load + Str equal optimal carried weight
	char					hp; // Hit poinst maximum is HP + Constitution
	char					damage; // Damage dice (d4, d6, d8, d10 or d12)
	looti					equiped;
	looti					*armament, *defence, *gear, *special;
	char					choose_gear_count; // 0 is default (chooses one)
	adat<move_s, 8>			moves;
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
	const char*				getname(const stringbuilder& sb) const;
	const char*				getweapon() const;
	bool					is(distance_s id) const;
	bool					is(monster_tag_s id) const;
	void					set(monster_s value);
	void					regroup();
};
class hero : public npc {
	char					stats[Charisma - Strenght + 1];
	char					forward[LastForward + 1];
	unsigned char			debilities;
	unsigned char			spells_known[1 + LastSpell / 8];
	unsigned char			spells_prepared[1 + LastSpell / 8];
	unsigned				moves[4];
	adat<spell_s, 2>		prodigy;
	char					castpenalty;
	item					signature_weapon;
public:
	item					weapon, shield, armor, gear[8];
	god_s					diety;
	char					hp;
	char					experience;
	hero();
	void					add(spell_s id);
	int						addbonus(forward_s id);
	static void				addcoins(int count, bool interactive = false);
	void					apply(effect_s id, int value, monster* enemy);
	bool					apply(aref<mastermove> moves, monster* enemy);
	void					apply(mastermove& m, monster* enemy);
	void					apply(looti& loot);
	result_s				cast(spell_s value, monster* te);
	void					clear();
	void					create(bool interactive);
	void					create(bool interactive, class_s value, gender_s gender);
	result_s				defydanger(stat_s stat);
	result_s				discernrealities();
	int						get(stat_s stat) const;
	int						get(forward_s stat) const;
	int						getarmor() const;
	static int				getcoins();
	dice					getdamage() const;
	static int				getdamage(class_s value);
	int						getencumbrance() const;
	char*					getequipment(stringbuilder& sb, const char* title) const;
	int						getharm() const;
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
	bool				isallow(variant id) const;
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
	void				getmarket(resourcea& result);
	char*				getname(stringbuilder& sb) const;
	bool				isoath(const steading* value) const;
	bool				isemnity(const steading* value) const;
	bool				istrade(const steading* value) const;
	void				lookaround(stringbuilder& sb);
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
	monstera			blight;
	steadinga			emnity;
	steadinga			trade;
	race_s				habbitants;
	npc					personage;
	steading*			oath;
	resourcea			resources;
	resourcea			need;
	resourcea			exotic;
	unsigned char		names[4];
};
struct resourcei {
	const char*			id;
	const char*			name;
};
struct steading_typei {
	const char*			id;
	const char*			name;
	prosperty_s			prosperty;
	population_s		population;
	defence_s			defence;
};
struct prospertyi {
	const char*			id;
	const char*			name;
	const char*			text;
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
bool					isallow(variant id);
bool					isgameover();
void					journey();
void					makecamp();
void					partyrest(bool forfree);
void					passtime(duration_s id);
void					pickup(item value);
unsigned				select(hero** result, unsigned maximum, variant id, bool alive);
void					sheets();
bool					useparty(tag_s id, bool run, bool interactive);
bool					useparty(item_s id, bool run, bool interactive);
int						whatdo(bool clear_text = true);
hero*					whodo(const char* format, ...);
hero*					whodo(stat_s stat, hero** exclude, const char* format, ...);
}
DECLENUM(alignment);
DECLENUM(class);
DECLENUM(distance);
DECLENUM(god);
DECLENUM(gender);
DECLENUM(item);
DECLENUM(monster);
DECLENUM(move);
DECLENUM(race);
DECLENUM(spell);
DECLENUM(stat);
DECLENUM(tag);
extern site				sites[256];
extern adat<spell_state, 48> spell_state_data;
extern steading			steadings[64];
inline int				d100() { return rand() % 100; }