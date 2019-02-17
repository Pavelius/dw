#include "main.h"

static const char* range_text[] = {"�� ���",
"����� ����� ����", "� ���� ������ �� ���", "�������� �� ���", "�������", "������ �������"};

struct scene_info {
	const char*		nameof;
};
static scene_info scene_data[] = {{"������� �������"},
{"������� �����"},
{"������ �������"},
};
struct feature_info {
	gender_s		gender;
	const char*		name;
	const char*		look;
};
static feature_info feature_data[] = {{Male, "���������� ����"},
{Female, "�������� ������", "��������� ������� �� ��� ���� ������ � ���� �� ���� ��� ���� ����� ������."},
{Female, "��������� �������", "�� �������� ��������� ����. ������ ��� ������� �����."},
{Male, "������ �� ������� �����", "������ ������� ��� ������ ������. �������� �� ��� �����-�� ��������� � ������ ����� �������."},
{Female, "���� ������", "���� ���� ��������� �������� �������� ��� � ������������. ������ ���-�� ����������. ����� ������� �����."},
};

enum feature_flag_s : unsigned {
	Hidden = 1,
};

int	scene::getplayercount() const {
	auto result = 0;
	for(auto p : players) {
		if(p)
			result++;
	}
	return result;
}

void feature::clear() {
	memset(this, 0, sizeof(*this));
}

void feature::create() {
	clear();
	type = feature_data + rand() % (sizeof(feature_data) / sizeof(feature_data[0]));
	position = xrand(0, 2);
}

const char* feature::getlook() const {
	return type->look;
}

const char* feature::getname() const {
	return type->name;
}

void scene::clear() {
	memset(this, 0, sizeof(*this));
}

void scene::create() {
	clear();
	type = scene_data + rand() % (sizeof(scene_data) / sizeof(scene_data[0]));
	auto maximum = xrand(2, sizeof(features) / sizeof(features[0]) - 3);
	for(auto i = 0; i < maximum; i++)
		features[i].create();
}

void scene::look(stringbuilder& sb) {
	auto current = features + 0;
	sb.adds("�� ������ %1.", type->nameof);
	sb.adds("%+1 ��������� %2.", range_text[ArmsHand], current->getname());
	sb.adds(current->getlook());
	for(auto& e : features) {
		if(!e)
			continue;
		if(&e == current)
			continue;
		auto d = Near + iabs(current->getposition() - e.getposition());
		sb.adds("%+1 ��������� %2.", range_text[d], e.getname());
	}
}