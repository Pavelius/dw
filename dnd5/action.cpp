#include "main.h"

actioni bsmeta<actioni>::elements[] = {{"MakeAttack", "��������� �����", {NeedHostile}, "��������� ����"},
{"ChangeWeapon", "������� ������"},
{"Dash", "����� ������"},
{"Dodge", "���������� �� ������ �����"},
{"Disengage", "�������������, ��������� �� ������"},
{"Hide", "���������� ����������"},
{"Help", "������ ��������", {NeedFriendly}, "���� ������ ������?"},
{"Search", "�������� ��� �����"},
{"StandUp", "��������� �� ����"},
};
assert_enum(action, StandUp);

action_s actioni::getid() const {
	return action_s(this - bsmeta<actioni>::elements);
}