#include "main.h"

enum word_s { Masculine, Femine, Neuter, Pluar };

static struct terrain_i
{
	const char*		name[2];
	word_s			word;
} terrains[] = {
	{{"Bay", "�����"}, Femine},
	{{"Bluffs", "������"}, Pluar},
	{{"Bog", "����"}, Femine},
	{{"Cliffs", "�����"}, Pluar},
	{{"Desert", "�������"}, Femine},
	{{"Downs", "������"}, Pluar},
	{{"Dunes", "����"}, Pluar},
	{{"Expanse", "��������"}, Neuter},
	{{"Fells", "�������"}, Femine},
	{{"Fen", "�������"}, Femine},
	{{"Flats", "������"}, Pluar},
	{{"Foothills", "�������� ���"}, Neuter},
	{{"Forest", "���"}, Masculine},
	{{"Groves", "����"}, Femine},
	{{"Heath", "����"}, Neuter},
	{{"Heights", "������"}, Pluar},
	{{"Hills", "�����"}, Pluar},
	{{"Hollows", "������"}, Femine},
	{{"Jungle", "�������"}, Pluar},
	{{"Lake", "�����"}, Neuter},
	{{"Lowland", "������"}, Femine},
	{{"March", "����"}, Neuter},
	{{"Meadows", "����"}, Pluar},
	{{"Moor", "���������"}, Pluar},
	{{"Morass", "������"}, Pluar},
	{{"Mounds", "�������"}, Pluar},
	{{"Mountains", "����"}, Pluar},
	{{"Peaks", "�����"}, Pluar},
	{{"Plains", "�������"}, Pluar},
	{{"Prairie", "������"}, Femine},
	{{"Quagmire", "������"}, Femine},
	{{"Range", "����"}, Masculine},
	{{"Reach", "��������"}, Masculine},
	{{"Sands", "�����"}, Pluar},
	{{"Savanna", "�������"}},
	{{"Scarps", "������"}, Pluar},
	{{"Sea", "����"}, Neuter},
	{{"Slough", "������"}, Pluar},
	{{"Sound", "������"}, Masculine},
	{{"Steppe", "�����"}, Femine},
	{{"Swamp", "������"}, Neuter},
	{{"Sweep", "��������"}, Femine},
	{{"Teeth", "����"}, Pluar},
	{{"Thicket", "������"}, Femine},
	{{"Upland", "�������"}, Neuter},
	{{"Wall", "�����"}, Femine},
	{{"Waste", "����������"}, Neuter},
	{{"Wasteland", "�������"}, Femine},
	{{"Woods", "����"}, Pluar},
};
static const char* adjectives[][6] = {
	{"Ageless", "��������", "������", "������", "������", "������"},
	{"Ashen", "����", "�������", "�������", "�������", "�������"},
	{"Black", "�������", "������", "������", "������", "������"},
	{"Blessed", "�������������", "��������������", "��������������", "��������������", "��������������"},
	{"Blighted", "�����", "�������", "�������", "�������", "�������"},
	{"Blue", "������", "�����", "�����", "�����", "�����"},
	{"Broken", "�������", "��������", "��������", "��������", "��������"},
	{"Burning", "�������", "�������", "�������", "�������", "�������"},
	{"Copper", "����", "������", "������", "������", "������"},
	{"Cursed", "���������", "���������", "���������", "���������", "���������"},
	{"Dark", "�������", "������", "������", "������", "������"},
	{"Dead", "�������", "�������", "�������", "�������", "�������"},
	{"Deep", "�������", "��������", "��������", "��������", "��������"},
	{"Demon�s", "������", "������������", "������������", "������������", "������������"},
	{"Desolate", "��������", "���������", "���������", "���������", "���������"},
	{"Devil�s", "�������", "����������", "����������", "����������", "����������"},
	{"Diamond", "����������", "������������", "������������", "������������", "������������"},
	{"Dismal", "���������", "����������", "����������", "����������", "����������"},
	{"Dun", "�������", "���������", "���������", "���������", "���������"},
	{"Emerald", "��������", "����������", "����������", "����������", "����������"},
	{"Endless", "�������������", "�����������", "�����������", "�����������", "�����������"},
	{"Fallen", "������", "������", "������", "������", "������"},
	{"Far", "���������", "�������", "�������", "�������", "�������"},
	{"Fell", "����������", "��������", "��������", "��������", "��������"},
	{"Fire", "����", "��������", "��������", "��������", "��������"},
	{"Forgotten", "�������", "�������", "�������", "�������", "�������"},
	{"Forsaken", "�������", "�����������", "�����������", "�����������", "�����������"},
	{"Frozen", "��������", "���������", "���������", "���������", "���������"},
	{"Ghost", "��������", "����������", "����������", "����������", "����������"},
	{"Golden", "������", "�������", "�������", "�������", "�������"},
	{"Green", "������", "�������", "�������", "�������", "�������"},
	{"Holy", "��������", "���������", "���������", "���������", "���������"},
	{"Iron", "������", "��������", "��������", "��������", "��������"},
	{"Jagged", "�����", "��������", "��������", "��������", "��������"},
	{"King�s", "������", "�����������", "�����������", "�����������", "�����������"},
	{"Light", "�����", "�������", "�������", "�������", "�������"},
	{"Perilous", "���������", "�������", "�������", "�������", "�������"},
	{"Queen�s", "��������", "�����������", "�����������", "�����������", "�����������"},
	{"Red", "��������", "�������", "�������", "�������", "�������"},
	{"Ruby", "������", "���������", "���������", "���������", "���������"},
	{"Sapphire", "�������", "����������", "����������", "����������", "����������"},
	{"Shadow", "���������", "�������", "�������", "�������", "�������"},
	{"Shattered", "��������", "��������", "��������", "��������", "��������"},
	{"Shifting", "��������", "����������", "����������", "����������", "����������"},
	{"Silver", "�������", "�����������", "�����������", "�����������", "�����������"},
	{"Umber", "�����", "����������", "����������", "����������", "����������"},
	{"White", "������", "�����", "�����", "�����", "�����"},
	{"Wicked", "�������", "��������", "��������", "��������", "��������"},
	{"Yellow", "��������", "������", "������", "������", "������"},
};
static const char* nouns[][6] = {
	{"", ""},
	{"Ash", "�����", "���������", "���������", "���������", "���������"},
	{"Bone", "������", "��������", "��������", "��������", "��������"},
	{"Darkness", "����", "������", "������", "������", "������"},
	{"Dead", "�������", "�������", "�������", "�������", "�������"},
	{"Death", "������", "�����������", "�����������", "�����������", "�����������"},
	{"Desolation", "�����������", "�����������", "�����������", "�����������", "�����������"},
	{"Despair", "��������", "��������", "���������", "��������", "���������"},
	{"Devil", "�������", "�����������", "�����������", "�����������", "�����������"},
	{"Doom", "����", "�������", "�������", "�������", "�������"},
	{"Dragon", "�������", "��������", "��������", "��������", "��������"},
	{"Fate", "������", "������������", "������������", "������������", "������������"},
	{"Fear", "������", "��������", "��������", "��������", "��������"},
	{"Fire", "����", "��������", "��������", "��������", "��������"},
	{"Fury", "������", "��������", "��������", "��������", "��������"},
	{"Ghost", "���������", "����������", "����������", "����������", "����������"},
	{"Giant", "��������", "���������", "���������", "���������", "���������"},
	{"God", "����", "������������", "������������", "������������", "������������"},
	{"Gold", "������", "�������", "�������", "�������", "�������"},
	{"Heaven", "���", "�������", "�������", "�������", "�������"},
	{"Hell", "���", "������", "������", "������", "������"},
	{"Hero", "������", "�����������", "�����������", "�����������", "�����������"},
	{"Honor", "�����", "�������", "�������", "�������", "�������"},
	{"Hope", "�������", "��������� �������", "��������� �������", "��������� �������", "��������� �������"},
	{"Horror", "�����", "�������", "�������", "�������", "�������"},
	{"King", "������", "�����������", "����������", "�����������", "�����������"},
	{"Life", "�����", "�������� �����", "�������� �����", "�������� �����", "�������� �����"},
	{"Light", "�����", "�������", "�������", "�������", "�������"},
	{"Lost", "����������", "����������", "����������", "����������", "����������"},
	{"Mist", "������", "��������", "��������", "��������", "��������"},
	{"Pity", "�������", "�����������", "�����������", "�����������", "�����������"},
	{"Queen", "��������", "�����������", "�����������", "�����������", "�����������"},
	{"Rain", "�����", "�������������", "��������������", "��������������", "��������������"},
	{"Refuge", "��������", "���������", "���������", "���������", "���������"},
	{"Regret", "���������", "����������", "����������", "����������", "����������"},
	{"Savior", "���������", "���������� ���������", "���������� ���������", "���������� ���������", "���������� ���������"},
	{"Shadow", "�����", "�������", "�������", "�������", "�������"},
	{"Silver", "�������", "�����������", "�����������", "�����������", "�����������"},
	{"Skull", "������", "��������", "��������", "��������", "��������"},
	{"Sky", "����", "��������", "��������", "��������", "��������"},
	{"Smoke", "����", "������", "������", "������", "������"},
	{"Snake", "����", "�������", "��������", "��������", "��������"},
	{"Sorrow", "������", "���������", "���������", "���������", "���������"},
	{"Storm", "����", "���������", "���������", "���������", "���������"},
	{"Sun", "������", "���������", "���������", "���������", "���������"},
	{"Thorn", "�������", "�������", "�������", "�������", "�������"},
	{"Thunder", "�����", "��������", "��������", "��������", "��������"},
	{"Traitor", "���������", "�������������", "�������������", "�������������", "�������������"},
	{"Troll", "������", "���������� ��������", "���������� ��������", "���������� ��������", "���������� ��������"},
	{"Witch", "������", "�����������", "�����������", "��������", "��������"},
};

void steading::getrandomname(unsigned char& tmp, unsigned char& terrain, unsigned char& adjective, unsigned char& noun)
{
	auto d = rand() % 12;
	if(d < 4)
		tmp = 0;
	else if(d < 6)
		tmp = 1;
	else if(d < 8)
		tmp = 2;
	else if(d < 10)
		tmp = 3;
	else if(d < 11)
		tmp = 4;
	else
		tmp = 5;
	terrain = rand() % 50;
	adjective = rand() % 50;
	noun = rand() % 50;
}

char* steading::getname(char* temp, unsigned char tmp, unsigned char terrain, unsigned char adjective, unsigned char noun) const
{
	auto pa = adjectives[adjective][terrains[terrain].word + 2];
	auto pn = nouns[noun][1];
	auto pt = terrains[terrain].name[1];
	switch(tmp)
	{
	case 1:
		szprint(temp, "%1 %3", pt, pa, pn);
		break;
	case 2:
		pa = adjectives[adjective][1];
		szprint(temp, "%1 %2", pt, pa, pn);
		break;
	case 3:
		pn = nouns[noun][terrains[terrain].word + 2];
		szprint(temp, "%3 %2 %1", pt, pa, pn);
		break;
	case 4:
		szprint(temp, "%2 %1 %3", pt, pa, pn);
		break;
	default:
		szprint(temp, "%2 %1", pt, pa, pn);
		break;
	}
	return temp;
}