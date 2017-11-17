#include "main.h"

enum monster_tag_s {
	Amorphous, Cautions, Construct, Devious, Hoarder, Intellegent,
	Magical, Organized, Planar, Stealthy, Terrifing
};
enum organization_s {
	Horde, Group, Solitary
};
enum size_s {
	Tiny, Small, Medium, Large, Huge
};
struct monster_weapon_i
{
	distance_s				distance;
	unsigned char			damage;
	const char*				text;
	operator bool() const { return text != 0; }
};
static struct monster_i
{
	const char*				single[2];
	const char*				multi[3];
	organization_s			organization;
	size_s					size;
	adat<monster_tag_s, 4>	tags;
	int						armor;
	unsigned char			damage[2];
	char					hp;
	distance_s				distance[4];

	bool is(monster_tag_s id) const
	{
		for(auto e : tags)
		{
			if(e == id)
				return true;
		}
		return false;
	}

} monster_data[] = {
	{{"goblin", "гоблин"}, {"goblins", "гоблинов", "гоблина"}, Horde, Small, {{Intellegent, Organized}, 2}, 1, {6}, 3},
	{{"kobold", "кобольд"}, {"kobolds", "кобольдов", "кобольда"}, Horde, Small, {{Stealthy, Intellegent, Organized}, 3}, 1, {6}, 3},
	{{"bandit", "бандит"}, {"bandits", "бандитов", "бандита"}, Horde, Small, {{Intellegent, Organized}, 2}, 1, {6}, 3},
};

monster::monster() : type(Kobold), count(0), hp(0)
{
}

monster::monster(monster_s type)
{
	set(type);
}

int monster::getmaxhits() const
{
	return monster_data[type].hp;
}

int	monster::getarmor() const
{
	return monster_data[type].armor;
}

int	monster::getharm() const
{
	int result = 0;
	int maximum = imin(count, (char)3);
	for(int i = 0; i < maximum; i++)
		result = imax(result, getdamage().roll());
	return result;
}

dice monster::getdamage() const
{
	dice result;
	result.c = 1;
	result.d = monster_data[type].damage[0];
	result.m = 0;
	return result;
}

void monster::set(monster_s value)
{
	type = value;
	switch(monster_data[type].organization)
	{
	case Horde: count = xrand(7, 10); break;
	case Group: count = xrand(3, 6); break;
	default: count = 1; break;
	}
	distance = Far;
	hp = getmaxhits();
}

const char* monster::getname() const
{
	return monster_data[type].single[1];
}

const char* monster::getLA() const
{
	return "";
}

char* monster::getname(char* result) const
{
	if(count == 1)
		szprint(result, "%1", getname());
	else if(count<5)
		szprint(result, "[%2i] %1", monster_data[type].multi[2], count);
	else
		szprint(result, "[%2i] %1", monster_data[type].multi[1], count);
	return result;
}

bool monster::is(distance_s id) const
{
	for(auto e : monster_data[type].distance)
	{
		if(e == id)
			return true;
	}
	return false;
}