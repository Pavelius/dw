#include "main.h"

static const int maximum_fighting = 4;

static int creature_index_compare(const void* p1, const void* p2) {
	auto& e1 = bsmeta<creature>::elements[*((short unsigned*)p1)];
	auto& e2 = bsmeta<creature>::elements[*((short unsigned*)p2)];
	return e2.get(Courage) - e1.get(Courage);
}

void scene::makeorder() {
	qsort(creatures.data, creatures.count, sizeof(creatures.data[0]), creature_index_compare);
}

void scene::add(creature& e) {
	auto index = e.getid();
	if(creatures.indexof(index) != -1)
		return;
	creatures.add(index);
}

void scene::add(monster_s i, bool hostile) {
	auto p = bsmeta<creature>::add();
	p->create(i);
	if(hostile)
		p->set(Hostile);
	add(*p);
}

void scene::addplayers() {
	for(auto& e : bsmeta<creature>()) {
		if(!e)
			continue;
		if(e.isplayer())
			add(e);
	}
}

void scene::addfeature(short unsigned id) {
	auto p = features.add();
	memset(p, 0, sizeof(*p));
	p->id = id;
}

void scene::addenviroment(stringbuilder& sb) const {
	sb.add(bsmeta<environmenti>::elements[environment].name_where);
}

void scene::look() const {
	for(auto& e : features)
		sb.adds(e.getlook());
}

creature& scene::getcreature(short unsigned id) {
	return bsmeta<creature>::elements[id];
}

static bool isready(const creature& e) {
	return e.isready();
}

creature* scene::get(state_s r, bool exclude) const {
	creaturea source = getcreatures();
	source.match(isready);
	if(exclude)
		source.remove(r);
	else
		source.match(r);
	if(!source)
		return 0;
	return &getcreature(source.data[0]);
}

bool scene::ishostile() const {
	return get(Hostile, false) != 0 && get(Hostile, true) != 0;
}

int scene::getfighting(const creature& player) const {
	auto result = 0;
	for(auto id : getcreatures()) {
		auto& e = getcreature(id);
		if(!e.isready())
			continue;
		if(e.getfighting() == &player)
			result++;
	}
	return result;
}

bool scene::charge(creature& player, int count) {
	for(auto id : getcreatures()) {
		auto& e = getcreature(id);
		if(!e.isready())
			continue;
		if(!player.isenemy(e))
			continue;
		auto enemy_fighting = getfighting(e);
		if(enemy_fighting != count)
			continue;
		player.setfighting(&e);
		player.act(e, "%герой набросил%ась на %оппонента.");
		return true;
	}
	return false;
}

void scene::charge(creature& e) {
	if(e.getfighting())
		return;
	auto player_fighting = getfighting(e);
	if(player_fighting >= maximum_fighting)
		return;
	for(auto i = 0; i < maximum_fighting; i++) {
		if(charge(e, i))
			break;
	}
}

void scene::ask(creature& player, const aref<action>& actions) {
	for(auto& a : actions) {
		if(!a.act(a, *this, player, false))
			continue;
		an.add((int)&a, a.text);
	}
}

void scene::choose(creature& player) {
	auto a = (action*)an.choose(true, false, "Что будет делать [%1]?", player.getname());
	a->act(*a, *this, player, true);
}

bool scene::charsheet(const action& ac, scene& sc, creature& player, bool run) {
	if(run)
		player.sheet();
	return true;
}