#include "main.h"

static struct feature_info {
	const char*	id;
	const char*	name;
} feature_data[] = {{"Tome", ""},
{"PhysicalWeapon", "��� ���������� ������. "},
{"MagicalWeapon", "��� ��������� ������. "},
{"CantStealOrLoose", "���� ������� ������ ��������, ���� �� ����� �� ������ � ����� ��� ������ �������. "},
{"CombatBonusTwoHand", "+1 � ������, ���� ������������ � ���� �����. "},
{"ExhaustToRerollDie", "��������� ����� ����������� ��� ������ � ������. "},
{"ExhaustToEffect", "����� ��������� ������ ���������� �����������. "},
{"CombatBonusVsUndead", "���� +2 � ������ ���� ������������ ������ �������. "},
{"DiscardAfterUse", "������������ ����� �������������. "},
{"SixDoubleSuccess", "������ \"6\" � ���������� ������ ���� ��� ������. "},
{"AutoCombatCheck", "������������� �������� ������ ������. "},
{"AutoGateCheck", "������������ �������� ������ ����. "},
{"OneHanded", "�������� 1 ����. "},
{"TwoHanded", "�������� 2 ����. "},
};
assert_enum(feature, TwoHanded);
getstr_enum(feature)