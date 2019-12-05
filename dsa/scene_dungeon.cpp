#include "main.h"

class dungeon_generator {
	class storage : adat<short unsigned, 64> {
		short unsigned	next;
	public:
		void add(short unsigned v) {
			if(indexof(v) != -1)
				return;
			adat::add(v);
		}
		short unsigned	getnext() {
			auto n = data[next];
			if(next >= count)
				next = 0;
			else
				next++;
			return n;
		}
		void shuffle() {
			zshuffle(data, count);
		}
		storage() :next(0) {}
	};
	storage				enviroments;
	storage				features;
public:
	void addenviroments(environment_s i) {
		for(auto& e : bsmeta<environmenti>()) {
			if(!e.tags.is(i))
				continue;
			auto index = &e - bsmeta<environmenti>::elements;
			enviroments.add(index);
		}
		enviroments.shuffle();
	}
	void addfeatures(environment_s i) {
		for(auto& e : bsmeta<featurei>()) {
			if(!e.tags.is(i))
				continue;
			auto index = &e - bsmeta<featurei>::elements;
			features.add(index);
		}
		features.shuffle();
	}
	void generate(scene& e) {
		e.setenviroment(enviroments.getnext());
		auto c = 2 + (rand() % 3);
		for(auto i = 0; i < c; i++)
			e.addfeature(features.getnext());
	}
};

void scene::generate() {
	dungeon_generator e;
	e.addenviroments(Dungeon);
	e.addfeatures(Dungeon);
	e.generate(*this);
}

void scene::adventure() {
	while(true) {

	}
}