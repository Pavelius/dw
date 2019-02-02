#include "main.h"

const unsigned combat_max = 10;

struct combat_scene {
	
	char			order[combat_max];
	character*		combatants[combat_max];

	combat_scene() {
		memset(combatants, 0, sizeof(combatants));
		for(auto i = 0; i < combat_max; i++)
			order[i] = i;
		zshuffle(order, combat_max);
	}

	int getindex() {
		for(auto i = 0; i < combat_max; i++) {
			if(combatants[order[i]])
				continue;
			return order[i];
		}
		return -1;
	}

	void add(character* p) {
		auto i = getindex();
		if(i == -1)
			return;
		combatants[i] = p;
	}

	void run() {

	}

};

void character::combat(character& e1, character& e2) {
	combat_scene scene;
	scene.add(&e1);
	scene.add(&e2);
	scene.run();
}