#include "main.h"

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("Dungeon&Dragons 5ed");
	scene room;
	//creature player(Elf, Male, Cleric, Soldier, 0, true);
	creature player;
	player.create(false);
	player.set(Helpful);
	player.rest(true);
	player.setcoins(100 * GP);
	creature m1, m2;
	m1.create(Kobold);
	m2.create(Kobold);
	room.creatures.add(&m1);
	room.creatures.add(&m2);
	room.creatures.add(&player);
	room.combat(true);
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(1100);
	return main(0, 0);
}