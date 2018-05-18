#include "main.h"

static struct experience_info {
	short		base;
	short		per_hp;
	short		special;
	short		exceprion;
} experience_data[] = {
	{5, 1, 2, 25},
	{10, 1, 4, 35},
	{20, 2, 8, 45},
	{35, 3, 15, 55},
};

int character::getcostexp() const {
	auto i = getHD();
	auto& e = maptbl(experience_data, i);
	auto result = e.base;
	result += e.per_hp*getmaxhp();
	return result;
}