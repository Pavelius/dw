#include "main.h"

using namespace game;

static void combat_printer(stringbuilder sb) {
	hero::getparty(sb);
}

void hero::volley(thing& enemy, distance_s distance) {
	auto result = roll(Volley);
	act("%герой сделал%а несколько выстрелов.");
	switch(result) {
	case Fail:
		sb.add("Ќо все стрелы легли мимо цели.");
		//if(enemy.is(distance)) {
		//	enemy.act("%герой выстрелил%а в ответ.");
		//	sufferharm(enemy.getharm());
		//}
		break;
	case PartialSuccess:
		//if(enemy.is(enemy.distance))
		//	an.add(1, "’от€ пришлось подойти очень близко и подставитьс€ под удар.");
		an.add(2, "Ќо, цели на самом деле достигло очень мало, -1d6 урона");
		if(weapon.getammo())
			an.add(3, "ѕришлось сделать слишком много выстрелов, боезапас уменьшитс€ на единицу");
		switch(an.choose(true, false, 0)) {
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

bool hero::turnundead(thing& enemy) {
	auto result = roll(TurnUndead);
	act("%герой выставил%а вперед св€той символ произнес%ла:\n");
	act(" - ¬о им€, %1 сгиньте в аду преисподни!\n", getstr(diety));
	switch(result) {
	case Fail:
		enemy.act("%герой зарычал%а от €рости и бросил%ась в атаку.");
		sufferharm(enemy.getharm());
		return false;
	case PartialSuccess:
		enemy.act("ћертвецы замерли в ожидании и начали злобно шипеть в вашу сторону. ¬идно, что они не могут теперь к вам подойти, но они ждут, когда вы расслабитесь и дадите слабинку.");
		//enemy.count = 0;
		return true;
	default:
		act("¬се мертвецы вокруг издали вопль ужаса и бросилсь бежать.");
		enemy.setcount(0);
		return true;
	}
}

void hero::hackandslash(thing& enemy) {
	auto result = roll(HackAndSlash);
	auto skip = false;
	switch(result) {
	case Fail:
		act("%герой нанес%ла удар, но промазал%а.");
		enemy.act(HackAndSlash);
		sufferharm(enemy.getharm());
		//skip = d100() < 60 && apply(enemy.getmoves(), &enemy);
		//if(!skip)
		break;
	case PartialSuccess:
		act("%герой и %1 провели короткий обмен ударами.", enemy.getname());
		inflictharm(enemy, getharm());
		sufferharm(enemy.getharm());
		break;
	default:
		act("%герой нанес%ла сокрушающий удар."); enemy.act("%герой присел%а и захрипел%а.");
		an.add(2, "»збежать атаки врага");
		an.add(1, "Ќанести врагу дополнительно +1d6 урона");
		switch(choosen(0)) {
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

static void description(thing& enemy, distance_s d) {
	switch(d) {
	case Far: enemy.act("ƒалеко впереди вы заметили %банда."); break;
	case Near: enemy.act("Ќедалеко от вас вы заметили %банда."); break;
	default: enemy.act("ќколо вас находитс€ %банда."); break;
	}
}

//static bool range_combat(monster& enemy) {
//	for(auto& player : bsmeta<hero>()) {
//		if(!enemy)
//			return true;
//		if(!player.iscombatable() || !enemy)
//			continue;
//		if(!player.prepareweapon(enemy))
//			continue;
//		if(!player.weapon.is(enemy.distance) || !player.isammo(player.weapon.getammo()))
//			continue;
//		an.add(variant(Volley), "ƒать залп по врагу.");
//		ask_spells(player, enemy);
//		variant id = player.whatdo();
//		if(id.type == Spell)
//			player.cast((spell_s)id.subtype, &enemy);
//		else if(id.type==Move) {
//			switch(id.subtype) {
//			case Volley: player.volley(enemy); break;
//			}
//		}
//	}
//	if(!enemy)
//		return true;
//	// ’од врагов
//	if(enemy.is(enemy.distance)) {
//		enemy.act("%герой дал%а залп.");
//		for(auto& e : bsmeta<hero>()) {
//			if(!e)
//				continue;
//			auto result = e.defydanger(Dexterity);
//			if(result>=PartialSuccess)
//				e.act("%герой избежал%а попадани€.");
//			else
//				e.sufferharm(enemy.getharm());
//		}
//	}
//	sb.add("¬раг подошел ближе."); enemy.distance = (distance_s)(enemy.distance - 1);
//	an.add(1, "—то€ть и сражатьс€");
//	an.add(0, "Ѕежать пока не поздно");
//	if(!an.choose())
//		return false;
//	return true;
//}

static bool iscontinue() {
	for(auto& e : bsmeta<hero>()) {
		if(e.iscombatable())
			return true;
	}
	return false;
}

static void finish() {
	static spell_s spells[] = {SpellBless, SpellInvisibility};
	for(auto& e : bsmeta<hero>()) {
		if(!e)
			continue;
		for(auto s : spells)
			e.remove(s);
	}
}

//static bool main_combat(monster& enemy) {
//	while(iscontinue() && enemy) {
//		description(enemy);
//		if(enemy.distance >= Near) {
//			if(!range_combat(enemy))
//				return false;
//		} else
//			melee_round(enemy);
//	}
//	if(isgameover())
//		return false;
//	if(enemy.effect == Regroup) {
//		sb.add("¬раг бежал, но скоро вернетс€ вновь и их будет больше.");
//		logs::next();
//		return true;
//	} else if(enemy) {
//		sb.add("¬ам удалось бежать.");
//		logs::next();
//		return false;
//	}
//	sb.add("ѕохоже все враги побеждены.");
//	logs::next();
//	auto hoard = enemy.getdamage().roll();
//	looti loot;
//	loot.clear();
//	loot.generate(hoard);
//	if(loot) {
//		sb.add("ѕокопавшись в их остатках вы нашли: ");
//		loot.pickup();
//	}
//	return true;
//}

hero* hero::chooseother(const char* format, ...) const {
	return 0;
}

hero* hero::takecover(thing& enemy) {
	auto result = roll(HackAndSlash);
	switch(result) {
	case Fail:
		act("%герой замешал%ась и потер€л%а бдительность.");
		enemy.act(HackAndSlash);
		sufferharm(enemy.getharm());
		return this;
	case PartialSuccess:
		enemy.act(HackAndSlash);
		sufferharm(enemy.getharm());
		return chooseother("— кем помен€етс€ %герой?");
	default:
		act("%герой ловко увернул%ась от всех ударов и отступил%а назад.");
		return chooseother("— кем помен€етс€ %герой?");
	}
}

static void melee_round(hero* player, thing& enemy) {
	while(player->isalive()) {
		if(!player->iscombatable())
			continue;
		if(!enemy || !enemy.isalive())
			return;
		an.add(variant(HackAndSlash), "–убить и крушить их всех.");
		an.add(variant(DefyDangerDexterity), "—крытьс€ за спинами более крепких товарищей.");
		if(player->is(TurnUndead) && enemy.is(Undead))
			an.add(variant(TurnUndead), "ќтпугнуть мертвых.");
		//ask_spells(player, enemy);
		variant id = player->choose(0);
		switch(id.type) {
		case Spell:
			break;
		case Move:
			switch(id.subtype) {
			case HackAndSlash: player->hackandslash(enemy); break;
			case DefyDangerDexterity: player = player->takecover(enemy); break;
			case TurnUndead: player->turnundead(enemy); break;
			}
			break;
		}
	}
}

result_s hero::fight(thing& enemy) {
	auto distance = Close;
	description(enemy, distance);
	while(iscontinue() && enemy) {
		melee_round(getplayer(), enemy);
	}
	return Success;
}