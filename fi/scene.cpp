#include "main.h"

struct scene_info {
	const char*		name;
	const char*		text;
	zone_kind_s		kind;
};
static scene_info scene_data[] = {{"����� ������", "�� ���������� � ������ ������. ������ ��� ���������� ��������� ����� � �������� �������."},
};

int	scene::getplayercount() const {
	auto result = 0;
	for(auto p : players) {
		if(p)
			result++;
	}
	return result;
}