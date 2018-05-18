#include "main.h"

struct item_conflict_info {
	char bonus[4];
	char success[4];
	bool use_two_hands;
	bool thrown;
	char heavy;
	bool heavy_skill_penalty;
};
static struct item_i {
	const char* name[2];
	char ob;
	item_conflict_info conflict;
	const char*	fight_text[Maneuver + 1];
} item_data[] = {{{0}, 0, {}, {"%герой яростно бросил%ась в атаку.", "%герой принял%а защитную позицию, готовясь отразить удар.", "%герой нанес%ла обманный удар.", "%герой начал%а маневрировать и в итоге нанес%ла удар."}},
{{"Axe", "Топор"}, 4, {{0, -1, -1, 0}, {1, 0, 0, 0}}, {"%герой бросил%ась в атаку и нанес%ла несколько сокрушающих ударов топором.", "%герой отбивал%ась тяжелым топором из-зо всех сил и в конце концов пришлось уйти в защиту.", "%герой нанес%ла обманный удар тяжелым и неуклюжим топором.", "%герой попытал%ась найти выгодную позицию и оттуда обрушил%а тяжелый топор."}},
{{"Bow", "Лук"}, 4, {{0, 0, 0, 2}, {0, 0, 0, 0}, true}},
{{"Halberd", "Алебарда"}, 4, {{1, 1, -1, -1}, {0, 0, 0, 0}, true}},
{{"Hook and Line", "Крюк на палке"}, 3, {{-1, 0, 0, 1}, {0, 0, 0, 1}}},
{{"Нож", "Нож"}, 3, {{0, 0, 0, 0}, {0, 0, 0, 0}, false, true}},
{{"Shield", "Щит"}, 3, {{0, 2, 0, 0}, {0, 0, 0, 0}, false, false, 1}},
{{"Sling", "Пращя"}, 2, {{0, 0, 0, 1}, {0, 0, 0, 0}}},
{{"Spear", "Копье"}, 3, {{0, 1, 1, 0}, {0, 0, 0, 0}}},
{{"Staff", "Посох"}, 2, {{0, 0, 1, 0}, {0, 0, 0, 0}}},
{{"Sword", "Меч"}, 3, {{1, 0, 0, 0}, {0, 0, 0, 0}}},
//
{{"Light Armor", ""}, 3, {{0, 0, 0, 0}, {0, 0, 0, 0}, false, false, 1}},
{{"Heavy Armor", ""}, 4, {{0, 0, 0, -1}, {0, 0, 0, 0}, false, false, 1, true}},
//
{{"Herbs", ""}, {}},
{{"Nuts", ""}, {}},
{{"Grains", ""}, {}},
{{"Roots", ""}, {}},
};
assert_enum(item, LastItem);

const char* item::getname() const {
	return item_data[type].name[1];
}

int item::getbonus(action_s value) const {
	return item_data[type].conflict.bonus[value];
}

int item::getsuccess(action_s value) const {
	return item_data[type].conflict.success[value];
}

bool item::istwohanded() const {
	return item_data[type].conflict.use_two_hands;
}

int	item::getcost() const {
	return item_data[type].ob;
}

const char* item::gettext(action_s value) const {
	return item_data[type].fight_text[value];
}

char* item::getbonuses(char* result, const char* result_max, action_s action, const char* prefix, const char* postfix) const {
	auto bs = getbonus(action);
	auto sc = getsuccess(action);
	if(bs || sc) {
		if(prefix)
			zcat(result, prefix);
		auto p = zend(result);
		auto pb = p;
		if(bs) {
			if(p != pb)
				zcat(p, ", ");
			szprints(zend(p), result_max, "%+1iD", bs);
		}
		if(sc) {
			if(p != pb)
				zcat(p, ", ");
			szprints(zend(p), result_max, "%+1iS", sc);
		}
		if(postfix)
			zcat(result, postfix);
	}
	return result;
}