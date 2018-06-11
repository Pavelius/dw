#include "main.h"

static struct ancient_info {
	const char*	id;
	const char*	name;
	char		doom;
	char		combat;
} ancient_data[] = {{"Azathoth", "Азазос", 14, 0},
{"Cthulhu", "Ктулху", 13, -6},
{"Hastur", "Хастур", 13, 0},
{"Ithaqua", "Итаку", 11},
{"Nyarlathotep", "", 11},
{"ShubNiggurath", "Шуб-Нигурасс", 12},
{"Yig", "Йиг", 10},
{"YogSothoth", "Йог-Созос", 12},
};
assert_enum(ancient, YogSothoth);
getstr_enum(ancient);

void shuffle_myth_deck();

void game_info::create(ancient_s value) {
	ancient = value;
	doom = 0;
	terror = 0;
	doom_maximum = ancient_data[value].doom;
	deck::initialize();
	monster::initialize();
	shuffle_myth_deck();
}

int	game_info::getcombat() const {
	auto result = ancient_data[ancient].combat;
	if(ancient == Hastur)
		result = -terror;
	return result;
}

int	game_info::getsealcost() const {
	auto result = 5;
	if(is(Hastur))
		result = 8;
	return result;
}