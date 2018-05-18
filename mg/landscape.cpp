#include "main.h"

static struct landscape_i {
	const char* id;
	const char* name;
	wise_s		wise;
} landscape_data[] = {{""},
{"Coast", "���������", CoastWise},
{"Forest", "���", ForestWise},
{"Lake", "�����", LakeWise},
{"Rocks", "��������� ���������", RockyTerrainWise},
{"Swamp", "������", SwampWise},
{"TallGrass", "������� �����", TallGrassWise},
};
assert_enum(landscape, TallGrass);
getstr_enum(landscape);

bool hero::ismatch(landscape_s id, wise_s wise) {
	if(!id)
		return false;
	return landscape_data[id].wise == wise;
}