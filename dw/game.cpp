#include "main.h"

int game::whatdo(bool clear_text) {
	if(!an)
		return 0;
	return an.choose(true, clear_text, "Что будете делать?");
}

hero* game::whodo(const char* format, ...) {
	for(auto i = 0; i < sizeof(players) / sizeof(players[0]); i++) {
		if(!players[i] || !players[i].isalive())
			continue;
		an.add(i, players[i].getname());
	}
	char temp[512]; stringbuilder sbn(temp); sbn.addv(format, xva_start(format));
	return players + an.choosev(true, false, true, temp);
}

hero* game::whodo(stat_s stat, hero** exclude, const char* format, ...) {
	for(auto i = 0; i < sizeof(players) / sizeof(players[0]); i++) {
		if(!players[i] || !players[i].isalive())
			continue;
		if(exclude && zchr(exclude, &players[i]))
			continue;
		auto value = players[i].get(stat);
		if(value >= 0)
			an.add(i, "%1 (%2[+ +%3i]).", players[i].getname(), getstr(stat), value);
		else
			an.add(i, "%1 (%2[- %3i]).", players[i].getname(), getstr(stat), value);
	}
	char temp[512]; stringbuilder sbn(temp); sbn.addv(format, xva_start(format));
	return players + an.choosev(true, false, false, format);
}

hero* game::getplayer() {
	for(auto& e : players) {
		if(!e || !e.isalive())
			continue;
		return &e;
	}
	return 0;
}

hero* game::choose(move_s id) {
	for(auto& e : players) {
		if(!e || !e.isalive())
			continue;
		if(e.is(id)) {
			auto stat = e.getstat(id);
			auto value = e.get(stat);
			an.add((int)&e, "%1 ([%2%+3i]).", e.getname(), getstr(stat), value);
		}
	}
	char temp[512]; stringbuilder sbn(temp); sbn.add("Кто сделает ход [%1]", getstr(id));
	return (hero*)an.choosev(true, false, false, temp);
}

bool game::isgameover() {
	for(auto& e : players) {
		if(e.isalive())
			return false;
	}
	return true;
}

bool game::useparty(tag_s id, bool run, bool interactive) {
	for(auto& e : players) {
		if(!e)
			continue;
		if(!e.isallow(id))
			continue;
		if(run) {
			e.use(id, interactive);
			return true;
		}
	}
	return false;
}

bool game::useparty(item_s id, bool run, bool interactive) {
	for(auto& e : players) {
		if(!e || !e.isalive())
			continue;
		if(!e.isallow(id))
			continue;
		if(run) {
			e.use(id, interactive);
			return true;
		}
	}
	return false;
}

bool game::isallow(tid id) {
	switch(id.type) {
	case DungeonMoves:
		return true;
	default:
		for(auto& e : players) {
			if(!e || !e.isalive())
				continue;
			if(e.isallow(id))
				return true;
		}
		break;
	}
	return false;
}

unsigned game::select(hero** result, unsigned maximum, tid id, bool alive) {
	auto ps = result;
	auto pe = result + maximum;
	for(auto& e : players) {
		if(!e)
			continue;
		if(alive && !e.isalive())
			continue;
		if(!e.isallow(id))
			continue;
		if(ps < pe)
			*ps++ = &e;
	}
	return ps - result;
}

void game::pickup(item value) {
	auto weight = value.getweight();
	for(auto i = 0; i < sizeof(players) / sizeof(players[0]); i++) {
		if(!players[i] || !players[i].isalive())
			continue;
		auto cur_weight = players[i].getencumbrance();
		auto max_weight = players[i].getload();
		if(cur_weight + weight <= max_weight)
			an.add(i, "%1 (Груз [%2i]/%3i)", players[i].getname(), cur_weight, max_weight);
	}
	an.sort();
	char temp[260]; stringbuilder sbn(temp); value.getname(sbn, false);
	auto p = players + an.choose(true, false, "Кто заберет [%1] весом [%2i].", sb, weight);
	p->set(value);
}

void game::sheets() {
	auto player = whodo("Чей листок пероснажа просмотреть?");
	if(!player)
		return;
	player->sheet();
}