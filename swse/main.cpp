#include "main.h"

int	main(int argc, char *argv[]) {
	logs::open("SW");
	logs::setlight();
	location test;
	creature c1(Stormtrooper);
	creature c2(Stormtrooper);
	auto p = new creature(Human, Male, Jedi, false, true);
	//game::combat(true);
	test.create();
	test.acting();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	//1srand((unsigned)time(0));
	srand(120);
	return main(0, 0);
}