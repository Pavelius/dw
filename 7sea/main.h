#include "logs/collection.h"
#include "logs/crt.h"
#include "logs/dice.h"
#include "logs/logs.h"

#pragma once

#define getinf_enum(ename) template<> const char* getinfo<ename##_s>(ename##_s value) { return ename##_data[value].text; }

enum trait_s : unsigned char {
	Brawn, Finesse, Resolve, Wits, Panache,
	FirstTrait = Brawn, LastTrait = Panache,
};
enum skill_s : unsigned char {
	Artist, Courtier, Criminal, Doctor, Hunter, Merchant, Performer, Sailor, Scholar, Servant, Spy, Streetwise,
	Archer, Athlete, Buckler, Commander, Crossbow, DirtyFighting, Fencing,
	Firearms, HeavyWeapon, Knife, PanzerhandSkill, Polearm, Pugilism, Rider, Wrestling,
	FirstSkill = Artist, LastSkill = Wrestling,
};
enum advantage_s : unsigned char {
	AbleDrinker, Academy, Appearance, CastilliansEducation,
	Citation, CombatReflexes, Commissions,
	DangerousBeauty, DracheneisenNoble, FoulWeatherJack,
	IndomitableWill, KeenSences,
	Large, Linguist,
	Noble, Ordained, Scoundrel, Small,
	Toughness, University,
	FirstAdvantage = AbleDrinker, LastAdvantage = University,
};
enum knack_s : unsigned char {
	NoKnack,
	Composer, Drawing, Musician, Sculpting, Singing, Writing,
	Dancing, Etiquette, Fashion, Oratory,
	Gambling, Quack, Shadowing, Stealth,
	Diagnosis, FirstAid,
	Fishing, Skinning, Survival, Tracking, TrailSigns, Traps,
	Blacksmith, Butcher, Cooking, Fletcher, Furrier, Glassblower, Innkeeper, Jeweler, Potter,
	Acting,
	Balance, Climbing, Knotwork, Rigging,
	History, Mathematics, Philosophy, Research,
	MenitalTask, Unobrusive,
	Socializing, StreetNavigation,
	AttackBow,
	Footwork, Sprinting, Throwing,
	ParryBuckler,
	Strategy, Tactics,
	AttackCrossbow,
	AttackDirtyFighting,
	AttackFencing, ParryFencing,
	AttackFirearms,
	AttackHeavyWeapon, ParryHeavyWeapon,
	AttackKnife, ParryKnife,
	AttackPanzerhand, ParryPanzerhand,
	AttackPolearm, ParryPolearm,
	AttackPugilism, Jab,
	Ride,
	Grapple,
	FirstKnack = Composer, LastKnack = Grapple,
	// Advenced knacks
	Diplomacy, Gaming, Gossip, LipReading, Mooch, Politics, Scheming, Sedution, Sincerity,
	Ambush, Cheating, Lockpicking, Pickpocket, Prestidigitation, Scrounging,
	Dentist, Examiner, Surgery, Veterinarian,
	AnimalTraining,
	Accounting, Appraising, Bartending, Haggling,
	Circus, ColdRead, Disguise, Storytelling,
	Cartography, Leaping, Navigation, Pilot, SeaLore, Swimming, Weather,
	Astronomy, Law, NaturalPhilosophy, Occult, Theology,
	DriveCarriage, Seneschal, Valet,
	Bribery, Conceal, Cryptography, Forgery, HandSigns, Interrogation, Poison,
	Shopping, UnderworldLore,
	HorseArchery, Snapshot, TrickShooting,
	BreakFall, LongDistanceRunning, Lifting, Rolling, Swinging, SideStep,
	AttackBuckler,
	Artillery, Gunnery, Incitation, Leadership, Logistic,
	ReloadCrossbow,
	AttackImprovisedWeapon, EyeGouge, Kick, ParryImprovisedWeapon, ThroatStrike, ThrowImprovisedWeapon,
	ReloadFirearms,
	ThrowKnife,
	Uppercut,
	SetDefence,
	EarClap,
	Mounting, TrickRiding,
	BearHug, Break, Escape, HeadButt,
	FirstAdvancedKnack = Diplomacy, LastAdvancedKnack = HeadButt,
	// Swordsman's knacks
	Beat, Bind, CorpseACorpse, Disarm, DoubleParry,
	Feint, Lunge, PommelStrike, Riposte, Togging, FindWeakness,
	FirstSwordsmansKnack = Beat, LastSwordsmansKnack = FindWeakness,
	// Glamour knacks
	GlamourGreenMan, GlamourHonoredHunter, GlamourJack, GlamourRobinGoodFellow, GlamourThomas,
	FirstGlamour = GlamourGreenMan, LastGlamour = GlamourThomas,
	// Laerdom knacks
	LaerdomAnger, LaerdomCalm, LaerdomEmpathy, LaerdomFlesh, LaerdomFury,
	LaerdomGateway, LaerdomGloom, LaerdomGreatness, LaerdomHarvest, LaerdomHatred,
	LaerdomIntensity, LaerdomJourney, LaerdomMountain, LaerdomMystery, LaerdomOmen,
	LaerdomPassion, LaerdomRuin, LaerdomSkill, LaerdomSolitude, LaerdomStrength,
	LaerdomUnbound, LaerdomWarrior, LaerdomWealth, LaerdomWholeness,
	FirstLaerdom = LaerdomAnger, LastLaerdom = LaerdomWholeness,
	// Porte knacks
	PorteAttunement, PorteBlooding, PorteBring, PortePocket, PorteWalk,
	FirstPorte = PorteAttunement, LastPorte = PorteWalk,
	// Pyeryem knacks
	PyeryemSpeak, PyeryemMan, PyeryemCat, PyeryemGoshawk, PyeryemBear, PyeryemMouse,
	PyeryemOtter, PyeryemOwl, PyeryemRabbit, PyeryemFox, PyeryemLeopard, PyeryemWolf,
	FirstPyeryem = PyeryemSpeak, LastPyeryem = PyeryemWolf,
	// Sorte knacks
	SorteArcana, SorteCoins, SorteCups, SorteStaves, SorteSwords,
	FirstSorte = SorteArcana, LastSorte = SorteSwords,
	FirstSorceryKnack = FirstGlamour, LastSorceryKnack = LastSorte,
};
enum background_s : unsigned char {
	Amnesia, Cursed, Debt, Defeated, Fear, Hunted, Hunting, LostLove, MistakenIdentify,
	Nemesis, Obligation, Rivalry, Romance, TrueIdentify, Vendetta, Vow,
	FirstBackground = Amnesia, LastBackground = Vow,
};
enum sorcery_s : unsigned char {
	NoSorcery,
	Glamour, Porte, Pyeryem, Laerdom, Sorte,
	FirstSorcery = Glamour, LastSorcery = Sorte,
};
enum ship_s : unsigned char {
	Sloop, Caravela, Frigata, Galeon, Linkor,
	FirstShipType = Sloop, LastShipType = Linkor,
};
enum cargo_s : unsigned char {
	Woods, Ore, Glass, Paper, Leather, Iron, Gold,
	FirstMaterial = Woods, LastMaterial = Gold,
};
enum modification_s : unsigned char {
	HiddenTowline, Oars, ProwRam, ReinforcedMasts,
	ConcealedGunports, Overgunned, SilkSails, SturdyHull, WellTrainedCrew, WideRudder,
	Decoration, ExtendedKeel, Lucky, SmugglingCompartments,
	ExtraCargoSpace, ExtraCrewQuarters, GoodCaptain, NarrowHull,
	BoardingParty, ExtraBoardingGuns, FriendlySpirit, SlightDraft, SwivelCannon,
	FirstModifications = HiddenTowline, LastModifications = SwivelCannon,
	FlimsyMasts, Old, Sluggish,
	BrittleHull, LeakyHull, PoorlyTrainedCrew, SmallKeel, SmallRudder, TatteredSails, Undergunned,
	FirstFlaws = FlimsyMasts, LastFlaws = Undergunned,
};
enum location_s : unsigned char {
	CitySanFeodoro, CityFalconsPoint, CitySanAugustin, CityLaReinaDelMar, CitySanJuan,
	CityLaBucca,
	CitySanFelipe, CityRioja, CityAvila, CitySanEliseo, CityPuertoDeSur, CityLaPasiego, CityTarango,
	CitySanCristobal, CitySanGustavo,
	CityVaticin,
	FirstCity = CitySanFeodoro, LastCity = CityVaticin,
};
enum nation_s : unsigned char {
	Avalon, Castille, Eisen, Montaigne, Ussura, Vendel, Vodacce,
	FirstNation = Avalon, LastNation = Vodacce,
	Crescent, HightEisen, Teodoran, Thean,
	FirstLanguage = Avalon, LastLanguage = Thean,
};
enum swordsman_s : unsigned char {
	NoSwordsman,
	Aldana, Ambrogia, Donowan, Eisenfaust, Leegstra, Valroux,
	FirstSwordsmansSchool = Aldana, LastSwordsmansSchool = Valroux,
};
enum family_s : unsigned char {
	NoFamily,
	Gaegos, Ochoa, Ordunio, Sandoval, Soldano, Torres, Zepeda,
	Asedo, Arsingierro, Avilla, Beharanno, Garsia, Grihalwa, Gusman, Lopez, Montoya, Nunyes, Ontiveros, Ramirez, Rioha, Rios, Rivera, Rodriges, Vaskes, Wellaskes, Yanches,
	AvalonLock, AvalonHood, AvalonGreen, AvalonDoors, AvalonSmith,
	MacAllister, MacDuff, MacBride, MacCordum, MacDonald, MacIchern, MacIntire, MacLaud,
	OBannon, OTool,
	AllaisDuCrieus, DuMontaigne, FlauberDuDore, RicheDuParroise, LevequeDAur,
};
enum side_s : unsigned char {
	PartySide, EnemySide,
};
enum dice_s : unsigned char {
	DramaDice, ReputationDice, GlamourDice,
	FirstDice = DramaDice, LastDice = GlamourDice,
};
enum item_s : unsigned char {
	NoItem,
	Pistol, Bow, Rapier, Sword, Axe, Spear,
};
struct damage_info {
	char				roll;
	char				keep;
};
struct item {
	item_s				type;
	item() : type(NoItem) {}
	item(item_s type) : type(type) {}
	const damage_info&	getdamage() const;
};
struct actor {
	void				act(const char* format, ...) const;
	void				actvs(const actor* opponent, const char* format, ...) const;
	virtual int			get(knack_s id) const = 0;
	virtual int			get(trait_s id) const = 0;
	virtual int			getcount() const { return 1; }
	virtual gender_s	getgender() const { return Male; }
	virtual const char*	getname() const { return ""; }
	char*				sayroll(char* temp, const char* result_maximum, trait_s trait, knack_s knack, int target_number) const;
};
class combatant : public actor {
	char				actions[10];
	side_s				side;
public:
	constexpr combatant() : actions{}, side(PartySide) {}
	void				add(side_s side);
	static void			beforecombat();
	static void			combat();
	virtual void		damage(int wounds, int drama_per_wounds = 20, bool interactive = true) {}
	int					getaction() const { return actions[0]; }
	int					getactioncount() const;
	int					getblockactions() const;
	virtual knack_s		getdefence() const { return Footwork; }
	void				getdescription(char* result, const char* result_maximum) const;
	virtual int			getdramawounds() const { return 0; }
	virtual int			getdramawoundsmax() const { return 0; }
	int					getinitiative() const;
	virtual int			getpassivedefence() const { return 0; }
	virtual side_s		getside() const { return side; }
	bool				isenemy(const combatant* p) const { return getside() != p->getside(); }
	bool				isenemyhero(const combatant* p) const { return p->ishero() && isenemy(p); }
	virtual bool		ishero() const { return false; }
	virtual bool		isplayer() const { return false; }
	bool				isready() const { return getcount()!=0; }
	virtual bool		roll(bool interactive, trait_s trait, knack_s knack, int target_number, int bonus = 0, int* result = 0) = 0;
	void				rollinitiative();
	int					whatdo(bool clear_text) const;
	void				useaction();
};
class hero : public combatant {
	nation_s			nation;
	family_s			family;
	gender_s			gender;
	char				advantages[LastAdvantage + 1];
	char				knacks[LastSorte + 1];
	char				traits[LastTrait + 1];
	unsigned char		dramawound, wounds;
	char				swordsman, sorcery;
	char				dices[LastDice + 1];
	short				experience;
	short unsigned		name;
	//
	void				chooseadvantage(bool interactive, char* skills);
	void				choosecivilskills(bool interactive, char* skills);
	void				choosecombatskills(bool interactive, char* skills);
	void				choosesorcery(bool interactive);
	void				choosetraits(bool interactive);
	void				set(advantage_s value, bool interactive, char* skills);
	void				set(nation_s value);
	void				set(skill_s value, bool interactive, char* skills);
	void				set(swordsman_s value, bool interactive, char* skills);
	int					use(int* dices, dice_s id);
public:
	hero(nation_s nation, gender_s gender, bool interactive, bool add_to_players);
	hero(bool interactive, bool add_to_players) : hero(choosenation(interactive), choosegender(interactive), interactive, add_to_players) {}
	explicit operator bool() const { return traits[0] != 0; }
	//
	bool				contest(bool interactive, trait_s trait, knack_s knack, int bonus, hero* opponent, trait_s opponent_trait, knack_s opponent_knack, int opponent_bonus);
	static gender_s		choosegender(bool interactive = true);
	static nation_s		choosenation(bool interactive = true);
	void				clear();
	void				damage(int wounds, int drama_per_wounds = 20, bool interactive = true) override;
	void				endsession();
	static short unsigned getnamerandom(gender_s gender, nation_s nation);
	static const char*	getname(short unsigned id);
	int					get(advantage_s id) const { return advantages[id]; }
	int					get(dice_s id) const;
	int					get(trait_s id) const override { return traits[id]; }
	int					get(knack_s id) const override { return knacks[id]; }
	int					getcost(advantage_s id) const;
	int					getcost(skill_s value) const;
	int					getdramawounds() const { return dramawound; }
	int					getexperience() const { return experience; }
	gender_s			getgender() const override { return gender; }
	int					getdramawoundsmax() const { return traits[Resolve] * 2; }
	const char*			getname() const override { return getname(name); }
	int					getpassivedefence() const override;
	sorcery_s			getsorcery() const;
	swordsman_s			getswordsman() const;
	int					getwounds() const { return wounds; }
	static bool			iscivil(skill_s value);
	bool				iscripled() const { return dramawound >= traits[Resolve]; }
	bool				ishero() const override { return true; }
	bool				isplayer() const override;
	bool				issorcery() const { return sorcery != 0; }
	bool				isswordsman() const { return swordsman != 0; }
	static int			roll(int roll, int keep);
	bool				roll(bool interactive, trait_s trait, knack_s knack, int target_number, int bonus = 0, int* result = 0);
	void				set(gender_s value) { gender = value; }
	void				set(family_s value) { family = value; }
	void				set(knack_s id, int value) { knacks[id] = value; }
	void				setdramawounds(int value) { dramawound = value; }
	void				setwounds(int value) { wounds = value; }
	void				use(dice_s id);
};
namespace logs {
struct state {
	const char*			information;
	state();
	~state();
};
}
extern adat<hero, 64>	heroes;
extern logs::state		logc;
extern hero*			players[6];
template<class T> const char* getinfo(T e);