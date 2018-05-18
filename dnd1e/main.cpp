#include "main.h"

static location_s path_to_dungeon[] = {DeepForest, DungeonEntrance};

int	main(int argc, char *argv[]) {
	treasure tr;
	logs::setlight();
	logs::open("Test");
	tr.generate("LCOQ10S");
	auto ic1 = tr.items[0].getcost();
	auto ic2 = tr.items[1].getcost();
	auto ic3 = tr.items[2].getcost();
	//character c2(Elf, Female, Fighter, 0, true);
	character c2(true);
	character c1(Dwarf, Male, Theif, 0, true);
	scene::combat(true, Orc, 2);
	//scene::adventure(Plain);
	//characters.add(c1);
	//characters.add(c2);
	//bsdata::read("character.txt");
	bsdata::write("character.txt", "character");
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw) {
	srand((int)time(0));
	//srand(101);
	return main(0, 0);
}