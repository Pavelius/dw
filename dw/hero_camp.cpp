#include "main.h"

void hero::makecamp()
{
	logs::add("[%1] ����� ������� ����� ��� �������.", getname());
	if(useration())
	{
		logs::add("�� ������ ������������ ����������� ������ � ������ ����������.");
		for(auto& e : players)
		{
			if(!e)
				continue;
			e.healharm(e.getmaxhits() / 2);
		}
	}
	// ��, ��� �����, ������ ������ ���� ����������
	for(auto& e : players)
	{
		if(!e)
			continue;
		if(e.is(Commune) || e.is(PrepareSpells))
			e.preparespells();
	}
	auto player = hero::chooseplayer(Wisdow, 0, 0, "��� ����� �������� ������?");
}

void game::eatrations(int count)
{
	for(auto& e : players)
	{

	}
}

void hero::journey()
{
	int extra;
	auto consume_days = 4;
	auto consume_food = consume_days;
	auto pathfinder = chooseplayer(Wisdow, 0, 0, "��� ����� ����� ������?");
	auto scout = chooseplayer(Wisdow, pathfinder, 0, "��� ����� ����������� ���� �������?");
	auto hunter = chooseplayer(Wisdow, scout, pathfinder, "��� ����� ������� �� ����������� ���?");
	logs::add("� ���, �� ����������� � ������.");
	logs::add("\n");
	auto hunter_result = hunter ? hunter->roll(hunter->get(Wisdow)) : Fail;
	switch(hunter_result)
	{
	case Success:
		logs::add("%1 �������� �� ������ ������� ���.",
			hunter->getname());
		consume_food--;
		break;
	case PartialSuccess:
		logs::add("%1 �������� �� ����, �� �� ����� ������� ����.",
			hunter->getname());
		break;
	case Fail:
		logs::add("�� ������ ����� ����� ��� �������.");
		consume_food += xrand(1, 3);
		break;
	}
	logs::add("\n");
	auto scout_result = scout ? scout->roll(pathfinder->get(Wisdow)) : Fail;
	switch(scout_result)
	{
	case Success:
		logs::add("%1 ����������%2 ��������� � �����%2 �������� ������ � ��������������.",
			scout->getname(), scout->getA());
		break;
	case PartialSuccess:
		break;
	case Fail:
		logs::add("� ����� �� ������ �� ������ � ������!");
		break;
	}
	logs::add("\n");
	auto pathfinder_result = pathfinder ? pathfinder->roll(pathfinder->get(Wisdow)) : Fail;
	switch(pathfinder_result)
	{
	case Success:
		logs::add("%1 �����%2 ����� �������� ����.",
			pathfinder->getname(), pathfinder->getA());
		break;
	case PartialSuccess:
		logs::add("%1 ����� ������ ����.",
			pathfinder->getname(), pathfinder->getA());
		break;
	case Fail:
		logs::add("�� �� ������ ����� ������, ������� ����������� � ������� � ���� �� ��������� ���� ������.");
		extra = xrand(1, 3);
		consume_food += extra;
		consume_days += extra;
		break;
	}
	if(consume_food < 0)
		consume_food = 0;
	logs::next();
}