#include "main.h"

static const char* text_golds[] = {"золотых", "золотой", "золотых"};
static const char* text_hits[] = {"повреждений", "повреждение", "повреждени€", "повреждени€", "повреждени€", "повреждений"};
static char stats_modifiers[] = {-4,
-3, -3, -3, -2, -2, -1, -1, -1, 0, 0,
0, 0, 1, 1, 1, 2, 2, 3
};

static int		party_coins;
hero			players[8];

hero::hero()
{
	clear();
}

void hero::clear()
{
	memset(this, 0, sizeof(hero));
}

void hero::addcoins(int count)
{
	party_coins += count;
}

int hero::getcoins() const
{
	return party_coins;
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
		addcoins(value.uses);
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

bool hero::useration()
{
	for(auto& e : gear)
	{
		if(e.is(Ration) && e.uses)
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

bool hero::remove(item it)
{
	for(auto& e : gear)
	{
		if(memcmp(&e, &it, sizeof(item))==0)
		{
			e.clear();
			return true;
		}
	}
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

item* hero::getitem(item_s type)
{
	for(auto& e : gear)
	{
		if(!e)
			continue;
		if(e.type == type)
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
	if(!logs::getcount())
		return 0;
	return logs::input(true, clear_text, "„то будет делать [%1]?", getname());
}

int hero::getarmor() const
{
	auto result = armor.getarmor();
	if(is(ArcaneWard) && getpreparedlevels() > 0)
		result += 2;
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
	// —просим про знаковое оружие
	if(is(SignatureWeapon) && !signature_weapon)
	{
		logs::add(SwordLong, getstr(SwordLong));
		logs::add(Warhammer, getstr(Warhammer));
		logs::add(Spear, getstr(Spear));
		signature_weapon.set(static_cast<item_s>(logs::input(interactive, true, "¬аше знаковое оружие:")));
		for(int count = 0; count < 2; count++)
		{
			for(auto e = Spiked; e <= WellCrafted; e = (enchantment_s)(e + 1))
			{
				if(signature_weapon.is(e))
					continue;
				logs::add(e, getstr(e));
			}
			auto id = (enchantment_s)logs::input(interactive, true, "¬ыберите улучшени€ (%1i/2):", count + 1);
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
				signature_weapon.set((distance_s)logs::input(interactive, true, "Ќа какой дистанции?"));
				break;
			}
		}
		weapon = signature_weapon;
	}
}

bool hero::prepareweapon(monster& enemy)
{
	if(weapon.is(enemy.distance))
		return true;
	auto p = getweapon(enemy.distance);
	if(p)
	{
		char temp[260];
		iswap(weapon, *p);
		logs::add("%player достал%а %1.", weapon.getname(temp, false));
		return true;
	}
	return false;
}

void hero::inflictharm(monster& enemy, int count)
{
	auto armor = enemy.getarmor();
	count -= armor;
	if(count <= 0)
	{
		logs::add("”дар не смог пробить броню.");
		return;
	}
	enemy.hp -= count;
	if(enemy.hp > 0)
	{
		logs::add("%1 получил%3 [%2i] урона.", enemy.getname(), count, enemy.getA());
		return;
	}
	enemy.hp = enemy.getmaxhits();
	logs::add("%1 получил [%2i] урона и упал.", enemy.getname(), count);
	enemy.count--;
	if(enemy.count == 1)
		logs::add("ќсталс€ еще один.");
	else if(enemy.count == 2)
		logs::add("ќсталось еще двое.");
	else if(enemy.count == 3)
		logs::add("ќсталось еще трое.");
	else
		logs::add("ќсталось еще %1i.", enemy.count);
}

void hero::sufferharm(int count)
{
	auto armor = getarmor();
	count -= armor;
	if(count <= 0)
	{
		logs::add("Ѕрон€ спасла вас от удара.");
		return;
	}
	if(is(SpellDefense) && ongoing.count)
	{
		for(unsigned i= 0; i<ongoing.count; i++)
		{
			logs::add(i, "%1 снизит урон на %2i.",
				getstr(ongoing.data[i].type),
				getlevel(ongoing.data[i].type));
		}
		logs::add(1000, "Ќехочу убирать никаких заклинаний.");
		auto i = logs::input(true, false, "[%1] получит [2i] урона, но может пожертвовать действуующим заклинанием, чтобы снизить урон.",
			getname(), count);
		if(i != 1000)
			count -= getlevel(ongoing.data[i].type);
	}
	hp -= count;
	if(hp > 0)
		logs::add("%2 получил%3 [%1i] урона.", count, getname(), getA());
	else
	{
		logs::add("%2 получил%3 [%1i] урона и упал%3.", count, getname(), getA());
		if(game::isgameover())
			logs::next();
	}
}

static int fill_supply(item* pb, item* pe, prosperty_s prosperty, int cost)
{
	auto p = pb;
	for(auto i = RaggedBow; i < Coin; i = (item_s)(i + 1))
	{
		item it(i);
		if(it.getprosperty() > prosperty)
			continue;
		if(it.getcost() > cost)
			continue;
		if(p < pe)
			*p++ = it;
	}
	return p - pb;
}

result_s hero::supply(item* source, int count)
{
	while(true)
	{
		char temp[260];
		auto cup = getcoins();
		for(auto i = 0; i < count; i++)
		{
			auto cost = source[i].getcost();
			if(cost > cup)
				continue;
			logs::add(i, "%1. ÷ена [%2i] %3.", source[i].getname(temp, true), cost, maptbl(text_golds, cost));
		}
		if(logs::getcount()<= 0)
		{
			logs::add(" - я сожелею, но у мен€ нет товаров, которые вам подойдут или которые вы можете себе позволить - сказал владелец магазина.");
			logs::next();
			return Success;
		}
		logs::sort();
		logs::add(500, "Ќичего не надо");
		auto id = logs::input(true, true, "„то купит [%1] (есть %2i монет)?", getname(), getcoins());
		if(id == 500)
			return Success;
		auto& it = source[id];
		auto cost = source[id].getcost();
		logs::add(" - ¬ы хотите купить %1 за [%2i] монет? - спросил владелец магазина.",
			it.getname(temp, false), cost);
		if(logs::yesno())
		{
			addcoins(-cost);
			set(it);
		}
	}
	return Success;
}

result_s hero::sell(prosperty_s prosperty)
{
	char temp[260];
	while(true)
	{
		for(auto i = 0; i < sizeof(gear) / sizeof(gear[0]); i++)
		{
			auto pi = gear + i;
			if(!*pi)
				continue;
			if(pi->getprosperty() > prosperty)
				continue;
			auto cost = pi->getsellcost();
			if(cost <= 0)
				continue;
			logs::add(i, "%1 за [%2i] %3.",
				pi->getname(temp, true),
				pi->getsellcost(),
				maptbl(text_golds, cost));
		}
		if(logs::getcount() <= 0)
		{
			logs::add(" - я сожелею, но у вас нет товаров, которые € могу позволить себе купить - сказал владелец магазина.");
			logs::next();
			return Success;
		}
		logs::sort();
		logs::add(500, "Ќичего не продавать");
		auto id = logs::input(true, true, "„то хочет продать [%1]?", getname());
		if(id == 500)
			return Success;
		auto cost = gear[id].getsellcost();
		logs::add(" - ¬ы хотите продать %1? - спросил владелец магазина - я готов дам за него [%2i] монет.",
			gear[id].getname(temp, false),
			cost);
		if(logs::yesno())
		{
			gear[id].clear();
			addcoins(-cost);
		}
	}
	return Success;
}

int hero::getspellpenalty() const
{
	return ongoing.count + castpenalty;
}

void hero::healharm(int count)
{
	auto mhp = getmaxhits();
	if(hp + count > mhp)
		count = mhp - hp;
	if(count == 0)
		return;
	hp += count;
	logs::add("%1 востановил%2 %3i %4.", getname(), getA(), count, maptbl(text_hits, count));
}

hero* hero::chooseplayer(stat_s stat, const hero* e1, const hero* e2, const char* format, ...)
{
	for(auto i = 0; i<sizeof(players) / sizeof(players[0]); i++)
	{
		if(!players[i] || !players[i].isalive())
			continue;
		if(e1 && e1==(players + i))
			continue;
		if(e2 && e2 == (players + i))
			continue;
		auto value = players[i].get(stat);
		if(value>0)
			logs::add(i, "%1 (%2 [+%+3i]).", players[i].getname(), getstr(stat), value);
		else
			logs::add(i, "%1 (%2 [-%+3i]).", players[i].getname(), getstr(stat), -value);
	}
	return players + logs::inputv(true, false, format, xva_start(format), "\n$(answers)");
}

void hero::hunger()
{
	logs::add("%1 голодает.", getname());
	sufferharm(xrand(1, 6));
}