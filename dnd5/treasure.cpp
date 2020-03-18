#include "main.h"

static rewardi table_a[] = {{50, Potion, CureWounds, 1, 2},
{60, Scroll0},
{70, Potion, SpiderClimb, 1},
{90, Scroll1},
{94, Scroll2},
{98, Potion, CureWounds, 2, 4},
{99, Bag, Strenght, 4}, // Сумка хранения
{100, Sphere, Light, 1}, // Парящая сфера
};
static rewardi table_b[] = {{36},
};
static rewardi table_v[] = {{36},
};
static rewardi table_e[] = {{36},
};
static rewardi table_ee[] = {{36},
};

static trepacki reward_1_4[] = {{36},
{60, table_a, {1, 6}},
{75, table_b, {1, 4}},
{85, table_v, {1, 4}},
{97, table_e, {1, 4}},
{100, table_ee, {1}},
{101},
};