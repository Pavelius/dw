#include "main.h"

int main(int argc, char* argv[]) {
	srand(clock());
	logs::setlight();
	logs::open("Appocalypse World");
	hero e; e.sethp(e.gethpmax());
	npc enemy("рейдер", Male, 1, 5, Rifle);
	e.combat(enemy);
	return 0;
}

int __stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main(0, 0);
}