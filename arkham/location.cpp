#include "main.h"

location location_data[YeOldeMagickShoppe + 1] = {{"Lost in Time and Space", "���������� �� ������� � ������������"},
{"Administration Building", "������ �������������"},
{"Arkham Asylum", "��������� �������", "� ������ ��������� ������� ���� ������ � ���� ��������� �������. ����� �� ������� ��������� ����� ������� ����� �������. ���������������� ����������� ������� �������� ���, �������� ��������� ������� ��������������."},
{"Bank of Arkham", "���� �������"},
{"Black Cave", "������ ������"},
{"Curiositie Shoppe", "������� ���������� �����"},
{"GeneralStore", "�������"},
{"Graveyard", "��������"},
{"HibbsRoadhouse", "���������� ������"},
{"HistoricalSociety", "������������ ��������"},
{"IndependenceSquare", "������� �������������"},
{"Library", "����������"},
{"MasBoardingHouse", ""},
{"Newspaper", "���� ������"},
{"PoliceStation", "����������� �������"},
{"RiverDocks", "����"},
{"ScienceBuilding", "�����������"},
{"SilverTwilightLodge", ""},
{"SouthChurch", "����� �������"},
{"StMarysHospital", "��������� ������ �����"},
{"TheUnnamable", ""},
{"TheWitchHouse", ""},
{"TrainStation", "������"},
{"UnvisitedIsle", "��������� ������"},
{"VelmasDiner", ""},
{"Woods", "����"},
{"YeOldeMagickShoppe", "������� �����"},
};
assert_enum(location, YeOldeMagickShoppe);
getstr_enum(location);

