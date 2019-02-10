#include "main.h"

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("Test");
	scene s;
	character e1; e1.create(false);
	character e2; e2.create(false);
	character e3; e3.create(Bear);
	auto m = sizeof(e1);
	s.initiative();
	s.add(&e1); e1.set(Friendly);
	s.add(&e2); e2.set(Hostile);
	s.combat();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(101);
	return main(0, 0);
}