#include "main.h"

template<> steading_typei bsmeta<steading_typei>::elements[] = {
	{"Village", "�������", Poor, Steady, Militia},
	{"Town", "�������", Moderate, Steady, Watch},
	{"Keep", "��������", Poor, Shrinking, Guard},
	{"City", "�����", Moderate, Steady, Guard},
};
assert_enum(steading_type, City);