#include "main.h"

BSDATA(steading_typei) = {
	{"Village", "�������", Poor, Steady, Militia},
	{"Town", "�������", Moderate, Steady, Watch},
	{"Keep", "��������", Poor, Shrinking, Guard},
	{"City", "�����", Moderate, Steady, Guard},
};
assert_enum(steading_typei, City)