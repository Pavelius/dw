#include "main.h"

using namespace game;

bool spaceship::marshto() {
	auto n = getlocation();
	auto p = n->getparent();
	auto r = chooselocation();
	// Случайное событие
	nextday();
	set(r);
	return true;
}

bool spaceship::encounter() {
	return true;
}

void spaceship::damage(bool interactive, int value, weapon_type_s type) {
	value -= armor;
	hits -= value;
	if(hits > 0) {
		if(interactive) {
			act("%герой получил%а [%1i] повреждений.", value);
		}
	} else {
		if(interactive) {
			act("%герой был%а уничтожен%а.");
		}
	}
}

void spaceship::shoot(bool interactive, weapon& e, spaceship& enemy) {
	damageinfo d; e.get(d);
	enemy.damage(interactive, d.roll(), e.gettype());
}

void spaceship::shoot(bool interactive, spaceship& enemy) {
	for(auto& w : weapons) {
		if(w)
			shoot(interactive, w, enemy);
	}
}

bool spaceship::isenemy(const spaceship* p) const {
	return this != p;
}