#include "main.h"

static location::scene location_data[] = {
	{3, {"������� �����", "������"}},
};
static struct scenery {
	gender_s		morph;
	const char*		description[3];
	const char*		getname() const { return description[0]; }
	const char*		getnameto() const { return description[1]; }
} scenery_data[] = {{Female, {"��������, ������� ����", "��������", "��������"}},
{NoGender, {"��������� ����������� ������ ��������", "�����������", "����������"}},
{NoGender, {"��������� ������, �� ������� ������ ������������ �������", "������", "�����"}},
{Male, {"����������� ������ �����", "�������� ������", "������� ������"}},
{NoGender, {"���������� ������� ���������", "�����������", "����������"}},
{Male, {"��� � ��������", "����", "���"}},
};

static bool moveto(activityi& a, creature* player, location& area, bool run, bool interactive) {
	auto index = a.conditions[0].subtype;
	if(!area.places[index])
		return false;
	if(area.party_position==index)
		return false;
	if(run)
		area.party_position = index;
	return true;
}

static activityi location_actions[] = {{{variant(Place, 0)}, "��������� � %1", moveto},
{{variant(Place, 1)}, "��������� � %1", moveto},
{{variant(Place, 2)}, "��������� � %1", moveto},
{{variant(Place, 3)}, "��������� � %1", moveto},
};

const char* location::place::getname() const {
	return type->getname();
}

const char* location::place::getnameto() const {
	return type->getnameto();
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

location::location() : places() {
	adat<scenery*, 32> source;
	source.count = select_scenery(source.data, source.data + sizeof(source.data) / sizeof(source.data[0]));
	zshuffle(source.data, source.count);
	clear();
	type = location_data + (rand() % (sizeof(location_data) / sizeof(location_data[0])));
	auto index = 0;
	for(int i = xrand(2, 4); i > 0; i--)
		places[index++] = source[i - 1];
}

static void show_figure(stringbuilder& sb, creature* p) {
	p->actv(sb, "����� �����%� %�����.", 0);
}

static void look(driver& sb, const char* format, location* p, char index) {
	sb.gender = p->places[index].type->morph;
	sb.adds(format, p->type->getname(), p->type->getnameof(), p->places[index].getname());
}

void location::getdescription(stringbuilder& sb) {
	logs::driver dr(sb);
	dr.adds("�� ����� � %1.", type->description[0]);
	look(dr, "����� ����� ��� ���%� %3.", this, 0);
	look(dr, "������� %2 �������%��� %3.", this, 1);
	look(dr, "� ������� ����� �������%��� %3.", this, 2);
	sb = dr;
}

void location::acting() {
	bool interactive = true;
	auto position = 0;
	while(true) {
		getdescription(sb);
		ask(0, location_actions);
		auto p = (activityi*)an.choosev(interactive, true, false, "��� ������ ������?");
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
	return result.data[an.choosev(interactive, false, false, "������� ����")];
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
			an.add((int)&a, a.text, places[v.subtype].getname(), places[v.subtype].getnameto());
			break;
		default:
			an.add((int)&a, a.text);
			break;
		}
	}
}

void location::input(creature* player, bool interactive) {
	if(!an)
		return;
	auto p = (activityi*)an.choose(interactive, true, "��� ����� ������ [%1]?", player->getname());
	p->proc(*p, player, *this, true, interactive);
	player->use(p->getaction(player));
}