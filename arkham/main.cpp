#include "main.h"

void test_main() {
	game.create(Cthulhu);
	game.players[0].create("joe");
	auto pm = monster::getfromcup();
	if(pm)
		game.players[0].combat(*pm);
	//player.add(BookOfDzyan);
	game.players[0].set(CuriositieShoppe);
	//game.players[0].run(player.getquest(Woods, 0));
	game.players[0].play();
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