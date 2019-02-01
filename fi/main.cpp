#include "main.h"

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("Test");
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(101);
	return main(0, 0);
}