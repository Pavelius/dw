#include "crt.h"
#include "logs.h"

#pragma once

const unsigned short Blocked = 0xFFFF;

using namespace logs;

enum ability_s : unsigned char {
	Courage, Wisdom, Charisma, Dexterity, Strenght,
	AG, HA, RA, GG, TO,
	LE, AE, AV, PV,
	PVC, RS, Level,
};
enum character_s : unsigned char {
	Adventurer, Warrior, Dwarf, Elf, Magician,
};
enum item_s : unsigned char {
	NoItem,
	Knife, Dagger, HeavyDagger, Rapier, Staff, Club,
	Mace, Saber, AxeBattle, Sword, SwordTwoHanded,
	Bow, Crossbow,
	Arrows, Bolts,
	ClothingSilk, ClothingRobe, ClothingHard, ClothingWinter,
	ArmourLeather, ArmourChain, ArmourScale, ArmourPlate,
};
enum tag_s : unsigned char {
	Ranged, Throwing, TwoHanded,
	Dungeon, Forest, Plain, Street, Village, Building,
};
enum state_s : unsigned char {
	Scared, Angry, Dirty, Shaked, Exhaused, Hostile,
	Fleeing,
};
enum wear_s : unsigned char {
	Weapon, Armor, Offhand,
	Backpack, LastWear = Backpack + 15,
};
enum monster_s : unsigned char {
	Ork, Goblin,
};
enum dice_s : unsigned char {
	W1m4, W1m3, W1m2, W1m1,
	W1p0, W1p1, W1p2, W1p3, W1p4,
	W2p0, W2p1, W2p2, W2p3, W2p4,
	W3p0
};
enum duration_s : unsigned {
	Minute = 12, Hour = Minute * 60, Day = Hour*24,
};
enum object_s : unsigned char {
	Altar, Barrel, Box, Chest, Heap, Hotel, Sarcophagus, Statue,
};
enum variant_s : unsigned char {
	NoVariant,
	Ability, Character, Feature, Item, Monster, State, Tag, Wear,
};
class scene;
struct variant {
	variant_s				type;
	unsigned char			value;
	constexpr variant() : type(NoVariant), value(0) {}
	constexpr variant(variant_s t, unsigned char v) : type(t), value(v) {}
	constexpr variant(ability_s v) : type(Ability), value(v) {}
	constexpr variant(character_s v) : type(Character), value(v) {}
	constexpr variant(item_s v) : type(Item), value(v) {}
	constexpr variant(monster_s v) : type(Monster), value(v) {}
	constexpr variant(state_s v) : type(State), value(v) {}
	constexpr variant(tag_s v) : type(Tag), value(v) {}
	constexpr variant(wear_s v) : type(Wear), value(v) {}
	constexpr operator bool() const { return type != NoVariant; }
};
typedef char				abilitya[Level + 1];
typedef flagable<1 + Fleeing / 8> statea;
class taga {
	flagable<1>				characters;
	flagable<1>				tags;
	flagable<1>				wears;
public:
	constexpr taga(const std::initializer_list<variant>& col) {
		for(auto v : col) {
			switch(v.type) {
			case Character: characters.set(v.value); break;
			case Tag: tags.set(v.value); break;
			case Wear: wears.set(v.value); break;
			}
		}
	}
	bool					is(character_s i) const { return characters.is(i); }
	bool					is(tag_s i) const { return tags.is(i); }
	bool					is(wear_s i) const { return wears.is(i); }
};
struct abilityi {
	const char*				id;
	const char*				name;
	const char*				short_name;
};
struct characteri {
	const char*				id;
	const char*				name;
	abilitya				abilities;
};
struct genderi {
	const char*				id;
	const char*				name;
};
struct dicei {
	char					c, d, b, m;
	int						roll() const;
	static int				roll(dice_s v) { return bsmeta<dicei>::elements[v].roll(); }
};
struct objecti {
	const char*				id;
	gender_s				gender;
	const char*				name;
	const char*				name_who_what;
};
struct environmenti {
	taga					tags;
	const char*				name_what;
	const char*				name_where;
	const char*				name_feature;
};
struct featurei {
	taga					tags;
	object_s				id;
	const char*				appear;
	const char*				examine;
};
struct monsteri {
	const char*				id;
	const char*				name;
	gender_s				gender;
	char					mu;
	char					le;
	char					at, pa;
	char					rs;
	dice_s					damage;
	char					mk;
	item_s					gear[4];
};
struct itemi {
	struct weaponi {
		char				attack, parry;
		dice_s				dice;
		int					roll() const { return dicei::roll(dice); }
	};
	struct armori {
		char				rs;
	};
	const char*				id;
	const char*				name;
	unsigned short			lenght;
	unsigned short			weight;
	unsigned short			cost;
	taga					tags;
	weaponi					weapon;
	armori					armor;
};
class item {
	item_s					type;
	const itemi&			getinfo() const { return bsmeta<itemi>::elements[type]; }
public:
	constexpr item() : type(NoItem) {}
	constexpr item(item_s type) : type(type) {}
	constexpr explicit operator bool() const { return type != NoItem; }
	int						get(ability_s v) const;
	dice_s					getdamage() const { return getinfo().weapon.dice; }
	const char*				getname() const { return getinfo().name; }
	bool					is(character_s v) const { return getinfo().tags.is(v); }
	bool					is(wear_s v) const { return getinfo().tags.is(v); }
};
typedef adat<item, 15>		itema;
class nameable : public variant {
	short unsigned			name;
protected:
	void					random_name(character_s character, gender_s gender);
public:
	void					act(const char* format, ...) const;
	void					act(const nameable& opponent, const char* format, ...) const;
	void					actv(stringbuilder& sb, const char* format, const char* format_param) const;
	void					actv(stringbuilder& sb, const nameable& opponent, const char* format, const char* format_param) const;
	gender_s				getgender() const;
	const char*				getname() const;
	void					say(const char* format, ...) const;
	void					say(const nameable& opponent, const char* format, ...) const;
};
struct boosti {
	unsigned				time;
	short unsigned			owner;
	ability_s				id;
	char					modifier;
};
class creature : public nameable {
	abilitya				abilities, abilities_maximum;
	statea					states;
	item					wears[LastWear + 1];
	void					apply(character_s i);
	dice_s					unarmed;
	short unsigned			fighting;
	//
	void					choose_ability(bool interactive);
	void					choose_character(bool interactive);
	void					choose_gender(bool interactive);
	void					place_ability(bool interactive, char* temp);
	void					post(ability_s i, int value, unsigned rounds);
	void					print_ability(stringbuilder& sb) const;
	void					random_ability();
public:
	typedef bool(*procis)(const creature&);
	creature() { clear(); }
	void					add(ability_s i, int v) { abilities[i] += v; }
	void					add(ability_s i, int v, unsigned rounds);
	void					attack(creature& enemy);
	bool					cast(int& value, int bonus, const char* text_cast);
	void					clear();
	void					create(bool interactive);
	void					create(character_s character, gender_s gender);
	void					create(monster_s v);
	void					damage(int value, bool ignore_amror);
	bool					equip(const item& it);
	bool					is(state_s i) const { return states.is(i); }
	bool					is(wear_s i) const { return wears[i].operator bool(); }
	bool					iscaster() const { return get(AE) > 0; }
	bool					isenemy(const creature& e) const { return is(Hostile) != e.is(Hostile); }
	bool					isfighting() const { return fighting != Blocked; }
	bool					isplayer() const { return type == Character && !is(Hostile); }
	bool					isready() const;
	int						get(ability_s i) const;
	dice_s					getdamage() const;
	creature*				getfighting() const;
	short unsigned			getid() const;
	int						getmaximum(ability_s i) const { return abilities_maximum[i]; }
	void					heal(int value);
	bool					roll(int value) const;
	bool					roll(ability_s i, int b) const;
	void					set(state_s i) { states.set(i); }
	void					set(ability_s i, int v) { abilities[i] = v; }
	void					setfighting(creature* p);
	void					sheet();
	void					status(stringbuilder& sb) const;
	void					testfighting();
};
struct creaturea : public adat<short unsigned, 22> {
	constexpr creaturea() : adat() {};
	creaturea(const creaturea& e) { memcpy(this, &e, sizeof(e)); }
	void					exclude(const creature& v);
	creature*				choose(const char* format, ...) const;
	void					choose(int minimum, int maximum, const char* format, ...);
	static creature&		get(short unsigned id) { return bsmeta<creature>::elements[id]; }
	bool					is(creature::procis proc) const;
	void					match(state_s r);
	void					match(creature::procis proc);
	void					remove(state_s r);
};
struct feature {
	short unsigned			id; 
	const featurei&			getinfo() const { return bsmeta<featurei>::elements[id]; }
	const objecti&			getobj() const { return bsmeta<objecti>::elements[getinfo().id]; }
	const char*				getname() const { return getobj().name; }
};
struct action {
	typedef bool(*proc)(const action& ac, scene& sc, creature& player, bool run);
	proc					act;
	const char*				text;
	variant					id;
};
class scene {
	short unsigned			environment;
	adat<feature, 4>		features;
	creaturea				creatures;
	bool					charge(creature& e, int count);
	void					makeorder();
public:
	constexpr scene() : environment(), features(), creatures() {}
	void					add(creature& e);
	void					add(monster_s i, bool hostile);
	void					addenviroment(short unsigned v) { environment = v; }
	void					addfeature(short unsigned id);
	void					addplayers();
	void					ask(creature& player, const aref<action>& actions);
	void					askmoveto();
	void					charge(creature& player);
	static bool				charsheet(const action& ac, scene& sc, creature& player, bool run);
	void					choose(creature& player, bool clear_text = false);
	void					look() const;
	void					look(const char* format, int index) const;
	void					fight();
	creature*				get(state_s r, bool exclude = true) const;
	static creature&		getcreature(short unsigned id);
	const creaturea&		getcreatures() const { return creatures; }
	const environmenti&		getenviroment() const { return bsmeta<environmenti>::elements[environment]; }
	feature&				getfeature(int i) { return features[i]; }
	unsigned				getfeaturecount() const { return features.getcount(); }
	int						getfighting(const creature& e) const;
	bool					ishostile() const;
	void					removeplayers();
	void					setenviroment(short unsigned v) { environment = v; }
};
class gamei {
	unsigned				time;
	short unsigned			player_id;
public:
	char					feature, location, location_max;
	creature&				getplayer() const { return bsmeta<creature>::elements[player_id]; }
	unsigned				getround() const { return time; }
	void					pass(unsigned v);
	void					setplayer(creature& e) { player_id = e.getid(); }
	void					update();
};
extern gamei				game;
class dungeon {
	char					depth;
	scene					locations[16];
public:
	dungeon() : depth(0), locations() {}
	void					explore();
	char					getsize() const { return depth; }
	scene&					getscene() { return locations[game.location]; }
	void					generate();
};
const char*					getsnm(ability_s id);