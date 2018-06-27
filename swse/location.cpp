#include "main.h"

static location::scene location_data[] = {
	{3, {"большой ангар", "ангара"}},
};
static struct scenery {
	morph_s			morph;
	const char*		description[3];
} scenery_data[] = {{Feminine, {"лестница, ведуща€ вниз", "лестнице", "лестницу"}},
{Neuter, {"множество контейнеров разных размеров", "контейнерам", "контейнеры"}},
{Neuter, {"несколько столов, на которых сто€ла компьютерна€ техника", "столам", "столы"}},
{Masculine, {"разобранный боевой робот", "остаткам робота", "остатки робота"}},
{Masculine, {"генераторы силовой установки", "генераторам", "генераторы"}},
{Masculine, {"чан с кислотой", "чану", "чан"}},
};

const char* location::place::getname() const {
	return type->description[0];
}

const char* location::place::getnameto() const {
	return type->description[1];
}

void location::clear() {
	memset(this, 0, sizeof(*this));
}

static unsigned select_scenery(scenery** result, scenery** result_maximum) {
	auto p = result;
	for(auto& e : scenery_data) {
		if(p < result_maximum)
			*p++ = &e;
	}
	return p - result;
}

location::location() {
	adat<scenery*, 32> source;
	source.count = select_scenery(source.data, source.data + sizeof(source.data) / sizeof(source.data[0]));
	zshuffle(source.data, source.count);
	clear();
	type = location_data + (rand() % (sizeof(location_data) / sizeof(location_data[0])));
	for(int i = xrand(2, 4); i > 0; i--)
		places.add(source[i - 1]);
}

static void show_figure(char* result, const char* result_maximum, creature* p) {
	p->actv(result, result_maximum, "«десь сто€л%а %герой.", 0);
}

static char* look(char* result, const char* result_maximum, const char* format, creature** source, unsigned source_count, location* p, char index) {
	//creature* figures[32];
	//auto figures_count = select(figures, sizeof(figures) / sizeof(figures[0]), source, source_count, p, index);
	szprints(result, result_maximum, format, p->type->description[0], p->places[index].getname());
	return zend(result);
}

void location::getdescription(char* result, const char* result_maximum) {
	szprints(zend(result), result_maximum, "¬ы зашли в %1. ", type->description[0]);
	result = look(zend(result), result_maximum, "ѕр€мо возле вас было %2. ", creatures.data, creatures.count, this, 0);
	result = look(zend(result), result_maximum, "ѕосреди %1 находилась %2. ", creatures.data, creatures.count, this, 1);
	result = look(zend(result), result_maximum, "в дальней части находилось %2. ", creatures.data, creatures.count, this, 2);
}

void location::acting() {
	bool interactive = true;
	auto position = 0;
	while(true) {
		getdescription(logs::getptr(), logs::getptrend());
		logs::add(1, "¬сем двигатьс€ к %1.", places[0].getname());
		auto id = logs::input(interactive, true, "„то будете делать?");
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
		logs::add(i, result.data[i]->getname());
	return result.data[logs::input(interactive, false, "”кажите цель")];
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

void location::ask(creature* player, aref<action> actions) {
	for(auto& a : actions) {
		auto action = a.getaction(player);
		if(!player->isallow(action))
			continue;
		if(!a.proc || !a.proc(a, player, *this, false, false))
			continue;
		logs::add((int)&a, a.text);
	}
}

void location::input(creature* player, bool interactive) {
	if(!logs::getcount())
		return;
	auto p = (action*)logs::input(interactive, true, "\n„то будет делать [%1]?", player->getname());
	p->proc(*p, player, *this, true, interactive);
	player->use(p->getaction(player));
}