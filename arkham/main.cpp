#include "main.h"

void test_main() {
	deck::initialize();
	monster e(Zombie);
	player.create("joe");
	player.run(player.getquest(ArkhamAsylum));
	player.upkeep();
	player.combat(e);
	player.choose(CommonItem, 1, true);
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