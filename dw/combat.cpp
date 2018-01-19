#include "main.h"

bool hero::volley(monster& enemy, bool run)
{
	if(!enemy.isalive() || !weapon.is(enemy.distance) || !isammo(weapon.getammo()))
		return false;
	if(run)
	{
		auto bonus = get(Dexterity);
		auto result = roll(bonus);
		logs::add("%1 сделал%2 несколько выстрелов.", getname(), getA());
		switch(result)
		{
		case Fail:
			logs::add("Ќо все стрелы легли мимо цели.");
			if(enemy.is(enemy.distance))
			{
				logs::add("%1 выстрелил%2 в ответ.", enemy.getname(), enemy.getA());
				sufferharm(enemy.getharm());
			}
			break;
		case PartialSuccess:
			if(enemy.is(enemy.distance))
				logs::add(1, "’от€ пришлось подойти очень близко и подставитьс€ под удар.");
			logs::add(2, "Ќо, цели на самом деле достигло очень мало, -1d6 урона");
			logs::add(3, "ѕришлось сделать слишком много выстрелов, боезапас уменьшитс€ на единицу");
			switch(whatdo(false))
			{
			case 2:
				inflictharm(enemy, getharm() - xrand(1, 6));
				break;
			case 3:
				inflictharm(enemy, getharm());
				useammo(weapon.getammo(), true);
				break;
			default:
				inflictharm(enemy, getharm());
				logs::add("%1 выстрелил%2 в ответ.", enemy.getname(), enemy.getA());
				sufferharm(enemy.getharm());
				break;
			}
			break;
		default:
			inflictharm(enemy, getharm());
			break;
		}
	}
	return true;
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
		act("%герой нанес%ла удар, но промазал%а.");
		if(!apply(enemy.getmoves(), &enemy))
			sufferharm(enemy.getharm());
		break;
	case PartialSuccess:
		logs::add("%1 и %2 провели короткий обмен ударами.", getname(), enemy.getname());
		inflictharm(enemy, getharm());
		sufferharm(enemy.getharm());
		break;
	default:
		logs::add("%1 нанес%2 сокрушающий удар. %3 присел%4 и захрипел%4.", getname(), getA(), enemy.getname(), enemy.getA());
		logs::add(2, "»збежать атаки врага");
		logs::add(1, "Ќанести врагу дополнительно +1d6 урона");
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
		logs::add(HackAndSlash, "–убить и крушить их всех.");
		player.ask(SpellMagicMissile);
		player.ask(SpellFireball);
		player.ask(SpellInvisibility);
		auto move = (move_s)player.whatdo();
		switch(move)
		{
		case SpellMagicMissile:
		case SpellInvisibility:
			player.cast((spell_s)move, &enemy);
			break;
		case HackAndSlash:
			player.hackandslash(enemy);
			break;
		}
	}
}

static void escape_combat(monster& enemy)
{
	if(!enemy.isalive())
		return;
	logs::add("¬ы бросились бежать.");
	for(auto& player : players)
	{
		if(!player.iscombatable())
			continue;
		auto result = player.defydanger(Dexterity);
		switch(result)
		{
		case Fail:
			logs::add("%1 попал%2 в окружение.", player.getname(), player.getA());
			player.sufferharm(enemy.getharm());
			break;
		case PartialSuccess:
			logs::add("%1 попал%2 под удар, но в целом избежал%2 окружени€.", player.getname(), player.getA());
			player.sufferharm(enemy.getharm()/2);
			break;
		default:
			logs::add("%1 удачно избежал%2 всех выпадов и скрыл%3 из виду.", player.getname(), player.getA(), player.getAS());
			break;
		}
	}
}

void game::combat(monster& enemy)
{
	char temp[260];
	while(enemy.distance >= Near)
	{
		switch(enemy.distance)
		{
		case Far:
			logs::add("ƒалеко впереди вы заметили %1.", enemy.getname(temp));
			break;
		default:
			logs::add("¬переди вы заметили %1.", enemy.getname(temp));
			break;
		}
		// ¬се игроки подготов€т оружие дл€ нужной дистанции
		for(auto& player : players)
		{
			if(!player.iscombatable() || !enemy.isalive())
				continue;
			if(!player.prepareweapon(enemy))
				continue;
			if(player.volley(enemy, false))
				logs::add(1, "ƒать залп по врагу.");
			switch(player.whatdo())
			{
			case 1:
				player.volley(enemy, true);
				break;
			}
		}
		if(!enemy.isalive())
			break;
		if(enemy.is(enemy.distance))
		{
			logs::add("%1 дал%2 залп.", enemy.getname(), enemy.getA());
			for(auto& e : players)
			{
				if(!e)
					continue;
				if(e.defydanger(Dexterity))
					logs::add("%1 избежал%2 попадани€.", e.getname(), e.getA());
				else
					e.sufferharm(enemy.getharm());
			}
		}
		enemy.distance = (distance_s)(enemy.distance - 1);
		logs::add("¬раг подошел ближе.");
		logs::add(1, "ƒвинутьс€ навстречу врагу");
		logs::add(2, "Ѕежать пока не поздно");
		if(logs::input() == 2)
			return;
	}
	if(enemy.isalive())
	{
		logs::add("ќколо вас находитс€ %1.", enemy.getname(temp));
		while(!isgameover() && enemy)
			melee_round(enemy);
	}
	if(!enemy)
		logs::add("ѕохоже все враги побеждены.");
	logs::next();
	if(!enemy)
	{
		loot_i loot; loot.clear();
		enemy.getloot(loot);
		if(loot)
		{
			logs::add("ѕокопавшись в их остатках вы нашли: ");
			loot.getitems(logs::getptr(), false);
			logs::add(1, "¬з€ть все с собой.");
			logs::add(2, "Ќе брать ничего. ¬се оставить здесь.");
			auto id = logs::input();
			if(id == 1)
			{
				hero::addcoins(loot.coins, true);
				logs::next();
				for(auto& e : loot.item)
				{
					if(e)
						pickup(e);
				}
			}
		}
	}
}

void game::combat(monster_s id, distance_s distance, int count)
{
	monster enemy(id);
	enemy.distance = distance;
	if(count)
		enemy.count = count;
	combat(enemy);
}