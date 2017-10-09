#include "main.h"

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
		logs::add(100, "Отдыхать и набираться сил, не принимая никакой активности");
		auto result = player.whatdo();
		switch(result)
		{
		case 1:
			player.supply(prosperty);
			break;
		case 100:
			break;
		}
		if(result != 100)
			actions[i]++;
	}
}