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
			an.add(items.indexof(e), "%1 (����� %2)", name, temp);
		}
		if(!an) {
			if(interactive) {
				sb.add(" - � ��������� ��� ��� ������ ����������. ��������, ����� � ��� �������� ������ �����.");
				next();
			}
			return;
		}
		an.add(-1, "������ �� ����");
		sc.clear();
		addcoins(sc, coins);
		auto index = an.choose(interactive, false, " - ��� ������� ����������? (� ��� ���� %1)", temp);
		if(index == -1)
			return;
		setcoins(coins - items[index].getcost());
		sn.clear(); items[index].addnamewh(sn);
		act("\n%����� �����%� %-1.", name);
		add(items[index]);
	}
}

void creature::buyweapon(int level, bool interactive) {
	static item simple_weapon[] = {Shortbow, Mace, Staff, Greatclub};
	sb.add("� �������������� ��������� ������ ��������� �������� � ���������� ������. � ������ � ��������� ������ ����, ����, �����, ������ � ������ ������, ���������� � �����.");
	buy(simple_weapon, interactive);
}