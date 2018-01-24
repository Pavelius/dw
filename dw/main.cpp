#include "main.h"

void test_hoard() {
	lootinfo te;
	te.clear();
	te.generate(xrand(1, 10));
	te.generate(xrand(1, 10));
	te.pickup();
}

int	main(int argc, char *argv[]) {
	logs::open("Test");
	steading::createworld();
	players[0].create(false, Cleric, Male);
	players[1].create(false, Wizard, Male);
	players[2].create(false, Theif, Female);
	players[3].create(false, Fighter, Male);
	steadings[0].adventure();
	monster enemy(Kobold);
	enemy.distance = Far;
	//test_hoard();
	//game::combat(enemy);
	//game::dungeon();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	//srand((int)time(0));
	srand(101);
	return main(0, 0);
}