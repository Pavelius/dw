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
	auto player = hero::whodo(Wisdow, 0, 0, " то будет охран€ть лагерь?");
}

void hero::eatrations(int count)
{
	for(auto& e : players)
	{
	}
}

void hero::journey()
{
	monster_s wander_monster = Bandit;
	hero* exclude[4] = {0};
	auto consume_days = 4;
	auto pathfinder = whodo(Wisdow, 0, " то будет вести партию?"); zcat(exclude, pathfinder);
	auto scout = whodo(Wisdow, exclude, " то будет разведывать путь впереди?"); zcat(exclude, scout);
	auto hunter = whodo(Wisdow, exclude, " то будет следить за количеством еды?");
	logs::add("» вот, вы отправились в дорогу.");
	logs::add("\n");
	auto hunter_result = hunter ? hunter->roll(hunter->get(Wisdow)) : Fail;
	switch(hunter_result)
	{
	case Success:
		logs::add("%1 раздобыл по дороге немного еды.",
			hunter->getname());
		pickup(DungeonRation);
		break;
	case PartialSuccess:
		logs::add("%1 охотилс€ по пути, но не сумел поймать дичь.",
			hunter->getname());
		break;
	case Fail:
		logs::add("ѕо дороге у вас испортилось немного еды.");
		for(auto& e : players)
		{
			if(e)
				e.useration();
		}
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
		combat(wander_monster, Far);
		break;
	case Fail:
		logs::add("» вдруг по дороге вы попали в засаду!");
		combat(wander_monster, Close);
		break;
	}
	logs::add("\n");
	auto pathfinder_result = pathfinder ? pathfinder->roll(pathfinder->get(Wisdow)) : Fail;
	switch(pathfinder_result)
	{
	case Success:
		logs::add("%1 сумел%2 найти короткий путь.",
			pathfinder->getname(), pathfinder->getA());
		consume_days--;
		break;
	case PartialSuccess:
		logs::add("%1 нашел верный путь.",
			pathfinder->getname(), pathfinder->getA());
		break;
	case Fail:
		logs::add("¬ы не сумели найти дорогу, поэтому заблудились и блукали на несколько дней больше.");
		consume_days += xrand(1, 3);
		break;
	}
	logs::next();
}