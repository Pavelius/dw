#include "main.h"

static struct item_info {
	struct weapon_info {
		range_s			range;
		char			grip;
		char			damage;
	};
	const char*			id;
	const char*			name;
	char				bonus;
	weapon_info			weapon;
	cflags<feature_s>		flags;
} item_data[] = {{"", "", 0, {Arm, 0, 1}, {Blunt}},
{"Knife", "Нож", 1, {Arm, 1, 1}, {Light, Pointed}},
{"Dagger", "Кинжал", 1, {Arm, 1, 1}, {Light, Edged, Pointed}},
{"Falchion", "Мачете", 1, {Arm, 1, 2}, {Edged, Pointed}},
{"Shortsword", "Короткий меч", 2, {Arm, 1, 1}, {Edged, Pointed, Parrying}},
{"Broadsword", "Меч", 2, {Arm, 1, 2}, {Edged, Pointed, Parrying}},
{"Longsword", "Длинный меч", 2, {Arm, 1, 2}, {Heavy, Edged, Pointed, Parrying}},
{"TwoHandedSword", "Двуручный меч", 2, {Arm, 2, 3}, {Heavy, Edged, Pointed, Parrying}},
{"Scimitar", "Сабля", 1, {Arm, 1, 2}, {Edged, Pointed, Hook, Parrying}},
{"Handaxe", "", 2, {Arm, 1, 2}, {Edged, Hook}},
{"Battleaxe", "", 2, {Arm, 1, 2}, {Heavy, Edged, Hook}},
{"TwoHandedAxe", "", 2, {Arm, 2, 3}, {Heavy, Edged, Hook}},
{"Mace", "", 2, {Arm, 1, 1}, {Blunt}},
{"Morningstar", "", 2, {Arm, 1, 2}, {Blunt}},
{"Warhammer", "", 2, {Arm, 1, 2}, {Blunt, Hook}},
{"Flail", "", 1, {Arm, 1, 2}, {Blunt}},
{"WoodenClub", "", 1, {Arm, 1, 1}, {Blunt}},
{"LargeWoodenClub", "", 1, {Arm, 2, 2}, {Heavy, Blunt}},
{"HeavyHammer", "", 2, {Arm, 2, 3}, {Heavy, Blunt, Hook}},
{"Staff", "", 1, {Near, 2, 1}, {Blunt, Hook, Parrying}},
{"ShortSpear", "", 1, {Near, 1, 1}, {Pointed}},
{"LongSpear", "", 2, {Near, 2, 1}, {Pointed}},
{"Pike", "", 2, {Near, 2, 2}, {Heavy, Pointed}},
{"Halberd", "", 2, {Near, 2, 2}, {Heavy, Pointed, Edged, Hook}},
{"Trident", "", 1, {Near, 2, 2}, {Pointed, Hook}},
//
{"Rock", "", 0, {Short, 1, 1}, {Light}},
{"ThrovingKnife", "", 1, {Short, 1, 1}, {Light}},
{"ThrovingAxe", "", 1, {Short, 1, 2}, {}},
{"ThrovingSpear", "", 2, {Short, 1, 1}, {}},
{"Sling", "", 1, {Short, 1, 1}, {Light}},
{"ShortBow", "", 2, {Short, 2, 1}, {Light}},
{"LongBow", "", 2, {Long, 2, 1}, {}},
{"LightCrossbow", "", 1, {Long, 2, 2}, {Reload}},
{"HeavyCrossbow", "", 1, {Long, 2, 3}, {Light, Reload}},
};
getstr_enum(item);

bool item::is(feature_s v) const {
	return item_data[type].flags.is(v);
}