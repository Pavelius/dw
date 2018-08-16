#include "logs/collection.h"
#include "logs/crt.h"
#include "logs/logs.h"
#include "logs/logs_driver.h"

#pragma once

enum result_s : unsigned char {
	Fail, PartialSuccess, Success,
};
enum distance_s : unsigned char {
	Hand, Close, Far,
};
enum stat_s : unsigned char {
	Strenght, Dexterity, Intellegence
};
enum item_s : unsigned char {
	NoItem,
	Revolver, Pistol, Rifle, Shotgun, Magnum, SawedOff, SMG,
	Knife, Spear, Staff, Chain, Crowbar, Grenades, Machete, ManyKnives,
	SniperRifle, MachineGun, AssaultRifle, GrenadeLauncher,
};
enum talent_s : unsigned char {
	Gunslinger, Idealist, Lucky, Medic, Mechanic, Ranger, Rogue, Slasher, Tought, Trader,
};
struct item {
	item_s				type;
	constexpr item() : type(NoItem), upgrade(0) {}
	item(item_s type);
	operator bool() const { return type != NoItem; }
	void				clear();
	int					getharm() const;
	const char*			getname() const;
	char*				getname(char* result, bool description = false);
	bool				is(distance_s value) const;
	bool				isarea() const;
	bool				isinfinite() const;
	bool				isloud() const;
	bool				ishitech() const;
	bool				ismessy() const;
	bool				isreload() const;
	bool				isupgrading() const;
	bool				isweapon() const;
	void				set(item_s value);
private:
	unsigned short		upgrade;
};
struct thing {
	virtual int			get(stat_s id) const { return 0; }
	virtual gender_s	getgender() const { return NoGender; }
	virtual int			gethp() const { return 0; }
	virtual int			gethpmax() const { return 0; }
	virtual const char*	getname() const { return "thing"; }
	virtual bool		is(talent_s value) const { return false; }
};
struct hero : thing {
	hero(talent_s id);
	constexpr hero() : hp(0), level(0), stats() {}
	virtual int			get(stat_s id) const { return stats[id]; }
	virtual int			gethp() const { return hp; }
	virtual int			gethpmax() const override;
	void				raise();
	result_s			roll(stat_s id, bool interactive = true, int bonus = 0);
	void				set(talent_s id);
	void				sethp(int value) { hp = value; }
	result_s			volley(aref<hero> enemies);
private:
	char				level;
	char				hp;
	char				stats[Intellegence + 1];
};