#include "main.h"

void hero::sheet() {
	logs::add("###%1 - %5 %4 %2 (%3i уровень)\n", getname(), getstr(type), level, getstr(race), getstr(alignment));
	for(auto m = Strenght; m <= Charisma; m = (stat_s)(m + 1)) {
		if(m != Strenght)
			logs::add(", ");
		logs::add("%1 %2i", getstr(m), getraw(m));
	}
	logs::add(".\n");
	for(auto& e : gear) {
		if(!e)
			continue;
		if(&e==gear)
			logs::add("**В рюкзаке**: ");
		else
			logs::add(", ");
		char temp[260];
		logs::add(e.getname(temp, true));
	}
	logs::add(".\n");
	logs::add(1, "Закончить просмотр.");
	auto id = whatdo();
	switch(id) {
	case 1: return;
	}
}