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
	logs::add("\nВы %2 [-%1i] очка силы воли.", value, (value>0) ? "получили" : "потеряли");
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
		logs::add("\nВы %3 [-%1i] очка %2.", value, getnameof(id), (value>0) ? "потеряли" : "восстановили");
}

void character::roll(diceroll& r, ability_s attribute, int base, int skill, int equipment, int artifact_dice) {
	r.roll(Attributes, base, 6);
	r.roll(Skills, skill, 6);
	r.roll(Items, equipment, 6);
	if(artifact_dice)
		r.roll(Items, 1, artifact_dice);
	auto sixth = 0;
	auto& sb = logs::getbuilder();
	auto pushed = false;
	auto interactive = true;
	auto p = sb.get();
	while(r) {
		r.print(sb);
		sixth = r.getsix();
		if(sixth>0)
			logs::add(1, "Принять успешный результат.");
		else {
			logs::add(1, "Смириться с проваленным броском.");
			if(pride>=1)
				logs::add(3, "Использовать гордость.");
		}
		if(!pushed && r.getreroll()>0)
			logs::add(2, "Пересилить себя.");
		auto result = logs::input(interactive, false);
		sb.set(p);
		if(result == 1)
			break;
		else if(result == 2) {
			pushed = true;
			r.pushroll();
			auto ones = r.getone(Attributes);
			damage(attribute, ones, true);
			addwill(ones);
			logs::add(1, "Продолжить");
			logs::input(interactive, false, 0);
			sb.set(p);
		} else if(result == 3) {
			r.roll(Talents, 1, 12);
			if(r.getsix() >= 0)
				pride = 0;
			else
				pride = -1;
		}
	}
}

void character::attack(item& weapon, character* enemy) {
	diceroll r;
	auto k = Melee;
	auto a = getkey(k);
	auto b = get(a);
	auto s = get(k);
	auto e = weapon.getbonus();
	roll(r, a, b, s, e, weapon.getartifact());
}

bool character::apply(action_s a, character* opponent, bool run) {
	auto& weapon = wears[Hand];
	switch(a) {
	case Slash:
		if(!weapon.is(Blunt) && !weapon.is(Edged))
			return false;
		break;
	case Stab:
		if(!weapon.is(Pointed))
			return false;
		break;
	}
	return true;
}