#include "logs/collection.h"
#include "logs/crt.h"
#include "logs/logs.h"
#include "logs/logs_driver.h"

#pragma once

enum result_s : unsigned char {
	Fail, PartialSuccess, Success
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
	virtual gender_s	getgender() const { return NoGender; }
	virtual int			gethp() const { return 0; }
	virtual int			gethpmax() const { return 0; }
	virtual const char*	getname() const { return "thing"; }
	virtual bool		is(talent_s value) const { return false; }
};
struct hero : thing {
	char				stats[Intellegence + 1];
	char				level;
	char				hp;
	constexpr hero() : hp(0), level(0), stats() {}
	virtual int			gethp() const { return 0; }
	virtual int			gethpmax() const override;
	void				sethp(int value) { hp = value; }
};