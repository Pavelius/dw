#include "crt.h"
#include "logs.h"

#pragma once

using namespace logs;

const unsigned max_players = 3;

enum distance_s : unsigned char {
	Intimate, Hand, Close, Far,
};
enum result_s : unsigned char {
	Fail, PartialSuccess, Success
};
enum booklet_s : unsigned char {
	NoBooklet,
	TheAngel, TheBattleBaby, TheGunlugger,
};
enum stat_s : unsigned char {
	Cool, Hard, Hot, Sharp, Weird
};
enum move_s : unsigned char {
	SixthSense, Infirmary, ProfessionalCompassion, BattlefieldGrace, HealingTouch, TouchedByDeath,
	DangerousAndSexy, IceCold, Merciless, VisionOfDeath, PerfectInstincts, ImpossibleReflexes,
	BattleHardened, FuckThisShit, BattlefieldInstincts, InsanoLikeDrano, PreparedForTheInevitable, Bloodcrazed, NotToBeFuckWith,
};
enum item_s : unsigned char {
	NoItem,
	Revolver, Pistol, Rifle, Shotgun, Magnum, SawedOff, SMG,
	Knife, Spear, Staff, Chain, Crowbar, Grenades, Machete, ManyKnives,
	SniperRifle, MachineGun, AssaultRifle, GrenadeLauncher,
};
enum upgrade_s : unsigned char {
	Blade, Spikes, Scoped, Big, HiPower, Semiautomatic, Silenced, Hidden, Valuable,
};
enum state_s : unsigned char {
	Frighten, ActingUnderFire, AddChoice, AddForward,
};
enum gig_s : unsigned char {
	Hunting, Farming, Scavenging,
	Tribute, Raiding, Manufactory, BustlyMarket,
};
enum strenght_s : unsigned char {
	Aggressive, Capacious, EasilyRepaired, Fast, Huge, Responsive,
	Rugged, Tight, OffRoad, Uncomplaining, Workhorse
};
enum vehicle_stat_s : unsigned char {
	Speed, Handling, Massive, Armor,
};
enum tag_s : unsigned char {
	Area, Autofire, HiTech, Infinite, Loud, Messy, Reload,
	Harm1, Harm2, Harm4,
	Armor1, Armor2, Armor4
};
enum variant_s : unsigned char {
	NoVariant,
	Booklet, Distance, Item, Move, Result, State, Tag, Upgrade
};
struct variant {
	variant_s			type;
	unsigned char		subtype;
	constexpr variant() : type(NoVariant), subtype(0) {}
	constexpr variant(booklet_s v) : type(Booklet), subtype(v) {}
	constexpr variant(distance_s v) : type(Distance), subtype(v) {}
	constexpr variant(move_s v) : type(Move), subtype(v) {}
	constexpr variant(item_s v) : type(Item), subtype(v) {}
	constexpr variant(result_s v) : type(Result), subtype(v) {}
	constexpr variant(state_s v) : type(State), subtype(v) {}
	constexpr variant(tag_s v) : type(Tag), subtype(v) {}
	constexpr variant(variant_s type, unsigned char v) : type(type), subtype(v) {}
	constexpr variant(unsigned short v) : type(variant_s(v >> 8)), subtype(v & 0xFF) {}
	constexpr operator unsigned short() const { return type << 8 | subtype; }
	constexpr explicit operator bool() const { return type != NoVariant; }
};
class tagable {
	cflags<distance_s, unsigned char>	distances;
	cflags<tag_s, unsigned short>		tags;
	cflags<move_s>						moves;
	cflags<upgrade_s, unsigned short>	upgrades;
	cflags<state_s, unsigned short>		states;
public:
	constexpr tagable() : distances(), tags(), moves(), upgrades() {}
	constexpr tagable(const std::initializer_list<variant>& list) : distances(), tags(), upgrades() {
		for(auto e : list) {
			switch(e.type) {
			case Distance: set(distance_s(e.subtype)); break;
			case Move: set(move_s(e.subtype)); break;
			case State: set(state_s(e.subtype)); break;
			case Tag: set(upgrade_s(e.subtype)); break;
			case Upgrade: set(upgrade_s(e.subtype)); break;
			}
		}
	}
	constexpr int		addchoice() const { return 0; }
	int					get(tag_s i1, tag_s i2) const;
	int					getarmor() const;
	int					getharm() const;
	constexpr bool		is(distance_s v) const { return distances.is(v); }
	constexpr bool		is(move_s v) const { return moves.is(v); }
	constexpr bool		is(tag_s v) const { return tags.is(v); }
	constexpr bool		is(upgrade_s v) const { return upgrades.is(v); }
	constexpr bool		is(state_s v) const { return states.is(v); }
	constexpr void		set(distance_s v) { distances.add(v); }
	constexpr void		set(move_s v) { moves.add(v); }
	constexpr void		set(tag_s v) { tags.add(v); }
	constexpr void		set(upgrade_s v) { upgrades.add(v); }
	constexpr void		set(state_s v) { states.add(v); }
	void				set(tag_s i1, tag_s i2, int v);
	constexpr void		remove(upgrade_s v) { upgrades.remove(v); }
	constexpr void		remove(move_s v) { moves.remove(v); }
	constexpr void		remove(state_s v) { states.remove(v); }
	constexpr void		remove(tag_s v) { tags.remove(v); }
	constexpr void		remove(distance_s v) { distances.remove(v); }
};
struct stati {
	const char*			id;
	const char*			name;
};
struct upgradei {
	const char*			id;
	const char*			name;
	bool				ending;
};
struct tagi {
	const char*			id;
	const char*			name;
	int					count;
};
struct bookleti {
	const char*			id;
	const char*			name;
	char				stats[4][5];
	char				choose_moves;
	adat<move_s, 8>		moves;
	adat<move_s, 4>		start;
};
struct movei {
	const char*			id;
	const char*			name;
	const char*			descritpion;
};
struct genderi {
	const char*			id;
	const char*			name;
};
struct itemi {
	const char*			id;
	const char*			name;
	char				harm;
	char				armor;
	tagable				tags;
};
struct namei {
	booklet_s			type;
	gender_s			gender;
	const char*			id;
	const char*			name;
};
class item : public tagable {
	item_s				type;
public:
	constexpr item() : type(NoItem) {}
	constexpr item(item_s type) : type(type), tagable(bsmeta<itemi>::elements[type].tags) {}
	operator bool() const { return type != NoItem; }
	void				clear();
	const char*			getname() const;
	char*				getname(char* result, bool description = false);
	constexpr bool		is(distance_s v) const { return tagable::is(v); }
	constexpr bool		is(upgrade_s v) const { return tagable::is(v); }
	bool				isupgrading() const;
	bool				isweapon() const;
	void				set(item_s value);
	constexpr void		set(upgrade_s v) { tagable::set(v); }
};
class nameablei {
	short unsigned		data;
public:
	constexpr nameablei() : data(0) {}
	const char*			getname() const;
	gender_s			getgender() const;
	void				setname(short unsigned v) { data = v; }
};
class thing : public variant, public tagable, public nameablei {
	char				health;
public:
	constexpr thing() : variant(), health(gethealthmax()) {}
	void				act(const char* format, ...) const;
	void				act(thing& enemy, const char* format, ...) const;
	gender_s			getgender() const;
	char				gethealth() const { return health; }
	const char*			getname() const;
	constexpr char		gethealthmax() const { return 6; }
	char				getsize() const { return 0; }
	constexpr bool		isalive() const { return health >= 0; }
	constexpr bool		iswounded() const { return health >= 2; }
	void				kill() { health = 0; }
	void				sethealth(char v) { health = v; }
};
class gang : public thing {
	unsigned char		count;
	unsigned char		wounded;
	unsigned char		dead;
public:
	constexpr gang() : count(20), wounded(0), dead(0) {}
	int					getcount() const { return count - dead; }
	char				getsize() const;
};
class hero : public thing {
	char				stats[Weird + 1];
	char				history[4];
	booklet_s			type;
	unsigned			moves;
	char				angelkit;
	item				weapon, weapons[4];
	gang				followers;
public:
	constexpr hero() : stats(), history(), type(), moves(), angelkit(), weapon(), weapons() {}
	result_s			actunderfire();
	bool				add(item value);
	static void			choose(aref<const char*> strings, const char* title, char* result, int answer_count);
	hero&				choose(bool interactive);
	hero&				chooseally(bool interactive, bool clear_text = true);
	void				choosegear(bool interactive);
	static gender_s		choosegender(bool interactive);
	void				choosehistory(bool interactive, int stage);
	void				choosemoves(bool interactive, booklet_s booklet, int count);
	void				choosename(bool interactive, booklet_s booklet, gender_s gender);
	void				choosestats(bool interactive);
	void				choosetype(bool interactive);
	bool				combat(thing& enemy);
	void				create(bool interactive);
	static void			createparty(bool interactive);
	int					get(stat_s id) const { return stats[id]; }
	int					getindex() const;
	int					gethistory(const hero& player) const;
	gang&				getgang() { return followers; }
	item*				getweapon(distance_s distance);
	result_s			goaggro(thing& enemy);
	void				inflictharm(thing& enemy, int count);
	bool				is(move_s value) const;
	static bool			is(booklet_s v);
	bool				keephold(thing& enemy);
	bool				laydownfire(thing& enemy);
	void				hardmove();
	void				hardmove(thing& enemy);
	result_s			openyourbrain();
	void				prepareweapon(distance_s distance);
	result_s			readasitch();
	result_s			readaperson();
	static result_s		roll(int bonus, int* result = 0, bool interactive = true);
	void				searchspoils();
	bool				seizbyforce(thing& enemy, const char* goal = "¬ы получили полный контроль над тем, что хотели");
	void				set(booklet_s value);
	void				set(move_s value);
	void				set(stat_s id, int value) { stats[id] = value; }
	void				sethistory(hero& player, int value) { history[player.getindex()] = value; }
	void				sufferharm(int harm);
	int					whatdo() const;
};
struct holding {
	holding();
	bool				is(gig_s v) const { return (gigs & (1 << v))!=0; }
	void				set(gig_s v) { gigs |= (1 << v); }
	void				remove(gig_s v) { gigs &= ~(1 << v); }
private:
	int					population;
	unsigned			gigs;
};
class counter {
	unsigned char		value;
public:
	constexpr counter() : value() {}
	int					get() const { return value; }
	bool				isactive() const { return value<6; }
	void				reset() { value = 0; }
};
DECLENUM(booklet);
DECLENUM(gender);
DECLENUM(item);
DECLENUM(move);
DECLENUM(stat);
DECLENUM(upgrade);
inline int				d100() { return rand() % 100; }