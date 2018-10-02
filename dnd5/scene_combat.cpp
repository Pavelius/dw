#include "main.h"

static struct combat_action {
	const char*			name;
	variant				id;
} combat_action_data[] = {{"Атаковать врага"},
{"Создать заклинание"},
{"Уворачиваться от ударов"},
};

static int compare_initiative(const void* p1, const void* p2) {
	return (*((creature**)p2))->getinitiative() - (*((creature**)p1))->getinitiative();
}

void scene::rollinititative() {
	for(auto p : creatures)
		p->setinitiative();
	qsort(creatures.data, creatures.count, sizeof(creatures.data[0]), compare_initiative);
}

void scene::combat(bool interactive) {
	rollinititative();
	while(isenemy()) {
		for(auto p : creatures) {
			auto pe = p->getenemy(creatures);
			for(unsigned i = 0; i < sizeof(combat_action_data) / sizeof(combat_action_data[0]); i++)
				logs::add(i, combat_action_data[i].name);
			auto index = logs::input(interactive, false, "Что будет делать %1?", p->getname());
			auto& ca = combat_action_data[index];
			switch(ca.id.type) {
			case Feat:
				break;
			}
		}
	}
}

bool scene::isenemy() const {
	reaction_s reaction = Undifferent;
	for(auto p : creatures) {
		auto r = p->getreaction();
		if(r == Hostile || r == Helpful) {
			if(reaction == Undifferent)
				reaction = r;
			else if(reaction != r)
				return true;
		}
	}
	return false;
}