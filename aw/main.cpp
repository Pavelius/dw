#include "main.h"

void test_grammar() {
	char temp[260];
	logs::add("%1\n", grammar::of(temp, zendof(temp), "������"));
	logs::add("%1\n", grammar::of(temp, zendof(temp), "�������"));
	logs::next();
}

void test_generate(hero& player) {
	hero::createparty(false);
	actor enemy("������", Male, 1, 2);
	if(player.combat(enemy))
		logs::add("������ ���� � �� ���������.");
	else
		player.act("%����� ��������%� ���%� ���������.");
	logs::next();
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
