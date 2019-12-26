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

static hero* create_party(bool interactive) {
	auto p1 = create(false, Guardmouse, Axe);
	auto p2 = create(false, Guardmouse, HookAndLine);
	auto p3 = create(false, PatrolLeader, Shield);
	return p1;
}

static void test_rolls() {
	hero animal;
	animal.create(Owl);
	auto p1 = bsmeta<hero>::elements;
	auto p2 = bsmeta<hero>::elements;
	heroa helps;
	p1->roll(StandartRoll, party, helps, true,
		Fighter, 2, 1, 1, &animal,
		Nature, 0, 0);
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
	//hero::quest("border_scent");
	//hero::fight(Squirrel);
	//hero::playersturn();
	//party.set(Forest);
	party.play();
	//test_rolls();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main(0, 0);
}