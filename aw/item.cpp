#include "main.h"

itemi bsmeta<itemi>::elements[] = {
	{"", ""},
	{"revolver", "���������", 2, 0, {Close, Loud, Reload}},
	{"pistol", "��������", 2, 0, {Close, Loud}},
	{"rifle", "�����", 3, 0, {Far, Loud}},
	{"shotgun", "��������", 3, 0, {Close, Messy}},
	{"magnum", "�������� ������", 3, 0, {Close, Loud, Reload}},
	{"sawed-off", "���������", 3, 0, {Close, Messy, Reload}},
	{"SMG", "SMG", 2, 0, {Close, Loud, Autofire}},
	//
	{"knife", "���", 2, 0, {Hand}},
	{"staff", "�����", 1, 0, {Hand, Area}},
	{"spear", "�����", 2, 0, {Hand}},
	{"chain", "����", 1, 0, {Hand, Area}},
	{"crowbar", "����������", 2, 0, {Hand, Messy}},
	{"grenades", "�������", 4, 0, {Hand, Area, Reload, Messy}},
	{"machete", "������", 3, 0, {Hand, Messy}},
	{"many knives", "����� �����", 2, 0, {Hand, Infinite}},
	//
	{"sniper rifle", "����������� ��������", 3, 0, {Far, Silenced}},
	{"machine gun", "�������", 3, 0, {Close, Far, Area, Messy}},
	{"assault rifle", "��������� ��������", 3, 0, {Close, Far, Loud, Autofire}},
	{"grenade launcher", "����������", 4, 0, {Close, Area, Messy}},
};
assert_enum(item, GrenadeLauncher);

void item::clear() {
	memset(this, 0, sizeof(*this));
}

bool item::isupgrading() const {
	switch(type) {
	case Revolver:
	case Pistol:
	case Rifle:
	case Knife:
	case Machete:
		return true;
	default:
		return false;
	}
}

bool item::isweapon() const {
	return bsmeta<itemi>::elements[type].harm != 0;
}

void item::set(item_s value) {
	type = value;
}

const char* item::getname() const {
	return getstr(type);
}

char* item::getname(char* result, bool description) {
	result[0] = 0;
	for(auto e = Blade; e <= Valuable; e = (upgrade_s)(e + 1)) {
		if(bsmeta<upgradei>::elements[e].ending)
			continue;
		if(is(e)) {
			zcat(result, bsmeta<upgradei>::elements[e].name);
			zcat(result, " ");
		}
	}
	zcpy(result, getstr(type));
	for(auto e = Blade; e <= Valuable; e = (upgrade_s)(e + 1)) {
		if(!bsmeta<upgradei>::elements[e].ending)
			continue;
		if(is(e)) {
			zcat(result, " ");
			zcat(result, bsmeta<upgradei>::elements[e].name);
		}
	}
	return result;
}