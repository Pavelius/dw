#include "main.h"

void test_main() {
	player.create("joe");
	auto pm = monster::getfromcup();
	if(pm)
		player.combat(*pm);
	//player.add(BookOfDzyan);
	player.set(CuriositieShoppe);
	player.run(player.getquest(Woods, 0));
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