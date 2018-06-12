#include "main.h"

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("7 sea");
	hero party[2];
	party[0].create(true, true);
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((unsigned)time(0));
	//srand(120);
	return main(0, 0);
}