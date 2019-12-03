#include "main.h"

creature bsmeta<creature>::elements[512];
DECLFULL(creature);

const char* text_wound[] = {"����", "����", "���"};

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
		act("%����� ��������%�.");
		return;
	}
	auto parry = enemy.get(PV);
	auto parry_count = enemy.get(PVC);
	if(parry && !parry_count) {
		if(enemy.roll(parry)) {
			act(enemy, "%����� �����%�, �� %�������� �����%� ����.");
			enemy.set(PVC, parry_count + 1);
			return;
		}
	}
	act("%����� �����%�.");
	dicei weapon = bsmeta<dicei>::elements[getdamage()];
	enemy.damage(weapon.roll());
}

int creature::get(parameter_s id) const {
	auto r = parameters[id];
	switch(id) {
	case RS:
		r += wears[Armor].getinfo().armor.rs;
		break;
	}
	return r;
}

void creature::damage(int value) {
	value -= get(RS);
	if(value <= 0) {
		act("���� �� ���� ������� �����.");
		return;
	}
	if(value > parameters[LE]) {
		parameters[LE] = 0;
		act("%����� �������%� [%1i] %2 � ����%�.", value, getn(text_wound, value));
	} else {
		parameters[LE] -= value;
		act("%����� �������%� [%1i] %2.", value, getn(text_wound, value));
	}
}

bool creature::roll(int value) const {
	auto result = 1 + rand() % 20;
	//act("{%1i vs %2i}", result, value);
	if(result == 20)
		return false;
	return result <= value;
}

dice_s creature::getdamage() const {
	if(wears[Weapon])
		return wears[Weapon].getinfo().weapon.dice;
	return unarmed;
}

reaction_s creature::getopposed(reaction_s v) {
	switch(v) {
	case Hostile: return Helpful;
	case Helpful: return Hostile;
	case Friendly: return Hostile;
	default: return v;
	}
}