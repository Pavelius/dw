#include "archive.h"
#include "logs.h"

#pragma once

using namespace logs;

enum famlity_stat_s : unsigned char {
	Reach, Grasp, Sleight,
};
enum stat_s : unsigned char {
	Force, Sway, Steel, Lore,
};
enum expendable_s : unsigned char {
	Mood, Tech, Data,
};
enum tone_s : unsigned char {
	Ruins, Echoes, Mirrors,
};
enum move_s : unsigned char {
	HoldTogether, ConductDiplomacy, ClaimByForce, Subterfuge,
	FlushWithResources, FallIntoCrisis,
	LendAid, CallInADebt, PowerUp, UncoverSecrets,
	DefuseForce, DefuseSway, DefuseSteel, DefuseLore,
	UnleashPower, FiercelyAssault, WastelandSurvival, FindCommonGround,
	CallForAid, InformationIsPower,
	FamiliarFace, ForgeAPath, UnearthForgottenLore,
	ShakeItOff, ProffessionalCare, ToolUp,
	UnderOrder,
};
enum resource_s : unsigned char {
	Artisans, BarterGoods, Crops, Defences, Energy,
	Engineering, FreshWater, Justice, Land, Leadership,
	Luxury, Medicine, Morale, Prestige, Progress,
	RareMaterials, Recruits, Safety, Scavengers, Scouts,
	Spies, Trade, Transport, Weaponry,
};
enum family_s : unsigned char {
	TheGildedCompanyOfMerchants, TheLawgivers, TheTyrantKings,
	LastFraction = TheTyrantKings,
};
enum item_type_s : unsigned char {
	WeaponItem, ArmorItem, OutfitItem, TransportItem, FollowersItem, DeviceItem,
};
enum item_s : unsigned char {
	NoItem, Shootgun, HeavyPistol,
};
typedef cflags<resource_s> resourcea;

class item {
	item_s			type;
};
class family {
	char			stats[Sleight + 1];
	char			stats_base[Sleight + 1];
	char			expendable[Data + 1];
	char			treaty[LastFraction + 1];
	resourcea		surpluses, needs;
public:
	void			add(resource_s i);
	int				get(stat_s i) const { return stats[i]; }
	int				get(expendable_s i) const { return expendable[i]; }
	int				get(family_s i) const { return treaty[i]; }
	bool			is(resource_s i) const { return surpluses.is(i); }
	bool			isneed(resource_s i) const { return needs.is(i); }
	void			remove(resource_s i);
};
class nameable {
	unsigned short	name;
public:
	const char*		getname() const;
};
class character : public nameable {
	char			stats[Sway + 1];
public:
	int				get(stat_s i) const { return stats[i]; }
};