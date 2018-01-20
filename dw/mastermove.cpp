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
		for(auto& e : players) {
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

void hero::apply(effect_s id, int type, int value, monster* enemy) {
	if(!id && !value)
		return;
	switch(id) {
	case LooseMoney: addcoins(value, false); break;
	case LooseItem:
		for(auto& e : players) {
			if(!e)
				continue;
			for(auto i : gear) {
				if(i.type == (item_s)value) {
					if(i.use())
						return;
					i.clear();
					return;
				}
			}
		}
		break;
	case Heal: healharm(value); break;
	case Debility: setdebilities((stat_s)value, true); break;
	case HealParty:
	case DebilityParty:
	case DamageAllParty:
	case DamageAllPartyIA:
		for(auto& e : players) {
			if(!e)
				continue;
			auto sid = getsingle(id);
			if(sid != id)
				e.apply(id, type, value, enemy);
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
	auto pe = source + lenghtof(source);
	for(auto& e : moves) {
		if(!isallow(e.effect, e.type, enemy))
			continue;
		if(ps < pe)
			*ps++ = &e;
	}
	auto count = ps - source;
	if(!count)
		return false;
	auto p = source[rand() % count];
	auto random_effect = p->count.roll();
	if(p->text)
		act(p->text, random_effect);
	if(p->defy) {
		auto result = defydanger(p->defy.stat);
		if(result >= Success) {
			act(p->defy.text, random_effect);
			return true;
		} else if(result == PartialSuccess)
			random_effect = random_effect / 2;
	}
	apply(p->effect, p->type, random_effect, enemy);
	return true;
}