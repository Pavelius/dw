#include "archive.h"
#include "logs.h"

#pragma once

using namespace logs;

enum distance_s : unsigned char {
	Hand, Close, Reach, Near, Far,
};
enum famlity_stat_s : unsigned char {
	Reach, Grasp, Sleight,
	Mood, Tech, Data,
};
enum stat_s : unsigned char {
};