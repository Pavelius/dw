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
	// Upgrades tags
	Spiked, Sharp, PerfectlyWeighted, SerratedEdges, Glows, HugeWeapon, Versatile, WellCrafted,
	// Monster tags
	Amorphous, Cautions, Construct, Devious, Hoarder,
	Intellegent, Magical, Organized, Planar, Stealthy, Undead,
	Terrifing,
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
	TargetSelf, TargetHero, TargetMonster,
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
enum organization_s : unsigned char {
	Horde, Group, Solitary
};
enum variant_s : unsigned char {
	NoVariant,
	Action, Alignment, Class, DungeonMoves, Item, Monster, Move, Player, Result, Spell, Tag,
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
	unsigned char			subtype;
	constexpr variant() : type(NoVariant), subtype(0) {}
	constexpr variant(alignment_s v) : type(Alignment), subtype(v) {}
	constexpr variant(class_s v) : type(Class), subtype(v) {}
	constexpr variant(spell_s v) : type(Spell), subtype(v) {}
	constexpr variant(move_s v) : type(Move), subtype(v) {}
	constexpr variant(dungeon_move_s v) : type(DungeonMoves), subtype(v) {}
	constexpr variant(item_s v) : type(Item), subtype(v) {}
	constexpr variant(monster_s v) : type(Monster), subtype(v) {}
	constexpr variant(result_s v) : type(Result), subtype(v) {}
	constexpr variant(variant_s type, unsigned char v) : type(type), subtype(v) {}
	constexpr variant(unsigned short v) : type(variant_s(v >> 8)), subtype(v & 0xFF) {}
	constexpr operator unsigned short() const { return type << 8 | subtype; }
	constexpr explicit operator bool() const { return type != NoVariant; }
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
struct godi {
	const char*				id;
	const char*				name;
};
struct tagi {
	const char*				id;
	const char*				name;
	char					count;
};
struct distancei {
	const char*				id;
	const char*				name;
};
template<unsigned last>
class flagable {
	static constexpr unsigned s = sizeof(unsigned) * 8;
	static constexpr unsigned c = 1 + last / s;
	unsigned				data[c];
public:
	constexpr flagable() : data{0} {}
	constexpr void			add(const flagable& e) { for(unsigned i = 0; i < c; i++) data[i] |= e.data[i]; }
	void					clear() { memset(this, 0, sizeof(*this)); }
	constexpr bool			is(short unsigned v) const { return (data[v / s] & (1 << (v%s))) != 0; }
	constexpr void			remove(short unsigned v) { data[v / s] &= ~(1 << (v%s)); }
	constexpr void			set(short unsigned v) { data[v / s] |= 1 << (v%s); }
	constexpr void			set(short unsigned v, bool activate) { if(activate) set(v); else remove(v); }
};
class tagable {
	flagable<Terrifing>		tags;
	flagable<Supply>		moves;
	flagable<LastSpell>		spells;
	int						get(tag_s i1, tag_s i2) const;
	void					set(tag_s i1, tag_s i2, int v);
public:
	constexpr tagable() {}
	constexpr tagable(const std::initializer_list<variant>& list) {
		for(auto e : list) {
			switch(e.type) {
			case Class: set((tag_s)e.subtype); break;
			case Move: set((move_s)e.subtype); break;
			case Spell: set((spell_s)e.subtype); break;
			}
		}
	}
	void					apply(const tagable& e) { tags.add(e.tags); moves.add(e.moves); spells.add(e.spells); }
	void					clear() { memset(this, 0, sizeof(*this)); }
	int						getarmor() const { return get(Armor1, Armor4); }
	int						getdamage() const;
	int						getpierce() const;
	int						getuses() const { return get(Use1, Use4); }
	int						getweight() const;
	constexpr bool			is(tag_s v) const { return tags.is(v); }
	constexpr bool			is(move_s v) const { return moves.is(v); }
	constexpr bool			is(spell_s v) const { return spells.is(v); }
	constexpr void			remove(tag_s v) { tags.remove(v); }
	constexpr void			remove(move_s v) { moves.remove(v); }
	constexpr void			remove(spell_s v) { spells.remove(v); }
	constexpr void			set(tag_s v) { tags.set(v); }
	constexpr void			set(move_s v) { moves.set(v); }
	constexpr void			set(spell_s v) { spells.set(v); }
	void					setarmor(int v) { set(Armor1, Armor4, v); }
	void					setdamage(int v) { set(Damage1, Damage2, v); }
	void					setpierce(int v) { set(Pierce1, Pierce2, v); }
	void					setuses(int v) { set(Use1, Use4, v); }
	void					setweight(int v) { set(Weight1, Weight8, v); }
};
class living {
	char					hp;
	char					count;
public:
	constexpr living() : hp(0), count(0) {}
	constexpr living(int hp, int count) : hp(hp), count(count) {}
	int						getcount() const { return count; }
	int						gethp() const { return hp; }
	bool					isalive() const { return hp > 0; }
	void					kill();
	void					setcount(int v) { count = v; }
	void					sethp(int v) { hp = v; }
};
class nameable {
	short unsigned			name;
public:
	constexpr nameable() : name(0) {}
	const char*				getname() const;
	gender_s				getnamegender() const;
	void					setname(short unsigned v) { name = v; }
	void					setname(race_s race, gender_s gender);
	void					setname(class_s type, race_s race, gender_s gender);
};
struct thing : variant, tagable, nameable, living {
	constexpr thing() {}
	constexpr thing(variant v) : variant(v) {}
	constexpr thing(variant v, int hp, int count) : variant(v), living(hp, count) {}
	void					act(move_s id) const;
	void					act(const char* format, ...) const { actv(sb, format, xva_start(format)); }
	void					actv(stringbuilder& sb, const char* format, const char* format_param) const;
	int						choose(bool interactive, bool clear_text, const char* format, ...) const { return choosev(interactive, clear_text, format, xva_start(format)); }
	int						choosev(bool interactive, bool clear_text, const char* format, const char* format_param) const;
	int						getdice() const;
	gender_s				getgender() const;
	int						getharm() const;
	int						getmaxhits() const;
	const char*				getname() const;
	void					say(const char* format, ...) const;
};
struct npc : thing {
	race_s					race;
	alignment_s				alignment;
	unsigned char			level;
	void					create(class_s subtype);
	static gender_s			choosegender(bool interactive);
	static race_s			chooserace(const racea& source, bool interactive);
	static class_s			chooseclass(bool interactive);
	static alignment_s		choosealignment(const alignmenta& source, bool interactive);
	bool					isdwarf() const { return race == Dwarf; }
	void					setalignment();
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
struct monstermovei {
	move_s					move;
	variant					id;
	const char*				name;
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
	tag_s					tags[4];
	int						armor;
	const char*				weapon;
	dice					damage;
	char					hp;
	distance_s				distance[4];
	aref<mastermove>		moves;
};
struct itemi {
	const char*				id;
	const char*				name;
	int						cost;
	unsigned char			weight;
	prosperty_s				prosperty;
	resource_s				resource;
	tagable					tags;
	distancea				distance;
	item_s					ammo;
	item_s					use_ammo;
};
class item : public tagable {
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
	bool					is(distance_s subtype) const;
	bool					is(tag_s v) const { return tagable::is(v); }
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
	void					set(tag_s v) { tagable::set(v); }
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
	monster(monster_s v);
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
	bool					is(distance_s v) const;
	bool					is(tag_s v) const;
	void					set(monster_s v);
	void					regroup();
};
class hero : public npc {
	char					stats[Charisma - Strenght + 1];
	char					forward[LastForward + 1];
	unsigned char			debilities;
	flagable<LastSpell>		spells_prepared;
	adat<spell_s, 2>		prodigy;
	char					castpenalty;
	item					signature_weapon;
	flagable<LastSpell>		known_spells;
public:
	item					weapon, shield, armor, gear[8];
	god_s					diety;
	char					experience;
	hero();
	void					add(spell_s id);
	int						addbonus(forward_s id);
	static void				addcoins(int count, bool interactive = false);
	void					apply(effect_s id, int subtype, monster* enemy);
	bool					apply(aref<mastermove> moves, monster* enemy);
	void					apply(mastermove& m, monster* enemy);
	void					apply(const looti& loot);
	result_s				cast(spell_s subtype, monster* te);
	int						choosecombat(bool clear_text, thing& enemy, const char* format = 0, ...) const;
	int						choosecombatv(bool clear_text, thing& enemy, const char* format, const char* format_param) const;
	hero*					choosecombatother(thing& enemy, const char* format, ...) const;
	void					clear();
	void					create(bool interactive);
	void					create(bool interactive, class_s subtype, gender_s gender);
	result_s				defydanger(stat_s stat);
	result_s				discernrealities();
	static result_s			fight(thing& enemy);
	int						get(stat_s stat) const;
	int						get(forward_s stat) const;
	int						getarmor() const;
	static int				getcoins();
	const classi&			getclass() const;
	int						getencumbrance() const;
	char*					getequipment(stringbuilder& sb, const char* title) const;
	item*					getitem(item_s type);
	int						getlevel(spell_s subtype) const;
	int						getload() const;
	void					getlook(stringbuilder& sb) const;
	int						getmaxhits() const;
	void					getparty(stringbuilder& sb) const;
	int						getpreparedlevels() const;
	int						getongoing() const;
	int						getraw(stat_s id) const { return stats[id]; }
	stat_s					getstat(move_s move) const;
	int						getspellpenalty() const;
	unsigned				getspells(spell_s* source, unsigned maximum);
	item*					getweapon(distance_s distance);
	void					hackandslash(monster& enemy);
	void					hackandslash(thing& enemy);
	void					healharm(int count);
	void					hunger();
	void					inflictharm(monster& enemy, int subtype);
	void					inflictharm(thing& enemy, int count);
	static bool				isactive(spell_s id);
	bool					isalive() const;
	bool					isallow(effect_s id, int subtype, monster* enemy) const;
	bool					isallow(item_s id) const;
	bool					isallow(tag_s id) const;
	bool					isallow(variant id) const;
	bool					isammo(item_s subtype) const;
	bool					iscaster() const { return type == Wizard || type == Cleric; }
	bool					iscombatable() const;
	bool					isclumsy() const;
	bool					isdebilities(stat_s subtype) const { return (debilities & (1 << subtype)) != 0; }
	bool					isequipment() const;
	static bool				isparty(variant v);
	bool					isprepared(spell_s v) const { return spells_prepared.is(v); }
	bool					isvariant(variant v) const;
	static bsreq			metadata[];
	result_s				parley();
	void					preparespells(bool interactive);
	bool					prepareweapon(monster& enemy);
	bool					remove(item it);
	static void				remove(spell_s id);
	result_s				roll(int bonus, int* result = 0, bool show_result = true);
	result_s				roll(move_s id);
	bool					set(item subtype);
	void					set(move_s subtype, bool interactive);
	void					set(forward_s id, char subtype);
	void					setdebilities(stat_s subtype, bool state);
	void					setknown(spell_s v, bool activate) { known_spells.set(v, activate); }
	void					setraw(stat_s id, int v) { stats[id] = v; }
	void					setprepared(spell_s v, bool activate) { spells_prepared.set(v, activate); }
	unsigned				select(spell_state** result, spell_state** result_maximum) const;
	result_s				sell(prosperty_s prosperty);
	void					sheet();
	result_s				spoutlore();
	void					sufferharm(int subtype, bool ignore_armor = false);
	static void				supply(item* items, unsigned count);
	hero*					takecover(thing& enemy);
	void					turnundead(monster& enemy);
	bool					use(tag_s id, bool interactive);
	bool					use(item_s id, bool interactive);
	bool					useammo(item_s subtype, bool run, bool interactive);
	void					volley(monster& enemy);
	int						whatdo(bool clear_text = true);
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
	bool				isoath(const steading* subtype) const;
	bool				isemnity(const steading* subtype) const;
	bool				istrade(const steading* subtype) const;
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
bool					isallow(variant id, bool alive = true);
bool					isgameover();
void					journey();
void					makecamp();
void					partyrest(bool forfree);
void					passtime(duration_s id);
void					pickup(item subtype);
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