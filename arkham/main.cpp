#include "main.h"

void test_main() {
	deck::initialize();
	monster e(Byakhee);
	player.create("joe");
	player.set(ArkhamAsylum);
	//player.choose(Spell, 1, true);
	//player.upkeep();
	//player.run(player.getquest(ArkhamAsylum));
	player.play();
}

int main() {
	srand(clock());
	//srand(252);
	logs::setlight();
	logs::open("Arkham horror");
	test_main();
	return 0;
}

int __stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main();
}