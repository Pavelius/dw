#include "main.h"

abilityi bsmeta<abilityi>::elements[] = {{"Courage", "��������", "MU"},
{"Wisdom", "��������"},
{"Charisma", "�������", "CH"},
{"Dexterity", "��������"},
{"Strenght", "����", "KK"},
//
{"LP", "��������� �������", "LE"},
{"AP", "���������� �������", "AE"},
{"AV", "�����", "�V"},
{"PV", "�����������", "PV"},
{"PVC", "���������� ����", "���"},
{"RS", "�����", "RS"},
{"Level", "�������", "LV"},
};
assert_enum(ability, Level);

const char* getsnm(ability_s id) {
	return bsmeta<abilityi>::elements[id].short_name;
}