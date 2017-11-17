#include "main.h"

void loot_i::clear()
{
	memset(this, 0, sizeof(*this));
}

void loot_i::add(item_s type)
{
	for(auto& e : item)
	{
		if(e)
			continue;
		e = type;
	}
}

char* loot_i::getitems(char* result, bool description) const
{
	result[0] = 0;
	int count = 1;
	for(int j = 0; item[j]; j++)
	{
		if(item[j] == item[j + 1])
		{
			count++;
			continue;
		}
		if(result[0])
			zcat(result, ", ");
		if(count > 1)
			szprint(zend(result), "%1i ", count);
		::item it(item[j]);
		it.getname(zend(result), description);
		count = 1;
	}
	if(coins)
	{
		if(result[0])
			zcat(result, ", ");
		szprint(zend(result), "%1i монет", coins);
	}
	if(result[0])
		zcat(result, ".");
	return result;
}