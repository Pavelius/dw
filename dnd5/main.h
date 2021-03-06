#include "crt.h"
#include "logs.h"

#pragma once

using namespace logs;

//const unsigned �P = 1;
const unsigned SP = 10;
const unsigned GP = 100;
const unsigned fraction_max = 12;
const unsigned Feet5 = 1;

enum ability_s : unsigned char {
	Strenght, Dexterity, Constitution, Intellegence, Wisdow, Charisma,
};
enum movement_s : unsigned char {
	FootSpeed, BurrowSpeed,
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
	// ����-������
	SaveStrenght, SaveDexterity, SaveConstitution, SaveIntellegence, SaveWisdow, SaveCharisma,
	// ������� �����������
	Brave, Darkvision, DwarvenResilience, DwarvenToughness, FeyAncestry,
	Lucky, MaskOfTheWild, NaturallyStealthy, Stonecunning, TranceInsteadSleep,
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
	Dying, Guided, Resisted, Slowed10feet,
	LastFeat = Slowed10feet,
};
enum skill_s : unsigned char {
	NoSkill,
	Athletics, Acrobatics, SleightOfHands, Stealth,
	Arcana, History, Investigation, Nature, Religion,
	AnimalHandling, Insight, Medicine, Perception, Survival,
	Deception, Intimidation, Performance, Persuasion,
	LastSkill = Persuasion,
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
	Cleric, Fighter, Rogue, Wizard,
};
enum alignment_s : unsigned char {
	LawfulGood, NeutralGood, ChaoticGood,
	LawfulNeutral, TrueNeutral, ChaoticNeutral,
	LawfulEvil, NeutralEvil, ChaoticEvil,
};
enum item_s : unsigned short {
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
	Bag, Sphere,
	Scroll0, Scroll1, Scroll2, Scroll3, Scroll4, Scroll5, Scroll6, Scroll7, Scroll8, Scroll9,
	Potion,
	//
	LastItem = Potion,
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
	Finesse, Heavy, Loading, Ranged, Reach, Thrown, TwoHanded, Versatile,
	LastItemFeat = Versatile
};
enum damage_type_s : unsigned char {
	Bludgeon, Slashing, Pierce,
	Acid, Cold, Fire, Force, Lightning, Necrotic, Poison, Psychic, Radiant, Thunder,
	Healing,
};
enum wear_s : unsigned char {
	Equipment,
	UnarmedAttack, Drinkable, Readable, LastEquipment = Equipment + 16,
	Head, Neck, Armor, MeleeWeapon, OffhandWeapon, LeftFinger, RightFinger, RangedWeapon, Elbow, Gridle, Legs, Ammunition,
	FirstWear = Head, LastWear = Ammunition
};
enum state_s : unsigned char {
	Disengaged, Dodged,
	//
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
	// Spells level 2
	SpiderClimb,
	FirstSpell = AcidSplash, LastSpell = SpiderClimb,
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
	MakeAttack, MakeMove, ChangeWeapon, Dash, Dodge, Disengage, Hide, Help, Search, StandUp,
};
enum target_s : unsigned char {
	You, HostileCreature, FriendlyCreature, Posable, WearItem, PossesedItem,
};
enum variant_s : unsigned char {
	NoVariant,
	Ability, Class, Creature, CombatAction, Feat, Item, Monster, Language, Pack, Race, Skill, Spell, State, Wear,
};
enum rarity_s : unsigned char {
	Common, Uncommon, Rare, VeryRare, Unique,
};
class creature;
typedef flagable<LastFeat>		feata;
typedef flagable<LastSpell>		spella;
typedef flagable<LastSkill>		skilla;
typedef flagable<LastItemFeat>	featia;
typedef flagable<Unconscious>	statea;
typedef char					indext;
struct variant {
	variant_s					type;
	unsigned char				value;
	constexpr variant() : type(NoVariant), value(0) {}
	constexpr variant(ability_s v) : type(Ability), value(v) {}
	constexpr variant(race_s v) : type(Race), value(v) {}
	constexpr variant(class_s v) : type(Class), value(v) {}
	constexpr variant(feat_s v) : type(Feat), value(v) {}
	constexpr variant(item_s v) : type(Item), value(v) {}
	constexpr variant(language_s v) : type(Language), value(v) {}
	constexpr variant(monster_s v) : type(Monster), value(v) {}
	constexpr variant(pack_s v) : type(Pack), value(v) {}
	constexpr variant(state_s v) : type(State), value(v) {}
	constexpr variant(skill_s v) : type(Skill), value(v) {}
	constexpr variant(action_s v) : type(CombatAction), value(v) {}
	constexpr variant(spell_s v) : type(Spell), value(v) {}
	constexpr variant(wear_s v) : type(Wear), value(v) {}
	constexpr variant(variant_s t, unsigned char v) : type(t), value(v) {}
	constexpr explicit variant(short unsigned v) : type(variant_s(v>>8)), value(v & 0xFF) {}
	constexpr operator short unsigned() const { return (type << 8) | value; }
	const char*					getinfo() const;
	creature*					getcreature() const;
};
struct varianta : adat<variant, 32> {
	variant						choose(bool interactive, indext start, const char* format, ...) const;
	void						match(creature& player, action_s v, bool remove);
	void						match(reaction_s r, bool remove);
	void						select(const varianta& source, creature& player, target_s id);
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
	feata						traits;
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
struct magici {
	variant						id;
	rarity_s					rarity;
	const char*					name;
	char						level;
	char						bonus;
};
struct itemi {
	const char*					id;
	const char*					name;
	unsigned					cost;
	unsigned					weight;
	wear_s						wears;
	feata						proficiency;
	featia						feats;
	dice						attack;
	armori						armor;
	aref<magici>				effect;
};
struct language_typei {
	const char*					id;
	const char*					name;
};
class item {
	item_s						type;
	unsigned char				charges : 6;
	unsigned char				cursed : 1;
	unsigned char				identyfied : 1;
	unsigned char				effect;
	unsigned char				count;
public:
	item() = default;
	constexpr item(item_s type) : type(type), charges(0), cursed(0), identyfied(0), effect(0), count(0) {}
	constexpr operator item_s() const { return type; }
	void						addname(stringbuilder& sb) const;
	void						addnameby(stringbuilder& sb) const;
	void						addnamewh(stringbuilder& sb) const;
	void						clear();
	void						consume();
	const dice&					getattack() const;
	int							getac() const { return getei().armor.ac; }
	int							getcost() const;
	constexpr int				getcount() const { return count + 1; }
	int							getdex() const { return 0; }
	variant						geteffect() const;
	const itemi&				getei() const { return bsmeta<itemi>::elements[type]; }
	constexpr bool				is(item_s v) const { return type == v; }
	bool						is(item_feat_s id) const;
	bool						is(feat_s v) const;
	bool						is(wear_s v) const;
	bool						ischargeable() const { return false; }
	bool						iscountable() const { return false; }
	bool						islight() const;
	bool						ismelee() const { return is(MeleeWeapon); }
	bool						isranged() const { return is(RangedWeapon); }
	void						setcount(int v);
};
struct rolli {
	char						advantages, bonus, rolled, result, dc;
	constexpr rolli() : advantages(0), bonus(0), rolled(0), result(0), dc(0) {}
	bool						issuccess() const { return result >= dc; }
	int							random() const;
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
struct actioni {
	const char*					id;
	const char*					name;
	target_s					target;
	const char*					choose_target;
	action_s					getid() const;
};
class nameable : public variant {
	gender_s					gender;
public:
	constexpr nameable() : gender(Male) {}
	void						actv(stringbuilder& sb, const char* format, const char* format_param) const;
	void						act(const char* format, ...) const { actv(sb, format, xva_start(format)); }
	constexpr gender_s			getgender() const { return gender; }
	const char*					getname() const;
	race_s						getrace() const;
	race_s						getsubrace() const;
	void						setgender(gender_s v) { gender = v; }
};
class posable {
	indext						position;
public:
	constexpr posable() : position(0) {}
	int							getdistance(const posable& e) const { return iabs(position - e.position); }
	static const char*			getdistance(char* temp, int value);
	indext						getposition() const { return position; }
	void						setposition(indext v) { position = v; }
};
struct rewardi {
	char						chance;
	item_s						item;
	variant						effect;
	char						level;
	char						magic;
};
struct trepacki {
	char						chance;
	aref<rewardi>				treasures;
	dice						count;
};
class creature : public nameable, public posable {
	background_s				background;
	domain_s					domain;
	short						hp, hp_temporary, hp_rolled;
	unsigned					languages;
	char						ability[Charisma + 1];
	skilla						skills;
	statea						states;
	feata						feats;
	spella						spells;
	spella						spells_known;
	unsigned char				slots[LastSlot + 1];
	unsigned char				classes[Wizard + 1];
	unsigned char				movement[BurrowSpeed];
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
	creature() = default;
	void						action(variant id, creature& enemy);
	bool						add(const item it);
	void						add(spell_s id, unsigned rounds);
	variant*					add(variant* result, const variant* result_maximum, variant it) const;
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
	void						create(monster_s id, reaction_s reaction = Hostile);
	void						create(race_s race, gender_s gender, class_s type, background_s background, char* ability, bool interactive);
	void						create(bool interactive);
	void						damage(int value, damage_type_s type, bool interactive);
	int							get(ability_s id) const { return getr(id) / 2 - 5; }
	void						get(attacki& e, wear_s slot) const;
	void						get(attacki& e, wear_s slot, const creature& enemy) const;
	unsigned char				get(movement_s v) const { return movement[v]; }
	int							get(slot_s id) const { return slots[id]; }
	int							getac() const;
	int							getcoins() const { return coins; }
	int							getinitiative() const { return initiative; }
	variant						getid() const;
	int							getlevel() const;
	static int					getlevel(spell_s id);
	int							getmove() const { return 6 * Feet5; }
	reaction_s					getfriendly() const;
	reaction_s					gethostile() const;
	int							gethp() const { return hp; }
	int							gethpmax() const;
	int							getproficiency() const;
	int							getr(ability_s id) const { return ability[id]; }
	int							getreach() const { return 1 * Feet5; }
	reaction_s					getreaction() const { return reaction; }
	int							getslots(int level) const;
	int							getspellcaster() const;
	int							getspellprepared() const;
	ability_s					getspellability(spell_s v) const;
	variant						getvar() const;
	bool						has(item_s v) const;
	bool						is(feat_s v) const { return feats.is(v); }
	bool						is(language_s v) const { return (languages & (1 << v)) != 0; }
	bool						is(reaction_s v) const { return reaction == v; }
	bool						is(skill_s v) const { return skills.is(v); }
	bool						is(spell_s v) const { return spells.is(v); }
	bool						is(state_s v) const { return states.is(v); }
	bool						is(variant v) const;
	bool						isactive(spell_s id) const;
	bool						isactive(variant v) const;
	bool						isallow(variant it) const;
	bool						isblocked() const;
	bool						isenemy(const creature* p) const;
	bool						isknown(spell_s v) const { return spells_known.is(v); }
	bool						isplayer() const { return is(Helpful); }
	static bool					ispresent(reaction_s v);
	bool						isproficient(item_s type) const;
	bool						isreach(const creature& e, int distance) const { return iabs(getposition() - e.getposition()) < distance; }
	bool						isreach(reaction_s reaction, int distance) const;
	bool						isready() const { return gethp() > 0; }
	void						make_death_save();
	void						moveto(indext i);
	static void					place_ability(char* result, char* ability, bool interactive);
	void						prepare(bool interactive);
	static void					random_ability(char* result);
	void						remove(feat_s v) { feats.remove(v); }
	void						remove(state_s v) { states.remove(v); }
	bool						remove(variant id, bool run);
	void						rest(bool long_rest);
	int							roll() const;
	int							roll(int advantages) const;
	void						roll(rolli& result, bool interactive);
	void						set(feat_s v) { feats.set(v); }
	void						set(language_s id) { languages |= 1 << id; }
	void						set(movement_s id, unsigned char v) { movement[id] = v; }
	void						set(skill_s v) { skills.set(v); }
	void						set(spell_s v) { spells.set(v); }
	void						set(domain_s value) { domain = value; }
	void						set(variant it);
	void						set(reaction_s value) { reaction = value; }
	void						set(slot_s id, int value) { slots[id] = value; }
	bool						set(variant id, bool run);
	void						setcoins(int value) { coins = value; }
	void						setinitiative();
	void						setknown(spell_s v) { spells_known.set(v); }
	bool						use(spell_s id, creature& opponent, int level, int modifier, bool run);
	bool						use(action_s id, creature& target, bool run);
	bool						use(action_s id, varianta& source, bool run);
};
struct fraction {
	const char*					id;
	const char*					name;
	reaction_s					reaction[fraction_max];
};
class scene {
	varianta					creatures;
	void						rollinititative();
public:
	~scene() { clear(); }
	void						add(creature& e) { creatures.add(e.getid()); }
	void						clear();
	void						combat(bool interactive);
	bool						isenemy() const;
};
class gamei : scene {
	unsigned					rounds;
public:
	unsigned					getround();
};
extern gamei					game;
inline int						d100() { return rand() % 100; }
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