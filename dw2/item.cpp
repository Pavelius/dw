#include "main.h"

const itemi bsmeta<itemi>::elements[] = {{"Empthy", "�����"},
// ������
{"RaggedBow", "����������� ���", 15, Moderate, Weapons, {Weight2, Near}, NoItem, Arrows},
{"FineBow", "������� ���", 60, Wealthy, Weapons, {Weight2, Near, Far}, NoItem, Arrows},
{"HuntersBow", "��������� ���", 100, Wealthy, Weapons, {Weight1, Near, Far}, NoItem, Arrows},
{"Crossbow", "�������", 35, Rich, Weapons, {Weight1, Weight2, Near, DamageP1, Reloaded}},
{"BundleOfArrows", "������", 1, Moderate, Weapons, {Weight1, Ammo1, Ammo2}, Arrows},
{"ElvenArrows", "���������� ������", 20, Rich, Weapons, {Weight1, Ammo4}, Arrows},
{"Club", "�������", 1, Moderate, Weapons, {Weight2, Close}},
{"Staff", "�����", 1, Moderate, Weapons, {Weight1, Close, TwoHanded}},
{"Knife", "���", 2, Moderate, Weapons, {Weight1, Hand}},
{"ThrowingDagger", "����������� ���", 2, Moderate, Weapons, {Thrown, Near}},
{"ShortSword", "�������� ���", 8, Moderate, Weapons, {Weight1, Close}},
{"Mace", "������", 8, Moderate, Weapons, {Weight1, Close}},
{"Warhammer", "�����", 8, Moderate, Weapons, {Weight1, Close}},
{"Spear", "�����", 5, Moderate, Weapons, {Weight1, Thrown, Reach, Near}},
{"LongSword", "������� ���", 15, Wealthy, Weapons, {Weight2, Close, DamageP1}},
{"Halberd", "��������", 9, Rich, Weapons, {Weight2, DamageP1, TwoHanded, Reach}},
{"Rapier", "������", 25, Wealthy, Weapons, {Precise, Close, Weight1}},
{"DuelingRapier", "������ �������", 50, Rich, Weapons, {Pierce1, Precise, Close, Weight2}},
//
{"FineClothing", "��������� ������", 10, Wealthy, Weapons, {}},
{"Leather", "�������� �����", 10, Moderate, Weapons, {Weight1, Armor1}},
{"Chainmail", "��������", 10, Wealthy, Weapons, {Weight1, Armor1}},
{"Scalemail", "���������� ������", 50, Wealthy, Weapons, {Weight1, Weight2, Clumsy, Armor2}},
{"Plate", "������ ������", 350, Rich, Weapons, {Weight4, Clumsy, Armor1, Armor2}},
{"Shield", "���", 15, Moderate, Weapons, {Weight2, ArmorP1}},
//
{"AdventuringGear", "���������� ��� �����������", 20, Poor, Tools, {Weight1, Use4, Use1}},
{"Bandages", "�����", 5, Poor, Tools, {Slow, Use2, Use1}},
{"Herbs", "����� � ��������", 10, Poor, Species, {Weight1, Slow, Use2}},
{"HealingPotion", "�������� �����", 50, Wealthy, Potions},
{"KegOfDwarvenStout", "������� ������������ ��������", 10, Rich, Species, {Weight4}},
{"BagOfBooks", "����� � �������", 10, Wealthy, Tools, {Weight2, Use4, Use1}},
{"Antitoxin", "����������", 10, Rich, Potions},
//
{"DungeonRation", "�������", 3, Poor, Foods, {Weight1, Ration, Use1, Use4}},
{"PersonalFeast", "�������� ���", 10, Wealthy, Foods, {Weight1, Ration, Use1}},
{"DwarvenHardtack", "������ �������", 3, Wealthy, Foods, {Weight1, Ration, Use1, Use4, Use2}},
{"ElvenBread", "���������� ����", 10, Wealthy, Foods, {Weight1, Ration, Use1, Use4, Use2}},
{"HalflingPipeleaf", "����� ��������", 5, Rich, Foods, {Ration, Use1}},
//
{"Mandoline", "���������", 40, Rich, Tools},
{"Lute", "�����", 40, Rich, Tools},
{"Pipes", "�������", 40, Rich, Tools},
//
{"HolySymbol", "������ ������", 5, Wealthy, Tools},
{"SpellBook", "����� ����������", 5, Wealthy, Tools},
//
{"Bloodstone", "������� ������", 5, Moderate, Gems},
{"Chrysoprase", "���������", 5, Moderate, Gems},
{"Iolite", "�����", 5, Moderate, Gems},
{"Jasper", "�������", 5, Moderate, Gems},
{"Moonstone", "������ ������", 5, Moderate, Gems},
{"Onyx", "�����", 5, Moderate, Gems},
// �����
{"Map", "�����", 5, Moderate, Clues},
{"Note", "�������", 5, Moderate, Clues},
{"Journal", "�������", 5, Moderate, Clues},
// �������������
{"Alexandrite", "�����������", 5, Rich, Gems},
{"Aquamarine", "���������", 5, Rich, Gems},
{"Black Pearl", "������ ���������", 5, Rich, Gems},
{"Topaz", "�����", 5, Rich, Gems},
//
{"Poison", "��", 5, Wealthy, Potions},
//
{"SilverCoins", "����������� ������", 1, Dirt, Gems},
{"GoldCoins", "������� ������", 10, Dirt, Gems},
};