#include "main.h"

int logs::getwidth(int panel) {
	return 300;
}

const char* logs::getpanel(int panel) {
	return "%party";
}

PRINTPLG(party) {
	logs::printer sc;
	result[0] = 0;
	auto p = result;
	for(auto& e : players) {
		if(!e)
			continue;
		sc.name = e.getname();
		sc.gender = e.getgender();
		if(e.getharm())
		sc.prints(p, result_maximum, "%герой\n");
		p = zend(p);
	}
	return result;
}