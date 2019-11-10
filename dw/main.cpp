#include "main.h"

void test_hoard() {
	looti te;
	te.clear();
	te.generate(xrand(1, 10));
	te.generate(xrand(1, 10));
	te.pickup();
}

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("Test");
	steading::createworld();
	bsmeta<hero>::add()->create(true);
	//bsmeta<hero>::add()->create(false, Cleric, Male);
	bsmeta<hero>::add()->create(false, Wizard, Male);
	bsmeta<hero>::add()->create(false, Theif, Female);
	bsmeta<hero>::add()->create(false, Fighter, Male);
	//steadings[0].adventure();
	//test_hoard();
	game::dungeon();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(101);
	return main(0, 0);
}