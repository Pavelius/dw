#include "main.h"

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("Dungeon&Dragons 5ed");
	scene room;
	//creature player(Elf, Male, Cleric, Soldier, 0, true);
	auto player = creature::generate(false);
	player->set(Helpful);
	player->rest(true);
	player->setcoins(100 * GP);
	//players.add(&player);
	//player.buyweapon(2, true);
	room.creatures.add(new creature(Kobold));
	room.creatures.add(new creature(Kobold));
	room.creatures.add(player);
	room.combat(true);
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(1100);
	return main(0, 0);
}