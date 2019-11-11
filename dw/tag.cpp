#include "main.h"

tagi bsmeta<tagi>::elements[] = {
	{"Awkward", "�������"},
	{"Clumsy", "���������"},
	{"Messy", "��������"},
	{"Ration", "����"},
	{"Reloaded", "�����������"},
	{"Precise", "������"},
	{"Slow", "���������"},
	{"Thrown", "�����������"},
	{"TwoHanded", "���������"},
	// �������� ����������
	{"Armor", "�����", 1},
	{"Armor", "�����", 2},
	{"Armor", "�����", 4},
	{"Damage", "����", 1},
	{"Damage", "����", 2},
	{"Pierce", "����������", 1},
	{"Pierce", "����������", 2},
	{"Weight", "���", 1},
	{"Weight", "���", 2},
	{"Weight", "���", 4},
	{"Weight", "���", 8},
	{"Use", "�����", 1},
	{"Use", "�����", 2},
	{"Use", "�����", 4},
	// ��������� �����
	{"Spiked", "��������"},
	{"Sharp", "������"},
	{"PerfectlyWeighted", "����������������"},
	{"SerratedEdge", "�����������"},
	{"Glows", "��������"},
	{"Huge", "��������"},
	{"Versatile", "��������������"},
	{"WellCrafted", "����������"},
};
assert_enum(tag, WellCrafted);

int	taga::get(tag_s i1, tag_s i2) const {
	auto r = 0;
	for(auto i = i1; i <= i2; i = (tag_s)(i + 1)) {
		if(is(i))
			r += bsmeta<tagi>::elements[i].value;
	}
	return r;
}

void taga::set(tag_s i1, tag_s i2, int v) {
	for(auto i = i2; i >= i1; i = (tag_s)(i - 1)) {
		remove(i);
		auto n = bsmeta<tagi>::elements[i].value;
		if(n && v >= n) {
			v -= n;
			add(i);
		}
	}
}