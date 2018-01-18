#include "main.h"

using namespace game;

void game::makecamp() {
	logs::add("������ �� ����� ������� ����� ��� �������.");
	partyrest(false);
	passtime(Duration8Hour);
	//auto guardian = whodo(Wisdow, 0, 0, "��� ����� �������� ������?");
}

void game::partyrest(bool forfree) {
	for(auto& e : players) {
		if(!e)
			continue;
		if(!useparty(Ration)) {
			e.act("%����� ����������%���.");
			continue;
		}
		e.healharm(e.getmaxhits() / 2);
		if(e.is(Commune) || e.is(PrepareSpells))
			e.preparespells(true);
	}
}

void game::eatrations(int count) {
	while(count > 0) {
		if(!useparty(Ration)) {
		}
	}
}

void game::journey() {
	monster_s wander_monster = Bandit;
	hero* exclude[4] = {0};
	auto consume_days = 4;
	auto pathfinder = whodo(Wisdow, 0, "��� ����� ����� ������?"); zcat(exclude, pathfinder);
	auto scout = whodo(Wisdow, exclude, "��� ����� ����������� ���� �������?"); zcat(exclude, scout);
	auto hunter = whodo(Wisdow, exclude, "��� ����� ������� �� ����������� ���?");
	logs::add("� ���, �� ����������� � ������.");
	logs::add("\n");
	auto hunter_result = hunter ? hunter->roll(hunter->get(Wisdow)) : Fail;
	switch(hunter_result) {
	case Success:
		logs::add("%1 �������� �� ������ ������� ���.",
			hunter->getname());
		pickup(DungeonRation);
		break;
	case PartialSuccess:
		logs::add("%1 �������� �� ����, �� �� ����� ������� ����.",
			hunter->getname());
		break;
	case Fail:
		logs::add("�� ������ � ��� ����������� ������� ���.");
		useparty(Ration);
		break;
	}
	logs::add("\n");
	auto scout_result = scout ? scout->roll(pathfinder->get(Wisdow)) : Fail;
	switch(scout_result) {
	case Success:
		logs::add("%1 ����������%2 ��������� � �����%2 �������� ������ � ��������������.",
			scout->getname(), scout->getA());
		break;
	case PartialSuccess:
		combat(wander_monster, Far);
		break;
	case Fail:
		logs::add("� ����� �� ������ �� ������ � ������!");
		combat(wander_monster, Close);
		break;
	}
	logs::add("\n");
	auto pathfinder_result = pathfinder ? pathfinder->roll(pathfinder->get(Wisdow)) : Fail;
	switch(pathfinder_result) {
	case Success:
		logs::add("%1 �����%2 ����� �������� ����.",
			pathfinder->getname(), pathfinder->getA());
		consume_days--;
		break;
	case PartialSuccess:
		logs::add("%1 ����� ������ ����.",
			pathfinder->getname(), pathfinder->getA());
		break;
	case Fail:
		logs::add("�� �� ������ ����� ������, ������� ����������� � ������� �� ��������� ���� ������.");
		consume_days += xrand(1, 3);
		break;
	}
	logs::next();
}