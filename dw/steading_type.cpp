#include "main.h"

BSDATA(steading_typei) = {
	{"Village", "Деревня", Poor, Steady, Militia},
	{"Town", "Поселок", Moderate, Steady, Watch},
	{"Keep", "Крепость", Poor, Shrinking, Guard},
	{"City", "Город", Moderate, Steady, Guard},
};
assert_enum(steading_typei, City)