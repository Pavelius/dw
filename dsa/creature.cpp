#include "main.h"

const char* text_wound[] = {"рану", "раны", "ран"};

static const char* getn(const char** pt, int value) {
	if(value == 0)
		return pt[2];
	else if(value == 1)
		return pt[0];
	else if(value <= 4)
		return pt[1];
	return pt[2];
}

int	creature::get(ability_s i) const {
	auto r = abilities[i];
	switch(i) {
	case Strenght:
		if(is(Exhaused))
			r--;
		break;
	}
	return r;
}

bool creature::equip(const item& it) {
	auto s = it.getinfo().wear;
	if(wears[s])
		return false;
	wears[s] = it;
	return true;
}

bool creature::isready() const {
	return get(LE) > 0;
}

void creature::attack(creature& enemy) {
	auto attack = get(AV);
	if(!roll(attack)) {
		act("%герой промазал%а.");
		return;
	}
	auto parry = enemy.get(PV);
	if(parry) {
		if(roll(parry)) {
			act(enemy, "%герой попал%а, но %оппонент отбил%ј удар.");
			return;
		}
	}
	act("%герой попал%а.");
	auto weapon = wears[Weapon];
	enemy.damage(weapon.getinfo().weapon.damage.roll());
}

void creature::damage(int value) {
	if(value > parameters[LE]) {
		parameters[LE] = 0;
		act("%герой получил%а [%1i] %2 и упал%а.", value, getn(text_wound, value));
	} else {
		parameters[LE] -= value;
		act("%герой получил%а [%1i] %2.", value, getn(text_wound, value));
	}
}

bool creature::roll(int value) const {
	auto result = 1 + rand() % 20;
	if(result == 20)
		return false;
	return result <= value;
}