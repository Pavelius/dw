#include "main.h"

int	main(int argc, char *argv[])
{
	logs::open("Test");
	game::createworld();
	players[0].create(true, Wizard, Male);
	players[1].create(true, Theif, Female);
	players[2].create(true, Fighter, Male);
	//hero::journey();
	hero::combat(Bandit);
	steadings[0].adventure();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw)
{
	srand((int)time(0));
	return main(0, 0);
}