#include "command.h"
#include "main.h"

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