#include "main.h"

void hero::sheet() {
	sb.add("###%1 - %5 %4 %2 (%3i уровень)\n", getname(), getstr(type), level, getstr(race), getstr(alignment));
	for(auto m = Strenght; m <= Charisma; m = (stat_s)(m + 1)) {
		if(m != Strenght)
			sb.add(", ");
		sb.add("%1 %2i", getstr(m), getraw(m));
	}
	sb.add(".\n");
	for(auto& e : gear) {
		if(!e)
			continue;
		if(&e==gear)
			sb.add("**В рюкзаке**: ");
		else
			sb.add(", ");
		e.getname(sb, false);
	}
	an.add(1, "Закончить просмотр.");
	auto id = whatdo();
	switch(id) {
	case 1: return;
	}
}