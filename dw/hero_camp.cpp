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
	auto player = hero::whodo(Wisdow, 0, 0, "��� ����� �������� ������?");
}

void hero::eatrations(int count)
{
	for(auto& e : players)
	{
	}
}

void hero::journey()
{
	hero* exclude[4] = {0};
	int extra;
	auto consume_days = 4;
	auto consume_food = consume_days;
	auto pathfinder = whodo(Wisdow, 0, "��� ����� ����� ������?"); zcat(exclude, pathfinder);
	auto scout = whodo(Wisdow, exclude, "��� ����� ����������� ���� �������?"); zcat(exclude, pathfinder);
	auto hunter = whodo(Wisdow, exclude, "��� ����� ������� �� ����������� ���?");
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
		logs::add("�� ������ �� �������� ������ [�����]. ��� ��� ���� ��������");
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