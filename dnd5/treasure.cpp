#include "main.h"

static magici potion_of_healing[] = {{CureWounds, Common, "�������", 1, 2},
{CureWounds, Uncommon, "�������� �������", 2, 4},
{CureWounds, Rare, "��������� �������", 4, 8},
{CureWounds, VeryRare, "������������� �������", 5, 10},
};

static rewardi table_a[] = {{50, PotionBlue, CureWounds, 0},
{60, ScrollOfBless},
{70, PotionBlue},
{90, ScrollOfBless},
{94, ScrollOfBless},
{98, PotionBlue, CureWounds, 1},
{99}, // ����� ��������
{100}, // ������� �����
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