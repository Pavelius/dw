#include "main.h"

seasoni bsmeta<seasoni>::elements[] = {{"Spring", "�����", 6},
{"Summer", "����", 4},
{"Autum", "�����", 5},
{"Winter", "����", 7},
};
assert_enum(season, Winter);

int hero::getobstacle(season_s v) {
	return bsmeta<seasoni>::elements[v].obstacle;
}