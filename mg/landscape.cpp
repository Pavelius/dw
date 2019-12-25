#include "main.h"

template<> landscapei bsmeta<landscapei>::elements[] = {{""},
{"Coast", "���������", CoastWise},
{"Forest", "���", ForestWise},
{"Lake", "�����", LakeWise},
{"Rocks", "��������� ���������", RockyTerrainWise},
{"Swamp", "������", SwampWise},
{"TallGrass", "������� �����", TallGrassWise},
};
assert_enum(landscape, TallGrass);

bool hero::ismatch(landscape_s id, wise_s wise) {
	if(!id)
		return false;
	return bsmeta<landscapei>::elements[id].wise == wise;
}