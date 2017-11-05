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
	auto player = hero::chooseplayer(Wisdow, "Кто будет охранять лагерь?");
}