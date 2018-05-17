#include "main.h"

enum assets_type_s : unsigned char {
	MeleeWeapon, Pistol, Rifle, HeavyWeapon, Grenade, Charge,
	RuggedAttire, SimpleAttire, CulturalAttire, FormalAttire, UniformAttire,
	Bike, Groundcar, Walker, QuadWalker, Speeder, Shuttle,
	Squad, Techs, Gang, Staff,
};
extern const char* assets_types_text[][2];
enum assets_tag_s : unsigned char {
	NoAssetsTag,
	// Weapon
	Concealed, Defensive, Destructive, Energy, Flexible,
	Glove, Hafted, Heavy, Impact, Impaling, Penetrating,
	Ripper, Severing, Shock, Stun, Stylish, Thrown,
	Attachment, Burst, Chemical, Explosive, Keyed, Laser, Launcher,
	Mounted, Plasma, RapidFire, Scope, Shrapnel, Silenced,
	Stabilized,
	Breaching, Concussive, Detonation, Seeking, Spray, Sustained,
	Cluster, Focused, Haywire, HighYield, Sticky,
	// Attire
	Armored, Carapace, Comms, Connected, Impressive,
	JumpJet, Meshweave, Rig, Tough, Sealed, Sensor, Shielded, Stealthy, Visor,
	// Vehicle
	Agile, Armed, Boosters, Controlled, Plated, Reinforced,
	Rugged, Transport, Turret, Workspace,
	// Crew
	Artillery, Athletic, Beautiful, Builders,
	Fearless, Informants, Loyal, Mechanics, Medics, Numerous,
	Teamsters, Wreckers,
};
static assets_tag_s melee_weapon_upgrade[] = {
	Concealed, Defensive, Destructive, Energy, Flexible,
	Glove, Hafted, Heavy, Impact, Impaling,
	Penetrating, Ripper, Severing, Shock, Stun,
	Stylish, Thrown,
	NoAssetsTag
};
static assets_tag_s range_weapon_upgrade[] = {
	Attachment, Burst, Concealed, Chemical, Destructive,
	Explosive, Impact, Keyed, Laser, Launcher,
	Mounted, Penetrating, Plasma, RapidFire, Scope,
	Shock, Shrapnel, Silenced, Stabilized, Stun,
	Stylish,
	NoAssetsTag
};
struct assets_info {
	const char*		name[3];
	assets_type_s	group;
	assets_tag_s	upgrades[3];
	kit_s		kit;
	visor_s			visor;
	chemical_s		chemical;
	asset_s	armed;

	assets_groups getgroup() const {
		switch(group) {
		case MeleeWeapon: case Pistol: case Rifle: case HeavyWeapon: case Grenade: case Charge:
			return GroupWeapon;
		case RuggedAttire: case SimpleAttire: case CulturalAttire: case FormalAttire: case UniformAttire:
			return GroupAttire;
		case Bike: case Groundcar: case Walker: case QuadWalker: case Speeder: case Shuttle:
			return GroupVehicle;
		case Squad: case Gang: case Techs: case Staff:
			return GroupCrew;
		default:
			return GroupKit;
		}
	}

	const assets_tag_s* getupgrades() const {
		switch(group) {
		case MeleeWeapon:
			return melee_weapon_upgrade;
		case Pistol:
		case Rifle:
			return range_weapon_upgrade;
		default:
			return 0;
		}
	}

	int	getmarket() const {
		return zlen(upgrades) - ((group == MeleeWeapon) ? 1 : 0);
	}

	bool is(assets_tag_s t) const {
		return upgrades[0] == t
			|| upgrades[1] == t
			|| upgrades[2] == t
			|| upgrades[3] == t;
	}

};

const char* assets_types_text[][2] = {{"melee weapon", "������ �������� ���"},
{"pistol", "��������"},
{"rifle", "��������"},
{"heavy weapon", "������� ������"},
{"grenade", "�������"},
{"charge", "�����"},
{"rugged attire", "��������"},
{"simple attire", "���������� ������"},
{"cultural attire", "���������� ������"},
{"formal attire", "����������� ������"},
{"uniform attire", "��������"},
{"bike", "��������"},
{"groundcar", "������"},
{"walker", "������"},
{"quadwalker", "����������"},
{"speeder", "������"},
{"shuttle", "�����"},
{"squad", "�����"},
{"techs", "�����������"},
{"gang", "�����"},
{"staff", "����������"},
};
static_assert((sizeof(assets_types_text) / sizeof(assets_types_text[0])) == Staff + 1, "Invalid assets types text count");
const char* assets_kits_text[][2] = {{"", ""},
{"Tools to send and receive signals", "����������� ��� ������� � ��������� ��������"},
{"Tools to access, program, diagnose and repair computer systems", "����������� ��� �������, ���������������, ����������� � ������� �����������"},
{"Tools to repair and dismantle machinery", "����������� ��� ������� � ��������� �������"},
{"Tools to gain access to forbidden places", "����������� ��� ������������� � ����������� � ���������� �����"},
{"Tools to perform medical treatments", "����������� ��� ��������� ������������ �����"},
{"Tools to study and experiment out in the field", "����������� ��� �������� � ������������� � ������� ��������"},
{"Tools to observe and monitor", "����������� ��� ���������� � �����������"},
{"Tools to observe and monitor", "����������� ��� ����������� ���������������� ����������"},
};
const char* assets_tags_text[][2] = {{"", ""},
{"Concealed", "�������"},
{"Defensive", "��������������"},
{"Destructive", "��������������"},
{"Energy", "��������������"},
{"Flexible", "������"},
{"Glove", "��������"},
{"Hafted", "�� ������"},
{"Heavy", "�������"},
{"Impact", "�������"},
{"Impaling", "�������"},
{"Penetrating", "�����������"},
{"Ripper", "����"},
{"Severing", "�������"},
{"Shock", "�������������"},
{"Stun", "��������������"},
{"Stylish", "��������"},
{"Thrown", "�����������"},
{"Attachment", "�������������"},
{"Burst", "�������"},
{"Chemical", "����������"},
{"Explosive", "��������"},
{"Keyed", "��������������"},
{"Laser", "��������"},
{"Launcher", "�������� ���������"},
{"Mounted", "��������"},
{"Plasma", "����������"},
{"Rapid fire", "��������������"},
{"Scope", "������"},
{"Shrapnel", "�������"},
{"Silenced", "���������"},
{"Stabilized", "����������"},
};
static assets_info assets_basic[] = {{{"Combat Knife", "������ ���"}, MeleeWeapon, {Severing}},
{{"Lenght of Chain", "������� ����"}, MeleeWeapon, {Flexible}},
{{"Brass Knuckles", "������ ������"}, MeleeWeapon, {Glove}},
{{"Stun Baton", "���������� ����"}, MeleeWeapon, {Shock}},
{{"Chainsaw", "���������"}, MeleeWeapon, {Heavy, Ripper}},
{{"Throwing Knives", "����������� ����"}, MeleeWeapon, {Thrown, Concealed}},
{{"Rapier", "������"}, MeleeWeapon, {Impaling, Stylish}},
{{"Shatter Hammer", "����� �����"}, MeleeWeapon, {Impact, Hafted, Destructive}},
{{"Storm Claws", "������ �����"}, MeleeWeapon, {Severing, Glove, Shock}},
{{"Star Sword", "�������� ���"}, MeleeWeapon, {Severing, Defensive, Energy}},
// Firearm
{{"Pistol", "��������"}, Pistol},
{{"Shotgun", "�����"}, Rifle},
{{"Stunner Pistol", "���������� ��������"}, Pistol, {Stun}},
{{"Scattershot", "���������"}, Pistol, {Burst}},
{{"Laser Rifle", "�������� ��������"}, Rifle, {Laser}},
{{"Sniper Rifle", "����������� ��������"}, Rifle, {Scope, Silenced}},
{{"Grenade Launcher", "����������"}, Rifle, {Launcher, Explosive}},
// Heavy weapon
{{"Heavy Stabber", "������� ���������"}, HeavyWeapon},
{{"LMG", "���"}, HeavyWeapon, {Sustained}},
{{"Roket Launcher", "���������"}, HeavyWeapon, {Detonation}},
{{"Plasma cannon", "���������� �����"}, HeavyWeapon, {Plasma}},
{{"Flamethrover", "�������"}, HeavyWeapon, {Chemical, Spray}},
{{"Lighting Coil", "��������� ������"}, HeavyWeapon, {Shock, Seeking}},
{{"Sonic Cannon", "�������� �����"}, HeavyWeapon, {Impact, Concussive}},
{{"Hull Buster", "����������"}, HeavyWeapon, {Breaching, Seeking}},
// Explosive
{{"Landmine", "����"}, Charge},
{{"Smoke bomb", "������� �������"}, Grenade, {Chemical}},
{{"Frag Grenade", "���������� �������"}, Grenade, {Shrapnel}},
{{"Flashbang", "�������� �������"}, Grenade, {Concussive}},
{{"Proximity Mine", "���� ��������"}, Grenade, {Sticky}},
{{"Shaped Charge", "����������"}, Grenade, {Focused, Breaching}},
{{"Incendiary Grenade", "�������������� �������"}, Grenade, {Plasma, Chemical}},
{{"Bomb briefcase", "�����"}, Grenade, {HighYield, Concealed}},
// Attire
{{"Jumpsuit", "������ ������"}, UniformAttire},
{{"Evening Gown", "�������� ������"}, FormalAttire},
{{"Brown Coat", "���������� ����"}, RuggedAttire},
{{"Body armor", "��������� �����"}, UniformAttire, {Armored}},
{{"EVA suit", "����������� ������"}, SimpleAttire, {Sealed}},
{{"Customs Uniform", "�������� �����������"}, UniformAttire, {NoAssetsTag}, NoKit, DetectWeapon},
{{"Climbing Gear", "������ ����������"}, RuggedAttire, {NoAssetsTag}, WildernessKit},
{{"Bulletproof Suit", "����������������� ������"}, FormalAttire, {Meshweave}},
{{"Regalia", "���������� �����"}, CulturalAttire, {Impressive}},
{{"Wing Suit", "�������� ������"}, SimpleAttire, {JumpJet, Sealed}},
{{"Battle plate", "�����������"}, RuggedAttire, {Armored, Carapace}},
{{"Boarding armor", "����� �������"}, UniformAttire, {Armored, Sealed}},
// Vehicle
{{"Stunt Bike", "������ ��������"}, Bike, {Agile}},
// Flyer
{{"Skycar", "�������� ������"}, Shuttle},
{{"Interceptor", "�����������"}, Speeder, {Armed}},
//
{{"Students", "��������", "���������"}, Techs},
{{"Rabble", "���������", "����������"}, Gang},
{{"Bandits", "�������", "��������"}, Gang, {Armed}},
{{"Soldiers", "�������", "������"}, Squad, {Armed}},
};

assets_groups assets::getgroup() const {
	return assets_basic[type].getgroup();
}

void assets::clear() {
	type = CombatKnife;
	count = 0;
}

template<> const char*	getstr<assets_groups>(assets_groups value) {
	static const char* strings[][2] = {
		{"Weapons", "������"},
	{"Outfits", "������"},
	{"Vehicles", "���������"},
	{"Crew", "�������"},
	{"Kits", "�����������"},
	{"Cargo", "����"},
	};
	return strings[value][1];
}

template<> const char* getstr<asset_s>(asset_s type) {
	return assets_basic[type].name[1];
}

const char* assets::getname() const {
	return getstr(type);
}

char* assets::getnamefull(char* temp) const {
	zcpy(temp, getname());
	if(assets_basic[type].upgrades[0]) {
		zcat(temp, " (");
		for(int i = 0; i < sizeof(assets_basic[type].upgrades) / sizeof(assets_basic[type].upgrades[0]); i++) {
			if(!assets_basic[type].upgrades[i])
				break;
			if(i != 0)
				zcat(temp, ", ");
			zcat(temp, assets_tags_text[assets_basic[type].upgrades[i]][1]);
		}
		zcat(temp, ")");
	}
	return temp;
}

int	assets::getmarket() const {
	return assets_basic[type].getmarket();
}

severity_s assets::getseverity() const {
	if(!count)
		return Minor;
	switch(assets_basic[type].group) {
	case MeleeWeapon: return Major;
	case Pistol: return Severe;
	case Rifle: return Severe;
	case HeavyWeapon: return Critical;
	case Grenade: return Critical;
	case Charge: return Fatal;
	default: return Minor;
	}
}

int assets::getarmor() const {
	auto& e = assets_basic[type];
	int r = 0;
	if(e.is(Armored))
		r += 2;
	if(e.is(Meshweave))
		r++;
	if(e.is(Shielded))
		r++;
	if(e.is(Carapace))
		r += 3;
	if(e.is(Reinforced))
		r += 3;
	if(e.is(Plated))
		r += 3;
	return r;
}

chemical_s assets::getchemical() const {
	return assets_basic[type].chemical;
}

bool assets::iscrew() const {
	return assets_basic[type].getgroup() == GroupCrew;
}

bool assets::isbreaching() const {
	auto& e = assets_basic[type];
	return e.is(Breaching);
}

bool assets::isclumsy() const {
	if(type == HeavyWeapon)
		return true;
	auto& e = assets_basic[type];
	if(e.is(Reinforced))
		return true;
	return e.is(Carapace);
}

bool assets::isdestructive() const {
	if(type == HeavyWeapon)
		return true;
	if(type == Charge)
		return true;
	auto& e = assets_basic[type];
	return e.is(Destructive);
}

bool assets::istwohanded() const {
	if(type == Rifle)
		return true;
	auto& e = assets_basic[type];
	if(e.is(Hafted))
		return true;
	if(e.is(Heavy))
		return true;
	if(e.is(Thrown))
		return true;
	return false;
}

bool assets::is(assets_range_s range) const {
	if(!count)
		return false;
	auto& e = assets_basic[type];
	switch(e.group) {
	case MeleeWeapon:
		switch(range) {
		case Melee: return !e.is(Flexible) && !e.is(Thrown);
		case Adjacent: return e.is(Flexible) || e.is(Hafted) || e.is(Thrown);
		case Close: return e.is(Thrown);
		default: return false;
		}
	case Pistol:
		switch(range) {
		case Adjacent: return true;
		case Close: return true;
		default: return false;
		}
	case Rifle:
		switch(range) {
		case Close: return !e.is(Scope);
		case Far: return true;
		case Distant: return e.is(Scope);
		default: return false;
		}
	case HeavyWeapon:
		switch(range) {
		case Far: return true;
		case Distant: return true;
		default: return false;
		}
	default:
		return false;
	}
}

int assets::getcountmax() const {
	switch(assets_basic[type].group) {
	case Staff: return 2;
	case Techs: return 3;
	case Squad: return 4;
	case Gang: return 6; break;
	default: return 1;
	}
}

char* assets::getname(char* result, const char* result_maximum) const {
	auto n = getcount();
	if(n == 1)
		zcpy(result, assets_basic[type].name[1]);
	else
		szprints(result, result_maximum, "%2i %1", assets_basic[type].name[2], count);
	return result;
}

void assets::set(asset_s value) {
	type = value;
	count = getcountmax();
}

int	assets::select(asset_s* indecies, assets_groups group, int market) {
	auto p = indecies;
	for(auto i = CombatKnife; i < sizeof(assets_basic) / sizeof(assets_basic[0]); i = (asset_s)(i + 1)) {
		if(assets_basic[i].getgroup() != group)
			continue;
		if(market != -1 && assets_basic[i].getmarket() != market)
			continue;
		*p++ = i;
	}
	return p - indecies;
}