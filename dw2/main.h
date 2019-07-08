#include "logs\collection.h"
#include "logs\crt.h"
#include "logs\dice.h"
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

struct tid {
	tid_s					type;
	union {
		spell_s				spell;
		move_s				move;
		move_s				move;
	};
	unsigned char			value;
	constexpr tid(spell_s v) : type(Spells), value(v) {}
	constexpr tid(move_s v) : type(Moves), value(v) {}
	constexpr tid(class_s v) : type(Classes), value(v) {}
	constexpr tid(alignment_s v) : type(Alignments), value(v) {}
	constexpr tid(item_s v) : type(Items), value(v) {}
	constexpr tid(result_s v) : type(Results), value(v) {}
	constexpr tid(tid_s type, unsigned char v) : type(type), value(v) {}
	constexpr tid(int v) : type(tid_s(v >> 8)), value(v & 0xFF) {}
	constexpr operator unsigned short() const { return ((type << 8) | (value)); }
};
class tagc {
	unsigned				data[2];
	static constexpr unsigned int size = sizeof(tagc::data[0]) * 8;
public:
	constexpr tagc() : data{0} {}
	constexpr tagc(const std::initializer_list<tag_s>& list) : data() { for(auto e : list) add(e); }
	constexpr void			add(tag_s id) { data[id / size] |= 1 << (id % size); }
	void					clear() { data[0] = 0; data[1] = 0; }
	constexpr bool			is(tag_s id) const { return (data[id/size] & (1 << (id % size))) != 0; }
	constexpr void			remove(tag_s id) { data[id / size] &= ~(1 << (id % size)); }
};
struct monsteri {
	const char*				name;
	char					armor, hits, damage, count;
	char					hits_current, count_current;
	const char*				getname() const;
};
class item {
	item_s					type;
	tagc					tags;
public:
	constexpr item() : type(NoItem), tags() {}
};