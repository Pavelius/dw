#include "main.h"

void hero::makecamp()
{
	logs::add("[%1] нашел хорошее место дл€ привала.", getname());
	if(useration())
	{
		logs::add("¬ы быстро организовали миниатюрный костер и слегка перекусили.");
		for(auto& e : players)
		{
			if(!e)
				continue;
			e.healharm(e.getmaxhits() / 2);
		}
	}
	// “е, кто умеют, заучат заново свои заклинани€
	for(auto& e : players)
	{
		if(!e)
			continue;
		if(e.is(Commune) || e.is(PrepareSpells))
			e.preparespells();
	}
	auto player = hero::chooseplayer(Wisdow, 0, 0, " то будет охран€ть лагерь?");
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
	auto pathfinder = chooseplayer(Wisdow, 0, 0, " то будет вести партию?");
	auto scout = chooseplayer(Wisdow, pathfinder, 0, " то будет разведывать путь впереди?");
	auto hunter = chooseplayer(Wisdow, scout, pathfinder, " то будет следить за количеством еды?");
	logs::add("» вот, вы отправились в дорогу.");
	logs::add("\n");
	auto hunter_result = hunter ? hunter->roll(hunter->get(Wisdow)) : Fail;
	switch(hunter_result)
	{
	case Success:
		logs::add("%1 раздобыл по дороге немного еды.",
			hunter->getname());
		consume_food--;
		break;
	case PartialSuccess:
		logs::add("%1 охотилс€ по пути, но не сумел поймать дичь.",
			hunter->getname());
		break;
	case Fail:
		logs::add("ѕо дороге часть вашей еды пропало.");
		consume_food += xrand(1, 3);
		break;
	}
	logs::add("\n");
	auto scout_result = scout ? scout->roll(pathfinder->get(Wisdow)) : Fail;
	switch(scout_result)
	{
	case Success:
		logs::add("%1 разведывал%2 местность и сумел%2 избежать встреч с непри€тност€ми.",
			scout->getname(), scout->getA());
		break;
	case PartialSuccess:
		break;
	case Fail:
		logs::add("» вдруг по дороге вы попали в засаду!");
		break;
	}
	logs::add("\n");
	auto pathfinder_result = pathfinder ? pathfinder->roll(pathfinder->get(Wisdow)) : Fail;
	switch(pathfinder_result)
	{
	case Success:
		logs::add("%1 сумел%2 найти короткий путь.",
			pathfinder->getname(), pathfinder->getA());
		break;
	case PartialSuccess:
		logs::add("%1 нашел верный путь.",
			pathfinder->getname(), pathfinder->getA());
		break;
	case Fail:
		logs::add("¬ы не сумели найти дорогу, поэтому заблудились и провели в пути на несколько дней больше.");
		extra = xrand(1, 3);
		consume_food += extra;
		consume_days += extra;
		break;
	}
	if(consume_food < 0)
		consume_food = 0;
	logs::next();
}