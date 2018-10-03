#include "main.h"

void creature::buy(aref<item> items, bool interactive) {
	auto coinst = getcoins();
	for(auto e : items) {
		if(e.getcost() > coins)
			continue;
		logs::add(items.indexof(e), "%1 (����� %2i �����)", getstr(e), e.getcost());
	}
	if(logs::getcount() == 0) {
		if(interactive) {
			logs::add(" - � ��������� ��� ��� ������ ����������. ��������, ����� � ��� �������� ������ �����.");
			logs::next();
		}
		return;
	}
	auto index = logs::input(interactive, false, " - ��� ������� ����������? (� ��� ���� [%1i] �����", coins);
	setcoins(coins - items[index].getcost());
	add(items[index]);
}

void creature::buyweapon(int level, bool interactive) {
	static item simple_weapon[] = {Shortbow, Mace, Staff, Greatclub};
	buy(simple_weapon, interactive);
}