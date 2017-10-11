#include "main.h"

int	main(int argc, char *argv[])
{
	srand((int)time(0));
	logs::open("Test");
	game::createworld();
	players[0].create(Theif);
	players[1].create(Ranger);
	steadings[0].adventure();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw)
{
	return main(0, 0);
}