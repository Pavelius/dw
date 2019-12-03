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
	cmb.add(Ork, Hostile);
	cmb.add(Goblin, Hostile);
	cmb.add(Ork, Hostile);
	cmb.fight();
}

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("DSA emulator");
	create_party();
	test_combat();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(101);
	return main(0, 0);
}