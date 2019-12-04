#include "main.h"

static bool melee(const scene::action& ac, scene& sc, creature& player, bool run) {
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

static bool range(const scene::action& ac, scene& sc, creature& player, bool run) {
	return false;
}

static bool runaway(const scene::action& ac, scene& sc, creature& player, bool run) {
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

static bool balsam_saladum(const scene::action& ac, scene& sc, creature& player, bool run) {
	if(!player.iscaster())
		return false;
	creaturea source = sc.getcreatures();
	source.remove(Hostile);
	source.match(isready);
	source.match(iswounded);
	if(!source)
		return false;
	if(run) {
		auto p = source.choose("Кого [%1] хочет подлечить?", player.getname());
		auto m = p->getmaximum(LE) - p->get(LE);
		if(m > player.get(AE))
			m = player.get(AE);
		while(m > 0) {
			an.add(m, "Подлечить [%1i] очков жиненной энергии", m);
			m = m / 2;
		}
		if(!an)
			return false;
		m = an.choosev(true, false, false, "Сколько очков энерги необходимо вылечить?");
		if(!player.cast(m, 0, " - Бальзам Салабись, рана исцелись! - громко сказал%а %герой прикоснувшись руками к %оппоненту."))
			return false;
		p->heal(m);
	}
	return true;
}

static bool fulminicktus_donnerkeil(const scene::action& ac, scene& sc, creature& player, bool run) {
	if(!player.iscaster())
		return false;
	creaturea source = sc.getcreatures();
	source.match(Hostile);
	source.match(isready);
	if(!source)
		return false;
	if(run) {
		auto p = source.choose("Укажите цель заклинания", player.getname());
		auto m = dicei::roll(W3p0) + player.get(Level);
		if(m > p->get(LE))
			m = p->get(LE);
		if(!player.cast(m, 0, " - Фульминискус доменкаил!! - воскрикнул%а %герой выставив левый кулак в направлении врага."))
			return false;
		player.act(*p, "Из кулака вылетел искрящийся шар, который поразил %оппонента.");
		p->damage(m, true);
	}
	return true;
}

static bool horriphbus_schreckenspein(const scene::action& ac, scene& sc, creature& player, bool run) {
	if(!player.iscaster())
		return false;
	auto cost = 7;
	auto cost_max = player.get(AE);
	if(cost_max < cost)
		return false;
	creaturea source = sc.getcreatures();
	source.match(Hostile);
	source.match(isready);
	if(!source)
		return false;
	if(run) {
		source.choose(1, cost_max / cost, "Выбирайте максимум [%1i] врагов, на которых хотите навести ужас.", cost_max / cost);
		auto m = cost * source.getcount();
		if(!player.cast(m, 0, " - Да свернет тьма ваши конечности в вечном мраке!! - закричал%а гробовым голосом %герой подняв руки над головой."))
			return false;
		for(auto id : source) {
			auto& e = source.get(id);
			if(!e.roll(Courage)) {
				static const char* text[] = {"Издав крик %герой бросил%ась бежать прочь.",
					"Попятившись назад %герой развернул%ась и скрыл%ась из виду.",
				};
				e.act(maprnd(text));
				e.set(Fleeing);
			}
		}
	}
	return true;
}

static scene::action actions[] = {{melee, "Атаковать врага в ближнем бою"},
{range, "Стрелять по врагу"},
{runaway, "Бежать отсюда как можно скорее"},
{balsam_saladum, "Подлечить союзника заклинанием [Целебный бальзам]"},
{fulminicktus_donnerkeil, "Поджарить врага заклинанием [Светошар]"},
{horriphbus_schreckenspein, "Испугать врага мрачным заклинанием [Ужаса]"},
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