#include "main.h"

int	main(int argc, char *argv[]) {
	auto item_size = sizeof(item);
	auto hero_size = sizeof(hero);
	srand((unsigned)time(0));
	logs::setlight();
	logs::open("Test");
	auto p = hero::create(Guardmouse, false, true); p->weapon = Axe;
	p = hero::create(Guardmouse, false); p->weapon = HookAndLine;
	p = hero::create(PatrolLeader, false); p->weapon = Shield;
	logc.location = NoLocation;
	logc.landscape = Forest;
	logc.weather = hero::getweather();
	hero::setyearweather();
	//hero::weatherwatch();
	hero::fight(Squirrel);
	//hero::playersturn();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main(0, 0);
}