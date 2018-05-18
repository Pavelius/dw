#include "logs/archive.h"
#include "main.h"

template<> void archive::set<character>(character& e) {
	set(e.gender);
	set(e.alignment);
	set(e.race);
	set(e.monster);
	set(e.abilities);
	set(e.hp); set(e.hp_maximum);
	set(e.initiative);
	set(e.feats);
	set(e.side);
	set(e.strenght_percent);
	set(e.name);
	set(e.position);
	set(e.classes);
	set(e.levels);
	set(e.wears);
	set(e.coopers);
	set(e.experience);
	set(e.count);
}

void game::write(const char* name) {
	character test[10]; class_s class_type[] = {Fighter, NoClass, NoClass};
	test[0].create(false, Elf, Male, class_type, 0, true);
	archive::dataset datasets[] = {test};
	io::file file(name, StreamWrite);
	archive e(file, true, datasets);
	e.set(test[0]);
}