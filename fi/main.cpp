#include "main.h"

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("Test");
	scene s;
	character e1; e1.create(true);
	character e2; e2.create(false);
	s.add(&e1); e1.set(Friendly);
	s.add(&e2); e2.set(Hostile);
	if(!s.isenemy())
		return 0;
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(101);
	return main(0, 0);
}