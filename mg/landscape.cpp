#include "main.h"

BSDATA(landscapei) = {{""},
{"Coast", "���������", CoastWise},
{"Forest", "���", ForestWise},
{"Lake", "�����", LakeWise},
{"Rocks", "��������� ���������", RockyTerrainWise},
{"Swamp", "������", SwampWise},
{"TallGrass", "������� �����", TallGrassWise},
};
assert_enum(landscapei, TallGrass)

bool hero::ismatch(landscape_s id, wise_s wise) {
	if(!id)
		return false;
	return bsdata<landscapei>::elements[id].wise == wise;
}