#include "main.h"

struct tag_info {
	const char*			id;
	const char*			name;
} tag_data[] = {{"Awkward", "�������"},
{"Clumsy", "���������"},
{"Messy", "��������"},
{"Ration", "����"},
{"Reloaded", "�����������"},
{"Precise", "������"},
{"Slow", "��������"},
{"Thrown", "�����������"},
{"TwoHanded", "���������"},
//
{"Spiked", "��������"},
{"Sharp", "������"},
{"PerfectlyWeighted", "������� ����������������"},
{"SerratedEdge", "�����������"},
{"Glows", "��������"},
{"Huge", "��������"},
{"Versatile", "��������������"},
{"WellCrafted", "������� ���������"},
};

int tagc::getarmor() const {
	auto r = 0;
	if(is(Armor1))
		r++;
	if(is(Armor2))
		r += 2;
	if(is(Armor4))
		r += 4;
	if(is(ArmorP1))
		r++;
	return r;
}

int	tagc::getdamage() const {
	auto r = 0;
	if(is(DamageP1))
		r += 1;
	if(is(DamageP2))
		r += 2;
	if(is(DamageM1))
		r -= 1;
	if(is(DamageM2))
		r -= 2;
	return r;
}

int	tagc::getweight() const {
	auto r = 0;
	if(is(Weight1))
		r += 1;
	if(is(Weight2))
		r += 2;
	if(is(Weight4))
		r += 4;
	return r;
}