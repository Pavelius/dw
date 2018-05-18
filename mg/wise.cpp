#include "main.h"

static struct wise_info {
	const char*		id;
	const char*		name;
} wise_data[] = {{"Birds-wise", "����� ������� ����"},
{"Burrow-wise", "����� ������� ���������"},
{"Mammal-wise", "����� ���������������"},
{"Predator-wise", "����� ��������"},
//
{"Coast-wise", "����� ���������"},
{"Forest-wise", "����� ����"},
{"Lake-wise", "����� �����"},
{"Rocky terrain-wise", "����� ���� � �����"},
{"Swamp-wise", "����� ������"},
{"Tall grass-wise", "����� ������� �����"},
//
{"Craft-wise", "����� ��� � �������"},
{"Crime-wise", "����� ������������"},
{"Governor-wise", "����� ������������"},
{"Guardmouse-wise", "����� ����������"},
//
{"Rain-wise", "����� ��� � ������"},
{"Calm weather-wise", "����� ��� � ������� ������"},
{"Snow-wise", "����� ��� � ���������"},
//
{"Barkstone-wise", "����� ����������"},
{"Cooperwood-wise", "����� �����������"},
{"Drakheather-wise", "����� ������ �������"},
{"Elmoss-wise", "����� �������"},
{"Ivydale-wise", "����� �����������"},
{"Lockhaven-wise", "����� ��������"},
{"Port Sumac-wise", "����� ���� �������"},
{"Shaleburrow-wise", "����� ����������"},
{"Sprucetuck-wise", "����� ������"},
};
assert_enum(wise, LastWise);
getstr_enum(wise);