#include "main.h"

template<> landscapei bsmeta<landscapei>::elements[] = {{""},
{"Coast", "Побережье", CoastWise},
{"Forest", "Лес", ForestWise},
{"Lake", "Озеро", LakeWise},
{"Rocks", "Скалистая местность", RockyTerrainWise},
{"Swamp", "Болото", SwampWise},
{"TallGrass", "Высокая трава", TallGrassWise},
};
assert_enum(landscape, TallGrass);

bool hero::ismatch(landscape_s id, wise_s wise) {
	if(!id)
		return false;
	return bsmeta<landscapei>::elements[id].wise == wise;
}