#include "main.h"

int main(int argc, char* argv[]) {
	srand(clock());
	logs::setlight();
	logs::open("Appocalypse World");
	hero e;
	npc enemy("байкер", Male, Revolver);
	e.volley(enemy);
	e.sethp(e.gethpmax());
	return 0;
}

int __stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main(0, 0);
}