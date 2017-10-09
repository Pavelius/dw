#include "main.h"

int	main(int argc, char *argv[])
{
	steading e;
	logs::open("Test");
	players[0].create(Ranger);
	e.adventure();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw)
{
	return main(0, 0);
}