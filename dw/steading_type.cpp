#include "main.h"

template<> steading_typei bsmeta<steading_typei>::elements[] = {
	{"Village", "Деревня", Poor, Steady, Militia},
	{"Town", "Поселок", Moderate, Steady, Watch},
	{"Keep", "Крепость", Poor, Shrinking, Guard},
	{"City", "Город", Moderate, Steady, Guard},
};
assert_enum(steading_type, City);