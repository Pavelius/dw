#include "main.h"

using namespace game;

static void combat_printer(stringbuilder sb) {
	hero::getparty(sb);
}

void hero::volley(thing& enemy, distance_s distance) {
	auto result = roll(Volley);
	act("%����� ������%� ��������� ���������.");
	switch(result) {
	case Fail:
		sb.add("�� ��� ������ ����� ���� ����.");
		//if(enemy.is(distance)) {
		//	enemy.act("%����� ���������%� � �����.");
		//	sufferharm(enemy.getharm());
		//}
		break;
	case PartialSuccess:
		//if(enemy.is(enemy.distance))
		//	an.add(1, "���� �������� ������� ����� ������ � ������������ ��� ����.");
		an.add(2, "��, ���� �� ����� ���� �������� ����� ����, -1d6 �����");
		if(weapon.getammo())
			an.add(3, "�������� ������� ������� ����� ���������, �������� ���������� �� �������");
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
			enemy.act("%����� ���������%� � �����.");
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
	act("%����� ��������%� ������ ������ ������ ��������%��:\n");
	act(" - �� ���, %1 ������� � ��� ����������!\n", getstr(diety));
	switch(result) {
	case Fail:
		enemy.act("%����� �������%� �� ������ � ������%��� � �����.");
		sufferharm(enemy.getharm());
		return false;
	case PartialSuccess:
		enemy.act("�������� ������� � �������� � ������ ������ ������ � ���� �������. �����, ��� ��� �� ����� ������ � ��� �������, �� ��� ����, ����� �� ������������ � ������ ��������.");
		//enemy.count = 0;
		return true;
	default:
		act("��� �������� ������ ������ ����� ����� � �������� ������.");
		enemy.setcount(0);
		return true;
	}
}

void hero::hackandslash(thing& enemy) {
	auto result = roll(HackAndSlash);
	auto skip = false;
	switch(result) {
	case Fail:
		act("%����� �����%�� ����, �� ��������%�.");
		enemy.act(HackAndSlash);
		sufferharm(enemy.getharm());
		//skip = d100() < 60 && apply(enemy.getmoves(), &enemy);
		//if(!skip)
		break;
	case PartialSuccess:
		act("%����� � %1 ������� �������� ����� �������.", enemy.getname());
		inflictharm(enemy, getharm());
		sufferharm(enemy.getharm());
		break;
	default:
		act("%����� �����%�� ����������� ����."); enemy.act("%����� ������%� � ��������%�.");
		an.add(2, "�������� ����� �����");
		an.add(1, "������� ����� ������������� +1d6 �����");
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
	case Far: enemy.act("������ ������� �� �������� %�����."); break;
	case Near: enemy.act("�������� �� ��� �� �������� %�����."); break;
	default: enemy.act("����� ��� ��������� %�����."); break;
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
//		an.add(variant(Volley), "���� ���� �� �����.");
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
//	// ��� ������
//	if(enemy.is(enemy.distance)) {
//		enemy.act("%����� ���%� ����.");
//		for(auto& e : bsmeta<hero>()) {
//			if(!e)
//				continue;
//			auto result = e.defydanger(Dexterity);
//			if(result>=PartialSuccess)
//				e.act("%����� �������%� ���������.");
//			else
//				e.sufferharm(enemy.getharm());
//		}
//	}
//	sb.add("���� ������� �����."); enemy.distance = (distance_s)(enemy.distance - 1);
//	an.add(1, "������ � ���������");
//	an.add(0, "������ ���� �� ������");
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
//		sb.add("���� �����, �� ����� �������� ����� � �� ����� ������.");
//		logs::next();
//		return true;
//	} else if(enemy) {
//		sb.add("��� ������� ������.");
//		logs::next();
//		return false;
//	}
//	sb.add("������ ��� ����� ���������.");
//	logs::next();
//	auto hoard = enemy.getdamage().roll();
//	looti loot;
//	loot.clear();
//	loot.generate(hoard);
//	if(loot) {
//		sb.add("����������� � �� �������� �� �����: ");
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
		act("%����� �������%��� � �������%� ������������.");
		enemy.act(HackAndSlash);
		sufferharm(enemy.getharm());
		return this;
	case PartialSuccess:
		enemy.act(HackAndSlash);
		sufferharm(enemy.getharm());
		return chooseother("� ��� ���������� %�����?");
	default:
		act("%����� ����� �������%��� �� ���� ������ � ��������%� �����.");
		return chooseother("� ��� ���������� %�����?");
	}
}

static void melee_round(hero* player, thing& enemy) {
	while(player->isalive()) {
		if(!player->iscombatable())
			continue;
		if(!enemy || !enemy.isalive())
			return;
		an.add(variant(HackAndSlash), "������ � ������� �� ����.");
		an.add(variant(DefyDangerDexterity), "�������� �� ������� ����� ������� ���������.");
		if(player->is(TurnUndead) && enemy.is(Undead))
			an.add(variant(TurnUndead), "��������� �������.");
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