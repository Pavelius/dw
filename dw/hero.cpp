#include "main.h"

static char stats_modifiers[] = {-4,
-3, -3, -3, -2, -2, -1, -1, -1, 0, 0,
0, 0, 1, 1, 1, 2, 2, 3
};

int hero::coins;

hero::hero()
{
	clear();
}

void hero::clear()
{
	type = Bard;
	race = Human;
	gender = Male;
	alignment = Good;
	weapon.clear();
	armor.clear();
	shield.clear();
	signature_weapon.clear();
	for(auto& e : gear)
		e.clear();
	memset(stats, 0, sizeof(stats));
	memset(moves, 0, sizeof(moves));
	hp = 0;
	experience = 0;
}

void hero::addcoins(int count)
{
	coins += count;
}

bool hero::is(move_s value) const
{
	return (moves[value / (sizeof(moves[0]) * 8)] & (1 << (value % (sizeof(moves[0]) * 8)))) != 0;
}

void hero::set(move_s value)
{
	moves[value / (sizeof(moves[0]) * 8)] |= 1 << (value % (sizeof(moves[0]) * 8));
}

bool hero::set(item value)
{
	if(value.iscoins())
	{
		coins += value.uses;
		return true;
	}
	if(value.isarmor() && !armor)
	{
		armor = value;
		return true;
	}
	if(value.isweapon() && !weapon)
	{
		weapon = value;
		return true;
	}
	for(auto& e : gear)
	{
		if(e)
			continue;
		e = value;
		return true;
	}
	return false;
}

bool hero::isammo() const
{
	for(auto& e : gear)
	{
		if(e.is(Ammo) && e.uses)
			return true;
	}
	return false;
}

bool hero::useammo()
{
	for(auto& e : gear)
	{
		if(e.is(Ammo) && e.uses)
			return e.use();
	}
	return false;
}

bool hero::isclumsy() const
{
	if(armor && !is(Armored) && armor.is(Clumsy))
		return true;
	return false;
}

int	hero::get(stat_s stat) const
{
	return stats_modifiers[stats[stat]];
}

bool hero::isequipment() const
{
	for(auto& e : gear)
	{
		if(e)
			return true;
	}
	return armor || weapon || shield;
}

char* hero::getequipment(char* result, const char* title) const
{
	bool description = false;
	result[0] = 0;
	if(!isequipment())
		return result;
	zcat(result, title);
	auto p = zend(result);
	if(armor)
	{
		if(p[0])
			zcat(p, ", ");
		armor.getname(zend(p), description);
	}
	if(weapon)
	{
		if(p[0])
			zcat(p, ", ");
		weapon.getname(zend(p), description);
	}
	if(shield)
	{
		if(p[0])
			zcat(p, ", ");
		shield.getname(zend(p), description);
	}
	for(auto& e : gear)
	{
		if(!e)
			continue;
		if(p[0])
			zcat(p, ", ");
		e.getname(zend(p), description);
	}
	zcat(p, ".");
	return result;
}

bool hero::isalive() const
{
	return hp > 0;
}

int hero::getharm() const
{
	return getdamage().roll();
}

item* hero::getweapon(distance_s distance)
{
	for(auto& e : gear)
	{
		if(!e)
			continue;
		if(e.is(distance))
			return &e;
	}
	return 0;
}

item* hero::getitem(items type)
{
	for(auto& e : gear)
	{
		if(!e)
			continue;
		if(e.type==type)
			return &e;
	}
	return 0;
}

result_s hero::roll(int bonus, int* result, bool show_result)
{
	char temp[64];
	int dr = 2 + (rand() % 6) + (rand() % 6);
	int tr = dr + bonus;
	szprint(temp, "{%2i%+3i=%1i}", tr, dr, bonus);
	if(result)
		*result = tr;
	auto ds = Fail;
	if(tr >= 10)
		ds = Success;
	else if(tr >= 7)
		ds = PartialSuccess;
	switch(ds)
	{
	case Fail:
		experience++;
		if(show_result)
			logs::add("[-%1]", temp);
		break;
	case Success:
		if(show_result)
			logs::add("[+%1]", temp);
		break;
	default:
		if(show_result)
			logs::add(temp);
		break;
	}
	return ds;
}

result_s hero::defydanger(stat_s stat)
{
	auto bonus = get(stat);
	return roll(bonus);
}

result_s hero::spoutlore()
{
	auto bonus = get(Intellegence);
	return roll(bonus);
}

result_s hero::discernrealities()
{
	auto bonus = get(Wisdow);
	return roll(bonus);
}

result_s hero::parley()
{
	auto bonus = get(Charisma);
	return roll(bonus);
}

int hero::whatdo(bool clear_text)
{
	return logs::input(true, clear_text, "Что будет делать %1?", getname());
}

int hero::getarmor() const
{
	return 0;
}

int hero::getload() const
{
	auto result = game::getload(type);
	result += get(Strenght);
	return result;
}

int hero::getmaxhits() const
{
	auto result = game::gethits(type);
	result += stats[Constitution];
	return result;
}

dice hero::getdamage() const
{
	dice result;
	result.c = 1;
	result.d = game::getdamage(type);
	result.b = (char)weapon.getdamage();
	result.m = 0;
	return result;
}

void hero::choosemoves(bool interactive)
{
	// Спросим про знаковое оружие
	if(is(SignatureWeapon) && !signature_weapon)
	{
		logs::add(SwordLong, getstr(SwordLong));
		logs::add(Warhammer, getstr(Warhammer));
		logs::add(Spear, getstr(Spear));
		signature_weapon.set(static_cast<items>(logs::input(interactive, true, "Ваше знаковое оружие:")));
		for(int count = 0; count < 2; count++)
		{
			for(auto e = Spiked; e <= WellCrafted; e = (enchantment_s)(e + 1))
			{
				if(signature_weapon.is(e))
					continue;
				logs::add(e, getstr(e));
			}
			auto id = (enchantment_s)logs::input(interactive, true, "Выберите улучшения (%1i/2):", count + 1);
			signature_weapon.set(id);
			switch(id)
			{
			case Versatile:
				for(auto d = Hand; d <= Reach; d = (distance_s)(d + 1))
				{
					if(signature_weapon.is(d))
						continue;
					logs::add(d, getstr(d));
				}
				signature_weapon.set((distance_s)logs::input(interactive, true, "На какой дистанции?"));
				break;
			}
		}
		weapon = signature_weapon;
	}
}