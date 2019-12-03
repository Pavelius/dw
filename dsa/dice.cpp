#include "main.h"

dicei bsmeta<dicei>::elements[] = {{1,6,-4},
{1, 6, -3}, {1, 6, -2}, {1, 6, -1},
{1, 6}, {1, 6, 1}, {1, 6, 2}, {1, 6, 3}, {1, 6, 4},
{2, 6}, {2, 6, 1}, {2, 6, 2}, {2, 6, 3}, {2, 6, 4},
{3, 6}
};
assert_enum(dice, W3p0);

int dicei::roll() const {
	if(!c)
		return b;
	auto r = b;
	for(int i = 0; i < c; i++)
		r += rand() % d + 1;
	return r;
}