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
	sb.add("Вы %2 [-%1i] очка силы воли.", value, ((value>0) ? "получили" : "потеряли"));
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
		sb.add("Вы %3 [-%1i] очка %2.", value, bsmeta<abilityi>::elements[id], ((value>0) ? "потеряли" : "восстановили"));
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
		auto n = r.getone(Items);
		pi->repair(-n);
	}
	return r.getsix();
}

void character::roll(diceroll& r, ability_s attribute, int base, int skill, int equipment, int artifact_dice) {
	r.roll(Attributes, base, 6);
	r.roll(Skills, skill, 6);
	r.roll(Items, equipment, 6);
	if(artifact_dice)
		r.roll(Items, 1, artifact_dice);
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
		an.add(1, "Смириться с проваленным броском.");
		if(!pushed && r.getreroll()>0)
			an.add(2, "Пересилить себя.");
		if(pride>=1)
			an.add(3, "Использовать гордость.");
		auto result = an.choose(interactive, false, 0);
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
				an.add(1, "Продолжить");
				an.choose(interactive, false, 0);
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

void character::react(const aref<variant>& source, character* opponent, int& result, bool run) {
	auto interactive = true;
	for(auto e : source) {
		switch(e.type) {
		case Actions:
			if(react((action_s)e.subtype, opponent, result, false))
				an.add((action_s)e.subtype, e.getname());
			break;
		}
	}
	if(!an)
		return;
	action_s a = (action_s)an.choose(interactive, false, "Как будет реагировать %1?", getname());
	react(a, opponent, result, run);
}

reaction_s character::getopposed(reaction_s value) {
	switch(value) {
	case Hostile: return Friendly;
	case Friendly: return Hostile;
	default: return value;
	}
}

bool character::equip(const item& it) {
	auto t = it.gettype();
	if(t >= CooperPiece && t <= SilverPiece) {
		cooper_piece += it.getcost() * it.getcount();
	}
	auto s = it.getslot();
	if(wears[s])
		return false;
	wears[s] = it;
	return true;
}

void character::add(const item& it) {
	if(equip(it))
		return;
	for(auto i = Gear; i <= LastGear; i = (slot_s)(i + 1)) {
		if(!wears[i]) {
			wears[i] = it;
			return;
		}
	}
}