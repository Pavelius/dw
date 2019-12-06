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
		e.setenviroment(enviroments.getnext());
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

static bool move_forward(const action& ac, scene& sc, creature& player, bool run) {
	if(game.location >= game.location_max || game.feature != -1)
		return false;
	if(run) {
		sb.adds("Вы двинулись дальше по темному проходу.");
		game.pass((2 + rand() % 5)*Minute);
		sc.look("Вскоре вы зашли в", 1);
		game.location++;
	}
	return true;
}

static bool move_backward(const action& ac, scene& sc, creature& player, bool run) {
	if(game.location <= 0 || game.feature != -1)
		return false;
	if(run) {
		sb.adds("Вы вернулись по темному проходу назад.");
		game.pass((2 + rand() % 5)*Minute);
		sc.look("Спустя некоторое время вы вышли в", 1);
		game.location--;
	}
	return true;
}

static bool exit_dungeon(const action& ac, scene& sc, creature& player, bool run) {
	if(game.location != 0 || game.feature != -1)
		return false;
	if(run) {
		sb.adds("Вы вышли из подземелья наружу.");
		game.location = -1;
	}
	return true;
}

static bool examine_feature(const action& ac, scene& sc, creature& player, bool run) {
	if(ac.id.value >= sc.getfeaturecount())
		return false;
	if(game.feature != -1)
		return false;
	if(run) {
		auto& e = sc.getfeature(ac.id.value);
		player.act(e.getinfo().examine);
		game.feature = ac.id.value;
	}
	return true;
}

static bool move_center(const action& ac, scene& sc, creature& player, bool run) {
	if(game.feature == -1)
		return false;
	if(run)
		game.feature = -1;
	return true;
}

static bool change_character(const action& ac, scene& sc, creature& player, bool run) {
	if(run) {
		creaturea source = sc.getcreatures();
		source.remove(Hostile);
		source.exclude(player);
		auto p = source.choose("На кого хотите сменить?");
		player.say(*p, " - %оппонент, подойди сюда - тихо сказал%а %герой."); sb.addsep('\n');
		p->act("%герой подош%ла ближе.");
		game.setplayer(*p);
	}
	return true;
}

static action actions[] = {{move_forward, "Двигаться вперед по проходу"},
{exit_dungeon, "Выбраться наружу"},
{change_character, "Выбрать другого персонажа"},
{examine_feature, "Осмотреть [%1]", {Feature, 0}},
{examine_feature, "Осмотреть [%1]", {Feature, 1}},
{examine_feature, "Осмотреть [%1]", {Feature, 2}},
{examine_feature, "Осмотреть [%1]", {Feature, 3}},
{move_backward, "Вернуться по проходу назад"},
{move_center, "Отойти назад"},
};

class scene_dungeon : logs::panel {
	dungeon& dg;
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
	sb.adds("Вы зашли в темное подземелье и спустились по лестнице вниз.");
	getscene().look("Вокруг вас была", 0);
	auto lookaroud = true;
	game.location_max = depth;
	while(game.location != -1) {
		auto current_location = game.location;
		auto& sc = getscene();
		sc.addplayers();
		sc.look();
		if(current_location < depth)
			sb.adds("Проход вел отсюда дальше в темноту.");
		game.feature = -1;
		while(current_location == game.location) {
			auto& player = game.getplayer();
			sc.ask(player, actions);
			sc.choose(player, true);
		}
		lookaroud = false;
		sc.removeplayers();
	}
}