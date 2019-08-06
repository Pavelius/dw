#include "logs\collection.h"
#include "logs\crt.h"
#include "logs\logs.h"

#pragma once

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
enum tag_s : unsigned char {
	Hand, Close, Reach, Near, Far,
	Awkward, Clumsy, Messy, Ration, Reloaded, Precise, Slow, Thrown, TwoHanded,
	Armor1, Armor2, Armor4, ArmorP1,
	DamageP1, DamageP2, DamageM1, DamageM2,
	Weight1, Weight2, Weight4,
	Pierce1, Pierce2, IgnoreArmor,
	Use1, Use2, Use4, Ammo1, Ammo2, Ammo4,
	// Special properties
	Identified,
	// Item upgrades
	Spiked, Sharp, PerfectlyWeighted, SerratedEdges, Glows, HugeWeapon, Versatile, WellCrafted,
};
enum class_s : unsigned char {
	Bard, Cleric, Druid, Fighter, Paladin, Ranger, Theif, Wizard,
};
enum race_s : unsigned char {
	NoRace,
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
	Choose1, Choose2, Choose3, Choose4,
	Damage, DamageAllParty,
	DamageIA, DamageAllPartyIA,
	DamageOpponent,
	Regroup, Summon,
	Heal, HealParty, BonusForward,
	LooseItem, LooseMoney,
	Debility, DebilityParty,
	UseAmmo, UseCharge,
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
	Actions, Alignments, Classes, DungeonMoves, Items, Results, Spells, Tag,
};

struct steading;
struct spell_state;

template<class T> struct bsmeta {
	static const T			elements[];
};
struct tid {
	tid_s					type;
	union {
		alignment_s			alignment;
		class_s				cls;
		item_s				item;
		move_s				move;
		spell_s				spell;
		tag_s				tag;
		unsigned char		value;
	};
	constexpr tid(alignment_s v) : type(Alignments), alignment(v) {}
	constexpr tid(class_s v) : type(Classes), cls(v) {}
	constexpr tid(item_s v) : type(Items), item(v) {}
	constexpr tid(move_s v) : type(Moves), move(v) {}
	constexpr tid(spell_s v) : type(Spells), spell(v) {}
	constexpr tid(result_s v) : type(Results), value(v) {}
	constexpr tid(tag_s v) : type(Tag), tag(v) {}
	constexpr tid(tid_s type, unsigned char v) : type(type), value(v) {}
};
struct range {
	unsigned char			dice;
	char					bonus;
	int						roll() const;
};
class tagc {
	static constexpr unsigned int size = sizeof(unsigned) * 8;
	unsigned				data[WellCrafted / size + 1];
public:
	constexpr tagc() : data{0} {}
	constexpr tagc(const std::initializer_list<tag_s>& list) : data() { for(auto e : list) add(e); }
	constexpr void			add(tag_s id) { data[id / size] |= 1 << (id % size); }
	void					clear() { data[0] = 0; data[1] = 0; }
	int						getarmor() const;
	int						getdamage() const;
	int						getweight() const;
	constexpr bool			is(tag_s id) const { return (data[id / size] & (1 << (id % size))) != 0; }
	constexpr void			remove(tag_s id) { data[id / size] &= ~(1 << (id % size)); }
};
struct itemi {
	const char*				id;
	const char*				name;
	int						cost;
	prosperty_s				prosperty;
	resource_s				resource;
	tagc					tags;
	item_s					ammo;
	item_s					use_ammo;
};
struct monsteri : tagc {
	const char*				name;
	gender_s				gender;
	race_s					race;
	char					hits_maximum, count_maximum, damage;
	char					hits, count;
	constexpr monsteri() : tagc{Close}, name(""), gender(Male), race(NoRace), damage(6),
		hits_maximum(1), count_maximum(1),
		hits(3), count(1) {}
	void					act(const char* format, ...) const;
	gender_s				getgender() const { return gender; }
	const char*				getname() const { return name; }
	bool					isalive() const { return hits > 0 && count > 0; }
	bool					iswounded() const { return hits < hits_maximum; }
	void					heal(int value, int* result_value = 0);
	int						rolldamage() const;
	void					sufferharm(int value, int pierce = 0, int* result_value = 0, int* killed = 0);
};
class item : public tagc {
	item_s					type;
	unsigned char			count;
public:
	constexpr item() : tagc(), type(NoItem), count(0) {}
	constexpr item(item_s type) : tagc(bsmeta<itemi>::elements[type].tags), type(type), count(0) {}
};
class playeri : public monsteri {
	char					stats[Charisma + 1];
	item					hands, gears[16];
	class_s					type;
};
struct effecti {
	effect_s				type;
	int						param;
	constexpr effecti() : type(NoEffect), param(0) {}
	constexpr effecti(effect_s type) : type(type), param(0) {}
	bool					allow(const playeri& player, const monsteri& opponent) const;
};
struct movei {
	result_s				result;
	const char*				text;
	effecti					effect, effect2;
	explicit constexpr operator bool() const { return text != 0; }
};