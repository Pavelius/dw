#include "main.h"

static struct landscape_i {
	const char* id;
	const char* name;
	wise_s		wise;
} landscape_data[] = {{""},
{"Coast", "Побережье", CoastWise},
{"Forest", "Лес", ForestWise},
{"Lake", "Озеро", LakeWise},
{"Rocks", "Скалистая местность", RockyTerrainWise},
{"Swamp", "Болото", SwampWise},
{"TallGrass", "Высокая трава", TallGrassWise},
};
assert_enum(landscape, TallGrass);
getstr_enum(landscape);

bool hero::ismatch(landscape_s id, wise_s wise) {
	if(!id)
		return false;
	return landscape_data[id].wise == wise;
}