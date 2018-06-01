#include "main.h"

void test_main() {
	deck::initialize();
	monster e(Byakhee);
	player.create("joe");
	player.set(ArkhamAsylum);
	player.run(player.getquest(Library, 0));
	player.play();
}

int main() {
	//srand(clock());
	srand(252);
	logs::setlight();
	logs::open("Arkham horror");
	test_main();
	return 0;
}

int __stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main();
}