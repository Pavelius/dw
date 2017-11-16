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
			logs::next();
			return;
		case PartialSuccess:
			logs::add(1, "Хотя пришлось подойти очень близко.");
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
		logs::add(1, "Нанести врагу дополнительно +1d6 урона");
		logs::add(2, "Избежать атаки врага");
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
	result_s result;
	for(auto& player : players)
	{
		if(!player || !player.isalive())
			continue;
		if(!enemy)
		{
			logs::add("Похоже вы зарубили всех врагов.");
			logs::next();
			return;
		}
		logs::add(1, "Рубить и крушить их всех.");
		logs::add(10, "Бежать отсюда прочь.");
		auto id = player.whatdo();
		switch(id)
		{
		case 1:
			player.hackandslash(enemy);
			break;
		case 10:
			result = player.defydanger(Dexterity);
			if(result == Fail)
			{
				logs::add("Вы попытались бежать, но вам не повезло. Вы подсказнулись и замедлели. %opponent нанес удар.");
				player.sufferharm(enemy.getharm());
				continue;
			}
			else if(result==PartialSuccess)
			{
				logs::add("Вы увернулись от очередного удара врага и рванули назад. %opponent нанес удар вам вслед.");
				player.sufferharm(enemy.getharm());
				if(!player.isalive())
					logs::add("Черт, вам таки не повезло. Этот удар вас убил.");
				else
					logs::add("Теперь вас не догонят.");
			}
			else
				logs::add("Вы удачно увернулись от очередного удара врага и рванули назад. %opponent нанес удар вам вслед, но промахнулся. Теперь вас не догонят.");
			logs::next();
			return;
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
			if(enemy.weapon)
				logs::add("Каждый из них носил %1.", enemy.weapon.getname(temp, false));
			break;
		}
		// Все игроки подготовят оружие для нужной дистанции
		for(auto& player : players)
		{
			if(!player)
				continue;
			if(!player.prepareweapon(enemy))
				continue;
			if(player.weapon.is(enemy.distance) && player.isammo())
				logs::add(1, "Дать залп по врагу.");
			logs::add(100, "Ничего не делать.");
			switch(player.whatdo())
			{
			case 1:
				player.volley(enemy);
				break;
			}
			if(!enemy.isalive())
				return;
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
		melee_round(enemy);
}

void hero::combat(monster_s id)
{
	monster enemy(id);
	combat(enemy);
}