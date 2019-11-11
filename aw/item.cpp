#include "main.h"

itemi bsmeta<itemi>::elements[] = {
	{"", ""},
	{"revolver", "револьвер", 2, 0, {Close}, {Loud, Reload}},
	{"pistol", "пистолет", 2, 0, {Close}, {Loud}},
	{"rifle", "ружье", 3, 0, {Far}, {Loud}},
	{"shotgun", "дробовик", 3, 0, {Close}, {Messy}},
	{"magnum", "пистолет магнум", 3, 0, {Close}, {Loud, Reload}},
	{"sawed-off", "бензопила", 3, 0, {Close}, {Messy, Reload}},
	{"SMG", "SMG", 2, 0, {Close}, {Loud, Autofire}},
	//
	{"knife", "нож", 2, 0, {Hand}},
	{"staff", "посох", 1, 0, {Hand}, {Area}},
	{"spear", "копье", 2, 0, {Hand}},
	{"chain", "цепь", 1, 0, {Hand}, {Area}},
	{"crowbar", "монтировка", 2, 0, {Hand}, {Messy}},
	{"grenades", "гранаты", 4, 0, {Hand}, {Area, Reload, Messy}},
	{"machete", "мачете", 3, 0, {Hand}, {Messy}},
	{"many knives", "много ножей", 2, 0, {Hand}, {Infinite}},
	//
	{"sniper rifle", "снайперская винтовка", 3, 0, {Far}, {}, {Silenced}},
	{"machine gun", "пулемет", 3, 0, {Close, Far}, {Area, Messy}},
	{"assault rifle", "штурмовая винтовка", 3, 0, {Close, Far}, {Loud, Autofire}},
	{"grenade launcher", "гранатомет", 4, 0, {Close}, {Area, Messy}},
};
assert_enum(item, GrenadeLauncher);

upgradei bsmeta<upgradei>::elements[] = {
	{"with blade", "с лезвием", true},
	{"with skipes", "с шипами", true},
	{"scoped", "с прицелом", true},
	{"big", "огромный"},
	{"high powered", "мощный"},
	{"semiautomatic", "полу-автоматический"},
	{"silenced", "с глушителем"},
	{"hidden", "скрытый"},
	{"valuable", "ценный"},
};
assert_enum(upgrade, Valuable);

item::item(item_s type) {
	set(type);
}

void item::clear() {
	type = NoItem;
	upgrade = 0;
}

int item::getharm() const {
	int r = bsmeta<itemi>::elements[type].harm;
	if(is(HiPower))
		r++;
	if(is(Big))
		r++;
	if(is(Spikes))
		r++;
	if(is(Blade))
		r++;
	return r;
}

bool item::is(distance_s value) const {
	return bsmeta<itemi>::elements[type].distance.is(value);
}

bool item::is(upgrade_s value) const {
	return (upgrade & (1 << value)) != 0;
}

void item::set(upgrade_s value) {
	upgrade |= 1 << value;
}

bool item::isarea() const {
	return bsmeta<itemi>::elements[type].tag.is(Area) || ismessy();
}

bool item::ishitech() const {
	return bsmeta<itemi>::elements[type].tag.is(HiTech);
}

bool item::isinfinite() const {
	return bsmeta<itemi>::elements[type].tag.is(Infinite) || is(Hidden);
}

bool item::isloud() const {
	return (bsmeta<itemi>::elements[type].tag.is(Loud) || ismessy()) && !is(Silenced);
}

bool item::ismessy() const {
	return bsmeta<itemi>::elements[type].tag.is(Messy);
}

bool item::isreload() const {
	return bsmeta<itemi>::elements[type].tag.is(Reload) && !is(Semiautomatic);
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
	upgrade = bsmeta<itemi>::elements[type].upgrade.data;
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