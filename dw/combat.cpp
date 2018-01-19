#include "main.h"

bool hero::volley(monster& enemy, bool run) {
	if(!enemy || !weapon.is(enemy.distance) || !isammo(weapon.getammo()))
		return false;
	if(run) {
		auto bonus = get(Dexterity);
		auto result = roll(bonus);
		logs::add("%1 ������%2 ��������� ���������.", getname(), getA());
		switch(result) {
		case Fail:
			logs::add("�� ��� ������ ����� ���� ����.");
			if(enemy.is(enemy.distance)) {
				enemy.act("%����� ���������%� � �����.");
				sufferharm(enemy.getharm());
			}
			break;
		case PartialSuccess:
			if(enemy.is(enemy.distance))
				logs::add(1, "���� �������� ������� ����� ������ � ������������ ��� ����.");
			logs::add(2, "��, ���� �� ����� ���� �������� ����� ����, -1d6 �����");
			logs::add(3, "�������� ������� ������� ����� ���������, �������� ���������� �� �������");
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
		act("%����� �����%�� ����, �� ��������%�.");
		if(d100()<60 && !apply(enemy.getmoves(), &enemy))
			sufferharm(enemy.getharm());
		break;
	case PartialSuccess:
		logs::add("%1 � %2 ������� �������� ����� �������.", getname(), enemy.getname());
		inflictharm(enemy, getharm());
		sufferharm(enemy.getharm());
		break;
	default:
		act("%����� �����%�� ����������� ����."); enemy.act("%����� ������%� � ��������%�.");
		logs::add(2, "�������� ����� �����");
		logs::add(1, "������� ����� ������������� +1d6 �����");
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
		logs::add(HackAndSlash, "������ � ������� �� ����.");
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
		logs::add("������ ������� �� �������� %1.", enemy.getname(temp));
		break;
	case Near:
		logs::add("�������� �� ��� �� �������� %1.", enemy.getname(temp));
		break;
	default:
		logs::add("����� ��� ��������� %1.", enemy.getname(temp));
		break;
	}
}

static bool range_combat(monster& enemy) {
	description(enemy);
	// ��� ������ ���������� ������ ��� ������ ���������
	for(auto& player : players) {
		if(!enemy)
			return true;
		if(!player.iscombatable() || !enemy)
			continue;
		if(!player.prepareweapon(enemy))
			continue;
		if(player.volley(enemy, false))
			logs::add(1, "���� ���� �� �����.");
		switch(player.whatdo()) {
		case 1:
			player.volley(enemy, true);
			break;
		}
	}
	if(!enemy)
		return true;
	if(enemy.is(enemy.distance)) {
		enemy.act("%����� ���%� ����.");
		for(auto& e : players) {
			if(!e)
				continue;
			if(e.defydanger(Dexterity))
				logs::add("%1 �������%2 ���������.", e.getname(), e.getA());
			else
				e.sufferharm(enemy.getharm());
		}
	}
	logs::add("���� ������� �����."); enemy.distance = (distance_s)(enemy.distance - 1);
	logs::add(1, "������ � ���������");
	logs::add(2, "������ ���� �� ������");
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
			logs::add("������ ������ ����� �������, �� ������ ��������� � ������ �� ������ � �������������.");
			logs::add(1, "�������� �� ������ �����");
			logs::add(0, "������ ������ ���� ���� �����������");
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
	logs::add("������ ��� ����� ���������.");
	logs::next();
	auto hoard = enemy.getdamage().roll();
	lootinfo loot; loot.generate(hoard);
	if(loot) {
		logs::add("����������� � �� �������� �� �����: ");
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