#include "main.h"

struct tag_info {
	const char*			id;
	const char*			name;
} tag_data[] = {{"Awkward", "опасное"},
{"Clumsy", "неуклюжее"},
{"Messy", "кровавое"},
{"Ration", "паек"},
{"Reloaded", "перезарядка"},
{"Precise", "точное"},
{"Slow", "медленно"},
{"Thrown", "метательное"},
{"TwoHanded", "двуручное"},
//
{"Spiked", "шипастое"},
{"Sharp", "острое"},
{"PerfectlyWeighted", "отлично сбалансированное"},
{"SerratedEdge", "зазубренное"},
{"Glows", "светится"},
{"Huge", "огромное"},
{"Versatile", "разностороннее"},
{"WellCrafted", "отлично сделанное"},
};

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