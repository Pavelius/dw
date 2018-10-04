#include "main.h"

void creature::buy(aref<item> items, bool interactive) {
	char temp[260];
	while(true) {
		auto coinst = getcoins();
		for(auto e : items) {
			if(e.getcost() > coins)
				continue;
			logs::add(items.indexof(e), "%1 (стоит %2)", getstr(e),
				getcoins(temp, zendof(temp), e.getcost()));
		}
		if(logs::getcount() == 0) {
			if(interactive) {
				logs::add(" -   сожелению мне вам нечего предложить. «аходите, когда у вас по€витс€ больше денег.");
				logs::next();
			}
			return;
		}
		logs::add(-1, "Ќичего не надо");
		auto index = logs::input(interactive, false, " - „то желаете приобрести? (у вас есть %1)", getcoins(temp, zendof(temp), coins));
		if(index == -1)
			return;
		setcoins(coins - items[index].getcost());
		act("\n%герой купил%а %-1.", items[index].getnamewh(temp, zendof(temp)));
		add(items[index]);
	}
}

void creature::buyweapon(int level, bool interactive) {
	static item simple_weapon[] = {Shortbow, Mace, Staff, Greatclub};
	buy(simple_weapon, interactive);
}