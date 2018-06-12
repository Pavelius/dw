#include "main.h"

int	main(int argc, char *argv[]) {
	auto item_size = sizeof(item);
	auto hero_size = sizeof(hero);
	srand((unsigned)time(0));
	logs::setlight();
	logs::open("Test");
	auto p = new hero(Guardmouse, Axe);
	p = new hero(Guardmouse, HookAndLine);
	p = new hero(PatrolLeader, Shield);
	logc.location = NoLocation;
	logc.landscape = Forest;
	logc.weather = hero::getweather();
	hero::setyearweather();
	//hero::weatherwatch();
	hero::quest("border_scent");
	//hero::fight(Squirrel);
	//hero::playersturn();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main(0, 0);
}