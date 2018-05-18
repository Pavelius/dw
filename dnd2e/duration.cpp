#include "main.h"

struct duration_i {
	duration_s		id;
	unsigned		base;
	unsigned		increment;
	unsigned		level_divider;
	unsigned		increment_dice;
	dice			increment_range;
} duration_data[] = {
	{Instantaneous},
	{Concetration},
	{Duration1Round, RRound},
	{Duration1RoundPerLevel, 0, RRound, 1},
	{Duration1RoundPerLevelPlus1, RRound, RRound, 1},
	{Duration1RoundPerLevelPlus2, 2 * RRound, RRound, 1},
	{Duration1RoundPerLevelPlus3, 3 * RRound, RRound, 1},
	{Duration1RoundPerLevelPlus1d3, 0, RRound, 1, RRound, {1, 3}},
	{Duration1RoundPerLevelPlus1d4, 0, RRound, 1, RRound, {1, 4}},
	{Duration1d10Rounds, 0, 0, 0, RRound, {1, 10}},
	{Duration2d20Rounds, 0, 0, 0, RRound, {2, 20}},
	{Duration2RoundPerLevel, 0, 2 * RRound, 1},
	{Duration2RoundPlus1RoundPerLevel, 2 * RRound, RRound, 1},
	{Duration4RoundPlus1RoundPerLevel, 4 * RRound, RRound, 1},
	{Duration5RoundPerLevel, 0, 5*RRound, 1},
	{Duration6Round, 6* RRound},
	{Duration1Turn, RTurn},
	{Duration1TurnPerLevel, 0, RTurn, 1},
	{Duration1TurnPlus1Per2Level, RTurn, RTurn, 2},
	{Duration3Turn, 3 * RTurn},
	{Duration5Turn, 5 * RTurn},
	{Duration6Turn, 6 * RTurn},
	{Duration6TurnPlus1PerLevel, 6 * RTurn, RTurn, 1},
	{Duration4Hours, 4 * RHour},
	{Duration10Hours, 10 * RHour},
	{Duration1DayPerLevel, 0, RDay, 1},
	{Duration1Month, RMonth},
	{Permanent, 500*RYear},
};
assert_enum(duration, Permanent);

unsigned game::get(duration_s id, int level) {
	auto& e = duration_data[id];
	auto result = e.base;
	if(e.level_divider)
		result += e.increment * (level / e.level_divider);
	if(e.increment_dice)
		result += e.increment_dice * e.increment_range.roll();
	return result;
}