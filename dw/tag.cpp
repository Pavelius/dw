#include "main.h"

tagi bsmeta<tagi>::elements[] = {
	{"Awkward", "Опасное"},
	{"Clumsy", "Неуклюжее"},
	{"Messy", "Кровавое"},
	{"Ration", "Паек"},
	{"Reloaded", "Перезарядка"},
	{"Precise", "Точное"},
	{"Slow", "Медленное"},
	{"Thrown", "Метательное"},
	{"TwoHanded", "Двуручное"},
	// Числовые показатели
	{"Armor", "Броня", 1},
	{"Armor", "Броня", 2},
	{"Armor", "Броня", 4},
	{"Damage", "Урон", 1},
	{"Damage", "Урон", 2},
	{"Pierce", "Проникание", 1},
	{"Pierce", "Проникание", 2},
	{"Weight", "Вес", 1},
	{"Weight", "Вес", 2},
	{"Weight", "Вес", 4},
	{"Weight", "Вес", 8},
	{"Use", "Запас", 1},
	{"Use", "Запас", 2},
	{"Use", "Запас", 4},
	// Улучшения воина
	{"Spiked", "Шипастое"},
	{"Sharp", "Острое"},
	{"PerfectlyWeighted", "Сбалансированное"},
	{"SerratedEdge", "Зазубренное"},
	{"Glows", "Светится"},
	{"Huge", "Огромное"},
	{"Versatile", "Разностороннее"},
	{"WellCrafted", "Мастерское"},
};
assert_enum(tag, WellCrafted);

int	tagable::get(tag_s i1, tag_s i2) const {
	auto r = 0;
	for(auto i = i1; i <= i2; i = (tag_s)(i + 1)) {
		if(is(i))
			r += bsmeta<tagi>::elements[i].count;
	}
	return r;
}

void tagable::set(tag_s i1, tag_s i2, int v) {
	for(auto i = i2; i >= i1; i = (tag_s)(i - 1)) {
		remove(i);
		auto n = bsmeta<tagi>::elements[i].count;
		if(n && v >= n) {
			v -= n;
			set(i);
		}
	}
}

int	tagable::getpierce() const {
	auto r = get(Pierce1, Pierce2);
	if(is(Sharp))
		r += 2;
	return r;
}

int tagable::getdamage() const {
	auto r = get(Damage1, Damage2);
	if(is(Spiked))
		r++;
	if(is(SerratedEdges))
		r++;
	return r;
}

int tagable::getweight() const {
	auto r = get(Weight1, Weight8);
	if(is(Spiked))
		r++;
	if(is(WellCrafted))
		r--;
	return imax(r, 0);
}