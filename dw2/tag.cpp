#include "main.h"

struct tagi {
	const char*		id;
	const char*		name;
	bool			hidden;
};

tagi bsmeta<tagi>::elements[] = {{"Hand", "вплотную"},
{"Close", "удар меча"},
{"Reach", "удар копья"},
{"Near", "недалеко"},
{"Far", "делако"},
//
{"Awkward", "опасное"},
{"Clumsy", "неуклюжее"},
{"Messy", "кровавое"},
{"Ration", "паек"},
{"Reloaded", "перезарядка"},
{"Precise", "точное"},
{"Slow", "медленно"},
{"Thrown", "метательное"},
{"TwoHanded", "двуручное"},
//
{"Armor1", "броня 1", true},
{"Armor2", "броня 2", true},
{"Armor4", "броня 4", true},
{"ArmorP1", "броня+1", true},
//
{"DamageP1", "урон+1", true},
{"DamageP2", "урон+2", true},
{"DamageM1", "урон-1", true},
{"DamageM2", "урон-2", true},
//
{"Weight1", "вес 1", true},
{"Weight2", "вес 2", true},
{"Weight4", "вес 4", true},
//
{"Pierce1", "проникание 1", true},
{"Pierce2", "проникание 2", true},
{"IgnoreArmor", "игнорирует броню"},
//
{"Use1", "использует 1", true},
{"Use2", "использует 2", true},
{"Use4", "использует 4", true},
//
{"Ammo1", "заряд 1", true},
{"Ammo2", "заряд 2", true},
{"Ammo4", "заряд 4", true},
//
{"Identified", "опознано", true},
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
assert_enum(tag, WellCrafted);

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