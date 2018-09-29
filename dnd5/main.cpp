#include "main.h"

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("Dungeon&Dragons 5ed");
	creature player(Human, Male, Fighter, Soldier, 0, false);
	creature enemy(Kobold);
	//auto player = creature::generate(false);
	player.attack(MeleeWeapon, enemy);
	logs::next();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(101);
	return main(0, 0);
}