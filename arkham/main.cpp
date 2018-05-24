#include "main.h"

void test_main() {
	deck::initialize();
	monster e(Zombie);
	player.create("joe");
	//player.choose(Spell, 1, true);
	//player.upkeep();
	player.run(player.getquest(ArkhamAsylum, 1));
	player.combat(e);
}

int main() {
	srand(clock());
	//srand(120);
	logs::setlight();
	logs::open("Arkham horror");
	test_main();
	return 0;
}

int __stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main();
}