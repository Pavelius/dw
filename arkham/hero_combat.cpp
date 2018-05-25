#include "main.h"

bool hero::before(monster& e, int round) {
	if(!isready())
		return false;
	logs::add(1, "������ ���.");
	logs::add(2, "����������� ������?");
	logs::add(3, "������� ������");
	auto id = logs::input(true, false, "��� ������ ������?");
	switch(id) {
	case 2:
		if(!roll(EvadeCheck, e.get(EvadeCheck))) {
			add(Stamina, e.get(Stamina), false);
			return false;
		}
		return true;
	case 3:
		changeweapon(weapons[0], weapons[1]);
		break;
	}
	return false;
}

void hero::changeweapon(item_s& w1, item_s& w2) {
	char temp[512];
	for(item_s i = PistolDerringer18; i <= Whiskey; i = (item_s)(i + 1)) {
		if(!get(i))
			continue;
		if(item::is(i, PhysicalWeapon) || item::is(i, MagicalWeapon)) {
			item::getname(temp, zendof(temp), i, true);
			logs::add(i, temp);
		}
	}
	w1 = (item_s)logs::input(true, false, "����� ������ ��������?");
}

bool hero::combat(monster& e) {
	auto round = 0;
	if(!isready())
		return false;
	logs::add("�������� �������� %1.", e.getname());
	if(before(e, round)) {
		logs::add("������� ������ �������.");
		return true;
	}
	if(!isready())
		return false;
	if(e.get(Sanity) && !roll(HorrorCheck, e.get(HorrorCheck), 1))
		add(Sanity, -e.get(Sanity), true);
	if(!e.get(Stamina))
		return true;
	while(isready()) {
		auto bonus = e.get(CombatCheck);
		bonus += item::get(weapons[0], CombatCheck);
		bonus += item::get(weapons[1], CombatCheck);
		if(roll(CombatCheck, bonus, e.get(Fight))) {
			logs::add("�� ������ �������� �������.");
			return true;
		}
		add(Stamina, -e.get(Stamina), true);
		if(before(e, ++round)) {
			logs::add("������� ������ �������.");
			return true;
		}
	}
	return false;
}