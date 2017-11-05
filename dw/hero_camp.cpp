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
	auto player = hero::chooseplayer(Wisdow, "��� ����� �������� ������?");
}