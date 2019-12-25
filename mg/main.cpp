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

static void create_party(bool interactive) {
	auto p1 = create(false, Guardmouse, Axe);
	auto p2 = create(false, Guardmouse, HookAndLine);
	auto p3 = create(false, PatrolLeader, Shield);
}

int	main(int argc, char *argv[]) {
	auto item_size = sizeof(item);
	auto hero_size = sizeof(hero);
	srand((unsigned)time(0));
	create_party(false);
	logs::setlight();
	logs::open("Test");
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