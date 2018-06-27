#include "main.h"

static struct item_i {
	struct weapon {
		dice			damage;
		item_s			ammo;
	};
	struct armor {
		char			defences[Will + 1];
	};
	const char*			id;
	const char*			name;
	const char*			descritpion;
	feat_s				group;
	int					cost;
	int					weight;
	weapon				weapon_stats;
	cflags<wear_s>		slots;
	armor				armor_stats;
	bool				is(wear_s id) const { return slots.is(id); }
} item_data[] = {{"", "", ""},
{"Vibro Dagger", "Вибро-кинжал", "", WeaponProficiencyAdvancedMeleeWeapons, 0, 0, {}, {Melee}},
{"Vibro Blade", "Вибро-меч", "", WeaponProficiencyAdvancedMeleeWeapons, 0, 0, {}, {Melee}},
{"Vibro boatan", "Вибро-штык", "", WeaponProficiencyAdvancedMeleeWeapons, 0, 0, {}, {Melee}},
{"Power spear", "Силовое копье", "", WeaponProficiencyAdvancedMeleeWeapons, 0, 0, {}, {Melee}},
{"Power staff", "электро-посох", "", WeaponProficiencyAdvancedMeleeWeapons, 0, 0, {}, {Melee}},
{"Vibro axe", "Вибро-топор", "", WeaponProficiencyAdvancedMeleeWeapons, 0, 0, {}, {Melee}},
{"Atlati", "Атлати", "", WeaponProficiencyExoticWeapons, 0, 0, {}, {Melee}},
{"Emfy staff", "Эмфи-посох", "", WeaponProficiencyExoticWeapons, 0, 0, {}, {Melee}},
{"Cesta", "Цеста", "", WeaponProficiencyExoticWeapons, 0, 0, {}, {Melee}},
{"Light dagger", "Световой кинжал", "", WeaponProficiencyLightsabers, 0, 0, {{2, 6}}, {Melee}},
{"Light saber", "Световой меч", "", WeaponProficiencyLightsabers, 0, 0, {{2, 8}}, {Melee}},
{"Light saber, double", "Световой меч, двойной", "", WeaponProficiencyLightsabers, 0, 0, {}, {Melee}},
// Простое оружие
{"Knife", "Нож", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
{"Club", "Дубина", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
{"Baton", "Шокирующая палка", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
{"Mace", "Булава", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
{"Spear", "Копье", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
{"Boatan", "Штык на винтовку", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
{"Staff", "Посох", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
{"Gauntlets", "Перчатки", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
{"Gauntlets", "Перчатки", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Melee}},
// Дистанционное оружие
{"Firebat", "Огнемет", "", WeaponProficiencyHeavyWeapons, 0, 0, {}, {Ranged}},
{"Plasmogun", "Плазмолет", "", WeaponProficiencyHeavyWeapons, 0, 0, {}, {Ranged}},
{"Granade Launcher", "Гранатомет", "", WeaponProficiencyHeavyWeapons, 0, 0, {}, {Ranged}},
{"Blaster Machinegun", "Тяжелый лазерный пулемет", "", WeaponProficiencyHeavyWeapons, 0, 0, {}, {Ranged}},
{"Blaster Cannon", "Лазерная пушка", "", WeaponProficiencyHeavyWeapons, 0, 0, {}, {Ranged}},
{"Rocket Launcher", "Ракетница", "", WeaponProficiencyHeavyWeapons, 0, 0, {}, {Ranged}},
{"Blaster Turrel E-web", "Лазерная установка E-Web", "", WeaponProficiencyHeavyWeapons, 0, 0, {}, {Ranged}},
{"Mini Blaster", "Мини-бластер", "", WeaponProficiencyPistols, 0, 0, {}, {Ranged}},
{"Blaster", "Бластер", "", WeaponProficiencyPistols, 0, 0, {{3, 6}}, {Ranged}},
{"Sport Blaster", "Спортивный бластер", "", WeaponProficiencyPistols, 0, 0, {}, {Ranged}},
{"Ion Blaster", "Импульсный бластер", "", WeaponProficiencyPistols, 0, 0, {}, {Ranged}},
{"Gun", "пистолет", "", WeaponProficiencyPistols, 0, 0, {}, {Ranged}},
{"Heavy Blaster", "Тяжелый бластер", "", WeaponProficiencyPistols, 0, 0, {}, {Ranged}},
{"Blaster Shotgun", "Лазерный карабин", "", WeaponProficiencyRifles, 0, 0, {}, {Ranged}},
{"Blaster Rifle", "Лазерная винтовка", "", WeaponProficiencyRifles, 0, 0, {{3, 8}}, {Ranged}},
{"Sport Blaster Rifle", "Спортивная лазерная винтовка", "", WeaponProficiencyRifles, 0, 0, {{3, 6}}, {Ranged}},
{"Ion Rifle", "Импульсная винтовка", "", WeaponProficiencyRifles, 0, 0, {}, {Ranged}},
{"Rifle", "Винтовка", "", WeaponProficiencyRifles, 0, 0, {}, {Ranged}},
{"Blaster Minigun", "Лазерный пулемет", "", WeaponProficiencyRifles, 0, 0, {}, {Ranged}},
{"Heavy Blaster Rifle", "Тяжелая лазерная винтовка", "", WeaponProficiencyRifles, 0, 0, {}, {Ranged}},
{"Plasma Sphere", "Плазменный шар", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Ranged}},
{"Grenade", "Осколочная граната", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Throwing}},
{"Grenade, ion", "Импульсная граната", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Throwing}},
{"Grenade, shock", "Шокирующая граната", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Throwing}},
{"Thermal detonator", "Термальный детонатор", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Throwing}},
{"Sling", "Праща", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Ranged}},
{"Bow", "Лук", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Ranged}},
{"Net", "Сеть", "", WeaponProficiencySimpleWeapons, 0, 0, {}, {Ranged}},
// Взрывчатки
{"Trotil", "Взрывчатка", "", WeaponProficiencySimpleWeapons},
{"Detonator", "Детонатор", "", WeaponProficiencySimpleWeapons},
// Легкая броня
{"Blast helmet and vest", "Шлем и куртка", "", ArmourProficienceLight, 0, 0, {}, {Armor}},
{"Flight suit", "Костюм пилота", "", ArmourProficienceLight, 0, 0, {}, {Armor}},
{"Armor, jumping", "Броня с прыжковым двигателем", "", ArmourProficienceLight, 0, 0, {}, {Armor}},
{"Flight suit, armored", "Костюм пилота, бронированный", "", ArmourProficienceLight, 0, 0, {}, {Armor}},
{"Vondoon crabshell armor", "Вондуунская крабовая броня", "", ArmourProficienceLight, 0, 0, {}, {Armor}},
{"Armor, trooper", "Броня штурмовика", "", ArmourProficienceLight, 0, 0, {}, {Armor}},
// Средняя броня
{"Ceremonial armour", "Церемониальная броня", "", ArmourProficienceMedium, 0, 0, {}, {Armor}},
{"Power suit", "Энерго-броня", "", ArmourProficienceMedium, 0, 0, {}, {Armor}},
{"Combat armour", "Боевая броня", "", ArmourProficienceMedium, 0, 0, {}, {Armor}},
// Тяжелая броня
{"Space suit, armored", "Бронированный космический скафандр", "", ArmourProficienceHeavy, 0, 0, {}, {Armor}},
{"Combat armor, heavy", "Тяжелая боевая броня", "", ArmourProficienceHeavy, 0, 0, {}, {Armor}},
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

int item::getreflexes() const {
	return 0;
}

const dice& item::getdice() const {
	return item_data[type].weapon_stats.damage;
}

bool item::is(wear_s id) const {
	return item_data[type].is(id);
}

void item::clear() {
	type = NoItem;
	count = 0;
}

void item::setcount(int count) {
	if(!count)
		clear();
	else {
		if(count > 255)
			count = 255;
		this->count = count;
	}
}