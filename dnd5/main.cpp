#include "main.h"

int	main(int argc, char *argv[]) {
	logs::quest q;
	if(!q.read("test.txt"))
		return 0;
	logs::setlight();
	auto s = sizeof(q);
	//logs::open("Dungeon&Dragons 5ed");
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(101);
	return main(0, 0);
}