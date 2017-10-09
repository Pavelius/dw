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