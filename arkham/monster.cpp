#include "main.h"

struct monster_info {
	const char*		id;
	const char*		name;
	monster_color_s	color;
	char			deck_count;
	char			awareness;
	char			horror[2];
	char			toughness;
	char			combat[2];
	cflags<monster_flag_s> flags;
	const char*		text;
} monster_data[] = {{"Byakhee", "Бьякхи", Flying, 3, -2, {-1, 1}, 1, {0, 2}, {}, "Внезапно в ночи послышался шум крыльев. Вы подняли голову и увидели страшное чудовище - человекообразое с серой кожей и огромными крыльями."},
{"Chthonian", "Чхониан", Unique, 2, 1, {-2, 2}, 3, {-3, 3}},
{"Cultist", "Культист", Normal, 6, -3, {0, 0}, 1, {1, 1}},
{"Dark Young", "Темная молодь", Stationary, 3, -2, {0, 3}, 3, {-1, 3}, {PhysicalResistance, NightmarishI}},
{"Dhole", "", Normal, 1, -1, {-1, 4}, 3, {-3, 4}, {PhysicalResistance, MagicalResistance, OvervelmingI, NightmarishI}},
{"Dimension Shambler", "", Fast, 2, -3, {-2, 1}, 1, {-2, 0}},
{"Elder Thing", "", Normal, 2, -2, {-3, 2}, 2, {0, 1}},
{"Fire Vampire", "", Flying, 2, 0, {0, 0}, 1, {-2, 2}, {Ambush, PhysicalResistance}},
{"Zombie", "Зобми", Normal, 2, 1, {-2, 2}, 3, {-3, 3}, {Undead}, "Впереди показалая фигура человека. Она очень быстро приблежалась к вам выставив вперед руки. Глаза горели неестественным цветом - похоже это оживший зомби."},
};
assert_enum(monster, Zombie);
getstr_enum(monster);

static struct monstercup : adat<monster_s, 128> {

	void initialize() {
		clear();
		for(auto& e : monster_data) {
			auto id = monster_s(&e - monster_data);
			for(auto i = 0; i < e.deck_count; i++)
				add(id);
		}
		zshuffle(data, count);
	}

} monstercups;

char monster::get(stat_s id) {
	switch(id) {
	case EvadeCheck: return monster_data[type].awareness;
	case HorrorCheck: return monster_data[type].horror[0];
	case Sanity: return monster_data[type].horror[1];
	case CombatCheck: return monster_data[type].combat[0];
	case Stamina: return monster_data[type].combat[1];
	case Fight: return monster_data[type].toughness;
	default: return 0;
	}
}

bool monster::is(monster_flag_s id) const {
	return monster_data[type].flags.is(id);
}

const char* monster::getname() const {
	return monster_data[type].name;
}

const char* monster::gettext() const {
	return monster_data[type].text;
}