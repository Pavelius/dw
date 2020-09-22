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
	if(it.is(Slow))
		return false;
	it.set(Slow);
	if(!it.is(Slow))
		return false;
	if(it.getpierce() != 0)
		return false;
	it.setpierce(1);
	if(it.getpierce() != 1)
		return false;
	if(it.getdamage() != 0)
		return false;
	it.setdamage(4);
	if(it.getdamage() != 3)
		return false;
	if(it.getweight() != 0)
		return false;
	it.setweight(4);
	if(it.getweight() != 4)
		return false;
	it.setpierce(it.getpierce()+1);
	if(it.getpierce() != 2)
		return false;
	return true;
}

static bool test_sizes() {
	auto s1 = sizeof(thing);
	return true;
}

static void test_combat() {
	thing enemy(Kobold, 3, 10);
	hero::fight(enemy);
}

static void test_generate_party(bool interactive, bool predefined) {
	bsmeta<hero>::source.clear();
	if(predefined) {
		bsmeta<hero>::add()->create(interactive, Fighter, Male);
		bsmeta<hero>::add()->create(interactive, Cleric, Female);
	} else {
		bsmeta<hero>::add()->create(interactive);
		bsmeta<hero>::add()->create(interactive);
		bsmeta<hero>::add()->create(interactive);
	}
}

int	main(int argc, char *argv[]) {
	if(!test_sizes())
		return -1;
	if(!test_item())
		return -1;
	logs::setlight();
	logs::open("Test");
	steading::createworld();
	//bsmeta<hero>::add()->create(false, Cleric, Male);
	//bsmeta<hero>::add()->create(false, Wizard, Male);
	//bsmeta<hero>::add()->create(false, Theif, Female);
	//bsmeta<hero>::add()->create(false, Fighter, Male);
	test_generate_party(false, false);
	//steadings[0].adventure();
	//test_hoard();
	//game::dungeon();
	test_combat();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(101);
	return main(0, 0);
}