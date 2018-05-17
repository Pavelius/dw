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

const char* assets_types_text[][2] = {{"melee weapon", "оружие ближнего боя"},
{"pistol", "пистолет"},
{"rifle", "винтовка"},
{"heavy weapon", "тяжелое оружие"},
{"grenade", "граната"},
{"charge", "заряд"},
{"rugged attire", "лохмотья"},
{"simple attire", "практичная одежда"},
{"cultural attire", "культурная одежда"},
{"formal attire", "официальный прикид"},
{"uniform attire", "униформа"},
{"bike", "мотоцикл"},
{"groundcar", "машина"},
{"walker", "двуног"},
{"quadwalker", "четвероход"},
{"speeder", "спидер"},
{"shuttle", "шаттл"},
{"squad", "отряд"},
{"techs", "специалисты"},
{"gang", "банда"},
{"staff", "сотрудники"},
};
static_assert((sizeof(assets_types_text) / sizeof(assets_types_text[0])) == Staff + 1, "Invalid assets types text count");
const char* assets_kits_text[][2] = {{"", ""},
{"Tools to send and receive signals", "Инструменты для посылки и получения сигналов"},
{"Tools to access, program, diagnose and repair computer systems", "Инструменты для доступа, програмирования, диагностики и ремонта компьютеров"},
{"Tools to repair and dismantle machinery", "Инструменты для ремонта и демонтажа техники"},
{"Tools to gain access to forbidden places", "Инструменты для проникновения в запрещенные и охраняемые места"},
{"Tools to perform medical treatments", "Инструменты для выпонения медицинского ухода"},
{"Tools to study and experiment out in the field", "Инструменты для изучения и экспериментов в полевых условиях"},
{"Tools to observe and monitor", "Инструменты для наблюдения и мониторинга"},
{"Tools to observe and monitor", "Инструменты для пересечения труднопроходимых ландшафтов"},
};
const char* assets_tags_text[][2] = {{"", ""},
{"Concealed", "Скрытое"},
{"Defensive", "Оборонительное"},
{"Destructive", "Разрушительное"},
{"Energy", "Энергетическое"},
{"Flexible", "Гибкое"},
{"Glove", "Перчатка"},
{"Hafted", "На древке"},
{"Heavy", "Тяжелое"},
{"Impact", "Ударное"},
{"Impaling", "Колющее"},
{"Penetrating", "Проникающее"},
{"Ripper", "Пила"},
{"Severing", "Рубящее"},
{"Shock", "Электрическое"},
{"Stun", "Парализирующее"},
{"Stylish", "Стильное"},
{"Thrown", "Метательное"},
{"Attachment", "Прикрепленное"},
{"Burst", "Очередь"},
{"Chemical", "Химическое"},
{"Explosive", "Взрывное"},
{"Keyed", "Закодированное"},
{"Laser", "Лазерное"},
{"Launcher", "Пусковая установка"},
{"Mounted", "Навесное"},
{"Plasma", "Плазменное"},
{"Rapid fire", "Автоматическое"},
{"Scope", "Прицел"},
{"Shrapnel", "Осколки"},
{"Silenced", "Глушитель"},
{"Stabilized", "Устойчивое"},
};
static assets_info assets_basic[] = {{{"Combat Knife", "Боевой нож"}, MeleeWeapon, {Severing}},
{{"Lenght of Chain", "Длинная цепь"}, MeleeWeapon, {Flexible}},
{{"Brass Knuckles", "Медный кастет"}, MeleeWeapon, {Glove}},
{{"Stun Baton", "Шокирующий жезл"}, MeleeWeapon, {Shock}},
{{"Chainsaw", "Бензопила"}, MeleeWeapon, {Heavy, Ripper}},
{{"Throwing Knives", "Метательные ножи"}, MeleeWeapon, {Thrown, Concealed}},
{{"Rapier", "Рапира"}, MeleeWeapon, {Impaling, Stylish}},
{{"Shatter Hammer", "Вибро молот"}, MeleeWeapon, {Impact, Hafted, Destructive}},
{{"Storm Claws", "Боевые когти"}, MeleeWeapon, {Severing, Glove, Shock}},
{{"Star Sword", "Звездный меч"}, MeleeWeapon, {Severing, Defensive, Energy}},
// Firearm
{{"Pistol", "Пистолет"}, Pistol},
{{"Shotgun", "Ружье"}, Rifle},
{{"Stunner Pistol", "Шокирующий пистолет"}, Pistol, {Stun}},
{{"Scattershot", "Гвоздемет"}, Pistol, {Burst}},
{{"Laser Rifle", "Лазерная винтовка"}, Rifle, {Laser}},
{{"Sniper Rifle", "Снайперская винтовка"}, Rifle, {Scope, Silenced}},
{{"Grenade Launcher", "Гранатомет"}, Rifle, {Launcher, Explosive}},
// Heavy weapon
{{"Heavy Stabber", "Тяжелый звездомет"}, HeavyWeapon},
{{"LMG", "ЛМГ"}, HeavyWeapon, {Sustained}},
{{"Roket Launcher", "Ракетница"}, HeavyWeapon, {Detonation}},
{{"Plasma cannon", "Плазменная пушка"}, HeavyWeapon, {Plasma}},
{{"Flamethrover", "Огнемет"}, HeavyWeapon, {Chemical, Spray}},
{{"Lighting Coil", "Разрядник молнии"}, HeavyWeapon, {Shock, Seeking}},
{{"Sonic Cannon", "Звуковая пушка"}, HeavyWeapon, {Impact, Concussive}},
{{"Hull Buster", "Корпусодер"}, HeavyWeapon, {Breaching, Seeking}},
// Explosive
{{"Landmine", "Мина"}, Charge},
{{"Smoke bomb", "Дымовая граната"}, Grenade, {Chemical}},
{{"Frag Grenade", "Осколочная граната"}, Grenade, {Shrapnel}},
{{"Flashbang", "Световая граната"}, Grenade, {Concussive}},
{{"Proximity Mine", "Мина Движения"}, Grenade, {Sticky}},
{{"Shaped Charge", "Взрывчатка"}, Grenade, {Focused, Breaching}},
{{"Incendiary Grenade", "Воспламеняющая граната"}, Grenade, {Plasma, Chemical}},
{{"Bomb briefcase", "Бомба"}, Grenade, {HighYield, Concealed}},
// Attire
{{"Jumpsuit", "Костюм пилота"}, UniformAttire},
{{"Evening Gown", "Вечернее платье"}, FormalAttire},
{{"Brown Coat", "Коричневый плащ"}, RuggedAttire},
{{"Body armor", "Нательная броня"}, UniformAttire, {Armored}},
{{"EVA suit", "Герметичный костюм"}, SimpleAttire, {Sealed}},
{{"Customs Uniform", "Униформа таможенника"}, UniformAttire, {NoAssetsTag}, NoKit, DetectWeapon},
{{"Climbing Gear", "Одежда альпиниста"}, RuggedAttire, {NoAssetsTag}, WildernessKit},
{{"Bulletproof Suit", "Пуленепробиваемый костюм"}, FormalAttire, {Meshweave}},
{{"Regalia", "Дворянский наряд"}, CulturalAttire, {Impressive}},
{{"Wing Suit", "Летающий костюм"}, SimpleAttire, {JumpJet, Sealed}},
{{"Battle plate", "Бронекостюм"}, RuggedAttire, {Armored, Carapace}},
{{"Boarding armor", "Броня десанта"}, UniformAttire, {Armored, Sealed}},
// Vehicle
{{"Stunt Bike", "Крутой мотоцикл"}, Bike, {Agile}},
// Flyer
{{"Skycar", "Летающая машина"}, Shuttle},
{{"Interceptor", "Перехватчик"}, Speeder, {Armed}},
//
{{"Students", "Студенты", "студентов"}, Techs},
{{"Rabble", "Грабители", "грабителей"}, Gang},
{{"Bandits", "Бандиты", "бандитов"}, Gang, {Armed}},
{{"Soldiers", "Солдаты", "солдат"}, Squad, {Armed}},
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
		{"Weapons", "Оружие"},
	{"Outfits", "Одежда"},
	{"Vehicles", "Транспорт"},
	{"Crew", "Команда"},
	{"Kits", "Инструменты"},
	{"Cargo", "Груз"},
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