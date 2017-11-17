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
assert_enum(monster, Bandit);

template<> const char* getstr<monster_s>(monster_s value)
{
	return monster_data[value].multi[1];
}

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

void monster::getloot(loot_i& loot) const
{
	auto hoard = getdamage().roll();
	if(hoard < 1)
		hoard = 1;
	switch(hoard)
	{
	case 1:
		loot.coins += dice::roll(2, 8);
		break;
	case 2:
		loot.add(AdventuringGear);
		break;
	case 3:
		loot.coins += dice::roll(4, 10);
		break;
	case 4:
		loot.add((item_s)xrand(Bloodstone, Onyx));
		break;
	case 5:
		loot.add(HealingPotion);
		break;
	case 6:
		loot.add(Map);
		break;
	case 7:
		loot.coins += dice::roll(1, 4) * 100;
		break;
	case 8:
		loot.add((item_s)xrand(Alexandrite, Topaz));
		break;
	case 9:
		loot.coins += dice::roll(2, 4) * 100;
		break;
	case 10:
		// A magical item or magical effect
		break;
	case 11:
		loot.coins += dice::roll(2, 4) * 100;
		break;
	case 12:
		loot.coins += dice::roll(3, 4) * 100;
		break;
	case 13:
		loot.coins += dice::roll(4, 4) * 100;
		break;
	case 14:
		loot.coins += dice::roll(5, 4) * 100;
		break;
	case 15:
		break;
	case 16:
		break;
	case 17:
		break;
	default:
		loot.coins += dice::roll(1, 10) * 1000;
		for(int i = xrand(1,6); i>0; i--)
			loot.add((item_s)xrand(Alexandrite, Topaz));
		break;
	}
}