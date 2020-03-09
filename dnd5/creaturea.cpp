#include "main.h"

void creaturea::match(reaction_s v) {
	auto pb = data;
	for(auto p : *this) {
		if(!p->is(v))
			continue;
		*pb++ = p;
	}
	count = pb - data;
}