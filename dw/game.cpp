#include "command.h"
#include "main.h"

hero* game::getplayer()
{
	for(auto& player : players)
	{
		if(!player || !player.isalive())
			continue;
		return &player;
	}
	return 0;
}

bool game::isgameover()
{
	for(auto& e : players)
	{
		if(!e)
			continue;
		if(e.isalive())
			return false;
	}
	return true;
}

void game::clearactions()
{
	for(auto& player : players)
		player.actions = 0;
}

int	game::select(item* source, unsigned maximum, prosperty_s prosperty, resource_a* resources)
{
	auto pb = source;
	auto pe = source + maximum;
	for(auto i = RaggedBow; i < Coin; i = (item_s)(i + 1))
	{
		if(pb >= pe)
			break;
		item it(i);
		if(resources && !resources->is(it.getresource()))
			continue;
		if(it.getprosperty() > prosperty)
			continue;
		*pb++ = it;
	}
	return pb - source;
}