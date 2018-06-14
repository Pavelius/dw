#include "main.h"

static struct item_info {
	struct weapon_info {
		knack_s			attack;
		knack_s			parry;
		damage_info		damage;
	};
	const char*			id;
	const char*			name;
	weapon_info			weapon;
} item_data[] = {{"", "", {AttackImprovisedWeapon, ParryImprovisedWeapon, {0, 2}}},
{"Pistol", "�������", {AttackFirearms, NoKnack, {5, 3}}},
{"Bow", "���", {AttackBow, NoKnack, {2, 2}}},
{"Rapier", "������", {AttackFencing, ParryFencing, {2, 2}}},
{"Sword", "���", {AttackHeavyWeapon, ParryHeavyWeapon, {3, 2}}},
{"Axe", "�����", {AttackHeavyWeapon, ParryHeavyWeapon, {3, 2}}},
{"Spear", "�����", {AttackPolearm, ParryPolearm, {2, 2}}},
};
assert_enum(item, Spear);
getstr_enum(item);

const damage_info& item::getdamage() const {
	return item_data[type].weapon.damage;
}