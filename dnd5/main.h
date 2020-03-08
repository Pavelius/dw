#include "crt.h"
#include "logs.h"

#pragma once

using namespace logs;

const unsigned СP = 1;
const unsigned SP = 10;
const unsigned GP = 100;
const unsigned fraction_max = 12;

enum ability_s : unsigned char {
	Strenght, Dexterity, Constitution, Intellegence, Wisdow, Charisma,
};
enum component_s : unsigned char {
	V, S, M
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
	GamingProficiency, RidingProficiency,
	DisguiseKitProficiency, ForgeryKitProficiency, HerbalismKitProficiency, NavigatorToolsProficiency, PoisonerKitProficiency, TheifToolsProficiency,
	// Спас-Броски
	SaveStrenght, SaveDexterity, SaveConstitution, SaveIntellegence, SaveWisdow, SaveCharisma,
	// Расовые способности
	Brave, Darkvision, DwarvenResilience, DwarvenToughness, FeyAncestry,
	Lucky, MaskOfTheWild, NaturallyStealthy, Stonecunning, TranceInsteadSleep,
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
	// Короткие эффекты
	Dying, Guided, Resisted, Slowed10feet,
	LastFeat = Slowed10feet,
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
	ArtisanToolsProficiency,
	LastPack = ArtisanToolsProficiency
};
enum save_s : unsigned char {
	NoSave, Save, Half, Attack,
};
enum item_feat_s : unsigned char {
	NoItemFeat,
	Finesse, Heavy, Loading, Reach, Thrown, TwoHanded, Versatile,
};
enum damage_type_s : unsigned char {
	Bludgeon, Slashing, Pierce,
	Acid, Cold, Fire, Force, Lightning, Necrotic, Poison, Psychic, Radiant, Thunder,
	Healing,
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
	Self,
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
	FirstSpell = AcidSplash, LastSpell = ShieldOfFaith,
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
enum reaction_s : unsigned char {
	Undifferent, Friendly, Helpful, Unfriendly, Hostile,
};
enum action_s : unsigned char {
	CastSpell, ChangeWeapon, UseItem,
};
enum variant_s : unsigned char {
	NoVariant,
	Class, Feat, CombatAction, Item, Language, Pack, Race, Skill, Spell, State, Wear,
};
class creature;
typedef void(*featureproc)(const struct featurei& e, creature& player, bool interactive);
struct variant {
	variant_s					type;
	unsigned char				value;
	constexpr variant() : type(NoVariant), value(0) {}
	constexpr variant(race_s v) : type(Race), value(v) {}
	constexpr variant(class_s v) : type(Class), value(v) {}
	constexpr variant(item_s v) : type(Item), value(v) {}
	constexpr variant(language_s v) : type(Language), value(v) {}
	constexpr variant(feat_s v) : type(Feat), value(v) {}
	constexpr variant(pack_s v) : type(Pack), value(v) {}
	constexpr variant(state_s v) : type(State), value(v) {}
	constexpr variant(skill_s v) : type(Skill), value(v) {}
	constexpr variant(action_s v) : type(CombatAction), value(v) {}
	constexpr variant(spell_s v) : type(Spell), value(v) {}
	constexpr variant(wear_s v) : type(Wear), value(v) {}
	constexpr variant(variant_s t, unsigned char v) : type(t), value(v) {}
	constexpr explicit variant(int v) : type(variant_s(v>>8)), value(v & 0xFF) {}
	constexpr operator short unsigned() const { return (type << 8) | value; }
	const char*					getinfo() const;
};
struct damage_typei {
	const char*					id;
	const char*					name;
	const char*					damage_action;
};
struct domain_info {
	const char*					id;
	const char*					name;
};
struct genderi {
	const char*					id;
	const char*					name;
};
struct racei {
	race_s						basic;
	const char*					id;
	const char*					name;
	const char*					text;
	char						abilities[Charisma + 1];
	char						speed;
	size_s						size;
	feat_s						traits[4];
	adat<language_s, 2>			languages;
	char						extra_languages;
	char						extra_cantrip;
};
struct packi {
	const char*					id;
	const char*					name;
	variant						elements[24];
};
struct backgroundi {
	const char*					id;
	const char*					name;
	skill_s						skills[2];
	char						extra_languages;
	variant						proficient[2];
	item_s						equipment[4];
	int							gp;
};
struct feati {
	const char*					id;
	const char*					name;
	const char*					description;
	slot_s						slot;
};
typedef variant equipment[3][4];
struct classi {
	const char*					id;
	const char*					name;
	char						hd, start_skills;
	adat<feat_s, 12>			traits;
	char						abilities[6];
	adat<variant, 12>			skills;
	aref<equipment>				equipment;
};
struct dice {
	char						c, d, b;
	damage_type_s				type;
	ability_s					save;
	save_s						save_type;
	explicit operator bool() const { return c != 0; }
	int							roll(int reroll = 0) const;
};
struct armori {
	char						ac;
	char						dex;
	char						str;
	skill_s						disadvantage;
};
struct itemi {
	const char*					id;
	const char*					name;
	unsigned					cost;
	unsigned					weight;
	wear_s						wears[2];
	feat_s						proficiency[4];
	item_feat_s					feats[3];
	dice						attack;
	armori						armor;
	unsigned char				count;
};
struct language_typei {
	const char*					id;
	const char*					name;
};
struct item {
	item_s						type;
	item() = default;
	item(item_s type) : type(type) {}
	operator item_s() const { return type; }
	const dice&					getattack() const;
	int							getac() const;
	int							getcost() const;
	int							getdex() const { return 0; }
	void						addname(stringbuilder& sb) const;
	void						addnameby(stringbuilder& sb) const;
	void						addnamewh(stringbuilder& sb) const;
	const char*					getnameof(char* result, const char* result_maximum) const;
	const itemi&				getei() const { return bsmeta<itemi>::elements[type]; }
	bool						is(item_feat_s id) const;
	bool						is(feat_s id) const;
	bool						is(wear_s id) const;
	bool						islight() const;
	bool						ismelee() const { return is(MeleeWeapon); }
	bool						isranged() const { return is(RangedWeapon); }
};
struct rolli {
	constexpr rolli() : rolled(0), bonus(0), result(0), dc(0), advantage(false), disadvantage(false) {}
	explicit operator bool() const;
	char						rolled, bonus, result, dc;
	bool						issuccess() const { return rolled >= dc; }
	roll_s						get() const;
	void						set(roll_s type);
private:
	bool						advantage;
	bool						disadvantage;
};
struct abilityi {
	const char*					id;
	const char*					name;
};
struct skilli {
	const char*					id;
	const char*					name;
};
struct attacki : dice, rolli {
	item*						weapon;
	char						critical;
};
struct languagei {
	const char*					id;
	const char*					name;
	language_type_s				type;
};
extern unsigned					current_round;
struct effect {
	spell_s						type;
	creature*					caster;
	creature*					target;
	unsigned					duration;
	explicit operator bool() { return duration >= current_round; }
};
struct spelli {
	const char*					id;
	const char*					name;
	char						level;
	cflags<component_s>			components;
	school_s					school;
	duration_s					cast;
	range_s						range;
	duration_s					duration;
	dice						damage;
	variant						value;
	bool(*proc)(creature& player, creature& opponent, spelli& e, bool interactive, bool run);
	bool						isbattle() const { return damage.c != 0; }
};
struct alignmenti {
	const char*					id;
	const char*					name;
};
struct monsteri {
	const char*					id;
	const char*					name;
	race_s						race;
	gender_s					gender;
	char						cr[2];
	char						hd;
	char						ability[6];
	feat_s						feats[8];
	item_s						items[4];
	language_s					languages[4];
};
class creature {
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
	unsigned					spells_known[1 + LastSpell / 32];
	unsigned char				slots[LastSlot + 1];
	unsigned char				classes[Wizard + 1];
	item						wears[LastWear + 1];
	char						fame[fraction_max];
	char						initiative;
	reaction_s					reaction;
	int							coins;
	char						death_save[2];
	//
	void						choose_languages(class_s type, bool interactive);
	void						choose_skills(class_s type, bool interactive);
	void						show_ability();
public:
	void* operator new(unsigned size);
	void operator delete (void* data);
	explicit operator bool() const { return ability[0] != 0; }
	creature() = default;
	creature(race_s race, gender_s gender, class_s type, background_s background, char* ability, bool interactive);
	creature(monster_s id, reaction_s reaction = Hostile);
	void						act(const char* format, ...) const;
	void						action(variant id, creature& enemy);
	bool						add(const item it);
	variant*					add(variant* result, const variant* result_maximum, variant it) const;
	void						add(variant id, const char* name, const creature* enemy) const;
	static void					addcoins(stringbuilder& sb, int value);
	void						apply(const aref<variant>& elements, const char* title, int count, bool interactive);
	void						apply(variant v1, variant v2, const char* title, int count, bool interactive);
	void						apply(variant id, int level, bool interactive);
	void						apply(background_s id, bool interactive);
	void						apply(class_s id, bool interactive);
	void						apply(race_s id, bool interactive);
	void						attack(wear_s slot, creature& enemy);
	void						buy(aref<item> items, bool interactive);
	void						buyweapon(int level, bool interactive);
	bool						cast(spell_s id, creature& enemy, bool interactive, bool run);
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
	void						get(attacki& e, wear_s slot) const;
	void						get(attacki& e, wear_s slot, const creature& enemy) const;
	int							get(slot_s id) const { return slots[id]; }
	int							getac() const;
	int							getcoins() const { return coins; }
	creature*					getenemy(aref<creature*> elements) const;
	int							getinitiative() const { return initiative; }
	int							getlevel() const;
	static int					getlevel(spell_s id);
	int							gethp() const { return hp; }
	int							gethpmax() const;
	const char*					getname() const;
	int							getproficiency() const;
	int							getr(ability_s id) const { return ability[id]; }
	race_s						getrace() const;
	reaction_s					getreaction() const { return reaction; }
	int							getslots(int level) const;
	int							getspellcaster() const;
	int							getspellprepared() const;
	ability_s					getspellability(spell_s id) const;
	bool						has(item_s id) const;
	bool						is(feat_s id) const { return (feats[id >> 5] & (1 << (id & 0x1F))) != 0; }
	bool						is(language_s id) const { return (languages & (1 << id)) != 0; }
	bool						is(skill_s id) const { return (skills & (1 << id)) != 0; }
	bool						is(spell_s id) const { return (spells[id >> 5] & (1 << (id & 0x1F))) != 0; }
	bool						is(variant id) const;
	bool						isactive(spell_s id) const;
	bool						isallow(variant it) const;
	bool						isenemy(const creature* p) const;
	bool						isknown(spell_s id) const { return (spells_known[id >> 5] & (1 << (id & 0x1F))) != 0; }
	bool						isplayer() const;
	bool						isproficient(item_s type) const;
	bool						israndom() const { return monster != NoMonster; }
	bool						isready() const { return gethp() > 0; }
	void						make_death_save();
	static void					place_ability(char* result, char* ability, bool interactive);
	void						prepare(bool interactive);
	static void					random_ability(char* result);
	void						remove(feat_s id) { feats[id >> 5] &= ~(1 << (id & 0x1F)); }
	void						rest(bool long_rest);
	int							roll() const;
	int							roll(roll_s type) const;
	void						roll(rolli& result, bool interactive);
	void						set(feat_s id) { feats[id >> 5] |= 1 << (id & 0x1F); }
	void						set(language_s id) { languages |= 1 << id; }
	void						set(skill_s id) { skills |= 1 << id; }
	void						set(spell_s id) { spells[id >> 5] |= 1 << (id & 0x1F); }
	void						set(domain_s value) { domain = value; }
	void						set(variant it);
	void						set(reaction_s value) { reaction = value; }
	void						set(slot_s id, int value) { slots[id] = value; }
	void						set(spell_s id, unsigned duration);
	void						setcoins(int value) { coins = value; }
	void						setinitiative();
	void						setknown(spell_s id) { spells_known[id >> 5] |= 1 << (id & 0x1F); }
};
struct fraction {
	const char*					id;
	const char*					name;
	reaction_s					reaction[fraction_max];
};
struct scene {
	~scene() { clear(); }
	adat<creature*, 32>			creatures;
	void						combat(bool interactive);
	void						clear();
	bool						isenemy() const;
private:
	void						rollinititative();
};
template<> const char* getstr<variant>(variant e);
DECLENUM(ability);
DECLENUM(background);
DECLENUM(class);
DECLENUM(feat);
DECLENUM(gender);
DECLENUM(item);
DECLENUM(language);
DECLENUM(language_type);
DECLENUM(monster);
DECLENUM(pack);
DECLENUM(race);
DECLENUM(skill);
DECLENUM(spell);