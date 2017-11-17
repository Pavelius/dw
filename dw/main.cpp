#include "main.h"

int	main(int argc, char *argv[])
{
	logs::open("Test");
	steading::createworld();
	players[0].create(false, Wizard, Male);
	players[1].create(false, Theif, Female);
	players[2].create(false, Fighter, Male);
	//hero::pickup(SwordLong);
	hero::journey();
	hero::combat(Bandit, Near, 1);
	steadings[0].adventure();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw)
{
	srand((int)time(0));
	return main(0, 0);
}