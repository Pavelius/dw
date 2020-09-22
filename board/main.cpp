#include "main.h"

static void test_battle() {
	auto win = 0;
	for(auto i = 0; i < 10000; i++) {
		forcei enemy = bsdata<forcei>::elements[Raiders];
		forcei player = {"Павелиус", 1, 1};
		combat cb;
		cb.roll();
		cb.apply(player, enemy);
		if(player.attack >= enemy.defence)
			win++;
	}
	sb.add("Победа %1i%%.", win/100);
	next();
}

int main() {
	setlight();
	logs::open("Board emulator");
	test_battle();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(101);
	return main();
}