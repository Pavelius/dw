#include "main.h"

bool hero::before(monster& e, int round) {
	if(!isready())
		return false;
	logs::add(1, round == 0 ? "Начать бой." : "Продолжить бой");
	logs::add(2, "Попробывать бежать");
	logs::add(3, "Сменить оружие");
	auto id = logs::input(true, false, "Что будете делать?");
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

item_s hero::changeweapon() const {
	char temp[512];
	for(item_s i = PistolDerringer18; i <= WardingStatue; i = (item_s)(i + 1)) {
		auto item_hands = item::gethands(i);
		if(item_hands == 0)
			continue;
		auto hands = item::gethands(weapons[0]) + item::gethands(weapons[1]) + item_hands;
		if(hands > 2)
			continue;
		auto count = get(i);
		if(weapons[0] == i)
			count--;
		if(weapons[1] == i)
			count--;
		if(count <= 0)
			continue;
		if(item::is(i, PhysicalWeapon) || item::is(i, MagicalWeapon)) {
			item::getname(temp, zendof(temp), i);
			logs::add(i, temp);
		}
	}
	logs::sort();
	if(!logs::getcount())
		return NoItem;
	return (item_s)logs::input(true, false, "Какое оружие выберете?");
}

void hero::changeweapon(item_s& w1, item_s& w2) {
	w1 = w2 = NoItem;
	w1 = changeweapon();
	w2 = changeweapon();
}

char hero::getbonus(item_s i, stat_s id) {
	auto result = item::get(i, id);
	if(item::is(i, DiscardAfterUse))
		discard(i);
	return result;
}

bool hero::combat(monster& e) {
	auto round = 0;
	if(!isready())
		return false;
	//logs::add("Внезапно появился %1.", e.getname());
	logs::add(e.gettext());
	if(before(e, round)) {
		logs::add("Попытка побега удалась.");
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
		bonus += getbonus(weapons[0], CombatCheck);
		bonus += getbonus(weapons[1], CombatCheck);
		if(roll(CombatCheck, bonus, e.get(Fight))) {
			logs::add("Вы сумели победить монстра.");
			return true;
		}
		add(Stamina, -e.get(Stamina), true);
		if(before(e, ++round)) {
			logs::add("Попытка побега удалась.");
			return true;
		}
	}
	return false;
}