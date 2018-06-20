#include "logs/collection.h"
#include "logs/crt.h"
#include "logs/dice.h"
#include "logs/logs.h"

#pragma once

#define getinf_enum(ename) template<> const char* getinfo<ename##_s>(ename##_s value) { return ename##_data[value].text; }

enum size_s : unsigned char {
	SizeFine, SizeDiminutive, SizeTiny,
	SizeSmall, SizeMeduim, SizeLarge,
	SizeHuge, SizeGargantuan, SizeCollosal
};
enum ability_s : unsigned char {
	Strenght, Dexterity, Constitution, Intellegence, Wisdow, Charisma
};
enum class_s : unsigned char {
	Jedi, Noble, Scoundrel, Scout, Soldier, Beast, NonHero,
};
enum specie_s : unsigned char {
	NoSpecies,
	Human, Bothan, Cerean, Duros, Ewoks, Gammorean, Gungans, Ithorians,
	KelDor, MonCalamari, Quarren, Rodians, Sullustans, Txrandoshans, Twileks, Zabrak,
	Wookie,
	FirstSpecies = Human, LastSpecies = Wookie
};
enum talent_s : unsigned char {
	NoTalant,
	General, Skills, RacialFeat,
	JediConsular, JediGuardian, JediSentinel, LightsaberCombat,
	Influence, Inspiration, Leadership, Lineage,
};
enum feat_s : unsigned short {
	NoFeat,
	// Jedi
	AdeptNegotiator, ForcePersuasion, MasterNegotiator, SkilledAdvisor,
	AcrobaticRecovery, BattleMeditation, ElusiveTarget, ForceIntuition, Resilience,
	ClearMind, DarkSideSence, DarkSideScourge, ForceHaze, ResistDarkSide,
	Block, Deflect, LightsaberDefence, LightsaberDefenceII, LightsaberDefenceIII, WeaponSpecializationLightsaber, LightSaberThrow, RedirectShot,
	// Noble
	Presence, DemandSurrender, ImprovedWeakenResolve, WeakenResolve,
	BolsterAlly, IgniteFerver, InspireConfidence, InspireHaste, InspireZeal,
	BornLeader, Coordinate, DistantCommand, FearlessLeader, Rally, Trust,
	Connections, Educated, SpontaneousSkill, Wealth,
	// General Feats
	AcrobaticStrike, ArmourProficienceLight, ArmourProficienceMedium, ArmourProficienceHeavy,
	BanthaRush, BurstFire, CarefulShoot, ChargingFire,
	Cleave, CombatReflexes, CoordinatedAttack, Crush, CyberneticSurgery,
	Deadeye, Dodge, DoubleAttack, DreadfulRage, DualWeaponMastery,
	ExtraRage, ExtraSecondWind,
	FarShoot, ForceBoon, ForceSensitivity, ForceTraining,
	ImprovedCharge, ImprovedDefences, ImprovedDisarm, ImprovedDamageThreshold, Linguist,
	MartialArts, MartialArtsII, MartialArtsIII,
	MeleeDefence, MightySwing,
	Mobility, Pin, PointBlankShoot, PowerAttack, PowerfulCharge,
	PreciseShoot, QuickDraw, RapidShoot, RapidStrike, RunningAttack,
	ShakeItOff,
	Sniper,
	SkillFocusAcrobatic, SkillFocusClimb, SkillFocusDeception, SkillFocusEndurance, SkillFocusGatherInformation,
	SkillFocusInitiative, SkillFocusJump, SkillFocusBuerocracy, SkillFocusGalacticLore, SkillFocusLifeSciences,
	SkillFocusPhysicalSciences, SkillFocusSocialSciences, SkillFocusTactics, SkillFocusTechnology, SkillFocusMechanics,
	SkillFocusPerception, SkillFocusPersuasion, SkillFocusPilot, SkillFocusRide, SkillFocusStealth,
	SkillFocusSurvival, SkillFocusSwim, SkillFocusTreatInjury, SkillFocusUseComputer, SkillFocusUseForce,
	StrongInTheForce,
	SurgicalExpertise, Throw, Toughness, Trip, TripleAttack,
	TripleCrit, VehicularCombat, WeaponFiness,
	WeaponProficiencyAdvancedMeleeWeapons, WeaponProficiencyExoticWeapons,
	WeaponProficiencyHeavyWeapons, WeaponProficiencyLightsabers, WeaponProficiencyPistols,
	WeaponProficiencyRifles, WeaponProficiencySimpleWeapons,
	WeaponFocusAdvancedMeleeWeapons, WeaponFocusExoticWeapons,
	WeaponFocusHeavyWeapons, WeaponFocusLightsabers, WeaponFocusPistols,
	WeaponFocusRifles, WeaponFocusSimpleWeapons,
	WhirlwindAttack,
	// Skills
	Acrobatic, Climb, Deception, Endurance, GatherInformation,
	Initiative, Jump, Buerocracy, GalacticLore, LifeSciences,
	PhysicalSciences, SocialSciences, Tactics, Technology, Mechanics,
	Perception, Persuasion, Pilot, Ride, Stealth,
	Survival, Swim, TreatInjury, UseComputer, UseForce,
	FirstSkill = Acrobatic, LastSkill = UseForce,
	// Races feats
	BonusSkill, BonusFeat,
	Primitive, LowlightVision, Darkvision,
	ExpertSwimmer, ExpertPilot, ExpertClimber, Sneaky, SurvivalInstinct, IntuitiveInitiative, KeenForceSence, HeightenAwareness, Deceptive,
	ExtraordinaryRecuperation, HoldBreath, BreathUnderwater, Bellow, LimbRegeneration, NaturalArmor,
	IronWill, GreatFortitude, LightingReflexes, SuperiorDefences,
	Rage, Scent,
	FirstFeat = AdeptNegotiator, LastFeat = Scent,
};
enum gender_s : unsigned char {
	Male, Female,
};
enum morph_s : unsigned char {
	Masculine, Feminine, Neuter
};
enum defence_s : unsigned char {
	Reflexes, Fortitude, Will
};
enum item_s : unsigned char {
	NoItem,
	Vibrodagger, Vibroblade, Vibrobayonet, ForcePike, Electrostaff, VibroAxe, Atlati, Amphistaff, Cesta,
	LightSaberShort, LightSaber, LightSaberDouble,
	Knife, Club, StunBatton, Mace, Spear, Bayonet, QuaterStaff, GlovesSmall, GlovesMedium,
	FlameThrower, BowCaster, // Exotic Ranged
	GrenadeLauncher, BlasterHeavyRepeating, BlasterCannon, MissileLauncher, BlasterEWebRepeating, // Heavy weapon
	BlasterPistolHoldOut, BlasterPistol, BlasterPistolSport, IonPistol, SlugthrowerPistol, BlasterPistolHeavy, // Pistols
	BlasterCarbine, BlasterRifle, BlasterRifleSport, IonRifle, SlugthrowerRifle, BlasterLightReapeating, BlasterRifleHeavy, // Rifles
	EnegryBall, GrenadeFrag, GrenadeIon, GrenadeStun, ThermalDetonator,
	Sling, Bow, Net, // Simple ranged
	ExplosiveCharge, Detonite, // Explosives
	BlastHelmetAndVest, FlightSuitPadded, CombatJumpSuit, FlightSuitArmored, VonduunCrabshell, StormtrooperArmour,
	CeremonialArmour, CorelianPowerSuit, BattleArmour,
	ArmouredSpacesuit, BattleArmourHeavy,
	PortableComputer, CodeCylinder, CreditChip, Holoprojector, DataCard, DataPad,
	Electrobinocular, GlowRod, FusionLatern, AudioRecorder, HoloRecorder, VideoRecorder, SensorPack,
	Comlink, PocketScrambler, VoxBox,
};
enum side_s : unsigned char {
	PartySide, EnemySide,
};
enum action_s : unsigned char {
	StandartAction, MoveAction, SwiftAction, Reaction, FreeAction, FullRoundAction,
};
enum state_s : unsigned char {
	StandAndReady, LayingDown,
};
enum combat_action_s : unsigned char {
	Attack, Aid, Charge, Disarm, FightDefensively, Grab,
	Move, DrawWeapon, ManiplateItem, StandUp, Withdraw,
	UseItem, Aim, CatchSecondWind, DropItem, FallProne, Recover,
	CoupDeGrace, FullAttack, Run,
};
enum pregen_s : unsigned char {
	NoPregen,
	Stormtrooper, StromtrooperHeavy,
};
typedef adat<feat_s, 8>				feata;
typedef adat<struct creature*, 64>	creaturea;
struct item
{
	item_s					type;
	unsigned char			count;
	operator bool() const { return type != NoItem; }
	void					clear();
	int						getcount() const;
	int						getreflexes() const;
	const dice&				getdice() const;
	void					setcount(int count = 1);
	bool					ismelee() const;
	bool					isweapon() const;
};
struct location
{
	struct scene
	{
		char				size;
		const char*			description[2];
	};
	struct place
	{
		struct scenery*		type;
		unsigned short		flags;
		const char*			getname() const;
		const char*			getnameto() const;
	};
	scene*					type;
	place					places[4];
	//
	void					acting();
	void					clear();
	void					create();
	void					getdescription(char* result, struct creature** source, unsigned source_index);
};
struct attackinfo
{
	char					bonus;
	dice					damage;
	char					critical_range;
	char					critical_multiply;
};
struct creature
{
	item					weapon, armor, gears[8];
	state_s					state;
	//
	creature(){}
	creature(pregen_s pregen) { create(pregen); }
	operator bool() const { return specie != NoSpecies; }
	//
	void					attack(creature* enemy, bool interactive, int bonus = 0);
	void					clear();
	void					combatactions(creaturea& enemies, bool interactive);
	static creature*		create(bool interactive = false, bool setplayer = false);
	void					create(pregen_s value);
	static creature*		create(specie_s specie, gender_s gender, class_s cls, bool interactive, bool setplayer);
	void					damage(int count, bool interactive);
	int						get(feat_s id) const;
	int						get(class_s id) const { return classes[id]; }
	int						get(defence_s id) const;
	const char*				getA() const { return gender == Female ? "а" : ""; }
	const char*				getAS() const { return gender == Female ? "ась" : "ся"; }
	action_s				getaction(combat_action_s id) const;
	void					getattackinfo(attackinfo& e) const;
	int						getbaseattack() const;
	int						getbonus(ability_s id) const;
	void					getenemies(creaturea& result, const creaturea& source) const;
	int						getfeats() const;
	int						getheroiclevel() const;
	const char*				getname() const;
	int						getinitiative() const { return initiative; }
	int						getreach() const { return 1; }
	side_s					getside() const { return side; }
	size_s					getsize() const { return SizeMeduim; }
	int						getspeed() const { return 6; }
	char*					getstatistic(char* result, const char* result_maximum) const;
	bool					is(feat_s id) const;
	bool					is(action_s id) const;
	bool					isactive() const;
	bool					isallow(action_s id) const;
	bool					isallow(feat_s id) const;
	bool					isclass(feat_s id) const;
	bool					isenemy(const creature* e) const;
	bool					ismelee() const { return weapon.ismelee(); }
	bool					isrange() const { return !weapon.ismelee(); }
	bool					isreachenemy(const creature* e) const;
	bool					isgearweapon() const;
	void					remove(feat_s id);
	int						roll(feat_s id, int dc = 0, bool interactive = true) const;
	int						roll(int bonus, int dc, bool interactive, int* dice_rolled) const;
	void					rollinitiative();
	void					set(class_s id, bool interactive = true);
	void					set(feat_s id, bool interactive = true);
	void					set(gender_s id);
	void					set(specie_s id);
	void					set(side_s id);
	void					set(action_s id);
	void					set(state_s id, bool interactive = true);
	void					setready();
	void					use(action_s id);
private:
	char					abilities[6];
	char					classes[NonHero + 1];
	unsigned char			feats[LastFeat / 8 + 1];
	short unsigned			name;
	gender_s				gender;
	specie_s				specie;
	pregen_s				pregen;
	short					hits;
	char					initiative;
	short					position;
	side_s					side;
	unsigned char			actions;
	char					reflex_bonus;
	//
	void					chooseabilities(bool interactive);
	static class_s			chooseclass(bool interactive);
	void					choosefeats(bool interactive, feat_s* source, unsigned source_count, int count = 1);
	void					choosefeats(bool interactive, talent_s talent, int count = 1);
	static gender_s			choosegender(bool interactive);
	void					chooseskill(bool interactive, int count);
	static specie_s			choosespecie(bool interactive);
	int						getskills() const;
	unsigned				select(feat_s* result, unsigned result_count, talent_s talent) const;
};
namespace game
{
	void					combat(bool interactive);
	ability_s 				getability(feat_s id);
	int						getdice(class_s id);
	feata&					getfeats(class_s id);
	const char*				getname(short unsigned id);
	short unsigned			getrandomname(specie_s race, gender_s gender);
	int						getskillpoints(class_s id);
}
namespace logs
{
	struct state
	{
		const char*			information;
		state();
		~state();
	};
}
extern adat<creature, 512>	creatures;
extern logs::state			logc;
extern creature*			players[6];