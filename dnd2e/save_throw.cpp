#include "main.h"

struct save_i {
	const char*		id;
	const char*		name;
} save_data[] = {
	{"Save vs Paralization", "Защита от парализации"},
	{"Save vs Poison", "Защита от яда"},
	{"Save vs Death", "Защита от смерти"},
	{"Save vs Wands", "Защита от палочек"},
	{"Save vs Petrification", "Защита от окаменения"},
	{"Save vs Polymorph", "Защита от превращения"},
	{"Save vs Breath Weapon", "Защита от дыхания"},
	{"Save vs Spells", "Защита от магии"},
};
assert_enum(save, SaveVsSpells);
getstr_enum(save);

static char savevs_data[4][5][22] = {
	{ // Warriors - 0
		{16, 14, 14, 13, 13, 11, 11, 10, 10, 8, 8, 7, 7, 5, 5, 4, 4, 3, 3, 2, 2, 2},
		{18, 16, 16, 15, 15, 13, 13, 12, 12, 10, 10, 9, 9, 7, 7, 6, 6, 5, 5, 3, 3, 2},
		{17, 15, 15, 14, 14, 12, 12, 11, 11, 9, 9, 8, 8, 6, 6, 5, 5, 4, 4, 3, 3, 2},
		{20, 17, 17, 16, 16, 13, 13, 12, 12, 9, 9, 8, 8, 5, 5, 4, 4, 3, 3, 3, 3, 3},
		{19, 17, 17, 16, 16, 14, 14, 13, 13, 11, 11, 10, 10, 8, 8, 7, 7, 6, 6, 5, 5, 4},
	},
	{ // Priest - 1
		{10, 10, 10, 10, 9, 9, 9, 7, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 2, 2, 2},
		{14, 14, 14, 14, 13, 13, 13, 11, 11, 11, 10, 10, 10, 9, 9, 9, 8, 8, 8, 6, 6, 6},
		{13, 13, 13, 13, 12, 12, 12, 10, 10, 10, 9, 9, 9, 8, 8, 8, 7, 7, 7, 5, 5, 5},
		{16, 16, 16, 16, 15, 15, 15, 13, 13, 13, 12, 12, 12, 11, 11, 11, 10, 10, 10, 8, 8, 8},
		{15, 15, 15, 15, 14, 14, 14, 12, 12, 12, 11, 11, 11, 10, 10, 10, 9, 9, 9, 7, 7, 7},
	},
	{ // Rogues - 2
		{13, 13, 13, 13, 13, 12, 12, 12, 12, 11, 11, 11, 11, 10, 10, 10, 10, 9, 9, 9, 9, 8},
		{14, 14, 14, 14, 14, 12, 12, 12, 12, 10, 10, 10, 10, 8, 8, 8, 8, 6, 6, 6, 6, 4},
		{12, 12, 12, 12, 12, 11, 11, 11, 11, 10, 10, 10, 10, 9, 9, 9, 9, 8, 8, 8, 8, 7},
		{16, 16, 16, 16, 16, 15, 15, 15, 15, 14, 14, 14, 14, 13, 13, 13, 13, 12, 12, 12, 12, 11},
		{15, 15, 15, 15, 15, 13, 13, 13, 13, 11, 11, 11, 11, 9, 9, 9, 9, 7, 7, 7, 7, 5},
	},
	{ // Wizards - 3
		{14, 14, 14, 14, 14, 14, 13, 13, 13, 13, 13, 11, 11, 11, 11, 11, 10, 10, 10, 10, 10, 8},
		{11, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 3},
		{13, 13, 13, 13, 13, 13, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 7, 7, 7, 7, 7, 5},
		{15, 15, 15, 15, 15, 15, 13, 13, 13, 13, 13, 11, 11, 11, 11, 11, 9, 9, 9, 9, 9, 7},
		{12, 12, 12, 12, 12, 12, 10, 10, 10, 10, 10, 8, 8, 8, 8, 8, 6, 6, 6, 6, 6, 4},
	},
};
extern char reaction_adjustment[26];
static char darwen_bonus[] = {
	0, 0, 0, 0, 1, 1, 1, 2, 2, 2,
	2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5,
	6, 6, 6, 6, 7
};
static char widow_spell_bonus[] = {
	-4, -4, -4, -3, -2, -1, -1, -1, 0, 0,
	0, 0, 0, 0, 0, 1, 2, 3, 4, 5
};
static char save_index[] = {
	0, 0, 0,
	1,
	2, 2,
	3,
	4,
};
static_assert(sizeof(save_index) / sizeof(save_index[0]) == SaveVsSpells + 1, "Invalid count of save index elements");

static int get_save_group(class_s value) {
	switch(value) {
	case Theif: return 2;
	case MagicUser: return 3;
	case Cleric: return 1;
	default: return 0;
	}
}

int	character::get(save_s id) const {
	auto index = save_index[id];
	auto result = 20;
	for(auto e : classes) {
		if(!e)
			continue;
		auto g = get_save_group(getkit(e));
		auto n = get(e);
		if(n >= sizeof(savevs_data[0][0]) / sizeof(savevs_data[0][0][0]))
			n = sizeof(savevs_data[0][0]) / sizeof(savevs_data[0][0][0]) - 1;
		auto v = savevs_data[g][index][n];
		if(v && v < result)
			result = v;
	}
	if(is(HolyGrace))
		result -= 2;
	switch(id) {
	case SaveVsPoison:
		if(is(BonusSaveVsPoison))
			result -= maptbl(darwen_bonus, get(Constitution));
		break;
	case SaveVsWands:
		if(is(BonusSaveVsWands))
			result -= maptbl(darwen_bonus, get(Constitution));
		result -= maptbl(reaction_adjustment, get(Dexterity));
		break;
	case SaveVsSpells:
		if(is(BonusSaveVsSpells))
			result -= maptbl(darwen_bonus, get(Constitution));
		result -= maptbl(widow_spell_bonus, get(Wisdow));
		break;
	}
	return result;
}