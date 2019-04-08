#include "main.h"

void test_generate(hero& player) {
	hero::createparty(true);
	actor enemy("������", Male, 1, 2);
	if(player.combat(enemy))
		enemy.act("%����� �����%� �� ����� ��� ��������.");
	else if(player.isalive()) {
		player.act("%����� ��������%� ���%� ���������, ��������� �� �������� ����� �������.");
		logs::next();
	}
}

int main(int argc, char* argv[]) {
	srand(clock());
	logs::setlight();
	logs::open("Appocalypse World");
	test_generate(players[0]);
	return 0;
}

int __stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	return main(0, 0);
}
