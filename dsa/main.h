#include "crt.h"
#include "logs.h"

#pragma once

using namespace logs;

enum ability_s : unsigned char {
	Courage, Wisdom, Charisma, Dexterity, Strenght,
};
enum character_s : unsigned char {
	Adventurer, Warrior, Dwarf, Elf, Magician,
};
enum parameter_s : unsigned char {
	LP, AP, AV, PV, Level,
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
enum variant_s : unsigned char {
	NoVariant,
	Ability, Character, Item, Monster, Wear,
};
enum state_s : unsigned char {
	Scared, Angry, Dirty, Shaked, Exhaused,
};
enum parameter_view_s : unsigned char {
	ViewStandart, ViewCurrentAndMaximum,
};
enum wear_s : unsigned char {
	Weapon, Armor, Offhand,
	Backpack, LastWear = Backpack + 15,
};
struct variant {
	variant_s				type;
	unsigned char			value;
	constexpr variant() : type(NoVariant), value(0) {}
	constexpr variant(ability_s v) : type(Ability), value(v) {}
	constexpr variant(character_s v) : type(Character), value(v) {}
	constexpr variant(item_s v) : type(Item), value(v) {}
	constexpr variant(wear_s v) : type(Wear), value(v) {}
	constexpr operator bool() const { return type != NoVariant; }
};
typedef short				parametera[Level + 1];
typedef char				abilitya[Strenght + 1];
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
struct parameteri {
	const char*				id;
	const char*				name;
	const char*				short_name;
	parameter_view_s		view;
};
struct dicew {
	char					dice;
	char					bonus;
	int						roll() const;
};
struct itemi {
	struct weaponi {
		char				attack, parry;
		dicew				damage;
	};
	struct armori {
		char				rs;
	};
	struct tagi {
		cflags<wear_s, unsigned char> wear;
		constexpr tagi() {}
		constexpr tagi(const std::initializer_list<variant>& col) { for(auto e : col) set(e); }
		void set(variant v) {
			switch(v.type) {
			case Wear: wear.add(wear_s(v.value)); break;
			}
		}
	};
	const char*				id;
	const char*				name;
	unsigned short			lenght;
	unsigned short			weight;
	unsigned short			cost;
	wear_s					wear;
	weaponi					weapon;
	armori					armor;
};
class item {
	item_s					type;
public:
	constexpr item() : type(NoItem) {}
	constexpr item(item_s type) : type(type) {}
	constexpr explicit operator bool() const { return type != NoItem; }
	const itemi&			getinfo() const { return bsmeta<itemi>::elements[type]; }
};
class nameable : public variant {
	short unsigned			name;
protected:
	void					random_name(character_s character, gender_s gender);
public:
	void					act(const char* format, ...) const;
	void					act(const nameable& opponent, const char* format, ...) const;
	void					actv(const char* format, const char* format_param) const;
	void					actv(const nameable& opponent, const char* format, const char* format_param) const;
	gender_s				getgender() const;
	const char*				getname() const;
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
public:
	creature() { memset(this, 0, sizeof(*this)); }
	void					attack(creature& enemy);
	void					create(bool interactive);
	void					create(character_s character, gender_s gender);
	void					damage(int value);
	bool					equip(const item& it);
	bool					is(state_s i) const { return states.is(i); }
	bool					isready() const;
	int						get(ability_s i) const;
	int						get(parameter_s i) const { return parameters[i]; }
	int						getmaximum(parameter_s i) const { return parameters_maximum[i]; }
	bool					roll(int value) const;
};