#include "main.h"

void creature::buy(aref<item> items, bool interactive) {
	auto coinst = getcoins();
	for(auto e : items) {
		if(e.getcost() > coins)
			continue;
		logs::add(items.indexof(e), "%1 (стоит %2i монет)", getstr(e), e.getcost());
	}
	if(logs::getcount() == 0) {
		if(interactive) {
			logs::add(" -   сожелению мне вам нечего предложить. «аходите, когда у вас по€витс€ больше денег.");
			logs::next();
		}
		return;
	}
	auto index = logs::input(interactive, false, " - „то желаете приобрести? (у вас есть [%1i] монет", coins);
	setcoins(coins - items[index].getcost());
	add(items[index]);
}

void creature::buyweapon(int level, bool interactive) {
	static item simple_weapon[] = {Shortbow, Mace, Staff, Greatclub};
	buy(simple_weapon, interactive);
}