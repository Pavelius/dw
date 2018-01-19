#include "main.h"

void lootinfo::clear() {
	memset(this, 0, sizeof(*this));
}

void lootinfo::add(item_s type) {
	for(auto& e : items) {
		if(e)
			continue;
		e = type;
		break;
	}
}

char* lootinfo::getitems(char* result, bool description) const {
	result[0] = 0;
	int count = 1;
	for(int j = 0; items[j]; j++) {
		if(items[j] == items[j + 1]) {
			count++;
			continue;
		}
		if(result[0])
			zcat(result, ", ");
		if(count > 1)
			szprint(zend(result), "%1i ", count);
		item it(items[j]);
		it.getname(zend(result), description);
		count = 1;
	}
	if(coins) {
		if(result[0])
			zcat(result, ", ");
		szprint(zend(result), "%1i монет", coins);
	}
	if(result[0])
		zcat(result, ".");
	return result;
}

void lootinfo::generate(int hoard) {
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

bool lootinfo::pickup() {
	getitems(logs::getptr(), false);
	logs::add(1, "Взять все с собой.");
	logs::add(0, "Не брать ничего. Все оставить все здесь.");
	auto id = logs::input();
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