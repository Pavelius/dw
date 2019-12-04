#include "main.h"

static void create(character_s type, gender_s gender, item_s i1, item_s i2) {
	auto p = bsmeta<creature>::add();
	p->create(type, gender);
	p->equip(i1);
	p->equip(i2);
}

static void create_party() {
	create(Warrior, Male, Sword, ArmourLeather);
	create(Magician, Female, Staff, ClothingRobe);
}

static void test_combat() {
	scene cmb;
	cmb.addplayers();
	cmb.add(Ork, true);
	cmb.add(Goblin, true);
	cmb.add(Ork, true);
	cmb.fight();
}

static void test_dialog() {
	auto& e = bsmeta<creature>::elements[0];
	e.sheet();
}

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("DSA emulator");
	create_party();
	//test_dialog();
	test_combat();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(101);
	return main(0, 0);
}