#include "logs/bsdata.h"
#include "logs/crt.h"
#include "logs/dice.h"
#include "logs/grammar.h"
#include "logs/logs.h"
#include "logs/logs_driver.h"
#include "logs/point.h"

#pragma once

const unsigned СP = 1;
const unsigned SP = 10;
const unsigned GP = 100;

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
	// Особенности монстров
	Aggressive, PackTactics, SunlightSensitivity,
	LastFeat = SunlightSensitivity,
};
enum skill_s : unsigned char {
	NoSkill,
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
	// Weapon
	Club, Dagger, Greatclub, Handaxe, Javelin, HammerLight, Mace, Staff, Spear,
	CrossbowLight, Dart, Shortbow, Sling,
	Battleaxe, Flail, Greataxe, Halberd, Lance, Longsword, Maul, Morningstar, Pike, Rapier, Scimitar, Shortsword, Trident, Warhammer, Whip,
	CrossbowHeavy, Longbow, Net,
	Arrow, Bolt, Stone,
	// Armor
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
	Head, Neck, Armor, MeleeWeapon, OffhandWeapon, LeftFinger, RightFinger, RangedWeapon, Elbow, Gridle, Legs, Ammunition,
	FirstWear = Head, LastWear = Ammunition
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
enum monster_s : unsigned char {
	NoMonster,
	Kobold,
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
struct damage_info;
struct item {
	item_s						type;
	item() = default;
	item(item_s type) : type(type) {}
	operator item_s() const { return type; }
	const damage_info&			getattack() const;
	int							getac() const;
	int							getdex() const { return 0; }
	bool						is(item_feat_s id) const;
	bool						is(wear_s id) const;
	bool						islight() const;
	bool						ismelee() const { return is(MeleeWeapon); }
	bool						isranged() const { return is(RangedWeapon); }
};
struct armor_info {
	char						ac;
	char						dex;
	char						str;
	skill_s						disadvantage;
};
struct damage_info {
	dice						damage;
	damage_type_s				type;
};
struct roll_info {
	explicit operator bool() const;
	char						rolled, bonus, result, dc;
	void						set(roll_s type);
	roll_s						get() const;
private:
	bool						advantage;
	bool						disadvantage;
};
struct attack_info : damage_info, roll_info {
	item*						weapon;
	char						critical;
};
struct item_info {
	const char*					id;
	const char*					name;
	unsigned					cost;
	unsigned					weight;
	wear_s						wears[2];
	feat_s						proficiency[4];
	item_feat_s					feats[3];
	damage_info					attack;
	armor_info					armor;
};
struct creature {
	void* operator new(unsigned size);
	void operator delete (void* data);
	explicit operator bool() const { return ability[0] != 0; }
	creature() = default;
	creature(race_s race, gender_s gender, class_s type, background_s background, char* ability, bool interactive);
	creature(monster_s id);
	void						act(const char* format, ...) const;
	bool						add(const item it);
	void						apply(aref<feat_s> elements, const char* title, bool interactive);
	void						apply(aref<language_s> elements, const char* title, int count, bool interactive);
	void						apply(aref<skill_s> elements, const char* title, int count, bool interactive);
	void						apply(aref<spell_s> elements, const char* title, bool interactive);
	void						apply(background_s id, bool interactive);
	void						apply(class_s id, bool interactive);
	void						apply(class_s id, int level, bool interactive);
	void						apply(race_s id, bool interactive);
	void						attack(wear_s slot, creature& enemy) const;
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
	void						get(attack_info& e, wear_s slot) const;
	void						get(attack_info& e, wear_s slot, const creature& enemy) const;
	int							getac() const;
	int							getlevel() const;
	int							gethp() const { return hp; }
	int							gethpmax() const;
	const char*					getname(char* result, const char* result_maximum) const;
	int							getproficiency() const;
	int							getr(ability_s id) const { return ability[id]; }
	race_s						getrace() const;
	bool						is(feat_s id) const { return (feats[id >> 5] & (1 << (id & 0x1F))) != 0; }
	bool						is(language_s id) const { return (languages & (1 << id)) != 0; }
	bool						is(skill_s id) const { return (skills & (1 << id)) != 0; }
	bool						is(spell_s id) const { return (spells[id >> 5] & (1 << (id & 0x1F))) != 0; }
	bool						isproficient(item_s type) const;
	static void					place_ability(char* result, char* ability, bool interactive);
	static void					random_ability(char* result);
	void						remove(feat_s id) { feats[id >> 5] &= ~(1 << (id & 0x1F)); }
	int							roll() const;
	int							roll(roll_s type) const;
	void						roll(roll_info& result) const;
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
	monster_s					monster;
	short						hp, hp_rolled;
	unsigned					skills, languages;
	char						ability[Charisma + 1];
	unsigned					feats[(LastFeat + 1)>>5];
	unsigned					spells[2];
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