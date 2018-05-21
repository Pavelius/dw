#include "main.h"

static struct nation_i
{
	const char*		name[2];
	trait_s			trait;
	sorcery_s		sorcery;
	swordsman_s		swordsman;
	const char*		text;
} nation_data[] = {
	{{"Avalon", "������"}, Resolve, Glamour, Donowan, "������� � ������������ �����. ������������ ����� ���� ���� ����������, ������� ����������� �� ��������� ��������� ��������."},
	{{"Castille", "��������"}, Finesse, NoSorcery, Aldana, "����-�������� ����������� ������. ��� ����������� ����� ������� ���� ��� �������� ����� �������, ������������ �� ��� � ������."},
	{{"Eisen", "�����"}, Brawn, NoSorcery, Eisenfaust, "������� ������ ������, �������� �������������� ����� �������������� ����� ������."},
	{{"Montaigne", "�������"}, Panache, Porte, Valroux, "���� �� ����� �������������� ����� ����, ������� ����� � �������� � ���������. ��� ����� ���������� ��� ����� ����������."},
	{{"Ussura", "������"}, Resolve, Pyeryem, NoSwordsman, "��������� � ����� ������, ���� ������� �� ��� ��� ����� ��� �� �������, ��� � �� ������ ����� ����� �����."},
	{{"Vendel", "�������"}, Wits, Laerdom, NoSwordsman, "���������� ��������, ����������� ����� ���������, ����������� ����� ��� �������� ��� ��������� ����, � ������������ ���������, ��������������� ���������� � �������."},
	{{"Vodacce", "�������"}, Wits, Sorte, NoSwordsman, "������ �������� �����������, ����������� ����� ����� ��������� ��������, ��� ���������� ������� ��������� ������, ���� ������ �������� ������ ����."},
	{{"Crescent", "����������"}, Wits, NoSorcery},
	{{"Hight Eisen", "������ ���������"}, Wits, NoSorcery},
	{{"Teodoran", "��������"}, Wits, NoSorcery},
	{{"Thean", "��������"}, Wits, NoSorcery}
};
assert_enum(nation, LastLanguage);
getstr_enum(nation);
getinf_enum(nation);

sorcery_s hero::getsorcery() const
{
	return nation_data[nation].sorcery;
}

swordsman_s hero::getswordsman() const
{
	return nation_data[nation].swordsman;
}

void hero::set(nation_s value)
{
	traits[nation_data[value].trait]++;
}