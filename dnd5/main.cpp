#include "main.h"

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("Dungeon&Dragons 5ed");
	scene room;
	auto player = bsmeta<creature>::add();
	player->create(Elf, Male, Fighter, Criminal, 0, false);
	player->set(Helpful);
	player->rest(true);
	player->setcoins(100 * GP);
	auto m1 = bsmeta<creature>::add();
	m1->create(Kobold);
	m1->setposition(10 * Feet5);
	auto m2 = bsmeta<creature>::add();
	m2->create(Kobold);
	m2->setposition(9 * Feet5);
	room.add(*m1);
	room.add(*m2);
	room.add(*player);
	room.combat(true);
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(1100);
	return main(0, 0);
}