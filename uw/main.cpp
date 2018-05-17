#include "main.h"

void test_combat(hero& player) {
	scene sc(Hangar, player);
	sc.enemy.set(Soldiers);
	player.openfire(sc.enemy);
	logs::next();
}

int test_main() {
	hero player;
	player.clear();
	player.kit.set(BroadcastKit);
	player.crew.set(Rabble);
	player.acquisition(2);
	return 0;
}

int main(int argc, char* argv[]) {
	int hs = sizeof(hero);
	srand(clock());
	logs::open("Не помеченный на карте мир");
	//quest::start("test/b11", "entrance");
	return test_main();
}

int __stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main(0, 0);
}