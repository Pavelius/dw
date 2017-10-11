#include "main.h"

void game::createworld()
{
	steading* source[sizeof(steadings) / sizeof(steadings[0])];
	auto ps = source;
	for(auto& e : steadings)
	{
		e.clear();
		*ps++ = &e;
	}
	zshuffle(source, sizeof(steadings) / sizeof(steadings[0]));
	int count_city = 6;
	int count_town = 12;
	int count_keep = 12;
	for(auto p : source)
	{
		if(count_city)
		{
			p->create(City);
			count_city--;
		}
		else if(count_town)
		{
			p->create(Town);
			count_town--;
		}
		else if(count_keep)
		{
			p->create(Town);
			count_keep--;
		}
		else
			p->create(Village);
	}
}