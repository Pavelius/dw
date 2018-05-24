#include "main.h"

int	main(int argc, char *argv[]) {
	auto hero_size = sizeof(hero);
	logs::setlight();
	logs::open("7 sea");
	hero party[2];
	//party[0].create(Castille, false, true);
	//party[0].set(AttackFencing, 2);
	//party[1].create(Avalon, false, true);
	//party[1].set(AttackHeavyWeapon, 1);
	//hero::beforecombat();
	//party[0].add(PartySide);
	//party[1].add(EnemySide);
	//hero::combat();
	party[0].create(true, true);
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((unsigned)time(0));
	//srand(120);
	return main(0, 0);
}