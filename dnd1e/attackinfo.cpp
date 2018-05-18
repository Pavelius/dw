#include "main.h"

const dice& damageinfo::getdamage(size_s value) const {
	switch(value) {
	case Medium:
	case Small:
		return damage;
	default:
		return damage_large;
	}
}

void attackinfo::clear() {
	memset(this, 0, sizeof(*this));
}