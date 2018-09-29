#include "main.h"

static struct feat_info {
	const char*			id;
	const char*			name;
	slot_s				slot;
} feat_data[] = {{"No feat", "��� �����������"},
{"Armor Proficiency (light)", "������� ������ �����"},
{"Armor Proficiency (medium)", "������� ������� �����"},
{"Armor Proficiency (heavy)", "������� ������� �����"},
{"Shield Proficiency", "�������� �����"},
{"Simple weapon proficiency", "�������� ������� �������"},
{"Martial weapon proficiency", "�������� ����������� �������"},
{"Elf weapon training", "���������� � ������� ������"},
{"Dwarven weapon training", "���������� � ������� ��������"},
{"Rogue weapon training", "���������� � ������� ������"},
{"Save Strenght", "����-������ �� ����"},
{"Save Dexterity", "����-������ �� ��������"},
{"Save Constitution", "����-������ �� ������������"},
{"Save Intellegence", "����-������ �� ����������"},
{"Save Wisdow", "����-������ �� ��������"},
{"Save Charisma", "����-������ �� �������"},
//
{"Brave", "���������"},
{"Darkvision", "�����������"},
{"Dwarven Resilience", "������������ ��������"},
{"Dwarven Toughness", "��������� ��������"},
{"Fey Ancestry", "����������� ������"},
{"Keen Sences", "����������� �������"},
{"Lucky", "�������"},
{"Mask of the Wild", "����� �������"},
{"Naturally Stealthy", "���������� ����������"},
{"Stonecunning", "��������� �����"},
{"Trance", "�����"},
// ��������� ����������� �����
{"Second Wind", "������ �������", SecondWindSlot},
{"Action Surge", "���������", ActionSurgeSlot},
{"Extra Attack", "�������������� �����"},
{"Indomitable", "����������", IndomitableSlot},
{"Improved Critical", "���������� �����������"},
{"Remarkable Athlete", "���������� �����"},
{"Superior Critical", "���������� �����������"},
{"Survivor", "������� ������"},
// ��������� ����������� �������
{"Channel Divinity", "������� ��������", ChannelDivinitySlot},
{"Destroy Undead", "����������� �������"},
{"Divine Intervention", "������������ ����"},
{"Disciple of Life", "������ �����"},
{"Blessed Healer", "��������� ��������"},
{"Divine Strike", "��������� ����"},
{"Supreme Healing", "������������ ���������"},
// ����� ���
{"Archery style", "����� �������"},
{"Defense style", "����� ������"},
{"Dueling style", "����� �������������"},
{"Great weapon fighting style", "����� �������� �������� �������"},
{"Protection style", "����� �������� � �����"},
{"Two-weapon fighting style", "����� �������� ����� ��������"},
};
assert_enum(feat, StyleTwoWeaponFighting);
getstr_enum(feat);