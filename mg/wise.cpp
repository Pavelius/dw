#include "main.h"

BSDATA(wisei) = {{"Birds-wise", "����� ������� ����", Animal},
{"Burrow-wise", "����� ������� ���������", Animal},
{"Mammal-wise", "����� ���������������", Animal},
{"Predator-wise", "����� ��������", Animal},
//
{"Coast-wise", "����� ���������", Coast},
{"Forest-wise", "����� ����", Forest},
{"Lake-wise", "����� �����", Lake},
{"Rocky terrain-wise", "����� ���� � �����", Rocks},
{"Swamp-wise", "����� ������", Swamp},
{"Tall grass-wise", "����� ������� �����", TallGrass},
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
{"Barkstone-wise", "����� ����������", Barkstone},
{"Cooperwood-wise", "����� �����������", Cooperwood},
{"Drakheather-wise", "����� ������ �������"},
{"Elmoss-wise", "����� �������", Elmoss},
{"Ivydale-wise", "����� �����������", Ivydale},
{"Lockhaven-wise", "����� ��������", Lockhaven},
{"Port Sumac-wise", "����� ���� �������", PortSumac},
{"Shaleburrow-wise", "����� ����������", Shaleburrow},
{"Sprucetuck-wise", "����� ������", Sprucetuck},
};
assert_enum(wisei, LastWise)