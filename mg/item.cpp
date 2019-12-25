#include "main.h"

itemi bsmeta<itemi>::elements[] = {{},
{"Axe", "�����", 4, {Deadly, Slow}},
{"Bow", "���", 4, {Missile, LongRange, TwoHanded, Fragile}},
{"Halberd", "��������", 4, {Versatile, Bulky, TwoHanded}},
{"Hook and Line", "���� �� �����", 3, {Hooked, Unwieldy}},
{"���", "���", 3, {ShortAndQuick, Thrown}},
{"Shield", "���", 3, {Protection, Heavy}},
{"Sling", "�����", 2, {Missile, MediumRange}},
{"Spear", "�����", 3, {Fast, CloseRanks}},
{"Staff", "�����", 2, {Handy, GentleThrashing}},
{"Sword", "���", 3, {Useful}},
//
{"Light Armor", "�������� ������", 3, {Absorb, Armor, Heavy}},
{"Heavy Armor", "��������", 4, {Armor, Heavy, Clumsy}},
//
{"Herbs", "�����", {}},
{"Nuts", "�����", {}},
{"Grains", "������", {}},
{"Roots", "�����", {}},
};
assert_enum(item, LastItem);

int item::getbonus(action_s value) const {
	auto r = 0;
	if(useful_used) {
		if(value == useful)
			r++;
	}
	switch(value) {
	case Attack:
		if(is(Versatile))
			r++;
		if(is(Unwieldy))
			r--;
		break;
	case Defend:
		if(is(Versatile))
			r++;
		if(is(Protection))
			r += 2;
		if(is(CloseRanks))
			r++;
		if(is(Slow))
			r--;
		break;
	case Maneuver:
		if(is(LongRange))
			r += 2;
		if(is(MediumRange))
			r++;
		if(is(Hooked))
			r++;
		if(is(Bulky))
			r--;
		break;
	case Feint:
		if(is(Fast))
			r++;
		if(is(Handy))
			r++;
		if(is(Bulky))
			r--;
		if(is(Slow))
			r--;
		break;
	}
	return r;
}

int item::getsuccess(action_s value) const {
	auto r = 0;
	switch(value) {
	case Attack:
		if(is(Deadly))
			r++;
		break;
	case Maneuver:
		if(is(Hooked))
			r++;
		break;
	}
	return r;
}

int	item::getcost() const {
	return getitem().ob;
}

const char* item::gettext(action_s value) const {
	return 0;
}

void item::getbonus(stringbuilder& sb, action_s action, const char* prefix, const char* postfix) const {
	auto bs = getbonus(action);
	auto sc = getsuccess(action);
	if(bs || sc) {
		if(prefix)
			sb.adds(prefix);
		if(bs) {
			sb.addsep(',');
			sb.add("%+1iD", bs);
		}
		if(sc) {
			sb.addsep(',');
			sb.add("%+1iS", sc);
		}
		if(postfix)
			sb.add(prefix);
	}
}