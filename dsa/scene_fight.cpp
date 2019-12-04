#include "main.h"

static bool melee(scene& sc, creature& player, bool run) {
	if(!player.is(Weapon))
		return false;
	if(run) {
		sc.charge(player);
		auto fighting = player.getfighting();
		if(fighting)
			player.attack(*fighting);
	}
	return true;
}

static bool range(scene& sc, creature& player, bool run) {
	return false;
}

static bool runaway(scene& sc, creature& player, bool run) {
	if(player.is(Fleeing))
		return false;
	if(run) {
		player.say(" - Во имя Борона, я не хочу умирать!! - закричал%а %герой и скрыл%ась из виду.");
		player.set(Fleeing);
	}
	return true;
}

static bool isready(const creature& e) {
	return e.isready();
}

static bool iswounded(const creature& e) {
	return e.get(LE) < e.getmaximum(LE);
}

static bool balsam_saladum(scene& sc, creature& player, bool run) {
	creaturea source = sc.getcreatures();
	source.match(Friendly);
	source.match(isready);
	source.match(iswounded);
	if(!source)
		return false;
	if(run) {
		auto p = source.choose("Кого [%1] хочет подлечить?", player.getname());
	}
	return true;
}

static scene::action actions[] = {{melee, "Атаковать врага в ближнем бою"},
{range, "Стрелять по врагу"},
{runaway, "Бежать отсюда как можно скорее"},
};

class scene_combat : logs::panel {
	scene&		sc;
public:
	scene_combat(scene& sc) : sc(sc) {}
	void print(stringbuilder& sb) override {
		for(auto id : sc.getcreatures()) {
			auto& e = sc.getcreature(id);
			sb.addsep('\n'); e.status(sb);
		}
	}
};

void scene::fight() {
	scene_combat sc(*this);
	makeorder();
	while(ishostile()) {
		for(auto id : creatures) {
			auto& e = getcreature(id);
			if(!e.isready())
				continue;
			sb.addsep('\n');
			e.testfighting();
			if(e.isplayer()) {
				ask(e, actions);
				choose(e);
			} else {
				charge(e);
				auto fighting = e.getfighting();
				if(fighting)
					e.attack(*fighting);
			}
		}
		an.add(1, "Завершить раунд боя");
		an.choose();
	}
}