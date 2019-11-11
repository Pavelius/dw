#include "main.h"

void thing::act(const char* format, ...) const {
	driver dr(sb);
	dr.name = getname();
	dr.gender = getgender();
	dr.opponent_name = 0;
	dr.opponent_gender = Male;
	dr.addv(format, xva_start(format));
	sb = dr;
}

void thing::act(thing& enemy, const char* format, ...) const {
	driver dr(sb);
	dr.name = getname();
	dr.gender = getgender();
	dr.opponent_name = enemy.getname();
	dr.opponent_gender = enemy.getgender();
	dr.addv(format, xva_start(format));
	sb = dr;
}

result_s thing::roll(int bonus, int* result, bool interactive) {
	auto d = (rand() % 6) + (rand() % 6) + 2;
	auto r = d + bonus;
	if(r <= 6) {
		if(interactive)
			sb.add("[-{%1i%+2i=%3i}]", d, bonus, r);
		return Fail;
	} else if(r <= 9) {
		if(interactive)
			sb.add("{%1i%+2i=%3i}", d, bonus, r);
		return PartialSuccess;
	} else {
		if(interactive)
			sb.add("[+{%1i%+2i=%3i}]", d, bonus, r);
		return Success;
	}
}