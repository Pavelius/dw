#include "main.h"

void looti::clear() {
	memset(this, 0, sizeof(*this));
}

void looti::add(item_s type) {
	for(auto& e : items) {
		if(e)
			continue;
		e = type;
		break;
	}
}

void looti::getitems(stringbuilder& sb, bool description) const {
	int count = 1;
	auto start = sb.get();
	for(int j = 0; items[j]; j++) {
		if(count == 1 && !items[j])
			break;
		if(items[j] == items[j + 1]) {
			count++;
			continue;
		}
		if(!sb.ispos(start))
			sb.add(", ");
		if(count > 1)
			sb.add("%1i ", count);
		item it(items[j]);
		it.getname(sb, description);
		count = 1;
	}
	if(coins) {
		if(!sb.ispos(start))
			sb.add(", ");
		sb.add("%1i монет", coins);
	}
	if(!sb.ispos(start))
		sb.add(".");
}

void looti::generate(int hoard) {
	if(hoard < 1)
		hoard = 1;
	switch(hoard) {
	case 1: coins += dice::roll(2, 8); break;
	case 2: add(AdventuringGear); break;
	case 3: coins += dice::roll(4, 10); break;
	case 4: add((item_s)xrand(Bloodstone, Onyx)); break;
	case 5: add(HealingPotion); break;
	case 6: add(Map); break;
	case 7: coins += dice::roll(1, 4) * 100; break;
	case 8: add((item_s)xrand(Alexandrite, Topaz)); break;
	case 9: coins += dice::roll(2, 4) * 100; break;
	case 10:
		// A magical item or magical effect
		break;
	case 11: coins += dice::roll(2, 4) * 100; break;
	case 12: coins += dice::roll(3, 4) * 100; break;
	case 13: coins += dice::roll(4, 4) * 100; break;
	case 14: coins += dice::roll(5, 4) * 100; break;
	case 15:
		break;
	case 16:
		break;
	case 17:
		break;
	default:
		coins += dice::roll(1, 10) * 1000;
		for(int i = xrand(1, 6); i > 0; i--)
			add((item_s)xrand(Alexandrite, Topaz));
		break;
	}
}

bool looti::pickup() {
	getitems(sb, false);
	an.add(1, "Взять все с собой.");
	an.add(0, "Не брать ничего. Все оставить все здесь.");
	auto id = an.choose();
	if(!id)
		return false;
	if(coins) {
		hero::addcoins(coins, true);
		logs::next();
	}
	for(auto& e : items) {
		if(e)
			game::pickup(e);
	}
	return true;
}