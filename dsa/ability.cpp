#include "main.h"

abilityi bsmeta<abilityi>::elements[] = {{"Courage", "��������"},
{"Wisdom", "��������"},
{"Charisma", "�������"},
{"Dexterity", "��������"},
{"Strenght", "����"},
//
{"LP", "��������� �������", "LE"},
{"AP", "���������� �������", "AE"},
{"AV", "�����", "�V"},
{"PV", "�����������", "PV"},
{"PVC", "���������� ����", "���"},
{"RS", "�����", "��"},
{"Level", "�������", "��"},
};
assert_enum(ability, Level);

const char* getsnm(ability_s id) {
	return bsmeta<abilityi>::elements[id].short_name;
}