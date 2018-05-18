#include "main.h"

void test_grammar() {
	char temp[260];
	auto tend = zendof(temp);
	logs::add(grammar::get(temp, tend, "���", 1));
	logs::add(", %1", grammar::get(temp, tend, "���", 4));
	logs::add(", %1", grammar::get(temp, tend, "���", 5));
	logs::add(", %1", grammar::get(temp, tend, "������", 2));
	logs::add(", %1", grammar::get(temp, tend, "�����", 5));
	logs::add(", %1", grammar::get(temp, tend, "����", 5));
	logs::add(", %1", grammar::get(temp, tend, "����", 2));
	logs::add(", %1", grammar::get(temp, tend, "���", 2));
	logs::add(", %1", grammar::get(temp, tend, "���", 5));
	logs::add(", %1", grammar::get(temp, tend, "�����", 2));
	logs::next();
}

void test_write(character& c1) {
	io::file file("test.dat", StreamWrite);
	archive e(file, true);
	e.set(c1);
}

int	main(int argc, char *argv[]) {
	logs::setlight();
	logs::open("Test");
	//test_grammar();
	character c2(Elf, Female, Fighter, 0, true);
	character c1(Dwarf, Male, Theif, 0, true);
	test_write(c1);
	game::dungeon();
	//game::combat(true, DwarfFolk, xrand(2, 8));
	//characters.add(c1);
	//characters.add(c2);
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(101);
	return main(0, 0);
}