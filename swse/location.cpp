#include "main.h"

static location::scene location_data[] = {
	{3, {"������� �����", "������"}},
};
static struct scenery {
	morph_s					morph;
	const char*				description[3];
} scenery_data[] = {{Feminine, {"��������, ������� ����", "��������", "��������"}},
{Neuter, {"��������� ����������� ������ ��������", "�����������", "����������"}},
{Neuter, {"��������� ������, �� ������� ������ ������������ �������", "������", "�����"}},
{Masculine, {"����������� ������ �����", "�������� ������", "������� ������"}},
{Masculine, {"���������� ������� ���������", "�����������", "����������"}},
{Masculine, {"��� � ��������", "����", "���"}},
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

static unsigned select(scenery** result, unsigned count) {
	auto p = result;
	auto pe = result + count;
	for(auto& e : scenery_data) {
		if(p < pe)
			*p++ = &e;
	}
	return p - result;
}

location::location() {
	adat<scenery*, 32> source;
	source.count = select(source.data, lenghtof(source.data));
	zshuffle(source.data, source.count);
	clear();
	type = location_data + (rand() % (sizeof(location_data) / sizeof(location_data[0])));
	for(int i = xrand(2, 4); i > 0; i--)
		places.add(source[i - 1]);
}

static void show_figure(char* result, const char* result_maximum, creature* p) {
	p->actv(result, result_maximum, "����� �����%� %�����.", 0);
}

static char* look(char* result, const char* result_maximum, const char* format, creature** source, unsigned source_count, location* p, char index) {
	//creature* figures[32];
	//auto figures_count = select(figures, sizeof(figures) / sizeof(figures[0]), source, source_count, p, index);
	szprints(result, result_maximum, format, p->type->description[0], p->places[index].getname());
	return zend(result);
}

void location::getdescription(char* result, const char* result_maximum) {
	szprints(zend(result), result_maximum, "�� ����� � %1. ", type->description[0]);
	result = look(zend(result), result_maximum, "����� ����� ��� ���� %2. ", creatures.data, creatures.count, this, 0);
	result = look(zend(result), result_maximum, "������� %1 ���������� %2. ", creatures.data, creatures.count, this, 1);
	result = look(zend(result), result_maximum, "� ������� ����� ���������� %2. ", creatures.data, creatures.count, this, 2);
}

void location::acting() {
	bool interactive = true;
	auto position = 0;
	while(true) {
		getdescription(logs::getptr(), logs::getptrend());
		logs::add(1, "���� ��������� � %1.", places[0].getname());
		auto id = logs::input(interactive, true, "��� ������ ������?");
	}
}