#include "main.h"

void test_grammar() {
	char temp[260];
	grammar::of(temp, zendof(temp), "длинный меч");
	grammar::of(temp, zendof(temp), "крепкая булава");
	grammar::by(temp, zendof(temp), "длинный меч");
	grammar::by(temp, zendof(temp), "крепкая булава");
}

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("Dungeon&Dragons 5ed");
	scene room;
	//auto p1 = creature::generate(true);
	creature player(Elf, Male, Cleric, Soldier, 0, false);
	player.set(Helpful);
	player.rest(true);
	player.setcoins(100 * GP);
	players.add(&player);
	//player.buyweapon(2, true);
	room.creatures.add(new creature(Kobold));
	room.creatures.add(new creature(Kobold));
	room.creatures.add(&player);
	room.combat(true);
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	test_grammar();
	//srand(1100);
	return main(0, 0);
}