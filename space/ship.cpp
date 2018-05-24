#include "main.h"

static ship ship_data[] = {{"dragonfly", "Стрекоза", Diminutive, {100}, 0, 4, 0, 1, 0, {Laser}},
{"falcon", "Ястреб", Diminutive, {95}, 1, 4, 0, 1, 0, {Laser}},
{"mouse", "Мышь", Small, {200},  0, 3, 0, 2, 1, {ShrapnelCannon}},
{"eagle", "Орел", Small, {220}, 1, 3, 1, 3, 2, {Laser, Laser, ShrapnelCannon}, {EngeneeringBay}},
};

static ship& findship(const char* id) {
	for(auto& e : ship_data) {
		if(strcmp(e.id, id) == 0)
			return e;
	}
	return ship_data[0];
}

void ship::act(const char* format, ...) const {
	stringcreator sc;
	logs::addv(sc, format, xva_start(format));
}

spaceship::spaceship(const char* id) : ship(findship(id)) {
	*((status*)this) = stat;
}

spaceship::spaceship() {
}