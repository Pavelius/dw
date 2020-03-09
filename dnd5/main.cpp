#include "main.h"

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("Dungeon&Dragons 5ed");
	scene room;
	creature player;
	player.create(Elf, Male, Fighter, Soldier, 0, false);
	player.set(Helpful);
	player.rest(true);
	player.setcoins(100 * GP);
	creature m1, m2;
	m1.create(Kobold);
	m2.create(Kobold);
	room.add(m1);
	room.add(m2);
	room.add(player);
	room.combat(true);
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(1100);
	return main(0, 0);
}