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
{"AutoCombatCheck", "������������� �������� ������ ������. "},
{"AutoGateCheck", "������������ �������� ������ ����. "},
{"OneHanded", "�������� 1 ����. "},
{"TwoHanded", "�������� 2 ����. "},
};
assert_enum(tag, TwoHanded);
getstr_enum(tag)