#include "main.h"

void hero::makecamp()
{
	logs::add("[%1] нашел хорошее место для привала.", getname());
	if(useration())
	{
		logs::add("Вы быстро организовали миниатюрный костер и слегка перекусили.");
		for(auto& e : players)
		{
			if(!e)
				continue;
			e.healharm(e.getmaxhits() / 2);
		}
	}
	// Те, кто умеют, заучат заново свои заклинания
	for(auto& e : players)
	{
		if(!e)
			continue;
		if(e.is(Commune) || e.is(PrepareSpells))
			e.preparespells();
	}
	auto player = hero::whodo(Wisdow, 0, 0, "Кто будет охранять лагерь?");
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
	auto pathfinder = whodo(Wisdow, 0, "Кто будет вести партию?"); zcat(exclude, pathfinder);
	auto scout = whodo(Wisdow, exclude, "Кто будет разведывать путь впереди?"); zcat(exclude, pathfinder);
	auto hunter = whodo(Wisdow, exclude, "Кто будет следить за количеством еды?");
	logs::add("И вот, вы отправились в дорогу.");
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
		logs::add("%1 охотился по пути, но не сумел поймать дичь.",
			hunter->getname());
		break;
	case Fail:
		logs::add("По дороге часть вашей еды пропало.");
		consume_food += xrand(1, 3);
		break;
	}
	logs::add("\n");
	auto scout_result = scout ? scout->roll(pathfinder->get(Wisdow)) : Fail;
	switch(scout_result)
	{
	case Success:
		logs::add("%1 разведывал%2 местность и сумел%2 избежать встреч с неприятностями.",
			scout->getname(), scout->getA());
		break;
	case PartialSuccess:
		logs::add("По дороге вы заметили группу [окров]. Они вас тоже заметили");
		break;
	case Fail:
		logs::add("И вдруг по дороге вы попали в засаду!");
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
		logs::add("Вы не сумели найти дорогу, поэтому заблудились и провели в пути на несколько дней больше.");
		extra = xrand(1, 3);
		consume_food += extra;
		consume_days += extra;
		break;
	}
	if(consume_food < 0)
		consume_food = 0;
	logs::next();
}