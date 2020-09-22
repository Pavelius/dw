#include "main.h"

BSDATA(landscapei) = {{""},
{"Coast", "Побережье", CoastWise},
{"Forest", "Лес", ForestWise},
{"Lake", "Озеро", LakeWise},
{"Rocks", "Скалистая местность", RockyTerrainWise},
{"Swamp", "Болото", SwampWise},
{"TallGrass", "Высокая трава", TallGrassWise},
};
assert_enum(landscapei, TallGrass)

bool hero::ismatch(landscape_s id, wise_s wise) {
	if(!id)
		return false;
	return bsdata<landscapei>::elements[id].wise == wise;
}