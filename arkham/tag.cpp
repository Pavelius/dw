#include "main.h"

static struct tag_info {
	const char*	id;
	const char*	name;
} tag_data[] = {{"Tome", ""},
{"PhysicalWeapon", "��� ���������� ������. "},
{"MagicalWeapon", "��� ��������� ������. "},
{"CantStealOrLoose", "���� ������� ������ ��������, ���� �� ����� �� ������ � ����� ��� ������ �������. "},
{"CombatBonusTwoHand", "+1 � ������, ���� ������������ � ���� �����. "},
{"ExhaustToRerollDie", "��������� ����� ����������� ��� ������ � ������. "},
{"ExhaustToEffect", "����� ��������� ������ ���������� �����������. "},
{"CombatBonusVsUndead", "���� +2 � ������ ���� ������������ ������ �������. "},
{"DiscardAfterUse", "������������ ����� �������������. "},
{"SixDoubleSuccess", "������ \"6\" � ���������� ������ ���� ��� ������. "},
{"MarkTokenToDiscard", "������. "},
};
assert_enum(tag, MarkTokenToDiscard);
getstr_enum(tag)