#include "main.h"

void test_grammar() {
	char temp[260];
	logs::add("%1\n", grammar::of(temp, zendof(temp), "байкер"));
	logs::add("%1\n", grammar::of(temp, zendof(temp), "человек"));
	logs::next();
}

void test_generate(hero& player) {
	hero::createparty(true);
	actor enemy("байкер", Male, 1, 2);
	if(player.combat(enemy))
		enemy.act("%герой лежал%а на земле без движения.");
	else if(player.isalive()) {
		player.act("%герой вынужден%а был%а отступить, скрывшись за стоящими рядом ящиками.");
		logs::next();
	}
}

int main(int argc, char* argv[]) {
	srand(clock());
	logs::setlight();
	logs::open("Appocalypse World");
	//test_grammar();
	test_generate(players[0]);
	return 0;
}

int __stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main(0, 0);
}
