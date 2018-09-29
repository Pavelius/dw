#include "logs/bsdata.h"
#include "logs/crt.h"
#include "logs/dice.h"
#include "logs/grammar.h"
#include "logs/logs.h"
#include "logs/logs_driver.h"
#include "logs/point.h"

#pragma once

const unsigned GP = 100;
const unsigned SP = 100;

enum ability_s : unsigned char {
	Strenght, Dexterity, Constitution, Intellegence, Wisdow, Charisma,
};
enum feat_s : unsigned char {
	NoFeat,
	// Proficiency with weapon and armor
	LightArmorProficiency, MediumArmorProficiency, HeavyArmorProficiency, ShieldProficiency,
	SimpleWeaponProficiency, MartialWeaponProfiency, ElfWeaponTrain, DwarvenWeaponTrain, RogueWeaponTrain,
	// Спас-Броски
	SaveStrenght, SaveDexterity, SaveConstitution, SaveIntellegence, SaveWisdow, SaveCharisma,
	// Расовые способности
	Brave, Darkvision, DwarvenResilience, DwarvenToughness, FeyAncestry,
	KeenSences, Lucky, MaskOfTheWild, NaturallyStealthy, Stonecunning, TranceInsteadSleep,
	// Классовые способности (воин)
	SecondWind, ActionSurge, ExtraAttack, Indomitable,
	ImprovedCritical, RemarkableAthlete, SuperiorCritical, Survivor,
	// Классовые способности (клерик)
	Spellcasting, ChannelDivinity, DestroyUndead, DivineIntervention,
	DiscipleofLife, BlessedHealer, DivineStrike, SupremeHealing,
	//
	SneakAttack, ThievesCant, CunningAction,
	FastHands, SecondStoryWork, SupremeSneak, UseMagicDevice, ThiefsReflexes,
	// Стили боя
	StyleArchery, StyleDefense, StyleDueling, StyleGreatWeaponFighting, StyleProtection, StyleTwoWeaponFighting,
	// Эксперты по навыкам
	ExpertAthletics, ExpertAcrobatics, ExpertSleightOfHands, ExpertStealth,
	ExpertArcana, ExpertHistory, ExpertInvestigation, ExpertNature, ExpertReligion,
	ExpertAnimalHandling, ExpertInsight, ExpertMedicine, ExpertPerception, ExpertSurvival,
	ExpertDeception, ExpertIntimidation, ExpertPerformance, ExpertPersuasion,
};
enum skill_s : unsigned char {
	Athletics, Acrobatics, SleightOfHands, Stealth,
	Arcana, History, Investigation, Nature, Religion,
	AnimalHandling, Insight, Medicine, Perception, Survival,
	Deception, Intimidation, Performance, Persuasion,
};
enum language_type_s : unsigned char {
	AnyLanguage,
	ModernLanguage, AncientLanguage,
};
enum language_s : unsigned char {
	LanguageCommon,
	LanguageDwarvish, LanguageElvish,
	LanguageGiant, LanguageGoblin, LanguageOrc,
	LanguageAbysal, LanguageCelestial, LanguageDraconic, LanguageDeepSpeech,
	LanguageInfernal,
};
enum school_s : unsigned char {
	Abjuration, Conjuration, Divination, Enchantment, Evocation, Illusion, Necromancy, Transmutation,
};
enum background_s : unsigned char {
	NoBackground,
	Acolyte, Criminal, FolkHero, Noble, Sage, Soldier,
};
enum race_s : unsigned char {
	NoRace,
	Dwarf, Elf, Halfling, Human,
	DwarfHill, DwarfMountain, ElfWood, ElfHight, HalflingLightfoot, HalflingStout,
};
enum class_s : unsigned char {
	NoClass,
	Cleric, Fighter, Rogue, Wizard,
};
enum alignment_s : unsigned char {
	LawfulGood, NeutralGood, ChaoticGood,
	LawfulNeutral, TrueNeutral, ChaoticNeutral,
	LawfulEvil, NeutralEvil, ChaoticEvil,
};
enum item_s : unsigned char {
	NoItem,
	Battleaxe, Handaxe, Greataxe,
	Club, Greatclub, Javelin, Dagger, HammerLight, HammerWar,
	Mace, Lance,
	Spear, Staff,
	SwordGreat, SwordLong, SwordShort,
	// Items (weapon ranged)
	CrossbowLight, CrossbowHeavy, BowLong, BowShort, Dart, Sling,
	Stone, Arrow, Bolt,
	// Items (armor)
	PaddedArmour, LeatherArmour, StuddedLeatherArmour,
	HideArmour, BreastPlate, HalfPlate, ChainShirt, ScaleMail,
	RingMail, PlateMail, ChainMail, SplintMail,
	Shield, Helmet, Bracers,
	Ring, Necklage,
};
enum item_feat_s : unsigned char {
	NoItemFeat,
	Finesse, Heavy, Loading, Reach, Thrown, TwoHanded, Versatile,
};
enum damage_type_s : unsigned char {
	Bludgeon, Slashing, Pierce,
};
enum wear_s : unsigned char {
	FirstInvertory, LastInvertory = FirstInvertory + 16,
	Head, Neck, Armor, MeleeWeapon, OffhandWeapon, RangedWeapon, Gridle, Legs,
	FirstWear = Head, LastWear = Legs
};
enum state_s : unsigned char {
	Blinded, Charmed, Deafened, Frightened, Grappled, Incapacitated,
	Invisible, Paralyzed, Petrified, Poisoned, Prone, Restrained,
	Stunned, Unconscious,
};
enum size_s : unsigned char {
	Tiny, Small, Medium, Large, Huge,
};
enum range_s : unsigned char {
	Touch, Range10, Range20, Range30, Range60, Range80, Range120,
};
enum duration_s : unsigned char {
	Instantaneous, BonusAction, Action,
	DurationMinute, Duration10Minute, DurationHour, DurationNight,
};
enum spell_s : unsigned char {
	// Spells level 0
	SpellAcidSplash, SpellDancingLight, SpellFireBolt, SpellGuidance, SpellLight, SpellMageHand, SpellMinorIllusion,
	SpellPoisonSpray, SpellPrestidigination, SpellRayOfFrost, SpellResistance,
	SpellSacredFlame, SpellShockingGrasp, SpellSpareOfDying, SpellThaumaturgy,
	// Spells level 1
	SpellBless, SpellCommand, SpellCureWounds, SpellDetectMagic, SpellGuidingBolt,
	SpellHealingWord, SpellInflictWounds, SpellSanctuary, SpellShieldOfFaith,
	FirstSpell = SpellAcidSplash, LastSpell = SpellShieldOfFaith,
};
enum roll_s : unsigned char {
	RollNormal, Advantage, Disadvantage
};
enum slot_s : unsigned char {
	SpellSlot1, SpellSlot2, SpellSlot3, SpellSlot4, SpellSlot5, SpellSlot6, SpellSlot7, SpellSlot8, SpellSlot9,
	ActionSurgeSlot, ChannelDivinitySlot, IndomitableSlot, SecondWindSlot,
	LastSlot = SecondWindSlot,
};
enum domain_s : unsigned char {
	NoDomain,
	LifeDomain,
};
struct creature;
struct feature_info;
typedef void(*featureproc)(const feature_info& e, creature& player, bool interactive);
struct domain_info {
	const char*					id;
	const char*					name;
};
struct race_info {
	race_s						basic;
	const char*					id;
	const char*					name;
	char						abilities[Charisma + 1];
	char						speed;
	size_s						size;
	feat_s						traits[4];
	adat<language_s, 2>			languages;
	char						extra_languages[2];
	char						extra_cantrip;
};
struct background_info {
	const char*					id;
	const char*					name;
	skill_s						skills[2];
	char						extra_languages[2];
};
struct class_info {
	const char*					id;
	const char*					name;
	char						hd, start_skills;
	adat<feat_s, 12>			traits;
	char						abilities[6];
	adat<skill_s, 12>			skills;
};
struct attack_info {
	dice						damage;
	damage_type_s				type;
	char						bonus;
	char						critical_thread;
};
struct item_info {
	const char*					id;
	const char*					name;
	unsigned					cost;
	unsigned					weight;
	wear_s						wears[2];
	feat_s						proficiency[4];
	item_feat_s					feats[2];
	attack_info					attack;
};
struct item {
	item_s						type;
	int							getac() const { return 10; }
	int							getdex() const { return 0; }
	bool						is(item_feat_s id) const;
	bool						is(wear_s id) const;
	bool						islight() const;
};
struct creature {
	void* operator new(unsigned size);
	void operator delete (void* data);
	explicit operator bool() const { return ability[0] != 0; }
	creature() = default;
	creature(race_s race, gender_s gender, class_s type, background_s background, char* ability, bool interactive);
	void						apply(aref<feat_s> elements, const char* title, bool interactive);
	void						apply(aref<language_s> elements, const char* title, int count, bool interactive);
	void						apply(aref<skill_s> elements, const char* title, int count, bool interactive);
	void						apply(aref<spell_s> elements, const char* title, bool interactive);
	void						apply(background_s id, bool interactive);
	void						apply(class_s id, bool interactive);
	void						apply(class_s id, int level, bool interactive);
	void						apply(race_s id, bool interactive);
	void						clear();
	static void					choose_ability(char* result, bool interactive);
	static background_s			choose_background(bool interactive);
	static class_s				choose_class(bool interactive);
	static domain_s				choose_domain(bool interactive);
	static gender_s				choose_gender(bool interactive);
	static race_s				choose_race(bool interactive);
	static race_s				choose_subrace(race_s race, bool interactive);
	static creature*			generate(bool interactive);
	int							get(ability_s id) const { return getr(id) / 2 - 5; }
	int							getac() const;
	int							getlevel() const;
	int							gethp() const { return hp; }
	int							gethpmax() const;
	int							getproficiency() const;
	int							getr(ability_s id) const { return ability[id]; }
	race_s						getrace() const;
	bool						is(feat_s id) const { return (feats[id >> 5] & (1 << (id & 0x1F))) != 0; }
	bool						is(language_s id) const { return (languages & (1 << id)) != 0; }
	bool						is(skill_s id) const { return (skills & (1 << id)) != 0; }
	bool						is(spell_s id) const { return (spells[id >> 5] & (1 << (id & 0x1F))) != 0; }
	bool						isallow(item it) const;
	static void					place_ability(char* result, char* ability, bool interactive);
	static void					random_ability(char* result);
	void						remove(feat_s id) { feats[id >> 5] &= ~(1 << (id & 0x1F)); }
	int							roll() const;
	int							roll(roll_s type) const;
	void						set(feat_s id) { feats[id >> 5] |= 1 << (id & 0x1F); }
	void						set(language_s id) { languages |= 1 << id; }
	void						set(skill_s id) { skills |= 1 << id; }
	void						set(spell_s id) { spells[id >> 5] |= 1 << (id & 0x1F); }
	void						set(domain_s value) { domain = value; }
private:
	gender_s					gender;
	race_s						race;
	background_s				background;
	domain_s					domain;
	short						hp, hp_rolled;
	char						ability[Charisma + 1];
	unsigned					feats[2];
	unsigned					spells[2];
	unsigned					skills, languages;
	unsigned char				slots[LastSlot + 1];
	unsigned char				classes[Wizard + 1];
	item						wears[LastWear + 1];
	//
	void						choose_languages(class_s type, bool interactive);
	void						choose_skills(class_s type, bool interactive);
};
extern class_info				class_data[];
extern item_info				item_data[];
extern race_info				race_data[];