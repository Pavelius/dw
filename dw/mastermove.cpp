#include "main.h"

bool hero::isallow(effect_s id, int subtype, monster* enemy) const {
	switch(id) {
	case LooseMoney:
		return getcoins() > 0;
	case LooseItem:
		for(auto i : gear) {
			if(i == (item_s)subtype)
				return true;
		}
		return false;
	case Heal:
		return gethp() < getmaxhits();
	case Debility:
		return !isdebilities((stat_s)subtype);
	case HealParty:
	case DebilityParty:
		for(auto& e : bsmeta<hero>()) {
			if(!e)
				continue;
			if(e.isallow(id, subtype, enemy))
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

void hero::apply(effect_s id, int subtype, monster* enemy) {
	if(!id && !subtype)
		return;
	switch(id) {
	case LooseMoney: addcoins(subtype, false); break;
	case LooseItem:
		for(auto& e : bsmeta<hero>()) {
			if(!e)
				continue;
			if(e.use((item_s)subtype, true))
				return;
		}
		break;
	case Heal: healharm(subtype); break;
	case Debility: setdebilities((stat_s)subtype, true); break;
	case HealParty:
	case DebilityParty:
	case DamageAllParty:
	case DamageAllPartyIA:
		for(auto& e : bsmeta<hero>()) {
			if(!e)
				continue;
			auto sid = getsingle(id);
			if(sid != id)
				e.apply(id, subtype, enemy);
		}
		break;
	case Summon: enemy->count += subtype; break;
	case Damage: sufferharm(subtype, false); break;
	case DamageIA: sufferharm(subtype, true); break;
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