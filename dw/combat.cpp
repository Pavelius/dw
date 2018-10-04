#include "main.h"

using namespace game;

static bool isallow(hero& player, monster& enemy, spell_s id) {
	if(!player.isprepared(id))
		return false;
	if(player.is(id))
		return false;
	switch(id) {
	case SpellMagicMissile:
	case SpellInvisibility:
	case SpellFireball:
	case SpellBless:
		return true;
	case SpellCureLightWounds:
		for(auto& e : players) {
			if(!e)
				continue;
			if(e.hp < e.getmaxhits())
				return true;
		}
		return false;
	default:
		return false;
	}
}

void ask_spells(hero& player, monster& enemy) {
	for(auto i = FirstSpell; i <= LastSpell; i=(spell_s)(i+1)) {
		if(!isallow(player, enemy, i))
			continue;
		logs::add(tid(i), "Использовать заклинание '%1'", getstr(i));
	}
}

void hero::volley(monster& enemy) {
	auto result = roll(Volley);
	act("%1 сделал%2 несколько выстрелов.", getname(), getA());
	switch(result) {
	case Fail:
		logs::add("Но все стрелы легли мимо цели.");
		if(enemy.is(enemy.distance)) {
			enemy.act("%герой выстрелил%а в ответ.");
			sufferharm(enemy.getharm());
		}
		break;
	case PartialSuccess:
		if(enemy.is(enemy.distance))
			logs::add(1, "Хотя пришлось подойти очень близко и подставиться под удар.");
		logs::add(2, "Но, цели на самом деле достигло очень мало, -1d6 урона");
		if(weapon.getammo())
			logs::add(3, "Пришлось сделать слишком много выстрелов, боезапас уменьшится на единицу");
		switch(whatdo(false)) {
		case 2:
			inflictharm(enemy, getharm() - xrand(1, 6));
			break;
		case 3:
			inflictharm(enemy, getharm());
			useammo(weapon.getammo(), true, true);
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

void hero::turnundead(monster& enemy) {
	char temp[260];
	auto result = roll(TurnUndead);
	act("%герой выставил%а вперед святой символ произнес%ла:\n");
	act(" - Во имя, %1 сгиньте в аду преисподни!\n", grammar::of(temp, zendof(temp), getstr(diety)));
	switch(result) {
	case Fail:
		enemy.act("%1 зарычал%а и бросил%ась в атаку.", enemy.getname(temp, zendof(temp)));
		sufferharm(enemy.getharm());
		break;
	case PartialSuccess:
		act("Все мертвецы вокруг издали вопль ужаса и бросилсь бежать.");
		enemy.count = 0;
		break;
	default:
		act("Все мертвецы вокруг издали вопль ужаса и бросилсь бежать.");
		enemy.count = 0;
		break;
	}
}

void hero::hackandslash(monster& enemy) {
	auto result = roll(HackAndSlash);
	bool skip = false;
	switch(result) {
	case Fail:
		act("%герой нанес%ла удар, но промазал%а.");
		skip = d100() < 60 && apply(enemy.getmoves(), &enemy);
		if(!skip)
			sufferharm(enemy.getharm());
		break;
	case PartialSuccess:
		logs::add("%1 и %2 провели короткий обмен ударами.", getname(), enemy.getname());
		inflictharm(enemy, getharm());
		sufferharm(enemy.getharm());
		break;
	default:
		act("%герой нанес%ла сокрушающий удар."); enemy.act("%герой присел%а и захрипел%а.");
		logs::add(2, "Избежать атаки врага");
		logs::add(1, "Нанести врагу дополнительно +1d6 урона");
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

static void melee_round(monster& enemy) {
	for(auto& player : players) {
		if(!player.iscombatable())
			continue;
		if(!enemy)
			return;
		logs::add(tid(HackAndSlash), "Рубить и крушить их всех.");
		if(player.is(TurnUndead) && enemy.is(Undead))
			logs::add(tid(TurnUndead), "Отпугнуть мертвых.");
		ask_spells(player, enemy);
		tid id = player.whatdo();
		if(id.type == Spells)
			player.cast((spell_s)id.value, &enemy);
		else {
			switch(id) {
			case tid(HackAndSlash): player.hackandslash(enemy); break;
			case tid(TurnUndead): player.turnundead(enemy); break;
			}
		}
	}
}

static void description(monster& enemy) {
	char temp[260];
	switch(enemy.distance) {
	case Far:
		logs::add("Далеко впереди вы заметили %1.", enemy.getname(temp, zendof(temp)));
		break;
	case Near:
		logs::add("Недалеко от вас вы заметили %1.", enemy.getname(temp, zendof(temp)));
		break;
	default:
		logs::add("Около вас находится %1.", enemy.getname(temp, zendof(temp)));
		break;
	}
}

static bool range_combat(monster& enemy) {
	for(auto& player : players) {
		if(!enemy)
			return true;
		if(!player.iscombatable() || !enemy)
			continue;
		if(!player.prepareweapon(enemy))
			continue;
		if(!player.weapon.is(enemy.distance) || !player.isammo(player.weapon.getammo()))
			continue;
		logs::add(tid(Volley), "Дать залп по врагу.");
		ask_spells(player, enemy);
		tid id = player.whatdo();
		if(id.type == Spells)
			player.cast((spell_s)id.value, &enemy);
		else {
			switch(id) {
			case tid(Volley): player.volley(enemy); break;
			}
		}
	}
	if(!enemy)
		return true;
	// Ход врагов
	if(enemy.is(enemy.distance)) {
		enemy.act("%герой дал%а залп.");
		for(auto& e : players) {
			if(!e)
				continue;
			auto result = e.defydanger(Dexterity);
			if(result>=PartialSuccess)
				e.act("%герой избежал%а попадания.");
			else
				e.sufferharm(enemy.getharm());
		}
	}
	logs::add("Враг подошел ближе."); enemy.distance = (distance_s)(enemy.distance - 1);
	logs::add(1, "Стоять и сражаться");
	logs::add(0, "Бежать пока не поздно");
	if(!logs::input())
		return false;
	return true;
}

static bool iscontinue() {
	for(auto& e : players) {
		if(e.iscombatable())
			return true;
	}
	return false;
}

static void finish() {
	static spell_s spells[] = {SpellBless, SpellInvisibility};
	for(auto& e : players) {
		if(!e)
			continue;
		for(auto s : spells)
			e.remove(s);
	}
}

static bool main_combat(monster& enemy) {
	logs::state push;
	logc.monster = &enemy;
	while(iscontinue() && enemy) {
		description(enemy);
		if(enemy.distance >= Near) {
			if(!range_combat(enemy))
				return false;
		} else
			melee_round(enemy);
	}
	if(isgameover())
		return false;
	if(enemy.effect == Regroup) {
		logs::add("Враг бежал, но скоро вернется вновь и их удет больше.");
		logs::next();
		return true;
	} else if(enemy) {
		logs::add("Вам удалось бежать.");
		logs::next();
		return false;
	}
	logs::add("Похоже все враги побеждены.");
	logs::next();
	auto hoard = enemy.getdamage().roll();
	lootinfo loot;
	loot.clear();
	loot.generate(hoard);
	if(loot) {
		logs::add("Покопавшись в их остатках вы нашли: ");
		loot.pickup();
	}
	return true;
}

bool game::combat(monster& enemy) {
	auto result = main_combat(enemy);
	finish();
	return result;
}

bool game::combat(monster_s id, distance_s distance, int count) {
	monster enemy(id);
	enemy.distance = distance;
	if(count)
		enemy.count = count;
	return combat(enemy);
}