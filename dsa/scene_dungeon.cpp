#include "main.h"

namespace {
class generator {
	class storage : adat<short unsigned, 64> {
		short unsigned	next;
	public:
		void add(short unsigned v) {
			if(indexof(v) != -1)
				return;
			adat::add(v);
		}
		short unsigned	getnext() {
			if(next >= count) {
				next = 1;
				return data[0];
			} else
				return data[next++];
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
}

void dungeon::generate() {
	generator e;
	memset(this, 0, sizeof(*this));
	e.addenviroments(Dungeon);
	e.addfeatures(Dungeon);
	depth = 3 + (rand() % 6);
	for(auto i = 0; i < depth; i++)
		e.generate(locations[i]);
}

static dungeon* current_dungeon;

static bool move_forward(const scene::action& ac, scene& sc, creature& player, bool run) {
	if(current_dungeon->getposition() >= current_dungeon->getsize()-1)
		return false;
	if(run) {
		sb.clear();
		sb.adds("Вы двинулись дальше по темному проходу.");
		game.pass((2 + rand() % 5)*Minute);
		sb.adds("Вскоре вы зашли");
		current_dungeon->setposition(current_dungeon->getposition() + 1);
	}
	return true;
}

static bool move_backward(const scene::action& ac, scene& sc, creature& player, bool run) {
	if(current_dungeon->getposition() <= 0)
		return false;
	if(run) {
		sb.clear();
		sb.adds("Вы вернулись по темному проходу назад.");
		game.pass((2 + rand() % 5)*Minute);
		sb.adds("Спустя некоторое время вы вышли в");
		current_dungeon->setposition(current_dungeon->getposition() - 1);
	}
	return true;
}

static bool exit_dungeon(const scene::action& ac, scene& sc, creature& player, bool run) {
	if(current_dungeon->getposition() != 0)
		return false;
	if(run) {
		sb.adds("Вы вышли из подземелья наружу.");
		current_dungeon->setposition(-1);
	}
	return true;
}

static bool move_to(const scene::action& ac, scene& sc, creature& player, bool run) {
	if(ac.id.value >= sc.getfeaturecount())
		return false;
	if(run) {
	}
	return true;
}

static scene::action actions[] = {{move_forward, "Двигаться вперед по проходу"},
{exit_dungeon, "Выбраться наружу"},
{move_to, "Осмотреть [%1]", {Feature, 0}},
{move_to, "Осмотреть [%1]", {Feature, 1}},
{move_to, "Осмотреть [%1]", {Feature, 2}},
{move_to, "Осмотреть [%1]", {Feature, 3}},
{move_backward, "Вернуться по проходу назад"},
};

class scene_dungeon : logs::panel {
	dungeon&		dg;
public:
	scene_dungeon(dungeon& dg) : dg(dg) {}
	void print(stringbuilder& sb) override {
		auto& sc = dg.getscene();
		for(auto id : sc.getcreatures()) {
			auto& e = sc.getcreature(id);
			sb.addsep('\n'); e.status(sb);
		}
	}
};

void dungeon::explore() {
	scene_dungeon pd(*this);
	auto pv = current_dungeon;
	current_dungeon = this;
	sb.adds("Вы зашли в темное подземелье и спустились по лестнице вниз.");
	sb.adds("Вокруг вас была");
	auto lookaroud = true;
	while(position != -1) {
		auto current_position = position;
		auto& sc = locations[position];
		sc.addplayers();
		sc.addenviroment(sb, lookaroud); sb.add(".");
		sc.look();
		if(position < depth)
			sb.adds("Проход вел отсюда дальше в темноту.");
		auto player = sc.getplayer();
		if(!player)
			return;
		while(current_position == position) {
			sc.ask(*player, actions);
			if(!an)
				break;
			sc.choose(*player);
		}
		lookaroud = false;
		sc.removeplayers();
	}
	current_dungeon = pv;
}