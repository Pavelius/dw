#include "main.h"

itemi bsmeta<itemi>::elements[] = {{},
{"Axe", "Топор", 4, {{0, -1, -1, 0}, {1, 0, 0, 0}}},
{"Bow", "Лук", 4, {{0, 0, 0, 2}, {0, 0, 0, 0}, true}},
{"Halberd", "Алебарда", 4, {{1, 1, -1, -1}, {0, 0, 0, 0}, true}},
{"Hook and Line", "Крюк на палке", 3, {{-1, 0, 0, 1}, {0, 0, 0, 1}}},
{"Нож", "Нож", 3, {{0, 0, 0, 0}, {0, 0, 0, 0}, false, true}},
{"Shield", "Щит", 3, {{0, 2, 0, 0}, {0, 0, 0, 0}, false, false, 1}},
{"Sling", "Пращя", 2, {{0, 0, 0, 1}, {0, 0, 0, 0}}},
{"Spear", "Копье", 3, {{0, 1, 1, 0}, {0, 0, 0, 0}}},
{"Staff", "Посох", 2, {{0, 0, 1, 0}, {0, 0, 0, 0}}},
{"Sword", "Меч", 3, {{1, 0, 0, 0}, {0, 0, 0, 0}}},
//
{"Light Armor", "Кожанный доспех", 3, {{0, 0, 0, 0}, {0, 0, 0, 0}, false, false, 1}},
{"Heavy Armor", "Кольчуга", 4, {{0, 0, 0, -1}, {0, 0, 0, 0}, false, false, 1, true}},
//
{"Herbs", "Травы", {}},
{"Nuts", "Орехи", {}},
{"Grains", "Семена", {}},
{"Roots", "Корни", {}},
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