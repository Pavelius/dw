#include "main.h"

adat<creature, 512>	creatures;
creature*			players[6];

void* creature::operator new(unsigned size) {
	for(auto& e : creatures) {
		if(!e)
			return &e;
	}
	return creatures.add();
}

void creature::act(const char* format, ...) const {
	actv(logs::getptr(), logs::getptrend(), format, xva_start(format));
}

void creature::actv(char* result, const char* result_maximum, const char* format, const char* param) const {
	logs::driver driver;
	driver.gender = gender;
	driver.name = getname();
	driver.printv(result, result_maximum, format, param);
}

void creature::clear() {
	memset(this, 0, sizeof(*this));
}

bool creature::is(feat_s id) const {
	return (feats[id / 8] & (1 << (id % 8))) != 0;
}

bool creature::is(action_s id) const {
	return (actions & (1 << id)) == 0;
}

void creature::set(feat_s id, bool interactive) {
	feats[id / 8] |= (1 << (id % 8));
}

void creature::remove(feat_s id) {
	feats[id / 8] &= ~(1 << (id % 8));
}

void creature::set(action_s id) {
	actions |= (1 << id);
}

void creature::setready() {
	actions = 0;
	reflex_bonus = 0;
}

int creature::get(ability_s id) const {
	return abilities[id] / 2 - 5;
}

void creature::set(gender_s id) {
	gender = id;
}

int	creature::get(feat_s id) const {
	auto result = getheroiclevel() / 2;
	if(is(id))
		result += 5;
	result += get(game::getability(id));
	return result;
}

int	creature::get(defence_s id) const {
	static char reflex_size_bonus[] = {10, 5, 2, 1, 0, -1, -2, -5, -10};
	static_assert(lenghtof(reflex_size_bonus) == SizeCollosal + 1, "Invalid count of size elements");
	auto result = 10;
	switch(id) {
	case Reflexes:
		if(wears[Armor])
			result += wears[Armor].getreflexes();
		else
			result += getheroiclevel();
		if(is(NaturalArmor))
			result += 1;
		result += reflex_bonus;
		result += get(Dexterity);
		result += reflex_size_bonus[getsize()];
		break;
	case Fortitude:
		result += getheroiclevel();
		result += get(Constitution);
		break;
	case Will:
		result += getheroiclevel();
		result += get(Wisdow);
		break;
	}
	if(is(SuperiorDefences))
		result++;
	return result;
}

int	creature::roll(feat_s id, int dc, bool interactive) const {
	return roll(get(id), dc, interactive, 0);
}

int	creature::roll(int bonus, int dc, bool interactive, int* dice_rolled) const {
	auto result = d20();
	auto outcome = result + bonus - dc;
	if(interactive) {
		if(outcome >= 0)
			logs::add("[+{%1i%+2i=%3i}] ", result, bonus, result + bonus);
		else
			logs::add("[-{%1i%+2i=%3i}] ", result, bonus, result + bonus);
	}
	if(dice_rolled)
		*dice_rolled = result;
	return outcome;
}

void creature::damage(int count, bool interactive) {
	if(count < 0)
		count = 1;
	if(count < hits) {
		hits -= count;
		if(interactive)
			act("%герой получил%а [%1i] повреждений.", count);
	} else {
		hits -= count;
		if(interactive)
			act("%герой получил%а [%1i] повреждений и упал%а.", count);
	}
}

void creature::attack(creature* enemy, bool interactive, int bonus) {
	int dice_rolled;
	attack_info e = {0}; get(e); e.bonus += bonus;
	int defence = enemy->get(Reflexes);
	int rolled = roll(e.bonus, defence, interactive, &dice_rolled);
	bool critical_hit = dice_rolled >= (20 - e.critical_range);
	if(rolled >= 0 || critical_hit) {
		auto damage = e.damage;
		auto damage_count = damage.roll();
		if(critical_hit) {
			if(interactive)
				act("%герой критически попал%а.");
			damage.b = 0;
			damage.c = 1 + e.critical_multiply;
			damage_count += damage.roll();
		} else {
			if(interactive)
				act("%герой попал%а.");
		}
		enemy->damage(damage_count, interactive);
	} else {
		if(interactive)
			act("%герой промазал%а.");
	}
}

int	creature::getheroiclevel() const {
	return classes[Jedi]
		+ classes[Noble]
		+ classes[Scoundrel]
		+ classes[Scout]
		+ classes[Soldier];
}

int	creature::getbaseattack() const {
	return classes[Jedi] + classes[Soldier] + (classes[Noble] + classes[Scoundrel] + classes[Scout]) * 3 / 4;
}

bool creature::isactive() const {
	return hits >= 0;
}

void creature::get(attack_info& e, wear_s slot) const {
	static unsigned char unarmed_dice[] = {1, 1, 2, 3, 4, 6, 8, 10, 12, 20};
	if(wears[slot])
		e.damage = wears[slot].getdice();
	else if (slot==Melee) {
		int d = getsize();
		if(is(MartialArts))
			d++;
		e.damage.c = 1;
		e.damage.d = unarmed_dice[d];
	}
	e.bonus += getbaseattack();
	e.damage.b += getheroiclevel() / 2;
	if(slot==Melee) {
		e.bonus += get(Strenght);
		e.damage.b += get(Strenght);
	} else
		e.bonus += get(Dexterity);
}

void creature::select(creaturea& result, const creaturea& source, bool (creature::*is)(const creature* object) const) const {
	result.clear();
	for(auto e : source) {
		if(!e->isactive())
			continue;
		if(!(this->*is)(e))
			continue;
		result.add(e);
	}
}

void creature::set(side_s value) {
	side = value;
}

void creature::rollinitiative() {
	initiative = roll(Initiative, 0, false);
}

bool creature::isenemy(const creature* e) const {
	return getside() != e->getside();
}

bool creature::isreachenemy(const creature* e) const {
	if(!isenemy(e))
		return false;
	return iabs(position - e->position) <= getreach();
}

bool creature::isallow(action_s id) const {
	switch(id) {
	case SwiftAction:
		return is(StandartAction) || is(MoveAction) || is(SwiftAction);
	case MoveAction:
		return is(StandartAction) || is(MoveAction);
	case FullRoundAction:
		return is(StandartAction) && is(MoveAction) && is(SwiftAction);
	default:
		return is(id);
	}
}

action_s creature::getaction(combat_action_s id) const {
	switch(id) {
	case Move:
		return MoveAction;
	case DrawWeapon:
		if(is(QuickDraw))
			return SwiftAction;
		return MoveAction;
	default:
		return StandartAction;
	}
}

void creature::use(action_s id) {
	switch(id) {
	case FullRoundAction:
		set(StandartAction);
		set(SwiftAction);
		set(MoveAction);
		break;
	case MoveAction:
		if(is(MoveAction))
			set(MoveAction);
		else
			set(StandartAction);
		break;
	case SwiftAction:
		if(is(SwiftAction))
			set(SwiftAction);
		else if(is(MoveAction))
			set(MoveAction);
		else
			set(StandartAction);
		break;
	case StandartAction:
		set(StandartAction);
		break;
	case Reaction:
		set(Reaction);
		break;
	}
}

void creature::set(state_s id, bool interactive) {
	if(this->state == LayingDown && id == StandAndReady) {
		this->state = StandAndReady;
		if(is(Acrobatic)) {
			if(roll(Acrobatic, 15, interactive) >= 0) {
				if(interactive)
					act("%герой резко вскочил%а на ноги.");
				use(SwiftAction);
				return;
			}
		}
		if(interactive)
			act("%герой поднял%ась на ноги.");
		use(MoveAction);
	}
}

bool creature::isgearweapon() const {
	for(auto slot = FirstGear; slot <= LastGear; slot = (wear_s)(slot+1)) {
		if(wears[slot].isweapon())
			return true;
	}
	return false;
}

const char*	creature::getname() const {
	if(pregen)
		return getstr(pregen);
	return getname(name);
}

int	creature::getskills() const {
	auto result = 0;
	for(auto e = Jedi; e <= Soldier; e = (class_s)(e + 1)) {
		if(!get(e))
			continue;
		result += game::getskillpoints(e);
	}
	result += get(Intellegence);
	if(is(BonusSkill))
		result++;
	return result;
}

int	creature::getfeats() const {
	auto result = 1;
	if(is(BonusFeat))
		result++;
	return result;
}