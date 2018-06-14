#include "main.h"

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("7 sea");
	hero player(false, true);
	hero enemy(false, false);
	player.beforecombat();
	player.add(PartySide);
	enemy.add(EnemySide);
	player.combat();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((unsigned)time(0));
	//srand(120);
	return main(0, 0);
}