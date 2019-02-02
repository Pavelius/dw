#include "main.h"

static struct item_info {
	struct weapon_info {
		range_s			range;
		char			grip;
		char			damage;
	};
	const char*			id;
	const char*			name;
	int					cost;
	slot_s				slot;
	char				bonus;
	weapon_info			weapon;
	cflags<feature_s>	flags;
} item_data[] = {{"", "", 0, Hand, 0, {Arm, 0, 1}, {Blunt}},
{"Knife", "Нож", 1, Hand, 1, {Arm, 1, 1}, {Light, Pointed}},
{"Dagger", "Кинжал", 2, Hand, 1, {Arm, 1, 1}, {Light, Edged, Pointed}},
{"Falchion", "Мачете", 4, Hand, 1, {Arm, 1, 2}, {Edged, Pointed}},
{"Shortsword", "Короткий меч", 6, Hand, 2, {Arm, 1, 1}, {Edged, Pointed, Parrying}},
{"Broadsword", "Меч", 10, Hand, 2, {Arm, 1, 2}, {Edged, Pointed, Parrying}},
{"Longsword", "Длинный меч", 18, Hand, 2, {Arm, 1, 2}, {Heavy, Edged, Pointed, Parrying}},
{"TwoHandedSword", "Двуручный меч", 40, Hand, 2, {Arm, 2, 3}, {Heavy, Edged, Pointed, Parrying}},
{"Scimitar", "Сабля", 8, Hand, 1, {Arm, 1, 2}, {Edged, Pointed, Hook, Parrying}},
{"Handaxe", "", 2, Hand, 2, {Arm, 1, 2}, {Edged, Hook}},
{"Battleaxe", "", 6, Hand, 2, {Arm, 1, 2}, {Heavy, Edged, Hook}},
{"TwoHandedAxe", "", 18, Hand, 2, {Arm, 2, 3}, {Heavy, Edged, Hook}},
{"Mace", "", 4, Hand, 2, {Arm, 1, 1}, {Blunt}},
{"Morningstar", "", 8, Hand, 2, {Arm, 1, 2}, {Blunt}},
{"Warhammer", "", 12, Hand, 2, {Arm, 1, 2}, {Blunt, Hook}},
{"Flail", "", 16, Hand, 1, {Arm, 1, 2}, {Blunt}},
{"WoodenClub", "", 1, Hand, 1, {Arm, 1, 1}, {Blunt}},
{"LargeWoodenClub", "", 2, Hand, 1, {Arm, 2, 2}, {Heavy, Blunt}},
{"HeavyHammer", "", 22, Hand, 2, {Arm, 2, 3}, {Heavy, Blunt, Hook}},
{"Staff", "", 1, Hand, 1, {Near, 2, 1}, {Blunt, Hook, Parrying}},
{"ShortSpear", "", 2, Hand, 1, {Near, 1, 1}, {Pointed}},
{"LongSpear", "", 4, Hand, 2, {Near, 2, 1}, {Pointed}},
{"Pike", "", 12, Hand, 2, {Near, 2, 2}, {Heavy, Pointed}},
{"Halberd", "", 30, Hand, 2, {Near, 2, 2}, {Heavy, Pointed, Edged, Hook}},
{"Trident", "", 6, Hand, 1, {Near, 2, 2}, {Pointed, Hook}},
//
{"Rock", "", 0, Hand, 0, {Short, 1, 1}, {Light}},
{"ThrovingKnife", "", 1, Hand, 1, {Short, 1, 1}, {Light}},
{"ThrovingAxe", "", 2, Hand, 1, {Short, 1, 2}, {}},
{"ThrovingSpear", "", 3, Hand, 2, {Short, 1, 1}, {}},
{"Sling", "", 1, Hand, 1, {Short, 1, 1}, {Light}},
{"ShortBow", "", 6, Hand, 2, {Short, 2, 1}, {Light}},
{"LongBow", "", 12, Hand, 2, {Long, 2, 1}, {}},
{"LightCrossbow", "", 24, Hand, 1, {Long, 2, 2}, {Reload}},
{"HeavyCrossbow", "", 40, Hand, 1, {Long, 2, 3}, {Light, Reload}},
//
{"LeatherArmor", "", 3, Body, 2, {}, {Light}},
{"StuddedLeather", "", 5, Body, 3, {}, {}},
{"Chainmail", "", 24, Body, 6, {}, {Heavy, PointedVulnerable}},
{"Platemail", "", 80, Body, 8, {}, {Heavy, MovePenalty}},
{"StuddedLeatherCap", "", 2, Head, 1, {}, {Light}},
{"OpenHelmet", "", 8, Head, 2, {}, {Light}},
{"ClosedHelmet", "", 18, Head, 3, {}, {}},
{"GreatHelm", "", 30, Head, 4, {}, {ScoutPenalty}},
};
getstr_enum(item);

bool item::is(feature_s v) const {
	return item_data[type].flags.is(v);
}

slot_s item::getslot() const {
	return item_data[type].slot;
}