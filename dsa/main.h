#include "crt.h"
#include "logs.h"

#pragma once

const unsigned short Blocked = 0xFFFF;

using namespace logs;

enum ability_s : unsigned char {
	Courage, Wisdom, Charisma, Dexterity, Strenght,
};
enum character_s : unsigned char {
	Adventurer, Warrior, Dwarf, Elf, Magician,
};
enum parameter_s : unsigned char {
	LE, AP, AV, PV, PVC, RS, Level,
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
};
enum state_s : unsigned char {
	Scared, Angry, Dirty, Shaked, Exhaused,
	Fleeing,
};
enum parameter_view_s : unsigned char {
	ViewStandart, ViewCurrentAndMaximum,
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
enum variant_s : unsigned char {
	NoVariant,
	Ability, Character, Item, Monster, Tag, Wear,
};
enum reaction_s : unsigned char {
	Friendly, Hostile,
};
struct variant {
	variant_s				type;
	unsigned char			value;
	constexpr variant() : type(NoVariant), value(0) {}
	constexpr variant(ability_s v) : type(Ability), value(v) {}
	constexpr variant(character_s v) : type(Character), value(v) {}
	constexpr variant(item_s v) : type(Item), value(v) {}
	constexpr variant(monster_s v) : type(Monster), value(v) {}
	constexpr variant(tag_s v) : type(Tag), value(v) {}
	constexpr variant(wear_s v) : type(Wear), value(v) {}
	constexpr operator bool() const { return type != NoVariant; }
};
typedef short				parametera[Level + 1];
typedef char				abilitya[Strenght + 1];
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
};
struct characteri {
	const char*				id;
	const char*				name;
	abilitya				abilities;
	parametera				parameters;
};
struct genderi {
	const char*				id;
	const char*				name;
};
struct dicei {
	char					c, d, b, m;
	int						roll() const;
};
struct parameteri {
	const char*				id;
	const char*				name;
	const char*				short_name;
	parameter_view_s		view;
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
		int					roll() const { return bsmeta<dicei>::elements[dice].roll(); }
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
	int						get(parameter_s v) const;
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
};
class creature : public nameable {
	abilitya				abilities, abilities_maximum;
	parametera				parameters, parameters_maximum;
	cflags<state_s>			states;
	item					wears[LastWear + 1];
	void					apply(character_s i);
	void					choose_ability(bool interactive);
	void					choose_character(bool interactive);
	void					choose_gender(bool interactive);
	void					place_ability(bool interactive, char* temp);
	void					print_ability(stringbuilder& sb) const;
	void					random_ability();
	dice_s					unarmed;
	reaction_s				reaction;
	short unsigned			fighting;
public:
	typedef bool(*procis)(const creature&);
	creature() { clear(); }
	void					attack(creature& enemy);
	void					clear();
	void					create(bool interactive);
	void					create(character_s character, gender_s gender);
	void					create(monster_s v);
	void					damage(int value);
	bool					equip(const item& it);
	bool					is(state_s i) const { return states.is(i); }
	bool					is(wear_s i) const { return wears[i].operator bool(); }
	bool					isenemy(const creature& e) const { return reaction != e.getreaction(); }
	bool					isfighting() const { return fighting != Blocked; }
	bool					isplayer() const { return type == Character && reaction==Friendly; }
	bool					isready() const;
	int						get(ability_s i) const;
	int						get(parameter_s i) const;
	dice_s					getdamage() const;
	creature*				getfighting() const;
	short unsigned			getid() const;
	int						getmaximum(parameter_s i) const { return parameters_maximum[i]; }
	reaction_s				getreaction() const { return reaction; }
	static reaction_s		getopposed(reaction_s v);
	bool					roll(int value) const;
	void					set(state_s i) { states.add(i); }
	void					set(parameter_s i, int v) { parameters[i] = v; }
	void					set(reaction_s i) { reaction = i; }
	void					setfighting(creature* p);
	void					sheet();
	void					status(stringbuilder& sb) const;
	void					testfighting();
};
struct creaturea : public adat<short unsigned, 22> {
	creaturea() = default;
	creaturea(const creaturea& e) { memcpy(this, &e, sizeof(e)); }
	void					exclude(const creature* v);
	creature*				choose(const char* format, ...) const;
	static creature&		get(short unsigned id) { return bsmeta<creature>::elements[id]; }
	bool					is(creature::procis proc) const;
	void					match(reaction_s r);
	void					match(creature::procis proc);
};
class scene {
	creaturea				creatures;
	void					makeorder();
	bool					charge(creature& e, int count);
public:
	struct action {
		typedef bool(*proc)(scene& sc, creature& player, bool run);
		proc				act;
		const char*			text;
	};
	void					add(creature& c1);
	void					add(monster_s i, reaction_s r);
	void					addplayers();
	void					ask(creature& player, const aref<action>& actions);
	void					charge(creature& player);
	void					choose(creature& player);
	void					fight();
	creature*				get(reaction_s r) const;
	int						getfighting(const creature& e) const;
	creature&				getcreature(short unsigned id) const;
	creaturea&				getcreatures() { return creatures; }
	creature*				getplayer() const { return get(Friendly); }
	bool					ishostile() const;
	bool					iswounded(reaction_s r) const;
};