#include "crt.h"
#include "logs.h"

#pragma once

using namespace logs;

const int max_players = 3;

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
enum tags : unsigned char {
	Area, Autofire, HiTech, Infinite, Loud, Messy, Reload,
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
	cflags<distance_s>	distance;
	cflags<tags>		tag;
	cflags<upgrade_s, unsigned short> upgrade;
};
class item {
	unsigned short		upgrade;
	item_s				type;
public:
	constexpr item() : type(NoItem), upgrade(0) {}
	item(item_s type);
	operator bool() const { return type != NoItem; }
	void				clear();
	int					getharm() const;
	const char*			getname() const;
	char*				getname(char* result, bool description = false);
	bool				is(distance_s value) const;
	bool				is(upgrade_s value) const;
	bool				isarea() const;
	bool				isinfinite() const;
	bool				isloud() const;
	bool				ishitech() const;
	bool				ismessy() const;
	bool				isreload() const;
	bool				isupgrading() const;
	bool				isweapon() const;
	void				set(item_s value);
	void				set(upgrade_s value);
};
struct thing {
	constexpr thing(const char* name, gender_s gender, char armor = 0) : name(name), gender(gender), armor(armor) {}
	explicit operator bool() const { return name != 0; }
	void				act(const char* format, ...) const;
	void				act(thing& enemy, const char* format, ...) const;
	virtual int			getarmor() const { return armor; }
	virtual gender_s	getgender() const { return gender; }
	virtual const char*	getname() const { return name; }
	static const char*	getname(gender_s gender, booklet_s type);
	virtual char		getsize() const { return 0; }
	static result_s		roll(int bonus, int* result = 0, bool interactive = true);
	virtual void		setarmor(int value) { armor = value; }
	virtual void		setgender(gender_s v) { gender = v; }
	virtual void		setname(const char* v) { name = v; }
private:
	const char*			name;
	gender_s			gender;
	char				armor;
};
class actor : public thing {
public:
	constexpr actor(const char* name = 0, gender_s gender = Male, char harm = 0, char armor = 0): thing(name, gender, armor), health(4), harm(harm), states(0) {}
	int					addbonus(state_s v);
	int					addchoice() { return addbonus(AddChoice); }
	int					addforward() { return addbonus(AddForward); }
	char				getharm() const { return harm; }
	bool				is(state_s v) const { return (states&(1 << v)) != 0; }
	bool				isalive() const { return health > 0; }
	bool				ishero() const;
	bool				iswounded() const { return health < 4; }
	void				remove(state_s v) { states &= ~(1 << v); }
	void				set(state_s v) { states |= (1 << v); }
	void				setharm(int value) { harm = value; }
	void				sufferharm(int harm);
protected:
	char				health, harm;
	unsigned			states;
};
struct gang : public actor {
	short unsigned		count;
	short unsigned		wounded;
	short unsigned		dead;
public:
	gang(const char* name = 0, short unsigned count = 0, char harm = 0, char armor = 0);
	int					getcount() const { return count - dead; }
	char				getsize() const override;
	void				sufferharm(int harm);
};
class hero : public actor {
	char				stats[Weird + 1];
	char				history[max_players];
	booklet_s			type;
	unsigned			moves;
	char				angelkit;
	item				weapon, weapons[4];
	gang				followers;
public:
	hero() : actor(), stats(), history(), type(), moves(), angelkit(), weapon(), weapons() {}
	result_s			actunderfire();
	bool				add(item value);
	static void			choose(aref<const char*> strings, const char* title, char* result, int answer_count);
	hero&				choose(bool interactive);
	hero&				chooseally(bool interactive, bool clear_text = true);
	void				choosegear(bool interactive);
	void				choosegender(bool interactive);
	void				choosehistory(bool interactive, int stage);
	void				choosemoves(bool interactive, booklet_s type, int count);
	void				choosename(bool interactive);
	void				choosestats(bool interactive);
	void				choosetype(bool interactive);
	bool				combat(actor& enemy);
	void				create(bool interactive);
	static void			createparty(bool interactive);
	int					get(stat_s id) const { return stats[id]; }
	int					getindex() const;
	int					getharm() const;
	int					gethistory(const hero& player) const;
	gang&				getgang() { return followers; }
	item*				getweapon(distance_s distance);
	result_s			goaggro(actor& enemy);
	void				inflictharm(actor& enemy, int count);
	bool				is(move_s value) const;
	bool				keephold(actor& enemy);
	bool				laydownfire(actor& enemy);
	void				hardmove();
	void				hardmove(actor& enemy);
	result_s			openyourbrain();
	void				prepareweapon(distance_s distance);
	result_s			readasitch();
	result_s			readaperson();
	void				searchspoils();
	bool				seizbyforce(actor& enemy, const char* goal = "�� �������� ������ �������� ��� ���, ��� ������");
	void				set(booklet_s value);
	void				set(move_s value);
	void				set(stat_s id, int value) { stats[id] = value; }
	void				sethistory(hero& player, int value) { history[player.getindex()] = value; }
	void				sufferharm(int harm);
	int					whatdo() const;
};
class vehicle : thing {
	constexpr vehicle(const char* name, gender_s gender, char armor) : thing(name, gender, armor), stats(), strenght() {}
	char				get(vehicle_stat_s id) const;
	void				remove(strenght_s id) { strenght &= ~(1 << id); }
	void				set(vehicle_stat_s id, int value);
	void				set(strenght_s id) { strenght |= (1 << id); }
private:
	char				stats[3];
	unsigned			strenght;
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
extern hero				players[max_players];
inline int				d100() { return rand() % 100; }