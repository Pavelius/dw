#include "main.h"

DECLDATA(creature, 256);

static const char* text_wound[] = {"����", "����", "���"};
static const char* text_score[] = {"����", "����", "�����"};

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
	if(type == Character) {
		if(!it.is((character_s)value))
			return false;
	}
	for(auto s = Weapon; s < Backpack; s = (wear_s)(s + 1)) {
		if(!it.is(s))
			continue;
		if(!wears[s]) {
			wears[s] = it;
			return true;
		}
	}
	return false;
}

bool creature::isready() const {
	if(get(LE) <= 0)
		return false;
	if(is(Fleeing))
		return false;
	return true;
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
	enemy.damage(weapon.roll(), false);
}

int creature::get(parameter_s id) const {
	auto r = parameters[id];
	switch(id) {
	case RS:
		r += wears[Armor].get(id);
		break;
	}
	return r;
}

void creature::heal(int value) {
	auto m = getmaximum(LE);
	if(get(LE) + value > m)
		value = m - get(LE);
	if(!value)
		return;
	act("%����� �����������%� [%1i] %2 ��������� �������.", value, getn(text_score, value));
	set(LE, get(LE) + value);
}

void creature::damage(int value, bool ignore_amror) {
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

bool creature::roll(ability_s i, int b) const {
	return roll(get(i) + b);
}

dice_s creature::getdamage() const {
	if(wears[Weapon])
		return wears[Weapon].getdamage();
	return unarmed;
}

short unsigned creature::getid() const {
	return this - bsmeta<creature>::elements;
}

void creature::clear() {
	memset(this, 0, sizeof(*this));
	fighting = Blocked;
}

creature* creature::getfighting() const {
	if(fighting == Blocked)
		return 0;
	return bsmeta<creature>::elements + fighting;
}

void creature::setfighting(creature* pc) {
	if(!pc)
		fighting = Blocked;
	else {
		fighting = pc->getid();
		pc->fighting = getid();
	}
}

void creature::testfighting() {
	auto p = getfighting();
	if(!p)
		return;
	if(!p->isready())
		setfighting(0);
}

void creature::status(stringbuilder& sb) const {
	sb.add(getname());
	auto lp = get(LE);
	auto lpm = getmaximum(LE);
	if(lp < lpm) {
		if(lp == 0)
			sb.adds("����� ��� ������");
		else if(lp < lpm / 2)
			sb.add("([-%1i/%2i])", lp, lpm);
		else
			sb.add("(%1i/%2i)", lp, lpm);
	}
	if(lp <= 0)
		return;
	if(is(Fleeing)) {
		actv(sb, "������%� ������ �����", 0);
		return;
	}
	auto count = 0;
	if(wears[Weapon]) {
		sb.adds("������ %-1", wears[Weapon].getname());
		count++;
	}
	if(wears[Armor]) {
		if(count)
			sb.add(", ");
		sb.adds("����� %-1", wears[Armor].getname());
		count++;
	}
}

bool creature::cast(int& value, int bonus, const char* text_cast) {
	if(value > get(AE))
		value = get(AE);
	auto result = roll(Wisdom, bonus);
	act(text_cast, value);
	if(!result) {
		act("��, �� ������ �� ���������. ������, ���������� �� �������������.");
		set(AE, get(AE) - value / 2);
	} else
		set(AE, get(AE) - value);
	return result;
}