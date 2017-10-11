#include "main.h"

static struct resource_i
{
	const char*		name[2];
} resource_data[] = {
	{{"Foods", "Еда"}},
	{{"Potions", "Зелья"}},
	{{"Weapons", "Оружие"}},
	{{"Species", "Специи"}},
	{{"Dress", "Одежда"}},
	{{"Gems", "Драгоценности"}},
	{{"Tools", "Инструменты"}},
	{{"Clues", "Улики"}},
	//
	{{"Wood", "Дерево"}},
	{{"Furs", "Меха"}},
	{{"Ore", "Руда"}},
};
assert_enum(resource, Ore);
getstr_enum(resource);

static struct steading_type_i
{
	const char*		name[2];
	prosperty_s		prosperty;
	population_s	population;
	defence_s		defence;
} steading_type_data[] = {
	{{"Village", "Деревня"}, Poor, Steady, Militia},
	{{"Town", "Город"}, Moderate, Steady, Watch},
	{{"Keep", "Цитадель"}, Poor, Shrinking, Guard},
	{{"City", "Мегаполис"}, Moderate, Steady, Guard},
};
assert_enum(steading_type, City);
getstr_enum(steading_type);

static steading	objects[64];

void* steading::operator new(unsigned size)
{
	for(auto& e : objects)
	{
		if(!e)
			return &e;
	}
	return 0;
}

steading::steading()
{
	clear();
	name = "Каменная крепость";
}

const char* steading::getname() const
{
	return name;
}

void steading::clear()
{
	memset(this, 0, sizeof(*this));
}

bool steading::is(steading_tag_s value) const
{
	switch(value)
	{
	case Religion:
		return religions.count != 0;
	default:
		return tags.is(value);
	}
}

void steading::create(steading_type_s type)
{
	auto& e = steading_type_data[type];
	clear();
	// Add basic types
	this->type = type;
	population = e.population;
	prosperty = e.prosperty;
	defence = e.defence;
	switch(type)
	{
	case Village:
		switch(rand() % 6)
		{
		case 0: need.add(Foods); break;
		case 1: religions.add(Bane); break;
		case 2: population = (population_s)(population - 1); break;
		case 3: break;
		case 4: break;
		case 5: break;
		}
		break;
	}
}

void steading::set(steading_tag_s value)
{
}

void steading::adventure()
{
	char actions[sizeof(players) / sizeof(players[0])];
	memset(actions, 0, sizeof(actions));
	logs::add("Вы находитесь в городе %1.", getname());
	for(int i = 0; i < sizeof(players) / sizeof(players[0]); i++)
	{
		auto& player = players[i];
		if(!player || actions[i]>0)
			continue;
		logs::add(1, "Пополнить запасы");
		if(prosperty >= Moderate)
			logs::add(2, "Продать что-то");
		logs::add(100, "Отдыхать и набираться сил, не принимая никакой активности");
		auto result = player.whatdo();
		switch(result)
		{
		case 1:
			player.supply(prosperty);
			break;
		case 2:
			player.sell(prosperty);
			break;
		case 100:
			break;
		}
		if(result != 100)
			actions[i]++;
	}
}