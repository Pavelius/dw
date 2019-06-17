#include "main.h"

static shipi ship_data[] = {{"dragonfly", "Стрекоза", Diminutive, {100}, 0, 4, 0, 1, 0, {Laser}},
{"falcon", "Ястреб", Diminutive, {95}, 1, 4, 0, 1, 0, {Laser}},
{"mouse", "Мышь", Small, {200},  0, 3, 0, 2, 1, {ShrapnelCannon}},
{"eagle", "Орел", Small, {220}, 1, 3, 1, 3, 2, {Laser, Laser, ShrapnelCannon}, {EngeneeringBay}},
};

static shipi& findship(const char* id) {
	for(auto& e : ship_data) {
		if(strcmp(e.id, id) == 0)
			return e;
	}
	return ship_data[0];
}

void shipi::act(const char* format, ...) const {
	//logs::driver sc();
	//sc.gender = Male;
	//sc.name = name;
	//logs::addv(sc, format, xva_start(format));
}

spaceship::spaceship(const char* id) : shipi(findship(id)) {
	hits = model.hits_maximum;
	hits_maximum = model.hits_maximum;
}

spaceship::spaceship() {
}