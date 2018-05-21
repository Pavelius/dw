#include "main.h"

static struct name_t
{
    nation_s			nation;
    gender_s			gender;
    const char*			name[2];
} name_data[] =
{
    {Avalon, Male, {"", "�����"}},
    {Avalon, Male, {"", "����"}},
    {Avalon, Male, {"", "����"}},
    {Avalon, Male, {"", "������"}},
    {Avalon, Male, {"", "������"}},
    {Avalon, Male, {"", "����"}},
    {Avalon, Male, {"", "�������"}},
    {Avalon, Male, {"", "������"}},
    {Avalon, Male, {"", "����"}},
    {Avalon, Male, {"", "����"}},
    {Avalon, Male, {"", "���"}},
    {Avalon, Male, {"", "���������"}},
    {Avalon, Male, {"", "�����"}},
    {Avalon, Male, {"", "������"}},
    {Avalon, Male, {"", "������"}},
    {Avalon, Male, {"", "�����"}},
    {Avalon, Male, {"", "������"}},
    {Avalon, Male, {"", "����"}},
    {Avalon, Male, {"", "�����"}},
    {Avalon, Male, {"", "������"}},
    {Avalon, Female, {"", "�����"}},
    {Avalon, Female, {"", "������"}},
    {Avalon, Female, {"", "�������"}},
    {Avalon, Female, {"", "��������"}},
    {Avalon, Female, {"", "�����"}},
    {Avalon, Female, {"", "�����"}},
    {Avalon, Female, {"", "�����"}},
    {Avalon, Female, {"", "�����"}},
    {Avalon, Female, {"", "�����"}},
    {Avalon, Female, {"", "�����"}},
    {Avalon, Female, {"", "�����"}},
    {Avalon, Female, {"", "���"}},
    {Avalon, Female, {"", "����"}},
    {Avalon, Female, {"", "�������"}},
    {Avalon, Female, {"", "�������"}},
    {Avalon, Female, {"", "�����"}},
    {Avalon, Female, {"", "������"}},
    {Avalon, Female, {"", "��������"}},
    {Avalon, Female, {"", "�����"}},
    {Avalon, Female, {"", "��������"}},
    {Castille, Male, {"", "������"}},
    {Castille, Male, {"", "������"}},
    {Castille, Male, {"", "��������"}},
    {Castille, Male, {"", "������"}},
    {Castille, Male, {"Carlos", "������"}},
    {Castille, Male, {"Diego", "�����"}},
    {Castille, Male, {"Domingo", "�������"}},
    {Castille, Male, {"Esteban", "�������"}},
    {Castille, Male, {"", "������"}},
    {Castille, Male, {"", "������"}},
    {Castille, Male, {"", "������"}},
    {Castille, Male, {"", "�����"}},
    {Castille, Male, {"", "����"}},
    {Castille, Male, {"", "�����"}},
    {Castille, Male, {"Migel", "������"}},
    {Castille, Male, {"Rodrigo", "�������"}},
    {Castille, Male, {"Sancho", "�����"}},
    {Castille, Male, {"", "���������"}},
    {Castille, Male, {"", "�����"}},
    {Castille, Female, {"", "������"}},
    {Castille, Female, {"", "������"}},
    {Castille, Female, {"", "�������"}},
    {Castille, Female, {"", "��������"}},
    {Castille, Female, {"", "�����"}},
    {Castille, Female, {"", "���������"}},
    {Castille, Female, {"", "��������"}},
    {Castille, Female, {"", "��������"}},
    {Castille, Female, {"", "���������"}},
    {Castille, Female, {"", "������"}},
    {Castille, Female, {"", "��������"}},
    {Castille, Female, {"", "��������"}},
    {Castille, Female, {"", "�����"}},
    {Castille, Female, {"", "�����"}},
    {Castille, Female, {"", "�����"}},
    {Castille, Female, {"", "��������"}},
    {Castille, Female, {"", "�����"}},
    {Castille, Female, {"", "�������"}},
    {Castille, Female, {"", "������"}},
    {Castille, Female, {"", "��������"}},
    {Eisen, Male, {"", "������"}},
    {Eisen, Male, {"", "�������"}},
    {Eisen, Male, {"", "����"}},
    {Eisen, Male, {"", "����"}},
    {Eisen, Male, {"", "������"}},
    {Eisen, Male, {"", "����"}},
    {Eisen, Male, {"", "�����"}},
    {Eisen, Male, {"", "����"}},
    {Eisen, Male, {"", "������"}},
    {Eisen, Male, {"", "����"}},
    {Eisen, Male, {"", "������"}},
    {Eisen, Male, {"", "������"}},
    {Eisen, Male, {"", "��������"}},
    {Eisen, Male, {"", "�����"}},
    {Eisen, Male, {"", "������"}},
    {Eisen, Male, {"", "�������"}},
    {Eisen, Male, {"", "�������"}},
    {Eisen, Male, {"", "�����"}},
    {Eisen, Male, {"", "�������"}},
    {Eisen, Male, {"", "������"}},
    {Eisen, Female, {"", "�������"}},
    {Eisen, Female, {"", "�����"}},
    {Eisen, Female, {"", "��������"}},
    {Eisen, Female, {"", "�����"}},
    {Eisen, Female, {"", "����"}},
    {Eisen, Female, {"", "�����"}},
    {Eisen, Female, {"", "���"}},
    {Eisen, Female, {"", "��������"}},
    {Eisen, Female, {"", "������"}},
    {Eisen, Female, {"", "��������"}},
    {Eisen, Female, {"", "�������"}},
    {Eisen, Female, {"", "���"}},
    {Eisen, Female, {"", "������"}},
    {Eisen, Female, {"", "�������"}},
    {Eisen, Female, {"", "����"}},
    {Eisen, Female, {"", "�����"}},
    {Montaigne, Male, {"", "�������"}},
    {Montaigne, Male, {"", "�����"}},
    {Montaigne, Male, {"", "������"}},
    {Montaigne, Male, {"", "�������"}},
    {Montaigne, Male, {"", "���"}},
    {Montaigne, Male, {"", "������"}},
    {Montaigne, Male, {"", "�����"}},
    {Montaigne, Male, {"", "���"}},
    {Montaigne, Male, {"", "������"}},
    {Montaigne, Male, {"", "���"}},
    {Montaigne, Male, {"", "����"}},
    {Montaigne, Male, {"", "����"}},
    {Montaigne, Male, {"", "����"}},
    {Montaigne, Male, {"", "������"}},
    {Montaigne, Male, {"", "����"}},
    {Montaigne, Male, {"", "����"}},
    {Montaigne, Male, {"", "�������"}},
    {Montaigne, Female, {"", "�������"}},
    {Montaigne, Female, {"", "�����"}},
    {Montaigne, Female, {"", "������"}},
    {Montaigne, Female, {"", "������"}},
    {Montaigne, Female, {"", "�������"}},
    {Montaigne, Female, {"", "������"}},
    {Montaigne, Female, {"", "������"}},
    {Montaigne, Female, {"", "��������"}},
    {Montaigne, Female, {"", "��������"}},
    {Montaigne, Female, {"", "���������"}},
    {Montaigne, Female, {"", "����"}},
    {Montaigne, Female, {"", "����"}},
    {Montaigne, Female, {"", "�����"}},
    {Montaigne, Female, {"", "������"}},
    {Montaigne, Female, {"", "����"}},
    {Montaigne, Female, {"", "�������"}},
    {Montaigne, Female, {"", "�������"}},
    {Montaigne, Female, {"", "������"}},
    {Montaigne, Female, {"", "���������"}},
    {Ussura, Male, {"Alexey", "�������"}},
    {Ussura, Male, {"Alexander", "���������"}},
    {Ussura, Male, {"Boris", "�����"}},
    {Ussura, Male, {"Dmitriy", "�������"}},
    {Ussura, Male, {"Erema", "�����"}},
    {Ussura, Male, {"Fedor", "�����"}},
    {Ussura, Male, {"Georgiy", "�������"}},
    {Ussura, Male, {"Ignatiy", "�������"}},
    {Ussura, Male, {"Ilya", "����"}},
    {Ussura, Male, {"Michail", "������"}},
    {Ussura, Male, {"Nikita", "������"}},
    {Ussura, Male, {"Petr", "����"}},
    {Ussura, Male, {"Sergey", "������"}},
    {Ussura, Male, {"Timofei", "�������"}},
    {Ussura, Male, {"Vasiliy", "�������"}},
    {Ussura, Male, {"Vladimir", "��������"}},
    {Ussura, Male, {"Ivan", "����"}},
    {Ussura, Female, {"Afalia", "������"}},
    {Ussura, Female, {"Anna", "����"}},
    {Ussura, Female, {"Bogdana", "�������"}},
    {Ussura, Female, {"Chenka", "�����"}},
    {Ussura, Female, {"Zoja", "���"}},
    {Ussura, Female, {"Daria", "�����"}},
    {Ussura, Female, {"Elena", "�����"}},
    {Ussura, Female, {"Galina", "������"}},
    {Ussura, Female, {"Irina", "�����"}},
    {Ussura, Female, {"Katherine", "��������"}},
    {Ussura, Female, {"Maria", "�����"}},
    {Ussura, Female, {"Nana", "����"}},
    {Ussura, Female, {"Natalia", "�������"}},
    {Ussura, Female, {"Sofia", "�����"}},
    {Ussura, Female, {"Tamara", "������"}},
    {Ussura, Female, {"Inna", "����"}},
    {Vendel, Male, {"", "��������"}},
    {Vendel, Male, {"", "�����"}},
    {Vendel, Male, {"", "����"}},
    {Vendel, Male, {"", "��������"}},
    {Vendel, Male, {"", "������"}},
    {Vendel, Male, {"", "�����"}},
    {Vendel, Male, {"", "����������"}},
    {Vendel, Male, {"", "�����"}},
    {Vendel, Male, {"", "���"}},
    {Vendel, Male, {"", "������"}},
    {Vendel, Male, {"", "������"}},
    {Vendel, Male, {"", "��������"}},
    {Vendel, Male, {"", "����"}},
    {Vendel, Male, {"", "����"}},
    {Vendel, Male, {"", "������"}},
    {Vendel, Male, {"", "��������"}},
    {Vendel, Male, {"", "������"}},
    {Vendel, Male, {"", "�����"}},
    {Vendel, Male, {"", "����"}},
    {Vendel, Male, {"", "������"}},
    {Vendel, Female, {"", "������"}},
    {Vendel, Female, {"", "����"}},
    {Vendel, Female, {"", "����"}},
    {Vendel, Female, {"", "�����"}},
    {Vendel, Female, {"", "����"}},
    {Vendel, Female, {"", "�������"}},
    {Vendel, Female, {"", "����������"}},
    {Vendel, Female, {"", "���������"}},
    {Vendel, Female, {"", "������"}},
    {Vendel, Female, {"", "������"}},
    {Vendel, Female, {"", "�����"}},
    {Vendel, Female, {"", "���"}},
    {Vendel, Female, {"", "��������"}},
    {Vendel, Female, {"", "����"}},
    {Vendel, Female, {"", "������"}},
    {Vendel, Female, {"", "��������"}},
    {Vendel, Female, {"", "�������"}},
    {Vendel, Female, {"", "������"}},
    {Vendel, Female, {"", "��������"}},
    {Vendel, Female, {"", "��"}},
    {Vodacce, Male, {"", "��������"}},
    {Vodacce, Male, {"", "�������"}},
    {Vodacce, Male, {"", "�����"}},
    {Vodacce, Male, {"", "�������"}},
    {Vodacce, Male, {"", "�����"}},
    {Vodacce, Male, {"", "���������"}},
    {Vodacce, Male, {"", "�������"}},
    {Vodacce, Male, {"", "��������"}},
    {Vodacce, Male, {"", "����"}},
    {Vodacce, Male, {"", "�����"}},
    {Vodacce, Male, {"", "�������"}},
    {Vodacce, Male, {"", "�����"}},
    {Vodacce, Male, {"", "��������"}},
    {Vodacce, Male, {"", "�������"}},
    {Vodacce, Male, {"", "������"}},
    {Vodacce, Male, {"", "����"}},
    {Vodacce, Male, {"", "�����"}},
    {Vodacce, Male, {"", "����"}},
    {Vodacce, Male, {"", "�������"}},
    {Vodacce, Male, {"", "����"}},
    {Vodacce, Female, {"", "������"}},
    {Vodacce, Female, {"", "��������"}},
    {Vodacce, Female, {"", "��������"}},
    {Vodacce, Female, {"", "���������"}},
    {Vodacce, Female, {"", "�����"}},
    {Vodacce, Female, {"", "�����"}},
    {Vodacce, Female, {"", "�������"}},
    {Vodacce, Female, {"", "���"}},
    {Vodacce, Female, {"", "�����"}},
    {Vodacce, Female, {"", "�������"}},
    {Vodacce, Female, {"", "�����"}},
    {Vodacce, Female, {"", "��������"}},
    {Vodacce, Female, {"", "������"}},
    {Vodacce, Female, {"", "�������"}},
    {Vodacce, Female, {"", "������"}},
    {Vodacce, Female, {"", "������"}},
    {Vodacce, Female, {"", "�������"}},
    {Vodacce, Female, {"", "�����"}},
    {Vodacce, Female, {"", "��������"}},
};

//int get_random_name(tags nation, tags gender)
//{
//    int count = 0;
//    for(auto& e : objects)
//    {
//        if(e.nation==nation && e.gender==gender)
//            count++;
//    }
//    if(count)
//    {
//        count = rand()%count;
//        int index = 0;
//        for(auto& e : objects)
//        {
//            if(e.nation==nation && e.gender==gender)
//            {
//                if(count==0)
//                    return index;
//                count--;
//            }
//            index++;
//        }
//    }
//    return 0;
//}

short unsigned random(gender_s gender, nation_s* nation)
{
	short unsigned source[sizeof(name_data) / sizeof(name_data[0])];
	auto p = source;
	for(unsigned i = 0; i < sizeof(name_data) / sizeof(name_data[0]); i++)
	{
		if(name_data[i].gender != gender)
			continue;
		if(nation && name_data[i].nation != *nation)
			continue;
		*p++ = i;
	}
	auto count = p - source;
	if(!count)
		return 0xFFFF;
	return source[rand() % count];
}

//const char* game::getname(char* temp, int nation, int gender, int name, int family, int mother, int noble)
//{
//    temp[0] = 0;
//    switch(nation)
//    {
//    case Castille:
//        if(noble)
//        {
//            zcat(temp, szt("Don", "���"));
//            zcat(temp, " ");
//        }
//        zcat(temp, getnamepart(name));
//        if(mother)
//		{
//			zcat(temp, " ");
//			zcat(temp, bsgets(mother, Name));
//		}
//        if(family)
//		{
//			zcat(temp, szt(" de ", " �� "));
//			zcat(temp, bsgets(family, Name));
//		}
//        break;
//    case Avalon:
//        if(noble)
//        {
//            if(gender==Female)
//                zcat(temp, szt("Ledi", "����"));
//            else
//                zcat(temp, szt("Lord", "����"));
//            zcat(temp, " ");
//        }
//        zcat(temp, getnamepart(name));
//        if(family)
//		{
//			zcat(temp, " ");
//			zcat(temp, bsgets(family, Name));
//		}
//        break;
//	default:
//		zcat(temp, szt("Outsider","�����������"));
//		break;
//    }
//    return temp;
//}

short unsigned hero::getnamerandom(gender_s gender, nation_s nation)
{
	auto r = random(gender, &nation);
	if(r != 0xFFFF)
		return r;
	return random(gender, 0);
}

const char* hero::getname(short unsigned id)
{
	return name_data[id].name[1];
}