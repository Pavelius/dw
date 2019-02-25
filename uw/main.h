#include "logs/crt.h"
#include "logs/logs.h"
#include "logs/point.h"

#pragma once

enum severity_s : unsigned char {
	Minor, Major, Severe, Critical, Fatal,
};
enum assets_range_s : unsigned char {
	Melee, Adjacent, Close, Far, Distant,
};
enum assets_groups : unsigned char {
	GroupWeapon, GroupAttire, GroupVehicle, GroupCrew, GroupKit, GroupCargo,
};
enum kit_s : unsigned char {
	NoKit,
	BroadcastKit, ComputerKit, EngineeringKit, InfiltrationKit,
	MedicalKit, ResearchKit, SurveyKit, WildernessKit,
};
extern const char* assets_kits_text[][2];
enum cargo_s : unsigned char {
	NoCargo,
	Foods, Minerals, Medicals, Devices, Luxuries, Alcohols, Weapons, Drugs,
};
enum chemical_s : unsigned char {
	NoChemical,
	Fire, Smoke,
};
enum visor_s : unsigned char {
	NoVisors,
	DetectWeapon,
};
extern const char* assets_tags_text[][2];
enum asset_s : unsigned char {
	CombatKnife, LenghtOfChain, BrassKnuckles, StunBatton, ChainsawAssets, ThrowingKnives, Rapier, ShatterHammer, StromClaws, StarSword,
	PistolAssets, Shotgun, StunnerPistol, Scattershoot, LaserRifle, SniperRifle, GrenadeLauncher,
	HeavyStabber, LMG, RoketLauncher, PlasmaCannon, Flamethrover, LightingCoil, SonicCannon, HullBuster,
	Landmine, SmokeBomb, FragGrenade, Flashbang, ProximityMine, ShapedCharge, IncendiaryGrenade, BombBriefcase,
	Jumpsuit, EveningGown, BrownCoat, BodyArmor, EVASuit, CustomsUniform, ClimbingGear, BulletproofSuit, Regalia, WingSuit, BattlePlate, BoardingArmor,
	StuntBike,
	Skycar, Interceptor,
	Students, Rabble, Bandits, Soldiers,
};
enum stat_s : unsigned char {
	Mettle, Physique, Influence, Expertise, Interface
};
enum skill_s : unsigned char {
	Education, Chemistry, Surgery, Deduction, Technobabble,
	Assassination, Interrogation, Sabotage, Stealth, Surveillance,
	Outfit, Marketing, Acumen, Luxury, Bribe,
	BoldlyGo, Reconnaissance, Survival, Recklessness, CustomVehicle,
	Repair, Construction, Tinker, Upgrade, Dismantle,
	Tactics, Toughness, UniqueWeapon, HeavyLifting, Authority,
	Fame, Leadership, Contacts, Inspiration, Diplomacy,
	Criminal, SneakAttack, Scapegoat, FalseIdentity, Addict,
	Weightless, Cosmopolitan, Navigation, Calibrations, CustomFlyer,
	Upload, Hijack, Program, Network, ArtificialIntelligence,
};
enum move_s : unsigned char {
	FaceAdversityMettle, FaceAdversityPhysique, FaceAdversityInfluence, FaceAdversityExpertise, FaceAdversityInterface,
	AssessmentMettle, AssessmentPhysique, AssessmentInfluence, AssessmentExpertise, AssessmentInterface,
	GetInvolved,
	OpenFire, LaunchAssault, Command, PatchUp, Access,
};
enum career_s : unsigned char {
	Academics, Clandestine, Commercial, Explorer, Industrial,
	Military, Personality, Scoundrel, Starfarer, Technocrat
};
enum debility_s : unsigned char {
	Shoking, Angry, Sick,
	Posion, Bleed, Blindness, Illness, Parasite,
};
enum workspace_s : char {
	MedicalWorkspace, ResearchWorkspace,
	StealthyWorkspace, SecureWorkspace,
	MercantileWorkspace, LeisyreWorkspace,
};
enum scene_s : char {
	Hangar, Forest, Dunes,
};
enum feature_s : char {
	Vehicles, Boxes, Trash, Trees
};
enum result_s : char {
	Fail, PartialSuccess, Success
};
enum market_s {
	MinorMarket, StandartMarket, MajorMarkets,
};
template<class T, class TC = unsigned>
struct flags {
	void					clear() { data = 0; }
	bool					is(T value) const { return (data & getmask(value)) != 0; }
	void					set(T value) { data |= getmask(value); }
	void					remove(T value) { data &= ~getmask(value); }
private:
	TC						data;
	inline TC				getmask(const T value) const { return 1 << value; }
};
struct assets {
	asset_s					type;
	unsigned char			count;
	operator bool() const { return count != 0; }
	//
	void					clear();
	int						getarmor() const;
	chemical_s				getchemical() const;
	int						getcount() const { return count; }
	int						getcountmax() const;
	assets_groups			getgroup() const;
	int						getmarket() const;
	const char*				getname() const;
	char*					getname(char* result, const char* result_maximum) const;
	char*					getnamefull(char* temp) const;
	severity_s				getseverity() const;
	bool					is(assets_range_s range) const;
	bool					isbreaching() const;
	bool					iscrew() const;
	bool					isclumsy() const;
	bool					isdestructive() const;
	bool					istwohanded() const;
	static int				select(asset_s* indecies, assets_groups type, int market = -1);
	void					set(asset_s type);
};
struct cargo {
	cargo_s					type;
	char					market;
	struct planet*			origin;
};
struct vehicle : assets {
	assets					armed, tool;
	cargo					load;
	kit_s					kit;
	flags<severity_s>		damage;
};
struct spaceship {
	char					type;
	assets					turrets[4];
	assets					quarters;
	cargo					cargobay[8];
	vehicle					vehicles[4];
	operator bool() const { return type != 0; }
};
struct hero {
	char					stats[Interface + 1];
	flags<skill_s>			skills;
	flags<kit_s>			kit;
	flags<skill_s>			debilities;
	flags<severity_s>		damages[2];
	assets					weapon; // Personal weapon
	assets					attire; // Personal attire
	assets					crew; // Personal crew or bodyguard
	struct vehicle			vehicle; // Personal vehicle
	struct vehicle*			passenger; // Passenger of this vehicle
	struct spaceship*		spaceship; // Crew member of this spaceship
	struct planet*			planet; // Landed on this planet
	//
	void					acquisition(int market_class);
	bool					acquisition(int market_class, bool specialized);
	void					acquisition(assets& ast, assets_groups group, int market_class);
	void					braceimpact(severity_s value);
	void					clear();
	assets&					get(assets_groups group);
	int						getarmor() const;
	char*					getname(char* result, const char* result_maximum) const;
	bool					is(kit_s value) const;
	bool					is(severity_s value) const;
	bool					isclumsy() const;
	bool					isready() const;
	bool					istwohanded() const;
	bool					openfire(assets& enemy);
	static void				passtime(unsigned minutes);
	result_s				roll(move_s move);
	result_s				roll(stat_s stat) { return roll2d6(stats[stat]); }
	static result_s			roll2d6(int bonus, int* result = 0, bool show_numbers = true);
	void					set(asset_s value);
	void					set(kit_s value);
	severity_s				set(severity_s value);
};
struct planet {
	const char*				name;
	market_s				market;
	cargo_s					cargo;
	assets_groups			markets[2]; // 0 - default, 1 - hidden/unpopular
	spaceship*				docks[16];
};
struct scene {
	scene_s					type;
	feature_s				features[3];
	hero&					player;
	assets					enemy;
	vehicle					vehicle;
	struct planet*			planet;
	scene(scene_s type, hero& player);
	~scene();
	void					enter();
private:
	scene*					previous_scene;
	const char*				previous_panel;
};
extern planet				planets[];