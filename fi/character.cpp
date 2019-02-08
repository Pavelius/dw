#include "main.h"

void character::clear() {
	memset(this, 0, sizeof(*this));
}

char character::getmaximum(ability_s v) const {
	auto r = 4;
	if(getkey(race) == v)
		r++;
	if(getkey(profession) == v)
		r++;
	return r;
}

char character::getminimum(ability_s v) const {
	return 2;
}

void character::apply_talents() {
	for(auto i = FirstTalent; i <= LastTalent; i = (talent_s)(i + 1)) {
		if(getkey(i) == variant(race))
			talents[i] = 1;
	}
}

void character::addwill(int value) {
	if(willpower + value > 10)
		value = 10 - willpower;
	if(willpower + value < 0)
		value = 0;
	if(value == 0)
		return;
	willpower += value;
	logs::add("Вы %2 [-%1i] очка силы воли.", value, ((value>0) ? "получили" : "потеряли"));
}

void character::damage(ability_s id, int value, bool interactive) {
	if(ability_damage[id] + value < 0)
		value = ability_damage[id];
	else if(ability_damage[id] + value > ability[id])
		value = ability[id] - ability_damage[id];
	if(value == 0)
		return;
	ability_damage[id] += value;
	if(interactive)
		logs::add("Вы %3 [-%1i] очка %2.", value, getnameof(id), ((value>0) ? "потеряли" : "восстановили"));
}

int character::roll(skill_s id, int modifier, item* pi) {
	diceroll r;
	auto a = getkey(id);
	auto b = get(a);
	auto s = get(id) + modifier;
	auto e = 0;
	auto t = 0;
	if(pi) {
		e += pi->getbonus();
		t = pi->getartifact();
	}
	roll(r, a, b, s, e, t);
	if(pi) {

	}
	return r.getsix();
}

void character::roll(diceroll& r, ability_s attribute, int base, int skill, int equipment, int artifact_dice) {
	r.roll(Attributes, base, 6);
	r.roll(Skills, skill, 6);
	r.roll(Items, equipment, 6);
	if(artifact_dice)
		r.roll(Items, 1, artifact_dice);
	auto& sb = logs::getbuilder();
	auto pushed = false;
	auto interactive = true;
	auto p = sb.get();
	while(r) {
		r.print(sb);
		auto sixth = r.getsix();
		if(sixth > 0) {
			sb.set(p);
			break;
		}
		logs::add(1, "Смириться с проваленным броском.");
		if(!pushed && r.getreroll()>0)
			logs::add(2, "Пересилить себя.");
		if(pride>=1)
			logs::add(3, "Использовать гордость.");
		auto result = logs::input(interactive, false);
		sb.set(p);
		if(result == 1)
			break;
		else if(result == 2) {
			sb.adds("Пришлось приложить усилие.");
			pushed = true;
			r.pushroll();
			auto ones = r.getone(Attributes);
			if(ones != 0) {
				damage(attribute, ones, true);
				addwill(ones);
				logs::add(1, "Продолжить");
				logs::input(interactive, false, 0);
				sb.set(p);
			}
		} else if(result == 3) {
			r.roll(Talents, 1, 12);
			if(r.getsix() >= 0)
				pride = 0;
			else
				pride = -1;
		}
	}
}

void character::react(const aref<action_s>& source, character* opponent, int& result, bool run) {
	auto interactive = true;
	for(auto e : source) {
		if(react(e, opponent, result, false))
			logs::add(e, getstr(e));
	}
	if(!logs::getcount())
		return;
	action_s a = (action_s)logs::input(interactive, false, "Как будет реагировать %1?", getname());
	react(a, opponent, result, run);
}

void character::attack(skill_s id, item& weapon, character* enemy) {
	diceroll r;
	static action_s react_melee[] = {DodgeProne, DodgeStand, ParryShield, ParryWeapon};
	auto k = Melee;
	auto a = getkey(k);
	auto b = get(a);
	auto s = get(k);
	auto e = weapon.getbonus();
	roll(r, a, b, s, e, weapon.getartifact());
	auto result = r.getsix();
	if(result > 0)
		react(react_melee, enemy, result, true);
	if(result > 0) {
		switch(id) {
		case Melee:
		case Marksmanship:
			damage(Strenght, -result, true);
			break;
		}
	}
}

reaction_s character::getopposed(reaction_s value) {
	switch(value) {
	case Hostile: return Friendly;
	case Friendly: return Hostile;
	default: return value;
	}
}

void character::actv(const char* format, const char* param) const {
	logs::driver driver;
	driver.name = getname();
	driver.gender = gender;
	logs::addv(format, param);
}