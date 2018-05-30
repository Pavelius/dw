#include "main.h"

struct monster_i {
	const char*		id;
	const char*		name;
	char			count;
	char			awareness;
	char			horror[2];
	char			toughness;
	char			combat[2];
	cflags<monster_flag_s> flags;
	const char*		text;
} monster_data[] = {{"Byakhee", "Бьякхи", 3, -2, {-1, 1}, 1, {0, 2}, {}, "Внезапно в ночи послышался шум крыльев. Вы подняли голову и увидели страшное чудовище - человекообразое с серой кожей и огромными крыльями."},
{"Chthonian", "Чхониан"},
{"Zombie", "Зобми", 2, 1, {-2, 2}, 3, {-3, 3}, {Undead}, "Впереди показалая фигура человека. Она очень быстро приблежалась к вам выставив вперед руки. Глаза горели неестественным цветом - похоже это оживший зомби."},
};
assert_enum(monster, Zombie);
getstr_enum(monster);

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