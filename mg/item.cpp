#include "main.h"

itemi bsmeta<itemi>::elements[] = {{},
{"Axe", "�����", 4, {{0, -1, -1, 0}, {1, 0, 0, 0}}},
{"Bow", "���", 4, {{0, 0, 0, 2}, {0, 0, 0, 0}, true}},
{"Halberd", "��������", 4, {{1, 1, -1, -1}, {0, 0, 0, 0}, true}},
{"Hook and Line", "���� �� �����", 3, {{-1, 0, 0, 1}, {0, 0, 0, 1}}},
{"���", "���", 3, {{0, 0, 0, 0}, {0, 0, 0, 0}, false, true}},
{"Shield", "���", 3, {{0, 2, 0, 0}, {0, 0, 0, 0}, false, false, 1}},
{"Sling", "�����", 2, {{0, 0, 0, 1}, {0, 0, 0, 0}}},
{"Spear", "�����", 3, {{0, 1, 1, 0}, {0, 0, 0, 0}}},
{"Staff", "�����", 2, {{0, 0, 1, 0}, {0, 0, 0, 0}}},
{"Sword", "���", 3, {{1, 0, 0, 0}, {0, 0, 0, 0}}},
//
{"Light Armor", "�������� ������", 3, {{0, 0, 0, 0}, {0, 0, 0, 0}, false, false, 1}},
{"Heavy Armor", "��������", 4, {{0, 0, 0, -1}, {0, 0, 0, 0}, false, false, 1, true}},
//
{"Herbs", "�����", {}},
{"Nuts", "�����", {}},
{"Grains", "������", {}},
{"Roots", "�����", {}},
};
assert_enum(item, LastItem);

int item::getbonus(action_s value) const {
	return getitem().conflict.bonus[value];
}

int item::getsuccess(action_s value) const {
	return getitem().conflict.success[value];
}

bool item::istwohanded() const {
	return getitem().conflict.use_two_hands;
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