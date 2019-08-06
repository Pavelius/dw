#include "main.h"

bool effecti::allow(const playeri& player, const monsteri& opponent) const {
	switch(type) {
	case Damage:
	case DamageAllParty:
	case DamageIA:
	case DamageAllPartyIA:
		return player.isalive();
	case DamageOpponent:
	case DamageOpponentIA:
		return opponent.isalive();
	case Heal:
	case HealParty:
		return player.iswounded();
	default:
		return false;
	}
}

void effecti::apply(const playeri& player, const monsteri& opponent) const {
}