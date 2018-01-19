#include "main.h"

bool hero::volley(monster& enemy, bool run) {
	if(!enemy || !weapon.is(enemy.distance) || !isammo(weapon.getammo()))
		return false;
	if(run) {
		auto bonus = get(Dexterity);
		auto result = roll(bonus);
		logs::add("%1 сделал%2 несколько выстрелов.", getname(), getA());
		switch(result) {
		case Fail:
			logs::add("Ќо все стрелы легли мимо цели.");
			if(enemy.is(enemy.distance)) {
				enemy.act("%герой выстрелил%а в ответ.");
				sufferharm(enemy.getharm());
			}
			break;
		case PartialSuccess:
			if(enemy.is(enemy.distance))
				logs::add(1, "’от€ пришлось подойти очень близко и подставитьс€ под удар.");
			logs::add(2, "Ќо, цели на самом деле достигло очень мало, -1d6 урона");
			logs::add(3, "ѕришлось сделать слишком много выстрелов, боезапас уменьшитс€ на единицу");
			switch(whatdo(false)) {
			case 2:
				inflictharm(enemy, getharm() - xrand(1, 6));
				break;
			case 3:
				inflictharm(enemy, getharm());
				useammo(weapon.getammo(), true);
				break;
			default:
				inflictharm(enemy, getharm());
				enemy.act("%герой выстрелил%а в ответ.");
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

void hero::hackandslash(monster& enemy) {
	auto bonus = get(Strenght);
	if(weapon.is(Precise)
		|| (race == Elf && type == Fighter && weapon.type == SwordLong))
		bonus = get(Dexterity);
	auto result = roll(bonus);
	switch(result) {
	case Fail:
		act("%герой нанес%ла удар, но промазал%а.");
		if(d100()<60 && !apply(enemy.getmoves(), &enemy))
			sufferharm(enemy.getharm());
		break;
	case PartialSuccess:
		logs::add("%1 и %2 провели короткий обмен ударами.", getname(), enemy.getname());
		inflictharm(enemy, getharm());
		sufferharm(enemy.getharm());
		break;
	default:
		act("%герой нанес%ла сокрушающий удар."); enemy.act("%герой присел%а и захрипел%а.");
		logs::add(2, "»збежать атаки врага");
		logs::add(1, "Ќанести врагу дополнительно +1d6 урона");
		switch(whatdo(false)) {
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

static bool melee_round(monster& enemy) {
	for(auto& player : players) {
		if(!player.iscombatable())
			continue;
		if(!enemy)
			return true;
		logs::add(HackAndSlash, "–убить и крушить их всех.");
		player.ask(SpellMagicMissile);
		player.ask(SpellFireball);
		player.ask(SpellInvisibility);
		auto move = (move_s)player.whatdo();
		switch(move) {
		case SpellMagicMissile:
		case SpellInvisibility:
			player.cast((spell_s)move, &enemy);
			break;
		case HackAndSlash:
			player.hackandslash(enemy);
			break;
		}
	}
	return true;
}

static void description(monster& enemy) {
	char temp[260];
	switch(enemy.distance) {
	case Far:
		logs::add("ƒалеко впереди вы заметили %1.", enemy.getname(temp));
		break;
	case Near:
		logs::add("Ќедалеко от вас вы заметили %1.", enemy.getname(temp));
		break;
	default:
		logs::add("ќколо вас находитс€ %1.", enemy.getname(temp));
		break;
	}
}

static bool range_combat(monster& enemy) {
	description(enemy);
	// ¬се игроки подготов€т оружие дл€ нужной дистанции
	for(auto& player : players) {
		if(!enemy)
			return true;
		if(!player.iscombatable() || !enemy)
			continue;
		if(!player.prepareweapon(enemy))
			continue;
		if(player.volley(enemy, false))
			logs::add(1, "ƒать залп по врагу.");
		switch(player.whatdo()) {
		case 1:
			player.volley(enemy, true);
			break;
		}
	}
	if(!enemy)
		return true;
	if(enemy.is(enemy.distance)) {
		enemy.act("%герой дал%а залп.");
		for(auto& e : players) {
			if(!e)
				continue;
			if(e.defydanger(Dexterity))
				logs::add("%1 избежал%2 попадани€.", e.getname(), e.getA());
			else
				e.sufferharm(enemy.getharm());
		}
	}
	logs::add("¬раг подошел ближе."); enemy.distance = (distance_s)(enemy.distance - 1);
	logs::add(1, "—то€ть и сражатьс€");
	logs::add(2, "Ѕежать пока не поздно");
	if(logs::input() == 2)
		return false;
	return true;
}

bool game::combat(monster& enemy) {
	while(enemy) {
		while(enemy.distance >= Near) {
			if(!range_combat(enemy))
				return false;
		}
		if(enemy) {
			description(enemy);
			while(!isgameover() && enemy) {
				if(!melee_round(enemy))
					return false;
			}
		}
		if(isgameover())
			return false;
		if(enemy.regroup>0) {
			logs::add("ѕохоже сейчас враги убежали, но должны вернутьс€ с минуты на минуту с подкреплением.");
			logs::add(1, "”строить им теплый прием");
			logs::add(0, "Ѕежать отсюда пока есть возможность");
			auto id = whatdo();
			if(!id)
				return false;
			enemy.set(enemy.type);
			enemy.distance = Near;
			enemy.regroup = -1;
			continue;
		}
		break;
	}
	logs::add("ѕохоже все враги побеждены.");
	logs::next();
	auto hoard = enemy.getdamage().roll();
	lootinfo loot; loot.generate(hoard);
	if(loot) {
		logs::add("ѕокопавшись в их остатках вы нашли: ");
		loot.pickup();
	}
	return true;
}

bool game::combat(monster_s id, distance_s distance, int count) {
	monster enemy(id);
	enemy.distance = distance;
	if(count)
		enemy.count = count;
	return combat(enemy);
}