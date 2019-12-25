#include "main.h"

seasoni bsmeta<seasoni>::elements[] = {{"Spring", "Весна", 6},
{"Summer", "Лето", 4},
{"Autum", "Осень", 5},
{"Winter", "Зима", 7},
};
assert_enum(season, Winter);

int hero::getobstacle(season_s v) {
	return bsmeta<seasoni>::elements[v].obstacle;
}