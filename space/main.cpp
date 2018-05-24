#include "main.h"

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("Test");
	auto p1 = game::find("mars");
	spaceship e1("dragonfly");
	spaceship e2("mouse");
	e1.set(p1);
	e2.set(p1);
	e1.shoot(true, e2);
	logs::next();
	while(game::getday()<20)
		e1.marshto();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main(0, 0);
}