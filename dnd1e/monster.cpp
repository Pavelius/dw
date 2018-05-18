#include "main.h"

enum intellegence_s : unsigned char {
	NoIntellegence, Animal, Semi, Low,
	Average, Very, Hight, Exeptional, Genius,
	SupraGenius, Godlike,
};

static struct monster_info {
	const char*		id;
	const char*		name;
	const char*		nameof;
	intellegence_s	intellegence;
	alignment_s		alignment;
	char			HD;
	size_s			size;
	dice			appearing;
	item			wears[4];
	feat_s			feats[4];
} monster_data[] = {
	{"character", "персонаж", "персонажей", Average, TrueNeutral},
	{"orc", "орк", "орков", Low, LawfulEvil, 1, Medium, {3, 10, 0, 10}, {Spear, Shield, ChainMail}},
	{"rogue", "брод€га", "брод€г", Average, NeutralEvil, 1, Medium, {2, 10, 0, 10}, {Dagger, LeatherArmor}},
};
assert_enum(monster, Rogue);
getstr_enum(monster);
metadc_enum(monster);

dice character::getappearing(monster_s id) {
	return monster_data[id].appearing;
}

alignment_s	character::getalignment(monster_s id) {
	return monster_data[id].alignment;
}

void character::setmonsterhp() {
	hp_maximum = 0;
	if(getHD() == 0)
		hp_maximum += dice::roll(1, 6);
	else {
		for(auto i = getHD(); i > 0; i--)
			hp_maximum += dice::roll(1, 8);
	}
}

character::character(monster_s type) {
	clear();
	auto& e = monster_data[type];
	// Set basic values
	alignment = e.alignment;
	levels[0] = e.HD;
	monster = type;
	// Set all ability to 10
	for(auto& c : abilities)
		c = 10;
	for(auto i : e.wears) {
		add(i);
	}
	// Set hit points
	setmonsterhp();
	// Get current hit points and raise levels
	finish(false);
}

char* character::getmonstername(char* result, const char* result_maximum) const {
	if(count == 1)
		zcpy(result, monster_data[monster].name);
	else
		szprints(result, result_maximum, "%1i %2", count, monster_data[monster].nameof);
	return result;
}