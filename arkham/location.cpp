#include "main.h"

location location_data[Yuggoth + 1] = {{"Lost in Time and Space", "���������� �� ������� � ������������"},
{"Administration Building", "������ �������������", "� ���������������� ������ ������������ ������ ��������� �������������� � �����������, ������� ��������� ���� ������� ���������.", {MiskatonicUniversity}},
{"Arkham Asylum", "��������� �������", "� ������ ��������� ������� ���� ������ � ���� ��������� �������. ����� �� ������� ��������� ����� ������� ����� �������. ���������������� ����������� ������� �������� ���, �������� ��������� ������� ��������������.", {Downtown}},
{"Bank of Arkham", "���� �������", "", {Downtown}},
{"Black Cave", "������ ������"},
{"Curiositie Shoppe", "������� ���������� �����", "", {Northside}},
{"GeneralStore", "�������", "� �������� ���������� �������� �����, �� ������� ������ ����� ������������� ������. ���� ��� ��� ���������� ����������� ��������, ��� ��� ����� ������.", {Rivertown}},
{"Graveyard", "��������", "�� ������ �� ��������� �������� ����� ������ �����. ������������, ��� ����� ������� ����� ������� ������ ��� ���������� ����� � � ����� �������� ������� ��������� �������� �������.", {Rivertown}},
{"HibbsRoadhouse", "����������� ������", "����� ���� �����, ���� ������ � ����� � ���� �����. � ������� ���������� ���������� ����� ������������� ����� � ������.", {Easttown}},
{"HistoricalSociety", "������������ ��������"},
{"IndependenceSquare", "������� �������������"},
{"Library", "����������", "", {MiskatonicUniversity}},
{"MasBoardingHouse", ""},
{"Newspaper", "���� ������", "", {Northside}},
{"PoliceStation", "����������� �������", "� ����������� ������� ������ ������� �����. �������� ����� � ����� �������� ������ ������.", {Easttown}},
{"RiverDocks", "����"},
{"ScienceBuilding", "�����������", "", {MiskatonicUniversity}},
{"SilverTwilightLodge", ""},
{"SouthChurch", "����� �������"},
{"StMarysHospital", "��������� ������ �����", "� �������� ���� ����� � ��������. ����� ����� � ������� ��� ����� ��������� ������ ����������� � �������� ����������."},
{"TheUnnamable", ""},
{"TheWitchHouse", ""},
{"TrainStation", "������", "�� ������� ���� ��������� �����. ���������� ����� �������� ���� ����.", {Northside}},
{"UnvisitedIsle", "��������� ������"},
{"VelmasDiner", "���������� \"� �����\"", "� ������ ���� ���������� �����, ����� ������� ���� � ������ ����. ���� ������ ������ �� ������ ������ � ��������� �������������� ���.", {Easttown}},
{"Woods", "����"},
{"YeOldeMagickShoppe", "������� �����"},
//
{"Easttown", "��������� �����", "��������� ������� ��������� �� �������� ������ ���� �������. ����� ���� ���� ���������, ��� ����� �������� ����� ��� ������, � ����� ����������� �������.", {HibbsRoadhouse, VelmasDiner, PoliceStation, Downtown, Rivertown}},
{"Downtown", "������ �����", "������ ����� ��������� � ������. ��������� ���� � ��� ����� �������� ��� ������� �����.", {BankOfArkham, ArkhamAsylum, IndependenceSquare, Northside, MerchantDistrict, Easttown}},
{"FrenchHill", "���������� �����", "���������� ����� ���������� �� �������������. ������� ���� � ���� ������� �������� ���������� �����. ���� � �������� ��������� ����� ���� �������� ������� ������ �� ���.", {TheWitchHouse, SilverTwilightLodge, Rivertown, SouthSide}},
{"MerchantDistrict", "�������� �����", "� �������� ������ ������ ��� ���������� ����������� ����. ����� ��� ���� ��������� ����������� ������ � �������. �� ������ ���������� ��������� ����, � ������� ������������ ����� ��������� �� ����. ������� ������������ �������� �� ���.", {RiverDocks, UnvisitedIsle, TheUnnamable, Northside, Downtown, MiskatonicUniversity, Rivertown}},
{"Miskatonic University", "�������������� �����������", "�� ���������� ���������� ������������ ����������� ������������� ��������. ��������, ���� ����������, �� � �� ��������� ���� ����� ��������.", {Library, ScienceBuilding, AdministrationBuilding, MerchantDistrict, Uptown, FrenchHill}},
{"Northside", "�������� �����", "� �������� ����� ������� ���������� ������������ ����. ��������� ������ ���� ������������� � ��������� ���� ��� ���� ������� �����. �� ������� ��������� ������, � �������� ������ ������.", {TrainStation, Newspaper, CuriositieShoppe, MerchantDistrict, Downtown}},
{"Rivertown", "������ �����", "������ ����� ��������� �� ����� ������ ����� �� ��������� ������� ������. ����� ���������� ��������� ��������� � ��������� ��������. �� ������� ��������� ������� �����.", {BlackCave, Graveyard, GeneralStore, Easttown, FrenchHill}},
{"SouthSide", "����� �����", "����� ����� ��������� �������� ������������. ����� ���������� ��������� ������������ ������� � ��������� ������ ������������� ����������.", {MasBoardingHouse, SouthChurch, HistoricalSociety, FrenchHill, Uptown}},
{"Uptown", "������� �����", "������� ����� ��������� �� ����� ������� ������ �� ������������ � ���������� ������ � �����, ������� ������� ������ �� ����� �� ��.", {YeOldeMagickShoppe, StMarysHospital, Woods, MiskatonicUniversity, SouthSide}},
//
{"Abyss", "����������", "������ ��� ���� ������� �������� �������. ����� �������� �����, ���-�� � ������ �� ������ ����������� ������� ����. ���-��� �������� �������, � ������� ���������� ����. ��� ���� ����� ��������� ����������."},
{"AnotherDimension", "������ ���������", ""},
{"CityOfTheGreatRace", "����� ���������� ����", ""},
{"GreatHallOfCeleano", "���������� ���� ������", ""},
{"PlateauOfLeng", "����� ����", ""},
{"Rlyeh", "�����", ""},
{"TheDreamlands", "������ ����", ""},
{"Yuggoth", "�����", ""},
};
assert_enum(location, Yuggoth);
getstr_enum(location);