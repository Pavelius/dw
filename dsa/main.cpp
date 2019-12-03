#include "main.h"

class combat_scene : logs::panel{
	creature&	c1;
	creature&	c2;
public:
	combat_scene(creature& c1, creature& c2) : c1(c1), c2(c2) {}
	void print(stringbuilder& sb) override {
		sb.addsep('\n'); c1.status(sb);
		sb.addsep('\n'); c2.status(sb);
	}
};

static void test_generate() {
	creature c1, c2;
	c1.create(Warrior, Male);
	c1.equip(Sword);
	c1.equip(ArmourLeather);
	c2.create(Ork);
	//c2.equip(HeavyDagger);
	combat_scene cs(c1, c2);
	while(c1.isready() && c2.isready()) {
		c1.attack(c2); c2.attack(c1);
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