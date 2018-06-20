#include "main.h"

static struct name_i
{
	specie_s		race;
	gender_s		gender;
	const char*		name;
} name_data[] = {
	{Human, Male, "Анакен"},
	{Human, Male, "Арани"},
	{Human, Male, "Бейл"},
	{Human, Male, "Бен"},
	{Human, Male, "Беру"},
	{Human, Male, "Бигз"},
	{Human, Male, "Боба"},
	{Human, Male, "Корран"},
	{Human, Male, "Корбен"},
	{Human, Male, "Дек"},
	{Human, Male, "Дейн"},
	{Human, Male, "Галлак"},
	{Human, Male, "Гарм"},
	{Human, Male, "Хан"},
	{Human, Male, "Джанго"},
	{Human, Male, "Йодо"},
	{Human, Male, "Ландо"},
	{Human, Male, "Люк"},
	{Human, Male, "Мейс"},
	{Human, Male, "Обиван"},
	{Human, Male, "Овен"},
	{Human, Male, "Квигон"},
	{Human, Male, "Сейлан"},
	{Human, Male, "Рэнн"},
	{Human, Male, "Риддик"},
	{Human, Male, "Талон"},
	{Human, Male, "Ведж"},
	{Human, Male, "Винтер"},
	{Human, Female, "Лея"},
	{Human, Female, "Мара"},
	{Human, Female, "Падмэ"},
};

static unsigned select(short unsigned* result, unsigned count, name_i* source, unsigned source_count, gender_s gender, specie_s* race)
{
	auto p = result;
	auto pe = p + count;
	for(unsigned i = 0; i < source_count; i++)
	{
		if(gender != source[i].gender)
			continue;
		if(race && *race!= source[i].race)
			continue;
		if(p < pe)
			*p++ = (short unsigned)i;
		else
			break;
	}
	return p - result;
}

short unsigned game::getrandomname(specie_s race, gender_s gender)
{
	short unsigned result[128];
	auto count = select(result, lenghtof(result), name_data, lenghtof(name_data), gender, &race);
	if(count)
		return result[rand() % count];
	count = select(result, lenghtof(result), name_data, lenghtof(name_data), gender, 0);
	if(count)
		return result[rand() % count];
	return 0;
}

const char* game::getname(short unsigned id)
{
	return name_data[id].name;
}