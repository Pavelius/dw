#include "main.h"

using namespace game;

void game::makecamp() {
	sb.add("������ �� ����� ������� ����� ��� �������.");
	partyrest(false);
	//auto guardian = whodo(Wisdow, 0, 0, "��� ����� �������� ������?");
	passtime(Duration8Hour);
}

void game::partyrest(bool forfree) {
	for(auto& e : players) {
		if(!e)
			continue;
		if(!forfree && !useparty(Ration, true, true)) {
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
		if(!useparty(Ration, true, true)) {
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
	sb.add("� ���, �� ����������� � ������.");
	auto hunter_result = hunter ? hunter->roll(hunter->get(Wisdow)) : Fail;
	switch(hunter_result) {
	case Success:
		sb.adds("%1 �������� �� ������ ������� ���.",
			hunter->getname());
		pickup(DungeonRation);
		break;
	case PartialSuccess:
		sb.adds("%1 �������� �� ����, �� �� ����� ������� ����.",
			hunter->getname());
		break;
	case Fail:
		sb.adds("�� ������ � ��� ����������� ������� ���.");
		useparty(Ration, true, true);
		break;
	}
	auto scout_result = scout ? scout->roll(pathfinder->get(Wisdow)) : Fail;
	switch(scout_result) {
	case Success:
		sb.adds("%1 ����������%2 ��������� � �����%2 �������� ������ � ��������������.",
			scout->getname(), scout->getA());
		break;
	case PartialSuccess:
		combat(wander_monster, Far);
		break;
	case Fail:
		sb.adds("� ����� �� ������ �� ������ � ������!");
		combat(wander_monster, Close);
		break;
	}
	auto pathfinder_result = pathfinder ? pathfinder->roll(pathfinder->get(Wisdow)) : Fail;
	switch(pathfinder_result) {
	case Success:
		sb.adds("%1 �����%2 ����� �������� ����.",
			pathfinder->getname(), pathfinder->getA());
		consume_days--;
		break;
	case PartialSuccess:
		sb.adds("%1 ����� ������ ����.",
			pathfinder->getname(), pathfinder->getA());
		break;
	case Fail:
		sb.adds("�� �� ������ ����� ������, ������� ����������� � ������� �� ��������� ���� ������.");
		consume_days += xrand(1, 3);
		break;
	}
	logs::next();
}