#include "main.h"

struct commandi {
	action_s		id;
	dice			result;
};
commandi bsmeta<commandi>::elements[] = {{},
{Inflict, {1, 3}},
{Inflict, {1, 6}},
{Inflict, {2, 4}},
{Suffer, {1, 3}},
{Suffer, {1, 6}},
{Suffer, {2, 6}},
};

//static action_s getsingle(action_s id) {
//	switch(id) {
//	case DamageAllParty: return Damage;
//	case DamageAllPartyIA: return DamageIA;
//	case HealParty: return Heal;
//	case DebilityParty: return Debility;
//	default: return id;
//	}
//}

//bool hero::isallow(effect_s id, int subtype, monster* enemy) const {
//	switch(id) {
//	case LooseMoney:
//		return getcoins() > 0;
//	case LooseItem:
//		for(auto i : gear) {
//			if(i == (item_s)subtype)
//				return true;
//		}
//		return false;
//	case Heal:
//		return gethp() < getmaxhits();
//	case Debility:
//		return !isdebilities((stat_s)subtype);
//	case HealParty:
//	case DebilityParty:
//		for(auto& e : bsmeta<hero>()) {
//			if(!e)
//				continue;
//			if(e.isallow(id, subtype, enemy))
//				return true;
//		}
//		return false;
//	case Summon:
//		return enemy && enemy->count < 8;
//	case Regroup:
//		return enemy && enemy->count <= 5;
//	default:
//		return true;
//	}
//}

void hero::apply(thing& e, command_s id) {
	auto& ci = bsmeta<commandi>::elements[id];
	switch(ci.id) {
	case Inflict:
		inflictharm(e, ci.result.roll()); 
		break;
	case Suffer:
		sufferharm(ci.result.roll(), false);
		break;
	case SufferIA:
		sufferharm(ci.result.roll(), true);
		break;
	}
}