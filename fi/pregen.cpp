#include "main.h"

struct pregen_info {
	const char*			id;
	const char*			name;
	race_s				race;
	profession_s		profession;
	char				ability[4];
	adat<skill_set, 8>	skills;
	item_s				gear[8];
};
pregen_info pregen_data[] = {{""},
{"Aliander", "Алиандерец", Human, Fighter, {3, 3, 3, 3}, {{Melee, 2}, {Move, 2}, {Marksmanship, 2}, {Healing, 1}}, {Shortsword, ShortBow}},
{"Frailer", "Фрайлер", HalfElf, Druid, {2, 3, 4, 4}, {{Lore, 2}, {Insight, 2}, {Manipulation, 2}}, {Dagger}},
{"Bear", "Медведь", Animal, Fighter, {6, 2}, {{Melee, 3}, {Scouting, 3}}},
{"Wolf", "Волк", Animal, Fighter, {4, 4}, {{Move, 3}, {Melee, 3}, {Scouting, 5}}},
};
assert_enum(pregen, Wolf);

void character::create(pregen_s id) {
	clear();
	race = pregen_data[id].race;
	profession = pregen_data[id].profession;
	memcpy(ability, pregen_data[id].ability, sizeof(ability));
	memcpy(ability_damage, ability, sizeof(ability));
}