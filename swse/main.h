#include "crt.h"
#include "dice.h"
#include "logs.h"

using namespace logs;

#pragma once

class creature;
struct location;

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
	NoAction,
	StandartAction, MoveAction, SwiftAction, Reaction, FreeAction, FullRoundAction,
};
enum state_s : unsigned char {
	StandAndReady, LayingDown,
};
enum wear_s : unsigned char {
	Melee, Ranged, Throwing, Armor,
	FirstGear, LastGear = FirstGear + 7,
};
enum pregen_s : unsigned char {
	NoPregen,
	Stormtrooper, StromtrooperHeavy,
};
typedef adat<feat_s, 16> feata;
struct abilityi {
	const char*				id;
	const char*				name;
};
struct speciei {
	const char*				id;
	const char*				name;
	char					abilities[6];
	feata					starting_feats;
};
struct pregeni {
	const char*				id;
	const char*				name;
	char					classes[NonHero + 1];
	char					ability[Charisma + 1];
	feata					feats;
	item_s					wears[LastGear + 1];
};
struct classi {
	const char*				id;
	const char*				name;
	char					dice;
	char					skills;
	feata					starting_feats;
};
struct itemi {
	struct weapon {
		dice				damage;
		item_s				ammo;
	};
	struct armor {
		char				defences[Will + 1];
	};
	const char*				id;
	const char*				name;
	const char*				descritpion;
	feat_s					group;
	int						cost;
	int						weight;
	weapon					weapon_stats;
	cflags<wear_s>			slots;
	armor					armor_stats;
	bool					is(wear_s id) const { return slots.is(id); }
};
struct prerequisiti {
	feata					feats;
	char					abilities[Charisma + 1];
	char					base_attack_bonus;
};
struct feati {
	const char*				id;
	const char*				name;
	talent_s				tree;
	prerequisiti			require;
};
struct item {
	item_s					type;
	unsigned char			count;
	item() = default;
	constexpr item(item_s type) : type(type), count(1) {}
	constexpr item(item_s type, unsigned char count) : type(type), count(count) {}
	operator bool() const { return type != NoItem; }
	void					clear();
	bool					is(wear_s id) const;
	int						getreflexes() const;
	int						getcount() { return count; }
	const dice&				getdice() const;
	void					setcount(int count = 1);
};
struct action {
	action_s				type;
	const char*				text;
	bool(*proc)(action& a, creature* player, location& area, bool run, bool interactive);
	feat_s					feat;
	action_s				getaction(const creature* player) const { return type; }
};
struct attacki {
	char					bonus;
	dice					damage;
	char					critical_range;
	char					critical_multiply;
};
struct location {
	struct scene {
		char				size;
		const char*			description[2];
	};
	struct place {
		struct scenery*		type;
		unsigned short		flags;
		constexpr place() : type(0), flags(0) {}
		constexpr place(struct scenery* type) : type(type), flags(0) {}
		const char*			getname() const;
		const char*			getnameto() const;
	};
	typedef					bool(*testproc)(const location& area, const creature* player, const creature* opponent);
	scene*					type;
	adat<place, 4>			places;
	adat<creature*, 32>		creatures;
	location();
	void					acting();
	void					add(creature* p, side_s side = EnemySide);
	void					ask(creature* player, aref<action> actions);
	creature*				choose(creature* player, testproc proc, bool interactive) const;
	void					clear();
	void					combat(bool interactive);
	void					enter();
	void					getdescription(stringbuilder& sb);
	void					input(creature* player, bool interactive);
	bool					is(creature* p) const { return creatures.is(p); }
	bool					iscombat() const;
	void					leave();
	bool					match(creature* player, testproc proc) const;
	unsigned				select(creature** result, creature** result_maximum, creature* player, testproc proc) const;
};
class creature {
	pregen_s				pregen;
	char					abilities[6];
	char					classes[NonHero + 1];
	unsigned char			feats[LastFeat / 8 + 1];
	short unsigned			name;
	gender_s				gender;
	specie_s				specie;
	short					hits;
	short					position;
	char					initiative;
	unsigned char			actions;
	side_s					side;
	state_s					state;
	char					defence_bonus[Will+1];
	item					wears[LastGear + 1];
	creature*				close_enemy;
	//
	void					chooseabilities(bool interactive);
	static class_s			chooseclass(bool interactive);
	void					choosefeats(bool interactive, feat_s* source, unsigned source_count, int count = 1);
	void					choosefeats(bool interactive, talent_s talent, int count = 1);
	static gender_s			choosegender(bool interactive);
	void					chooseskill(bool interactive, int count);
	static specie_s			choosespecie(bool interactive);
	void					chooseequip(bool interactive);
	static const char*		getname(short unsigned id);
	static short unsigned	getrandomname(specie_s race, gender_s gender);
	int						getskills() const;
	unsigned				select(feat_s* result, unsigned result_count, talent_s talent) const;
public:
	creature() = default;
	creature(pregen_s pregen);
	creature(bool interactive, bool setplayer);
	creature(specie_s specie, gender_s gender, class_s cls, bool interactive, bool setplayer);
	void* operator new(unsigned size);
	operator bool() const { return specie != NoSpecies; }
	//
	void					act(const char* format, ...) const { actv(format, xva_start(format)); }
	void					actv(stringbuilder& sb, const char* format, const char* param) const;
	void					actv(const char* format, const char* param) const { actv(sb, format, param); }
	void					add(item it);
	void					add(defence_s id, int value);
	void					attack(creature* enemy, wear_s slot, bool interactive, int bonus = 0);
	void					attackop(bool interactive);
	void					clear();
	void					damage(int count, bool interactive);
	void					finish();
	void					get(attacki& e, wear_s slot = Melee) const;
	int						get(ability_s id) const;
	int						get(feat_s id) const;
	int						get(class_s id) const { return classes[id]; }
	int						get(defence_s id) const;
	item&					get(wear_s id) { return wears[id]; }
	static ability_s 		getability(feat_s id);
	int						getbaseattack() const;
	static int				getdice(class_s id);
	int						getfeats() const;
	static aref<feat_s>		getfeats(class_s id);
	int						getheroiclevel() const;
	int						gethitsmax() const;
	const char*				getname() const;
	int						getinitiative() const { return initiative; }
	int						getindex() const { return 0; }
	creature*				getmelee() const;
	creature*				getenemymelee() const;
	int						getreach() const { return 1; }
	side_s					getside() const { return side; }
	size_s					getsize() const { return SizeMeduim; }
	static int				getskillpoints(class_s id);
	int						getspeed() const { return 6; }
	state_s					getstate() const { return state; }
	void					getstatistic(stringbuilder& sb) const;
	bool					is(feat_s id) const;
	bool					is(action_s id) const;
	bool					is(state_s id) const { return state == id; }
	bool					isactive() const;
	bool					isallow(action_s id) const;
	bool					isallow(feat_s id) const;
	bool					isclass(feat_s id) const;
	bool					isenemy(const creature* e) const;
	bool					isplayer() const;
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
	void					set(defence_s id, int value);
	void					setmelee(creature* value) { close_enemy = value; }
	void					setready();
	void					use(action_s id);
};
namespace logs {
struct state {
	const char*				information;
	state();
	~state();
};
}
extern creature*			players[6];
extern aref<action>			standart_actions;
DECLENUM(ability);
DECLENUM(class);
DECLENUM(feat);
DECLENUM(pregen);
DECLENUM(specie);