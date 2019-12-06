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
	void addenviroments(tag_s i) {
		for(auto& e : bsmeta<environmenti>()) {
			if(!e.tags.is(i))
				continue;
			auto index = &e - bsmeta<environmenti>::elements;
			enviroments.add(index);
		}
		enviroments.shuffle();
	}
	void addfeatures(tag_s i) {
		for(auto& e : bsmeta<featurei>()) {
			if(!e.tags.is(i))
				continue;
			auto index = &e - bsmeta<featurei>::elements;
			features.add(index);
		}
		features.shuffle();
	}
	void generate(scene& e) {
		e.addenviroment(enviroments.getnext());
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

static bool move_forward(const scene::action& ac, scene& sc, creature& player, bool run) {
	return true;
}

static bool exit_dungeon(const scene::action& ac, scene& sc, creature& player, bool run) {
	return true;
}

static scene::action actions[] = {{move_forward, "Двигаться вперед по проходу"},
{exit_dungeon, "Выбраться наружу"},
{scene::charsheet, "Посмотреть листок персонажа"},
};

void scene::explore() {
	sb.add("Вы зашли в темное подземелье и спустились по лестнице вниз.");
	sb.add("Вокруг вас была "); addenviroment(sb); sb.add(".");
	look();
	auto player = getplayer();
	if(!player)
		return;
	while(true) {
		ask(*player, actions);
		choose(*player);
	}
}