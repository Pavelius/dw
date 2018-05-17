#include "range.h"

const range* range::find(int value) const
{
	if(!this)
		return 0;
	for(auto p = this; p->text; p++)
	{
		if(p->from >= value && value <= p->to)
			return p;
	}
	return 0;
}