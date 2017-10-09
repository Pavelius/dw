#include "main.h"

int	main(int argc, char *argv[])
{
	logs::open("Test");
	players[0].create();
	monster e1(Goblin);
	game::combat(e1);
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw)
{
	return main(0, 0);
}