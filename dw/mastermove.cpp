#include "main.h"

bool hero::isallow(effect_s id, int value) const {
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
		return hp<getmaxhits();
	case Debility:
		return !isdebilities((stat_s)value);
	case HealParty:
	case DebilityParty:
		for(auto& e : players) {
			if(!e)
				continue;
			if(e.isallow(id, value))
				return true;
		}
		return false;
	default:
		return true;
	}
}

void hero::apply(effect_s id, int value, bool interactive) {
	switch(id) {
	case LooseMoney: addcoins(value, interactive); break;
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
		for(auto& e : players) {
			if(!e)
				continue;
			e.apply(id, value, interactive);
		}
		break;
	case Damage: sufferharm(value, false); break;
	}
}