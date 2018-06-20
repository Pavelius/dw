#include "main.h"

static struct item_i
{
	struct weapon
	{
		dice			damage;
		item_s			ammo;
	};
	struct armor
	{
		char			defences[Will+1];
	};
	const char*			id;
	const char*			name;
	const char*			descritpion;
	feat_s				group;
	int					cost;
	int					weight;
	weapon				weapon_stats;
	armor				armor_stats;
} item_data[] = {{"", "", ""},
	{"Vibro Dagger", "Вибро-кинжал", "", WeaponProficiencyAdvancedMeleeWeapons},
	{"Vibro Blade", "Вибро-меч", "", WeaponProficiencyAdvancedMeleeWeapons},
	{"Vibro boatan", "Вибро-штык", "", WeaponProficiencyAdvancedMeleeWeapons},
	{"Power spear", "Силовое копье", "", WeaponProficiencyAdvancedMeleeWeapons},
	{"Power staff", "электро-посох", "", WeaponProficiencyAdvancedMeleeWeapons},
	{"Vibro axe", "Вибро-топор", "", WeaponProficiencyAdvancedMeleeWeapons},
	{"Atlati", "Атлати", "", WeaponProficiencyExoticWeapons},
	{"Emfy staff", "Эмфи-посох", "", WeaponProficiencyExoticWeapons},
	{"Cesta", "Цеста", "", WeaponProficiencyExoticWeapons},
	{"Light dagger", "Световой кинжал", "", WeaponProficiencyLightsabers},
	{"Light saber", "Световой меч", "", WeaponProficiencyLightsabers},
	{"Light saber, double", "Световой меч, двойной", "", WeaponProficiencyLightsabers},
	// Простое оружие
	{"Knife", "Нож", "", WeaponProficiencySimpleWeapons},
	{"Club", "Дубина", "", WeaponProficiencySimpleWeapons},
	{"Baton", "Шокирующая палка", "", WeaponProficiencySimpleWeapons},
	{"Mace", "Булава", "", WeaponProficiencySimpleWeapons},
	{"Spear", "Копье", "", WeaponProficiencySimpleWeapons},
	{"Boatan", "Штык на винтовку", "", WeaponProficiencySimpleWeapons},
	{"Staff", "Посох", "", WeaponProficiencySimpleWeapons},
	{"Gauntlets", "Перчатки", "", WeaponProficiencySimpleWeapons},
	{"Gauntlets", "Перчатки", "", WeaponProficiencySimpleWeapons},
	// Дистанционное оружие
	{"Firebat", "Огнемет", "", WeaponProficiencyHeavyWeapons},
	{"Plasmogun", "Плазмолет", "", WeaponProficiencyHeavyWeapons},
	{"Granade Launcher", "Гранатомет", "", WeaponProficiencyHeavyWeapons},
	{"Blaster Machinegun", "Тяжелый лазерный пулемет", "", WeaponProficiencyHeavyWeapons},
	{"Blaster Cannon", "Лазерная пушка", "", WeaponProficiencyHeavyWeapons},
	{"Rocket Launcher", "Ракетница", "", WeaponProficiencyHeavyWeapons},
	{"Blaster Turrel E-web", "Лазерная установка E-Web", "", WeaponProficiencyHeavyWeapons},
	{"Mini Blaster", "Мини-бластер", "", WeaponProficiencyPistols},
	{"Blaster", "Бластер", "", WeaponProficiencyPistols},
	{"Sport Blaster", "Спортивный бластер", "", WeaponProficiencyPistols},
	{"Ion Blaster", "Импульсный бластер", "", WeaponProficiencyPistols},
	{"Gun", "пистолет", "", WeaponProficiencyPistols},
	{"Heavy Blaster", "Тяжелый бластер", "", WeaponProficiencyPistols},
	{"Blaster Shotgun", "Лазерный карабин", "", WeaponProficiencyRifles},
	{"Blaster Rifle", "Лазерная винтовка", "", WeaponProficiencyRifles},
	{"Sport Blaster Rifle", "Спортивная лазерная винтовка", "", WeaponProficiencyRifles},
	{"Ion Rifle", "Импульсная винтовка", "", WeaponProficiencyRifles},
	{"Rifle", "Винтовка", "", WeaponProficiencyRifles},
	{"Blaster Minigun", "Лазерный пулемет", "", WeaponProficiencyRifles},
	{"Heavy Blaster Rifle", "Тяжелая лазерная винтовка", "", WeaponProficiencyRifles},
	{"Plasma Sphere", "Плазменный шар", "", WeaponProficiencySimpleWeapons},
	{"Grenade", "Осколочная граната", "", WeaponProficiencySimpleWeapons},
	{"Grenade, ion", "Импульсная граната", "", WeaponProficiencySimpleWeapons},
	{"Grenade, shock", "Шокирующая граната", "", WeaponProficiencySimpleWeapons},
	{"Thermal detonator", "Термальный детонатор", "", WeaponProficiencySimpleWeapons},
	{"Sling", "Праща", "", WeaponProficiencySimpleWeapons},
	{"Bow", "Лук", "", WeaponProficiencySimpleWeapons},
	{"Net", "Сеть", "", WeaponProficiencySimpleWeapons},
	// Взрывчатки
	{"Trotil", "Взрывчатка", "", WeaponProficiencySimpleWeapons},
	{"Detonator", "Детонатор", "", WeaponProficiencySimpleWeapons},
	// Легкая броня
	{"Blast helmet and vest", "Шлем и куртка", "", ArmourProficienceLight},
	{"Flight suit", "Костюм пилота", "", ArmourProficienceLight},
	{"Armor, jumping", "Броня с прыжковым двигателем", "", ArmourProficienceLight},
	{"Flight suit, armored", "Костюм пилота, бронированный", "", ArmourProficienceLight},
	{"Vondoon crabshell armor", "Вондуунская крабовая броня", "", ArmourProficienceLight},
	{"Armor, trooper", "Броня штурмовика", "", ArmourProficienceLight},
	// Средняя броня
	{"Ceremonial armour", "Церемониальная броня", "", ArmourProficienceMedium},
	{"Power suit", "Энерго-броня", "", ArmourProficienceMedium},
	{"Combat armour", "Боевая броня", "", ArmourProficienceMedium},
	// Тяжелая броня
	{"Space suit, armored", "Бронированный космический скафандр", "", ArmourProficienceHeavy},
	{"Combat armor, heavy", "Тяжелая боевая броня", "", ArmourProficienceHeavy},
	// Устройства
	{"Portable computer", "Переносной коспьютер", ""},
	{"Code cylinder", "Закодированный цилиндр", ""},
	{"Credit chip", "Кредитная карточка", ""},
	{"Holoproject", "Холопроэктор", ""},
	{"Data card", "Флешка", ""},
	{"Data pad", "Карманный компьютер", ""},
	// Устройства обнаружения
	{"Electro binocular", "Электро-бинокль", "Бинокль позволяет получить информацию о расстоянии, азимуте, текущей радиации, а также оснащены приборами ночного видения. Уменьшает штраф расстояния до -1 за каждые 10 квадратов, вместо -5 за каждые 10 квадратов."},
	{"Glow rod", "Светящаяся шашка", "Переносной осветитель, который производит света, достаточно для освещения 6 квадратов."},
	{"Fusion latern", "Атомный фонарик", "Фонарик обеспечивает свет и тепло. Освещает 6 квадратов впереди."},
	{"Audio-recorder", "Диктофон", "Хранит 100 часов звука в отличном качестве."},
	{"Holo-recorder", "Холорекордер", "Хранит 1 час качественной голограммы."},
	{"Video-recorder", "Видеокамера", "Хранит 10 часов видео в отличном качестве."},
	{"Sensor pack", "Портативный радар", "Квардратная коробка с дисплеем, разноцветными лампочками и индикатором. Позволяет сканировать местность в пределах 1 киллометра на наличие форм жизни, радиосигналов, радиации или других угроз."},
	// Связь
	{"Comlink", "Комлинк", ""},
	{"Pocket decipher", "Карманный шифратор", "Простое устройство, которое может быть подключено к передатчикам и приемникам информации, таким как комлинк."},
	{"Voxbox", "Голосовой ящик", ""},
};
assert_enum(item, VoxBox);
getstr_enum(item);

int item::getreflexes() const
{
	return 0;
}

const dice& item::getdice() const
{
	return item_data[type].weapon_stats.damage;
}

bool item::ismelee() const
{
	return type <= GlovesMedium;
}

bool item::isweapon() const
{
	if(type == NoItem)
		return false;
	return type <= Net;
}

void item::clear()
{
	type = NoItem;
	count = 0;
}

void item::setcount(int count)
{
	if(!count)
		clear();
	else
	{
		if(count > 256)
			count = 256;
		this->count = count - 1;
	}
}