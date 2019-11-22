#include "main.h"

int	main(int argc, char *argv[]) {
	logs::open("SW");
	logs::setlight();
	location test;
	test.add(new creature(true, true), PartySide);
	test.add(new creature(Stormtrooper));
	test.add(new creature(Stormtrooper));
	test.enter();
	test.combat(true);
	//test.acting();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	//1srand((unsigned)time(0));
	srand(120);
	return main(0, 0);
}