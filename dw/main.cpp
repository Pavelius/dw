#include "main.h"

static void test_hoard() {
	looti te;
	te.clear();
	te.generate(xrand(1, 10));
	te.generate(xrand(1, 10));
	te.pickup();
}

static bool test_item() {
	tagable it;
	auto d1 = it.getdamage();
	it.set(Sharp);
	it.setpierce(1);
	it.setdamage(d1 + 1);
	it.setweight(4);
	auto p3 = it.getpierce();
	if(p3 != 3)
		return false;
	auto d2 = it.getdamage();
	if(d2 != 1)
		return false;
	return true;
}

int	main(int argc, char *argv[]) {
	if(!test_item())
		return -1;
	logs::setlight();
	logs::open("Test");
	steading::createworld();
	bsmeta<hero>::add()->create(false);
	bsmeta<hero>::add()->create(false, Cleric, Male);
	bsmeta<hero>::add()->create(false, Wizard, Male);
	//bsmeta<hero>::add()->create(false, Theif, Female);
	//bsmeta<hero>::add()->create(false, Fighter, Male);
	//steadings[0].adventure();
	test_hoard();
	game::dungeon();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(101);
	return main(0, 0);
}