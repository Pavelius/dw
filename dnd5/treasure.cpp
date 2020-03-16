#include "main.h"

static magici potion_of_healing[] = {{CureWounds, Common, "лечения", 1, 2},
{CureWounds, Uncommon, "большого лечения", 2, 4},
{CureWounds, Rare, "отличного лечения", 4, 8},
{CureWounds, VeryRare, "превосходного лечения", 5, 10},
};

static rewardi table_a[] = {{50, PotionBlue, CureWounds, 0},
{60, Scroll0},
{70, PotionBlue},
{90, Scroll1},
{94, Scroll2},
{98, PotionBlue, CureWounds, 1},
{99}, // Сумка хранения
{100}, // Парящая сфера
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