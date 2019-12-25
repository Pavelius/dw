#include "main.h"

static hero* create(bool interactive, rang_s r, item_s weapon = NoItem, item_s offhand = NoItem, item_s armor = NoItem) {
	auto p = bsmeta<hero>::add();
	p->create(r, interactive);
	p->set(Hands, weapon);
	p->set(Offhand, offhand);
	p->set(Body, armor);
	p->addplayer();
	return p;
}

int	main(int argc, char *argv[]) {
	auto item_size = sizeof(item);
	auto hero_size = sizeof(hero);
	srand((unsigned)time(0));
	logs::setlight();
	logs::open("Test");
	auto p = create(false, Guardmouse, Axe);
	p = create(false, Guardmouse, HookAndLine);
	p = create(false, PatrolLeader, Shield);
	hero::setyearweather();
	hero::weatherwatch();
	hero::quest("border_scent");
	//hero::fight(Squirrel);
	//hero::playersturn();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main(0, 0);
}