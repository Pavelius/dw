#include "main.h"

static struct talent_info {
	const char*			id;
	const char*			name;
} talent_data[] = {{"Adaptible", "����������"},
{"InnerPeace", "��������� �����������"},
{"PsychicPower", "����������� ����"},
{"TrueGrit", "�������� ��������"},
{"HardToCatch", "������ �������"},
{"HuntingInstinct", "��������� ��������"},
{"Unbreakable", "����������"},
{"Sneaky", "��������"},
//
{"PathOfHealing", "���� ��������"},
{"PathOfShiftingShapes", "���� ��������"},
{"PathOfSight", "���� �����������"},
{"PathOfBlade", "���� ����"},
{"PathOfShield", "���� ����"},
{"PathOfArrow", "���� ������"},
{"PathOfBeast", "���� ������"},
{"PathOfForest", "���� ����"},
{"PathOfHymn", "���� �����"},
{"PathOfSong", "���� �����"},
{"PathOfWarcry", "���� ������� �����"},
{"PathOfGold", "���� ������"},
{"PathOfLies", "���� ���"},
{"PathOfManyThings", "���� ������ �����"},
{"PathOfCompanion", "���� �����������"},
{"PathOfKnight", "���� ������"},
{"PathOfPlains", "���� ������"},
{"PathOfFace", "���� ������ ���"},
{"PathOfKiller", "���� ������"},
{"PathOfPoison", "���� ���"},
{"PathOfBlood", "���� �����"},
{"PathOfDeath", "���� ������"},
{"PathOfSigns", "���� ������"},
{"PathOfStone", "���� �����"},
//
{"Ambidexterous", "��������� ����� ������"},
{"AxeFighter", "���� � �������"},
{"Berserker", "���������"},
{"Bowyer", "�������"},
{"Brawler", "������"},
{"Builder", "���������"},
{"Chef", "�����"},
{"ColdBlooded", "�������������"},
{"Defender", "��������"},
{"Dragonslayer", "������ ��������"},
{"Executioner", "�����"},
{"FastFootwork", "������� ������ ���"},
{"FastShooter", "������� �������"},
{"Fearless", "�����������"},
{"FirmGrip", "������� ������"},
{"Fisher", "�����"},
{"HammerFighter", "���� � �������"},
{"Herbalist", "�������"},
{"HorsebackFighter", "������ ����"},
{"Incorruptible", "�����������"},
{"KnifeFighter", "���� �� �����"},
{"LightingFast", "����������"},
{"Lockpicker", "��������"},
{"Lucky", "���������"},
{"MasterOfTheHunt", "������ �����"},
{"MeleeCharge", "����� � �������"},
{"PackRat", "������ ��������"},
{"PathFinder", "������������"},
{"Poisoner", "������ ����"},
{"QuarterMaster", "������ �������"},
{"QuickDraw", "������� ������������"},
{"Sailor", "�����"},
{"Sharpshooter", "������ �������"},
{"SharpTongue", "������ ����"},
{"ShieldFighter", "���� � �����"},
{"SixthSense", "������ �������"},
{"Smith", "������"},
{"SpearFighter", "���� � ������"},
{"SteadyFeet", "���������� ����"},
{"SwordFighter", "���� �� �����"},
{"Tailor", "�������"},
{"Tanner", "���������"},
{"Threatening", "����������"},
{"ThrowingArm", "���������� ����"},
{"Wanderer", "��������������"},
};
getstr_enum(talent);
assert_enum(talent, Wanderer);