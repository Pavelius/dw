#include "main.h"

enum tags : char {
	Area, HiTech, Infinite, Messy, Reload,
};

constexpr static struct item_i {
	const char*				id;
	const char*				name;
	dice					harm;
	char					armor;
	cflags<distance_s>		distance;
	cflags<tags>			tag;
} item_data[] = {{"", ""},
{"revolver", "���������", {1, 6}, 0, {Close}, {Reload}},
{"pistol", "��������", {1, 6}, 0, {Close}, {}},
{"rifle", "�����", {1, 6}, 0, {Far}, {}},
{"shotgun", "��������", {1, 6}, 0, {Close}, {Messy, Reload}},
{"magnum", "�������� ������", {1, 6, 1}, 0, {Close}, {}},
{"sawed-off", "���������", {1, 6}, 0, {Hand}, {Messy, Reload}},
{"SMG", "SMG", {1, 6}, 0, {Close}, {Area}},
//
{"knife", "���", {1, 3}, 0, {Hand}},
{"staff", "�����", {1, 3}, 0, {Hand}, {Area}},
{"spear", "�����", {1, 6}, 0, {Hand}},
{"chain", "����", {1, 6}, 0, {Hand}, {Area}},
{"crowbar", "����������", {1, 6}, 0, {Hand}, {}},
{"grenades", "�������", {1, 6, 1}, 0, {Close}, {Area}},
{"machete", "������", {1, 6}, 0, {Hand}, {Messy}},
//
{"sniper rifle", "����������� ��������", {1, 6}, 0, {Far}, {}},
{"machine gun", "�������", {1, 6, 2}, 0, {Close}, {Area}},
{"assault rifle", "��������� ��������", {1, 6, 1}, 0, {Close, Far}, {Area}},
{"grenade launcher", "����������", {1, 6, 3}, 0, {Close}, {Area, Messy, Reload}},
};
assert_enum(item, GrenadeLauncher);
getstr_enum(item);

template<> const char* getstr<item>(item value) {
	return item_data[value.type].name;
}

item::item(item_s type) {
	set(type);
}

void item::clear() {
	type = NoItem;
	upgrade = 0;
}

dice item::getharm() const {
	return item_data[type].harm;
}

bool item::is(distance_s value) const {
	return item_data[type].distance.is(value);
}

bool item::isarea() const {
	return item_data[type].tag.is(Area) || ismessy();
}

bool item::ishitech() const {
	return item_data[type].tag.is(HiTech);
}

bool item::ismessy() const {
	return item_data[type].tag.is(Messy);
}

bool item::isreload() const {
	return item_data[type].tag.is(Reload);
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
	return item_data[type].harm.c != 0;
}

void item::set(item_s value) {
	type = value;
}

const char* item::getname() const {
	return getstr(type);
}

char* item::getname(char* result, bool description) {
	result[0] = 0;
	//for(auto e = Blade; e <= Valuable; e = (upgrade_s)(e + 1)) {
	//	if(upgrade_data[e].ending)
	//		continue;
	//	if(is(e)) {
	//		zcat(result, upgrade_data[e].name);
	//		zcat(result, " ");
	//	}
	//}
	zcpy(result, getstr(type));
	//for(auto e = Blade; e <= Valuable; e = (upgrade_s)(e + 1)) {
	//	if(!upgrade_data[e].ending)
	//		continue;
	//	if(is(e)) {
	//		zcat(result, " ");
	//		zcat(result, upgrade_data[e].name);
	//	}
	//}
	return result;
}