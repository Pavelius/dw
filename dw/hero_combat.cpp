#include "main.h"

void hero::volley(monster& enemy)
{
	auto bonus = get(Dexterity);
	while(true)
	{
		if(!isammo() || !enemy.isalive() || !weapon.is(enemy.distance))
			return;
		auto result = roll(bonus);
		logs::add("%1 сделал%2 несколько выстрелов.", getname(), getA());
		switch(result)
		{
		case Fail:
			logs::add("Но все стрелы легли мимо цели.");
			if(enemy.is(enemy.distance))
			{
				logs::add("%1 выстрелил%2 в ответ.", enemy.getname(), enemy.getA());
				sufferharm(enemy.getharm());
			}
			logs::next();
			return;
		case PartialSuccess:
			logs::add(1, "Хотя пришлось подойти очень близко и подставиться под удар.");
			logs::add(2, "Но, цели на самом деле достигло очень мало, -1d6 урона");
			logs::add(3, "Пришлось сделать слишком много выстрелов, боезапас уменьшится на единицу");
			switch(whatdo(false))
			{
			case 2:
				inflictharm(enemy, getharm() - xrand(1,6));
				break;
			case 3:
				inflictharm(enemy, getharm());
				useammo();
				break;
			default:
				inflictharm(enemy, getharm());
				if(enemy.is(enemy.distance))
				{
					logs::add("%1 выстрелил%2 в ответ.", enemy.getname(), enemy.getA());
					sufferharm(enemy.getharm());
				}
				logs::next();
				return;
			}
			break;
		default:
			inflictharm(enemy, getharm());
			break;
		}
		logs::next();
	}
}

void hero::hackandslash(monster& enemy)
{
	auto bonus = get(Strenght);
	if(weapon.is(Precise)
		|| (race == Elf && type == Fighter && weapon.type == SwordLong))
		bonus = get(Dexterity);
	auto result = roll(bonus);
	switch(result)
	{
	case Fail:
		logs::add("%1 нанес%2 удар, но промазал%3.", getname(), getLA(), getA());
		sufferharm(enemy.getharm());
		break;
	case PartialSuccess:
		logs::add("%1 и %2 провели короткий обмен ударами.", getname(), enemy.getname());
		inflictharm(enemy, getharm());
		sufferharm(enemy.getharm());
		break;
	default:
		logs::add("%1 нанес%2 сокрушающий удар. %3 присел%4 и захрипел%4.", getname(), getA(), enemy.getname(), enemy.getA());
		logs::add(2, "Избежать атаки врага");
		logs::add(1, "Нанести врагу дополнительно +1d6 урона");
		switch(whatdo(false))
		{
		case 1:
			inflictharm(enemy, getharm() + xrand(1, 6));
			sufferharm(enemy.getharm());
			break;
		default:
			inflictharm(enemy, getharm());
			break;
		}
		break;
	}
}

static void melee_round(monster& enemy)
{
	for(auto& player : players)
	{
		if(!player.iscombatable())
			continue;
		if(!enemy)
			return;
		logs::add(1, "Рубить и крушить их всех.");
		switch(player.whatdo())
		{
		case 1:
			player.hackandslash(enemy);
			break;
		}
	}
}

static void escape_combat(monster& enemy)
{
	if(!enemy.isalive())
		return;
	logs::add("Вы бросились бежать.", enemy.getname());
	for(auto& player : players)
	{
		if(!player.iscombatable())
			continue;
		auto id = player.defydanger(Dexterity);
		switch(id)
		{
		case Fail:
			logs::add("%1 попал%2 в окружение.", player.getname(), player.getA());
			player.sufferharm(enemy.getharm());
			break;
		case PartialSuccess:
			logs::add("%1 попал%2 под удар, но в целом избежал%2 окружения.", player.getname(), player.getA());
			player.sufferharm(enemy.getharm());
			player.set(Escape);
			break;
		default:
			logs::add("%1 удачно избежал%2 всех выпадов и скрыл%3 из виду.", player.getname(), player.getA(), player.getAS());
			player.set(Escape);
			break;
		}
	}
}

void hero::combat(monster& enemy)
{
	char temp[260];
	while(enemy.distance >= Near)
	{
		switch(enemy.distance)
		{
		case Far:
			logs::add("Далеко впереди вы заметили %1.", enemy.getname(temp));
			break;
		default:
			logs::add("Впереди вы заметили %1.", enemy.getname(temp));
			break;
		}
		// Все игроки подготовят оружие для нужной дистанции
		for(auto& player : players)
		{
			if(!player.iscombatable())
				continue;
			if(!player.prepareweapon(enemy))
				continue;
			if(player.weapon.is(enemy.distance) && player.isammo())
				logs::add(1, "Дать залп по врагу.");
			switch(player.whatdo())
			{
			case 1:
				player.volley(enemy);
				break;
			}
			if(!enemy.isalive())
				return;
		}
		if(enemy.is(enemy.distance))
		{
			logs::add("%1 дал%2 залп.", enemy.getname(), enemy.getA());
			for(auto& e : players)
			{
				if(!e)
					continue;
				if(e.defydanger(Dexterity))
					logs::add("%1 избежал%2 попадания.", e.getname(), e.getA());
				else
					e.sufferharm(enemy.getharm());
			}
		}
		enemy.distance = (distance_s)(enemy.distance - 1);
		logs::add("Враг подошел ближе.");
		logs::add(1, "Двинуться навстречу врагу");
		logs::add(2, "Бежать пока не поздно");
		if(logs::input() == 2)
			return;
	}
	logs::add("Около вас находится %1.", enemy.getname(temp));
	while(!isgameover() && enemy)
	{
		melee_round(enemy);
		if(enemy && !isgameover())
		{
			logs::add(1, "Продолжить сражаться");
			logs::add(2, "Пробывать бежать");
			auto id = logs::input(true, true, "Что будете делать?");
			if(id == 2)
				escape_combat(enemy);
		}
	}
	if(!enemy)
		logs::add("Похоже все враги побеждены.");
	logs::next();
	if(!enemy)
	{
		loot_i loot; loot.clear();
		enemy.getloot(loot);
		if(loot)
		{
			logs::add("Покопавшись в их остатках вы нашли: ");
			loot.getitems(logs::getptr(), false);
			logs::add(1, "Взять все с собой.");
			logs::add(2, "Не брать ничего. Все оставить здесь.");
			auto id = logs::input();
			if(id == 1)
			{
				hero::addcoins(loot.coins, true);
				for(auto& e : loot.item)
				{
					if(e)
						hero::pickup(e);
				}
			}
		}
	}
}

void hero::combat(monster_s id, distance_s distance, int count)
{
	monster enemy(id);
	enemy.distance = distance;
	if(count)
		enemy.count = count;
	combat(enemy);
}