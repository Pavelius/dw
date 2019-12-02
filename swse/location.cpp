#include "main.h"

static location*		current_locaion;

static location::scene location_data[] = {
	{3, {"большой ангар", "ангара"}},
};

static bool moveto(activityi& a, creature* player, location& area, bool run, bool interactive) {
	auto index = a.conditions[0].subtype;
	if(!area.places[index])
		return false;
	if(area.party_position==index)
		return false;
	if(run) {
		area.party_position = index;
		area.examine(sb);
	}
	return true;
}

static bool search_place(activityi& a, creature* player, location& area, bool run, bool interactive) {
	return true;
}

static activityi location_actions[] = {{{variant(Place, 0)}, "Двигаться к %2.", moveto},
{{variant(Place, 1)}, "Двигаться к %2.", moveto},
{{variant(Place, 2)}, "Двигаться к %2.", moveto},
//{{Perception}, "Осмотреть %3.", search_place},
};

const char* location::place::getname() const {
	return bsmeta<sceneryi>::elements[type].getname();
}

const char* location::place::getnameto() const {
	return bsmeta<sceneryi>::elements[type].getnameto();
}

const char* location::place::getnamewh() const {
	return bsmeta<sceneryi>::elements[type].getnamewh();
}

void location::clear() {
	memset(this, 0, sizeof(*this));
}

static void select_scenery(scenerya& result) {
	for(auto& e : bsmeta<sceneryi>()) {
		if(!e)
			continue;
		result.add(&e);
	}
}

location::location() : places() {
	scenerya source;
	select_scenery(source);
	zshuffle(source.data, source.count);
	unsigned n = 2;//xrand(1, 3);
	if(source.count > n)
		source.count = n;
	clear();
	type = location_data + (rand() % (sizeof(location_data) / sizeof(location_data[0])));
	auto index = 0;
	for(auto p : source)
		places[index++].type = getbsid(p);
}

static void show_figure(stringbuilder& sb, creature* p) {
	p->actv(sb, "Здесь стоял%а %герой.", 0);
}

static void look(driver& sb, const char* format, location* p, char index) {
	sb.gender = bsmeta<sceneryi>::elements[p->places[index].type].morph;
	sb.adds(format, p->type->getname(), p->type->getnameof(), p->places[index].getname());
	if(p->party_position == index)
		p->examine(sb);
}

void location::getdescription(stringbuilder& sb) {
	int indecies[] = {0, 1, 2};
	logs::driver dr(sb);
	if(party_position == 2) {
		indecies[0] = 2;
		indecies[1] = 1;
		indecies[2] = 0;
	} else if(party_position == 1) {
		indecies[0] = 1;
		indecies[1] = 0;
		indecies[2] = 2;
	}
	if(places[2]) {
		if(indecies[0] == 1) {
			look(dr, "Прямо возле вас был%а %3.", this, indecies[0]);
			look(dr, "Сзади находил%ась %3.", this, indecies[1]);
			look(dr, "Впереди был%а %3.", this, indecies[2]);
		} else {
			look(dr, "Возле вас был%а %3.", this, indecies[0]);
			look(dr, "Посреди %2 находил%ась %3.", this, indecies[1]);
			look(dr, "в дальней части находил%ась %3.", this, indecies[2]);
		}
	} else if(places[1]) {
		look(dr, "Прямо перед вами находил%ась %3.", this, indecies[0]);
		look(dr, "Недалеко от вас находил%ась %3.", this, indecies[1]);
	} else
		look(dr, "Здесь находил%ась %3.", this, 0);
	sb = dr;
}

void location::examine(stringbuilder& sb) {
	auto& e = bsmeta<sceneryi>::elements[places[party_position].type];
	sb.adds(e.description);
}

class location_panel : panel {
	location&	area;
	void print(stringbuilder& sb) override {
		sb.addn("%+1", area.type->getname());
		sb.addn("%+1", area.places[area.party_position].getname());
	}
public:
	location_panel(location& area) : area(area) {}
};

void location::acting() {
	location_panel panel(*this);
	sb.adds("Вы зашли в %1.", type->description[0]);
	getdescription(sb);
	while(true) {
		ask(0, location_actions);
		if(!an)
			an.add(0, "Продолжить");
		auto p = (activityi*)an.choosev(true, true, false, "Что будете делать?");
		if(!p)
			break;
		p->proc(*p, 0, *this, true, true);
	}
}

void location::add(creature* p, side_s side) {
	if(creatures.is(p))
		return;
	p->set(side);
	creatures.add(p);
}

unsigned location::select(creature** result, creature** result_maximum, creature* player, testproc proc) const {
	auto pa = result;
	for(auto p : creatures) {
		if(!p->isactive())
			continue;
		if(proc && !proc(*this, player, p))
			continue;
		if(pa < result_maximum)
			*pa++ = p;
		else
			break;
	}
	return pa - result;
}

bool location::match(creature* player, testproc proc) const {
	creature* result[1];
	return select(result, result + sizeof(result) / sizeof(result[0]), player, proc) != 0;
}

creature* location::choose(creature* player, testproc proc, bool interactive) const {
	adat<creature*, 32> result;
	result.count = select(result.data, result.endof(), player, proc);
	if(!result.count)
		return 0;
	else if(result.count == 1)
		return result.data[0];
	for(unsigned i = 0; i < result.count; i++)
		an.add(i, result.data[i]->getname());
	return result.data[an.choosev(interactive, false, false, "Укажите цель")];
}

bool location::iscombat() const {
	if(!creatures.count)
		return false;
	auto side = creatures.data[0]->getside();
	for(auto p : creatures) {
		if(!p->isactive())
			continue;
		if(p->getside() != side)
			return true;
	}
	return false;
}

void location::enter() {
	for(auto p : players) {
		if(p)
			add(p);
	}
}

void location::ask(creature* player, aref<activityi> actions) {
	for(auto& a : actions) {
		auto action = a.getaction(player);
		if(action && !player->isallow(action))
			continue;
		if(!a.proc || !a.proc(a, player, *this, false, false))
			continue;
		auto v = a.conditions[0];
		switch(v.type) {
		case Place:
			an.add((int)&a, a.text,
				places[v.subtype].getname(),
				places[v.subtype].getnameto(),
				places[v.subtype].getnamewh());
			break;
		default:
			an.add((int)&a, a.text,
				places[party_position].getname(),
				places[party_position].getnameto(),
				places[party_position].getnamewh());
			break;
		}
	}
}

void location::input(creature* player, bool interactive) {
	if(!an)
		return;
	auto p = (activityi*)an.choose(interactive, true, "Что будет делать [%1]?", player->getname());
	p->proc(*p, player, *this, true, interactive);
	player->use(p->getaction(player));
}

location* location::getcurrent() {
	return current_locaion;
}

void location::activate() {
	current_locaion = this;
}