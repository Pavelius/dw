#include "main.h"

result_s game::roll(int bonus, int* result, bool interactive) {
	auto d = (rand() % 6) + (rand() % 6) + 2;
	auto r = d + bonus;
	if(r <= 6) {
		if(interactive)
			logs::add("[-{%1i%+2i=%3i}]", d, bonus, r);
		return Fail;
	} else if(r <= 9) {
		if(interactive)
			logs::add("{%1i%+2i=%3i}", d, bonus, r);
		return PartialSuccess;
	} else {
		if(interactive)
			logs::add("[+{%1i%+2i=%3i}]", d, bonus, r);
		return Success;
	}
}