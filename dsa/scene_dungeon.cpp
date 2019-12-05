#include "main.h"

class dungeon_generator {
	struct storage : adat<short unsigned, 64> {
		unsigned		current;
	};
	storage				enviroments;
	storage				rooms;
public:
	void addenviroments(environment_s i) {
		for(auto& e : bsmeta<environmenti>()) {
			if(!e.tags.is(i))
				continue;
			auto index = &e - bsmeta<environmenti>::elements;
			if(enviroments.indexof(index) != -1)
				continue;
			enviroments.add(index);
		}
		zshuffle(enviroments.data, enviroments.count);
	}
	void addrooms(environment_s i) {
		for(auto& e : bsmeta<roomi>()) {
			if(!e.tags.is(i))
				continue;
			auto index = &e - bsmeta<roomi>::elements;
			if(rooms.indexof(index) != -1)
				continue;
			rooms.add(index);
		}
		zshuffle(rooms.data, rooms.count);
	}
	void build() {

	}
	dungeon_generator() : enviroments(), rooms() {
	}
};

void scene::generate() {
	dungeon_generator e;
	e.addenviroments(Dungeon);
	e.build();
}