#include "main.h"

tagi bsmeta<tagi>::elements[] = {{"Area", "Область"},
{"Autofire", "Автоматическое"},
{"HiTech", "Технологичное"},
{"Infinite", "Бесконечное"},
{"Loud", "Громкое"},
{"Messy", "Кровавое"},
{"Reload", "Перезарядка"},
// Числовые показатели
{"Harm", "Урон", 1},
{"Harm", "Урон", 2},
{"Harm", "Урон", 4},
{"Armor", "Броня", 1},
{"Armor", "Броня", 2},
{"Armor", "Броня", 4},
};
assert_enum(tag, Armor4);

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

int	tagable::getarmor() const {
	auto r = get(Armor1, Armor4);
	return r;
}

int	tagable::getharm() const {
	auto r = get(Harm1, Harm4);
	if(is(Bloodcrazed) || is(Merciless))
		r++;
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