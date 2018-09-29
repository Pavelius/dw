#include "main.h"

item_info item_data[] = {{"No item", "Нет предмета"},
//
{"Battleaxe", "Боевой топор", 10 * GP, 4, {MeleeWeapon}, {MartialWeaponProfiency}, {}, {{1, 8}, Slashing}},
{"Handaxe", "Топор", 5 * GP, 2, {MeleeWeapon, OffhandWeapon}, {SimpleWeaponProficiency}, {}, {{1, 6}, Slashing}},
{"Greataxe", "Секира", 30 * GP, 7, {MeleeWeapon}, {MartialWeaponProfiency}, {Heavy, TwoHanded}, {{1, 12}, Slashing}},
{"Club", "Палица", 1 * SP, 2, {MeleeWeapon, OffhandWeapon}, {SimpleWeaponProficiency}, {}, {{1, 8}, Bludgeon}},
{"Greatclub", "Дубина", 2 * SP, 10, {MeleeWeapon}, {SimpleWeaponProficiency}, {TwoHanded}, {{1, 8}, Bludgeon}},
};
getstr_enum(item);

bool item::is(item_feat_s id) const {
	return item_data[type].feats[0] == id
		|| item_data[type].feats[1] == id;
}

bool item::is(wear_s id) const {
	return item_data[type].wears[0] == id
		|| item_data[type].wears[1] == id;
}

bool item::islight() const {
	return item_data[type].wears[0] == MeleeWeapon
		&& item_data[type].wears[1] == OffhandWeapon;
}