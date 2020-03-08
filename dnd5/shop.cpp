#include "main.h"

void creature::buy(aref<item> items, bool interactive) {
	char temp[260]; stringbuilder sc(temp);
	char name[260]; stringbuilder sn(name);
	while(true) {
		auto coinst = getcoins();
		for(auto e : items) {
			if(e.getcost() > coins)
				continue;
			sn.clear(); e.addname(sn);
			sc.clear(); addcoins(sc, e.getcost());
			an.add(items.indexof(e), "%1 (стоит %2)", name, temp);
		}
		if(!an) {
			if(interactive) {
				sb.add(" -   сожелению мне вам нечего предложить. «аходите, когда у вас по€витс€ больше денег.");
				next();
			}
			return;
		}
		an.add(-1, "Ќичего не надо");
		sc.clear();
		addcoins(sc, coins);
		auto index = an.choose(interactive, false, " - „то желаете приобрести? (у вас есть %1)", temp);
		if(index == -1)
			return;
		setcoins(coins - items[index].getcost());
		sn.clear(); items[index].addnamewh(sn);
		act("\n%герой купил%а %-1.", name);
		add(items[index]);
	}
}

void creature::buyweapon(int level, bool interactive) {
	static item simple_weapon[] = {Shortbow, Mace, Staff, Greatclub};
	sb.add("¬ полуподвальном помещении сто€ло множество стелажей и дерев€нных шкафов. ¬ шкафах и стеллажах лежали мечи, щиты, шлемы, топоры и прочее оружие, замотанное в ткань.");
	buy(simple_weapon, interactive);
}