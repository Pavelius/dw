#include "logs/adat.h"
#include "logs/aref.h"
#include "logs/crt.h"
#include "logs/logs.h"
#include "logs/logs_driver.h"

#pragma once

enum population_s : unsigned char {
	NoPopulated, Outposts, Colonies, Cities, Overpopulated,
};
enum landscape_s : unsigned char {
	Terrain, ColdRealm, SandRealm, WaterRealm, FoggyJungles, RockyRealm, CorrosiveHell,
};
enum size_s : unsigned char {
	Diminutive, Small, Medium, Large, Huge, Gigantic,
};
enum disposition_s : unsigned char {
	OnOrbit, NearTo, InCosmoportOf, OnSurfaceOf,
};
enum bay_s : unsigned char {
	NoBay,
	EngeneeringBay, FotifiedStorage, Hangar, Laboratory, LivingCells, LifeSupport, MedicalBay, Manipulator,
	Prison, Radar, Stock, Weaponry,
};
enum weapon_type_s : unsigned char {
	Energy, Shrapnel, Rocket,
};
enum weapon_s : unsigned char {
	NoWeapon,
	Laser, ShrapnelCannon, RocketLauncher, Torpedo
};
struct location {
	location*		parent;
	const char*		id;
	const char*		name;
	unsigned		distance;
	population_s	population;
	landscape_s		landscape;
	size_s			size;
	location*		neighboards[8];
	location*		getparent() const { return parent; }
	const char*		getname() const { return name; }
};
struct status {
	unsigned short	hits;
	unsigned short	hits_maximum;
	unsigned char	level;
	constexpr status(unsigned short hits = 200) : hits(hits), hits_maximum(hits), level(0) {}
	short unsigned	gethits() const { return hits; }
	short unsigned	gethitsmax() const { return hits_maximum; }
};
// Не оружейный отсек
struct bay : status {
	bay_s			type;
	constexpr bay(bay_s type = NoBay) : type(type) {}
	operator bool() const { return type != NoBay; }
};
typedef adat<bay, 8> baya;
struct damageinfo {
	unsigned char	damage[2];
	unsigned char	count;
	unsigned char	distance;
	void			set(weapon_s id, int level);
	int				roll();
};
// Оружие или оружейная платформа
struct weapon : status {
	weapon_s		type;
	constexpr weapon(weapon_s type = NoWeapon) : type(type) {}
	operator bool() const { return type != 0; }
	void			get(damageinfo& e) const;
	weapon_type_s	gettype() const;
};
typedef weapon		weapona[6];
struct ship {
	const char*		id;
	const char*		name;
	size_s			size;
	unsigned short	hits_maximum;
	char			armor;
	char			march_speed; // Скорость маршевых двигателей (4 - 10)
	char			hyper_speed; // Скорость в гипер пространстве (0 - 3)
	char			weapon_slots; // Количество слотов оружия
	char			bay_slots; // Количество отсеков
	weapona			weapons;
	baya			bays;
	void			act(const char* format, ...) const;
};
class spaceship : status, ship {
	disposition_s	disposition;
	location*		parent;
	spaceship*		leader;
	char			distance;
	char			side;
public:
	spaceship();
	spaceship(const char* id);
	location*		chooselocation();
	bool			encounter();
	void			damage(bool interactive, int value, weapon_type_s type);
	bool			isenemy(const spaceship* p) const;
	disposition_s	getdisposition() const { return disposition; }
	unsigned char	getdistance() const { return distance; }
	location*		getlocation() const { return parent; }
	bool			marshto();
	void			set(disposition_s value) { disposition = value; }
	void			set(location* value) { parent = value; }
	void			shoot(bool interactive, weapon& e, spaceship& enemy);
	void			shoot(bool interactive, spaceship& enemy);
};
class solar : adat<spaceship*, 64> {
public:
	solar() {}
	spaceship*		getenemy(const spaceship* source) const;
};
extern adat<spaceship, 260> spaceships;
namespace game {
location*			find(const char* id);
unsigned			getday();
unsigned			getyear();
void				nextday();
}