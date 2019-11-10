#include "main.h"

bool hero::isallow(effect_s id, int value, monster* enemy) const {
	switch(id) {
	case LooseMoney:
		return getcoins() > 0;
	case LooseItem:
		for(auto i : gear) {
			if(i.type == (item_s)value)
				return true;
		}
		return false;
	case Heal:
		return hp < getmaxhits();
	case Debility:
		return !isdebilities((stat_s)value);
	case HealParty:
	case DebilityParty:
		for(auto& e : bsmeta<hero>()) {
			if(!e)
				continue;
			if(e.isallow(id, value, enemy))
				return true;
		}
		return false;
	case Summon:
		return enemy && enemy->count < 8;
	case Regroup:
		return enemy && enemy->count <= 5;
	default:
		return true;
	}
}

static effect_s getsingle(effect_s id) {
	switch(id) {
	case DamageAllParty: return Damage;
	case DamageAllPartyIA: return DamageIA;
	case HealParty: return Heal;
	case DebilityParty: return Debility;
	default: return id;
	}
}

void hero::apply(effect_s id, int value, monster* enemy) {
	if(!id && !value)
		return;
	switch(id) {
	case LooseMoney: addcoins(value, false); break;
	case LooseItem:
		for(auto& e : bsmeta<hero>()) {
			if(!e)
				continue;
			if(e.use((item_s)value, true))
				return;
		}
		break;
	case Heal: healharm(value); break;
	case Debility: setdebilities((stat_s)value, true); break;
	case HealParty:
	case DebilityParty:
	case DamageAllParty:
	case DamageAllPartyIA:
		for(auto& e : bsmeta<hero>()) {
			if(!e)
				continue;
			auto sid = getsingle(id);
			if(sid != id)
				e.apply(id, value, enemy);
		}
		break;
	case Summon: enemy->count += value; break;
	case Damage: sufferharm(value, false); break;
	case DamageIA: sufferharm(value, true); break;
	case Regroup: enemy->effect = Regroup; break;
	}
}

bool hero::apply(aref<mastermove> moves, monster* enemy) {
	if(!moves)
		return false;
	mastermove* source[24];
	auto ps = source;
	auto pe = zendof(source);
	for(auto& e : moves) {
		if(!isallow(e.effect, e.count.c, enemy))
			continue;
		if(ps < pe)
			*ps++ = &e;
	}
	auto count = ps - source;
	if(!count)
		return false;
	apply(*source[rand() % count], enemy);
	return true;
}

void hero::apply(mastermove& m, monster* enemy) {
	auto random_effect = m.count.roll();
	if(m.text)
		act(m.text, random_effect);
	if(m.defy) {
		auto result = defydanger(m.defy.stat);
		if(result >= Success) {
			act(m.defy.text, random_effect);
			return;
		} else if(result == PartialSuccess)
			random_effect = random_effect / 2;
	}
	apply(m.effect, random_effect, enemy);
}