#include "main.h"

struct commandi {
	action_s	id;
	char		p1, p2;
	int roll() const {
		dice d = {(unsigned char)p1, (unsigned char)p2};
		return d.roll();
	}
};

BSDATA(commandi) = {{},
{Inflict, 1, 3},
{Inflict, 1, 6},
{Inflict, 2, 4},
{Suffer, 1, 3},
{Suffer, 1, 6},
{Suffer, 2, 6},
{Heal, 1, 6},
{Heal, 2, 6},
{Heal, 3, 6},
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

void hero::apply(command_s id) {
	auto& ci = bsdata<commandi>::elements[id];
	switch(ci.id) {
	case Suffer: sufferharm(ci.roll(), false); break;
	case Heal: healharm(ci.roll()); break;
	case SufferIA: sufferharm(ci.roll(), true); break;
	}
}

void hero::apply(command_s id, thing& e) {
	auto& ci = bsdata<commandi>::elements[id];
	switch(ci.id) {
	case Inflict: inflictharm(e, ci.roll());  break;
	default: apply(id); break;
	}
}