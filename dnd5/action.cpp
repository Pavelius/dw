#include "main.h"

actioni bsmeta<actioni>::elements[] = {{"MakeAttack", "��������� �����"},
{"ChangeWeapon", "������� ������"},
{"Dash", "����� ������"},
{"Dodge", "���������� �� ������ �����"},
{"Disengage", "�������������, ��������� �� ������"},
{"Hide", "���������� ����������"},
{"Help", "������ ��������"},
{"Search", "�������� ��� �����"},
{"StandUp", "��������� �� ����"},
};

action_s actioni::getid() const {
	return action_s(this - bsmeta<actioni>::elements);
}