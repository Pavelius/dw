#include "logs/bsdata.h"
#include "logs/crt.h"
#include "logs/grammar.h"
#include "logs/logs.h"
#include "logs/logs_driver.h"
#include "logs/point.h"

#pragma once

const unsigned �P = 1;
const unsigned SP = 10;
const unsigned GP = 100;
const unsigned fraction_max = 12;

enum ability_s : unsigned char {
	Strenght, Dexterity, Constitution, Intellegence, Wisdow, Charisma,
};
enum feat_s : unsigned char {
	NoFeat,
	// Proficiency with weapon and armor
	LightArmorProficiency, MediumArmorProficiency, HeavyArmorProficiency, ShieldProficiency,
	SimpleWeaponProficiency, MartialWeaponProfiency, ElfWeaponTrain, DwarvenWeaponTrain, RogueWeaponTrain,
	AlchemistProficiency, CalligrapherProficiency, CarpenterProficiency, CartographerProficiency,
	CobblerProficiency, CookProficiency, GlassblowerProficiency, JewelerProficiency, LeatherworkerProficiency,
	MasonProficiency, PainterProficiency, PotterProficiency, SmithProficiency, TinkerProficiency, WeaverProficiency, WoodcarverProficiency,
	//
	DisguiseKitProficiency, ForgeryKitProficiency, HerbalismKitProficiency, NavigatorToolsProficiency, PoisonerKitProficiency, TheifToolsProficiency,
	// ����-������
	SaveStrenght, SaveDexterity, SaveConstitution, SaveIntellegence, SaveWisdow, SaveCharisma,
	// ������� �����������
	Brave, Darkvision, DwarvenResilience, DwarvenToughness, FeyAncestry,
	KeenSences, Lucky, MaskOfTheWild, NaturallyStealthy, Stonecunning, TranceInsteadSleep,
	// ��������� ����������� (����)
	SecondWind, ActionSurge, ExtraAttack, Indomitable,
	ImprovedCritical, RemarkableAthlete, SuperiorCritical, Survivor,
	// ��������� ����������� (������)
	Spellcasting, ChannelDivinity, DestroyUndead, DivineIntervention,
	DiscipleofLife, BlessedHealer, DivineStrike, SupremeHealing,
	//
	SneakAttack, ThievesCant, CunningAction,
	FastHands, SecondStoryWork, SupremeSneak, UseMagicDevice, ThiefsReflexes,
	// ����� ���
	StyleArchery, StyleDefense, StyleDueling, StyleGreatWeaponFighting, StyleProtection, StyleTwoWeaponFighting,
	// �������� �� �������
	ExpertAthletics, ExpertAcrobatics, ExpertSleightOfHands, ExpertStealth,
	ExpertArcana, ExpertHistory, ExpertInvestigation, ExpertNature, ExpertReligion,
	ExpertAnimalHandling, ExpertInsight, ExpertMedicine, ExpertPerception, ExpertSurvival,
	ExpertDeception, ExpertIntimidation, ExpertPerformance, ExpertPersuasion,
	// ����������� ��������
	Aggressive, PackTactics, SunlightSensitivity,
	// �������� �������
	Slowed10feet, Guided, Resisted,
	LastFeat = Resisted,
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
	LeatherArmour, PaddedArmour, StuddedLeatherArmour,
	HideArmour, BreastPlate, HalfPlate, ChainShirt, ScaleMail,
	RingMail, PlateMail, ChainMail, SplintMail,
	Shield, Helmet, Bracers,
	Ring, Necklage,
	//
	Bedroll, Book, ComponentPounch, Crowbar, HolySymbol, Map, Parchment, Ration, Rope, Spellbook, Torches, Waterskin,
	Dices, PlayingCards,
	Flute, Lute,
	//
	AlchemistSupplies, BrewerSupplies, CalligrapherSupplies, CarpenterTools, CartographerTools,
	CobblerTools, CookUtensils, GlassblowerTools, JewelerTools, LeatherworkerTools,
	MasonTools, PainterSupplies, PotterTools, SmithTools, TinkerTools, WeaverTools, WoodcarverTools,
	//	
	DisguiseKit, ForgeryKit, HerbalismKit, NavigatorTools, PoisonerKit, TheifTools,
	//
	LastItem = TheifTools,
};
enum pack_s : unsigned char {
	BurglarPack, DiplomatPack, DungeoneerPack, EntertainerPack, ExplorerPack, PriestsPack, ScholarsPack,
	GamingSet,
	LastPack = GamingSet
};
enum save_s : unsigned char {
	NoSave, Save, Half,
};
enum item_feat_s : unsigned char {
	NoItemFeat,
	Finesse, Heavy, Loading, Reach, Thrown, TwoHanded, Versatile,
};
enum damage_type_s : unsigned char {
	Bludgeon, Slashing, Pierce,
	Acid, Cold, Fire, Force, Lightning, Necrotic, Poison, Psychic, Radiant, Thunder
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
	Instantaneous, Concentration, BonusAction, Action,
	DurationMinute, Duration10Minute, DurationHour, DurationNight,
};
enum spell_s : unsigned char {
	NoSpell,
	// Spells level 0
	AcidSplash, DancingLight, FireBolt, Guidance, Light, MageHand, MinorIllusion,
	PoisonSpray, Prestidigination, RayOfFrost, Resistance,
	SacredFlame, ShockingGrasp, SpareOfDying, Thaumaturgy,
	// Spells level 1
	Bless, Command, CureWounds, DetectMagic, GuidingBolt,
	HealingWord, InflictWounds, Sanctuary, ShieldOfFaith,
	LastSpell = ShieldOfFaith,
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
	Kobold, Orc,
};
enum variant_s : unsigned char {
	NoVariant,
	Race, Class, Feat, Item, Language, Pack, Skill, State,
};
enum reaction_s : unsigned char {
	Undifferent, Friendly, Helpful, Unfriendly, Hostile,
};
struct creature;
struct feature_info;
typedef void(*featureproc)(const feature_info& e, creature& player, bool interactive);
struct variant {
	variant_s					type;
	union {
		race_s					race;
		class_s					classv;
		feat_s					feat;
		state_s					state;
		skill_s					skill;
		item_s					item;
		language_s				language;
		pack_s					pack;
		unsigned char			number;
	};
	constexpr variant() : type(NoVariant), number(0) {}
	constexpr variant(race_s v) : type(Race), race(v) {}
	constexpr variant(class_s v) : type(Class), classv(v) {}
	constexpr variant(item_s v) : type(Item), item(v) {}
	constexpr variant(language_s v) : type(Language), language(v) {}
	constexpr variant(feat_s v) : type(Feat), feat(v) {}
	constexpr variant(pack_s v) : type(Pack), pack(v) {}
	constexpr variant(state_s v) : type(State), state(v) {}
	constexpr variant(skill_s v) : type(Skill), skill(v) {}
	constexpr variant(variant_s t, unsigned char v) : type(t), number(v) {}
	constexpr explicit variant(int v) : type(variant_s(v>>8)), number(v & 0xFF) {}
	constexpr operator short unsigned() const { return (type << 8) | number; }
};
struct damage_type_info {
	const char*					id;
	const char*					name;
	const char*					attack;
};
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
struct pack_info {
	const char*					id;
	const char*					name;
	variant						elements[8];
};
struct background_info {
	const char*					id;
	const char*					name;
	skill_s						skills[2];
	char						extra_languages[2];
	item_s						equipment[4];
	variant						feats[4];
	int							gp;
};
typedef variant equipment[3][4];
struct class_info {
	const char*					id;
	const char*					name;
	char						hd, start_skills;
	adat<feat_s, 12>			traits;
	char						abilities[6];
	adat<variant, 12>			skills;
	aref<equipment>				equipment;
};
struct dice {
	unsigned char				c, d;
	char						b;
	damage_type_s				type;
	ability_s					save;
	save_s						save_type;
	int							roll(int reroll = 0) const;
};
struct item {
	item_s						type;
	item() = default;
	item(item_s type) : type(type) {}
	operator item_s() const { return type; }
	const dice&					getattack() const;
	int							getac() const;
	int							getdex() const { return 0; }
	const char*					getnameby(char* result, const char* result_maximum) const;
	const char*					getnameof(char* result, const char* result_maximum) const;
	bool						is(item_feat_s id) const;
	bool						is(feat_s id) const;
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
struct roll_info {
	explicit operator bool() const;
	char						rolled, bonus, result, dc;
	void						set(roll_s type);
	roll_s						get() const;
private:
	bool						advantage;
	bool						disadvantage;
};
struct attack_info : dice, roll_info {
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
	dice						attack;
	armor_info					armor;
	unsigned char				count;
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
	variant*					add(variant* result, const variant* result_maximum, variant it) const;
	void						apply(const aref<variant>& elements, const char* title, int count, bool interactive);
	void						apply(variant v1, variant v2, const char* title, int count, bool interactive);
	void						apply(background_s id, bool interactive);
	void						apply(class_s id, bool interactive);
	void						apply(class_s id, int level, bool interactive);
	void						apply(race_s id, bool interactive);
	void						attack(wear_s slot, creature& enemy) const;
	void						clear();
	static void					choose_ability(char* result, bool interactive);
	item_s						choose_absent_item(feat_s feat, const char* title, bool interactive) const;
	static background_s			choose_background(bool interactive);
	static class_s				choose_class(bool interactive);
	static domain_s				choose_domain(bool interactive);
	void						choose_equipment(class_s type, bool interactive);
	static gender_s				choose_gender(bool interactive);
	static race_s				choose_race(bool interactive);
	static race_s				choose_subrace(race_s race, bool interactive);
	void						damage(int value, damage_type_s type, bool interactive);
	static creature*			generate(bool interactive);
	int							get(ability_s id) const { return getr(id) / 2 - 5; }
	void						get(attack_info& e, wear_s slot) const;
	void						get(attack_info& e, wear_s slot, const creature& enemy) const;
	int							getac() const;
	int							getlevel() const;
	int							gethp() const { return hp; }
	int							gethpmax() const;
	const char*					getname() const;
	int							getproficiency() const;
	int							getr(ability_s id) const { return ability[id]; }
	race_s						getrace() const;
	bool						is(feat_s id) const { return (feats[id >> 5] & (1 << (id & 0x1F))) != 0; }
	bool						is(language_s id) const { return (languages & (1 << id)) != 0; }
	bool						is(skill_s id) const { return (skills & (1 << id)) != 0; }
	bool						is(spell_s id) const { return (spells[id >> 5] & (1 << (id & 0x1F))) != 0; }
	bool						isallow(variant it) const;
	bool						isproficient(item_s type) const;
	bool						has(item_s id) const;
	static void					place_ability(char* result, char* ability, bool interactive);
	static void					random_ability(char* result);
	void						remove(feat_s id) { feats[id >> 5] &= ~(1 << (id & 0x1F)); }
	int							roll() const;
	int							roll(roll_s type) const;
	void						roll(roll_info& result, bool interactive) const;
	void						set(feat_s id) { feats[id >> 5] |= 1 << (id & 0x1F); }
	void						set(language_s id) { languages |= 1 << id; }
	void						set(skill_s id) { skills |= 1 << id; }
	void						set(spell_s id) { spells[id >> 5] |= 1 << (id & 0x1F); }
	void						set(domain_s value) { domain = value; }
	void						set(variant it);
private:
	gender_s					gender;
	race_s						race;
	background_s				background;
	domain_s					domain;
	monster_s					monster;
	short						hp, hp_temporary, hp_rolled;
	unsigned					skills, languages;
	char						ability[Charisma + 1];
	unsigned					feats[1 + LastFeat / 32];
	unsigned					spells[1 + LastSpell / 32];
	unsigned char				slots[LastSlot + 1];
	unsigned char				classes[Wizard + 1];
	item						wears[LastWear + 1];
	char						fame[fraction_max];
	//
	void						choose_languages(class_s type, bool interactive);
	void						choose_skills(class_s type, bool interactive);
	void						show_ability();
};
struct fraction {
	const char*					id;
	const char*					name;
	reaction_s					reaction[fraction_max];
};
extern class_info				class_data[];
extern damage_type_info			damage_type_data[];
extern item_info				item_data[];
extern pack_info				pack_data[];
extern race_info				race_data[];
extern fraction					fraction_data[fraction_max];