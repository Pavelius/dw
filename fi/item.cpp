#include "main.h"

static struct item_info {
	struct weapon_info {
		range_s			range;
		char			grip;
		char			damage;
		talent_s		talent;
	};
	const char*			id;
	const char*			name;
	int					cost;
	slot_s				slot;
	char				bonus;
	weapon_info			weapon;
	cflags<feature_s>	flags;
} item_data[] = {{"Hand", "Рука", 0, Hand, 0, {Arm, 0, 1}, {Blunt}},
{"Knife", "Нож", 1, Hand, 1, {Arm, 1, 1, KnifeFighter}, {Light, Pointed}},
{"Dagger", "Кинжал", 2, Hand, 1, {Arm, 1, 1, KnifeFighter}, {Light, Edged, Pointed}},
{"Falchion", "Мачете", 4, Hand, 1, {Arm, 1, 2, KnifeFighter}, {Edged, Pointed}},
{"Shortsword", "Короткий меч", 6, Hand, 2, {Arm, 1, 1, SwordFighter}, {Edged, Pointed, Parrying}},
{"Broadsword", "Меч", 10, Hand, 2, {Arm, 1, 2, SwordFighter}, {Edged, Pointed, Parrying}},
{"Longsword", "Длинный меч", 18, Hand, 2, {Arm, 1, 2, SwordFighter}, {Heavy, Edged, Pointed, Parrying}},
{"TwoHandedSword", "Двуручный меч", 40, Hand, 2, {Arm, 2, 3, SwordFighter}, {Heavy, Edged, Pointed, Parrying}},
{"Scimitar", "Сабля", 8, Hand, 1, {Arm, 1, 2, SwordFighter}, {Edged, Pointed, Hook, Parrying}},
{"Handaxe", "Топор", 2, Hand, 2, {Arm, 1, 2, AxeFighter}, {Edged, Hook}},
{"Battleaxe", "Боевой топор", 6, Hand, 2, {Arm, 1, 2, AxeFighter}, {Heavy, Edged, Hook}},
{"TwoHandedAxe", "Двуручный топор", 18, Hand, 2, {Arm, 2, 3, AxeFighter}, {Heavy, Edged, Hook}},
{"Mace", "Булава", 4, Hand, 2, {Arm, 1, 1, HammerFighter}, {Blunt}},
{"Morningstar", "Шестопер", 8, Hand, 2, {Arm, 1, 2, HammerFighter}, {Blunt}},
{"Warhammer", "Боевой молот", 12, Hand, 2, {Arm, 1, 2, HammerFighter}, {Blunt, Hook}},
{"Flail", "Цеп", 16, Hand, 1, {Arm, 1, 2, HammerFighter}, {Blunt}},
{"WoodenClub", "Дубина", 1, Hand, 1, {Arm, 1, 1, HammerFighter}, {Blunt}},
{"LargeWoodenClub", "Большая дубина", 2, Hand, 1, {Arm, 2, 2, HammerFighter}, {Heavy, Blunt}},
{"HeavyHammer", "Тяжелый молот", 22, Hand, 2, {Arm, 2, 3, HammerFighter}, {Heavy, Blunt, Hook}},
{"Staff", "Посох", 1, Hand, 1, {Near, 2, 1, HammerFighter}, {Blunt, Hook, Parrying}},
{"ShortSpear", "Копье", 2, Hand, 1, {Near, 1, 1, SpearFighter}, {Pointed}},
{"LongSpear", "Длинное копье", 4, Hand, 2, {Near, 2, 1, SpearFighter}, {Pointed}},
{"Pike", "Пика", 12, Hand, 2, {Near, 2, 2, SpearFighter}, {Heavy, Pointed}},
{"Halberd", "Алебарда", 30, Hand, 2, {Near, 2, 2, SpearFighter}, {Heavy, Pointed, Edged, Hook}},
{"Trident", "Тризубец", 6, Hand, 1, {Near, 2, 2, SpearFighter}, {Pointed, Hook}},
//
{"Rock", "Камень", 0, Hand, 0, {Short, 1, 1}, {Light}},
{"ThrovingKnife", "Метательный нож", 1, Hand, 1, {Short, 1, 1}, {Light}},
{"ThrovingAxe", "Метательный топор", 2, Hand, 1, {Short, 1, 2}, {}},
{"ThrovingSpear", "Метательное копье", 3, Hand, 2, {Short, 1, 1}, {}},
{"Sling", "Праща", 1, Hand, 1, {Short, 1, 1}, {Light}},
{"ShortBow", "Лук", 6, Hand, 2, {Short, 2, 1}, {Light}},
{"LongBow", "Длинный лук", 12, Hand, 2, {Long, 2, 1}, {}},
{"LightCrossbow", "Арбалет", 24, Hand, 1, {Long, 2, 2}, {Reload}},
{"HeavyCrossbow", "Тяжелый арбалет", 40, Hand, 1, {Long, 2, 3}, {Light, Reload}},
//
{"LeatherArmor", "Кожанная броня", 3, Body, 2, {}, {Light}},
{"StuddedLeather", "Клепанная броня", 5, Body, 3, {}, {}},
{"Chainmail", "Кольчуга", 24, Body, 6, {}, {Heavy, PointedVulnerable}},
{"Platemail", "Латы", 80, Body, 8, {}, {Heavy, MovePenalty}},
{"StuddedLeatherCap", "Клепанный шлем", 2, Head, 1, {}, {Light}},
{"OpenHelmet", "Открытый шлем", 8, Head, 2, {}, {Light}},
{"ClosedHelmet", "Закрытый шлем", 18, Head, 3, {}, {}},
{"GreatHelm", "Полный шлем", 30, Head, 4, {}, {ScoutPenalty}},
{"SmallShield", "Щит", 6, LeftHand, 1, {}, {Light}},
{"LargeShield", "Большой щит", 16, LeftHand, 2, {}, {}},
//
};
getstr_enum(item);

bool item::is(feature_s v) const {
	return item_data[type].flags.is(v);
}

slot_s item::getslot() const {
	return item_data[type].slot;
}

void item::repair(int value) {
	if(bonus + value < 0)
		bonus = 0;
	else if(bonus + value > origin_bonus)
		bonus = origin_bonus;
	else
		bonus += value;
}

int	item::getartifact() const {
	static int artifact_dice[] = {0, 8, 10, 12};
	return artifact_dice[magic];
}

const char* item::getname() const {
	return item_data[type].name;
}