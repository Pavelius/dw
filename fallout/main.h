#include "crt.h"
#include "dice.h"
#include "logs.h"

#pragma once

using namespace logs;

enum result_s : unsigned char {
	Fail, PartialSuccess, Success,
};
enum stat_s : unsigned char {
	Strenght, Dexterity, Intellegence
};
enum item_s : unsigned char {
	NoItem,
	Revolver, Pistol, Rifle, Shotgun, Magnum, SawedOff, SMG,
	Knife, Spear, Staff, Chain, Crowbar, Grenades, Machete,
	SniperRifle, MachineGun, AssaultRifle, GrenadeLauncher,
};
enum talent_s : unsigned char {
	Doctor, Idealist, Lucky, Mechanic, Ranger, Rogue, Shooter, Slasher, Tought, Trader,
};
enum label_s : unsigned char {
	Area, ArmorPierce, Close,
	Dangerous, Destructive, Far,
	Hand, HiTech, Infinite, Light, Messy,
	Powerfull, Reload, Scope,
};
enum scenery_s : unsigned char {
	NoScenery, Box, Door, Passage
};
struct thing;
typedef adat<thing*, 16> thinga;
struct itemi {
	const char*			name;
	char				harm;
	char				armor;
	cflags<label_s>		tag;
	const char*			success;
};
struct sceneryi {
	const char*			name;
	gender_s			gender;
	const char*			description;
};
struct item {
	item_s				type;
	constexpr item(item_s type = NoItem) : type(type), upgrade(0) {}
	operator bool() const { return type != NoItem; }
	void				clear();
	dice				getharm() const;
	const char*			getname() const;
	char*				getname(char* result, bool description = false);
	const char*			gettextsuccess() const;
	bool				is(label_s value) const;
private:
	unsigned short		upgrade;
};
struct thing {
	virtual operator bool() const { return true; }
	void				act(const char* format, ...);
	void				ask(int id, const char* format, ...);
	virtual int			get(stat_s id) const { return 0; }
	virtual int			getarmor() const { return 0; }
	virtual gender_s	getgender() const { return NoGender; }
	virtual dice		getharm() const { return {1, 2}; }
	virtual int			gethp() const { return 0; }
	virtual int			gethpmax() const { return 0; }
	virtual const char*	getname() const { return "thing"; }
	virtual const item*	getweapon() const { return 0; }
	virtual bool		is(label_s value) const { return false; }
	virtual bool		is(talent_s value) const { return false; }
	virtual void		sethp(int hp) {}
	virtual void		sufferharm(int value, bool ap = false) {}
};
struct actor : thing {
	virtual operator bool() const override { return gethp() > 0; }
	virtual bool		is(label_s value) const override;
	virtual bool		is(talent_s value) const  override { return false; }
	virtual void		sufferharm(int value, bool ap) override;
	virtual dice		getharm() const override { return {1, 6}; }
};
struct npc : actor {
	npc(const char* name, gender_s gender, char armor, char hits, item weapon = NoItem) : name(name), gender(gender),
		hp(hits), hpmax(hits), armor(armor),
		weapon(weapon) {
	}
	virtual gender_s	getgender() const override { return gender; }
	virtual int			gethp() const override { return hp; }
	virtual int			gethpmax() const override { return hpmax; }
	virtual const char*	getname() const override { return name; }
	virtual const item*	getweapon() const { return &weapon; }
	virtual void		sethp(int value) override { hp = value; }
private:
	const char*			name;
	char				hp, hpmax, armor;
	gender_s			gender;
	item				weapon;
};
struct hero : actor {
	constexpr hero() : hp(0), level(0), stats(), cups(), weapon() {}
	hero(talent_s id);
	result_s			combat(thing& enemy, label_s distance);
	virtual int			get(stat_s id) const { return stats[id]; }
	virtual int			getarmor() const { return 1; }
	virtual const char*	getname() const override { return "Вонг"; }
	virtual int			gethp() const override { return hp; }
	virtual int			gethpmax() const override;
	virtual const item*	getweapon() const override { return &weapon; }
	result_s			hackandslash(thing& enemy);
	void				look(scenery_s id, thing& enemy, label_s distance);
	void				raise();
	result_s			roll(stat_s id, bool interactive = true, int bonus = 0);
	void				set(talent_s id);
	virtual void		sethp(int value) override { hp = value; }
	result_s			volley(thing& enemy, label_s& distance);
	int					whatdo() const;
private:
	char				stats[Intellegence + 1];
	char				level, hp;
	int					cups;
	item				weapon, gears[6];
};
DECLENUM(item);