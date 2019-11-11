#include "main.h"

struct tagi {
	const char*		id;
	const char*		name;
	bool			hidden;
};

tagi bsmeta<tagi>::elements[] = {{"Hand", "��������"},
{"Close", "���� ����"},
{"Reach", "���� �����"},
{"Near", "��������"},
{"Far", "������"},
//
{"Awkward", "�������"},
{"Clumsy", "���������"},
{"Messy", "��������"},
{"Ration", "����"},
{"Reloaded", "�����������"},
{"Precise", "������"},
{"Slow", "��������"},
{"Thrown", "�����������"},
{"TwoHanded", "���������"},
//
{"Armor1", "����� 1", true},
{"Armor2", "����� 2", true},
{"Armor4", "����� 4", true},
{"ArmorP1", "�����+1", true},
//
{"DamageP1", "����+1", true},
{"DamageP2", "����+2", true},
{"DamageM1", "����-1", true},
{"DamageM2", "����-2", true},
//
{"Weight1", "��� 1", true},
{"Weight2", "��� 2", true},
{"Weight4", "��� 4", true},
//
{"Pierce1", "���������� 1", true},
{"Pierce2", "���������� 2", true},
{"IgnoreArmor", "���������� �����"},
//
{"Use1", "���������� 1", true},
{"Use2", "���������� 2", true},
{"Use4", "���������� 4", true},
//
{"Ammo1", "����� 1", true},
{"Ammo2", "����� 2", true},
{"Ammo4", "����� 4", true},
//
{"Identified", "��������", true},
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
assert_enum(tag, WellCrafted);

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