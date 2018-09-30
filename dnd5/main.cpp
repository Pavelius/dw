#include "main.h"

void test_grammar() {
	char temp[260];
	grammar::of(temp, zendof(temp), "длинный меч");
	grammar::of(temp, zendof(temp), "крепкая булава");
	grammar::by(temp, zendof(temp), "длинный меч");
	grammar::by(temp, zendof(temp), "крепкая булава");
}

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("Dungeon&Dragons 5ed");
	//auto player_test = creature::generate(true);
	creature player(Elf, Male, Fighter, Soldier, 0, false);
	creature enemy(Kobold);
	player.choose_equipment(Fighter, true);
	player.attack(MeleeWeapon, enemy);
	logs::next();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	test_grammar();
	//srand(101);
	return main(0, 0);
}