#include "main.h"

weaponi bsmeta<weaponi>::elements[] = {{""},
{"лазер", Energy, {{10, 15}, 1}, {1, 2}},
{"пушка", Shrapnel, {{15, 30}, 1}, {2, 4}},
{"ракеты", Rocket, {{5, 10}, 3}, {1, 2}},
{"торпеда", Rocket, {{30, 40}, 1}, {3, 5}},
};
assert_enum(weapon, Torpedo);

void damageinfo::set(weapon_s id, int level) {
	*this = bsmeta<weaponi>::elements[id].damage;
	damage[0] += bsmeta<weaponi>::elements[id].upgrade.damage[0] * level;
	damage[1] += bsmeta<weaponi>::elements[id].upgrade.damage[1] * level;
	distance += bsmeta<weaponi>::elements[id].upgrade.distance * level;
}

void weapon::get(damageinfo& e) const {
	e.set(type, level);
}

weapon_type_s weapon::gettype() const {
	return bsmeta<weaponi>::elements[type].type;
}