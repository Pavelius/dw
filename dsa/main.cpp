#include "main.h"

static void test_generate() {
	creature c1, c2;
	c1.create(Warrior, Male);
	c1.equip(Sword);
	c2.create(Magician, Female);
	c2.equip(Staff);
	while(c1.isready() && c2.isready()) {
		c1.attack(c2); sb.add("\n");
		c2.attack(c1);
		logs::next();
	}
}

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("DSA emulator");
	test_generate();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(101);
	return main(0, 0);
}