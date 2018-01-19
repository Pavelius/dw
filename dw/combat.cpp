#include "main.h"

void hero::volley(monster& enemy) {
	auto result = roll(Volley);
	act("%1 ������%2 ��������� ���������.", getname(), getA());
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

void hero::hackandslash(monster& enemy) {
	auto result = roll(HackAndSlash);
	bool skip = false;
	switch(result) {
	case Fail:
		act("%����� �����%�� ����, �� ��������%�.");
		skip = d100() < 60 && apply(enemy.getmoves(), &enemy);
		if(!skip)
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

static void melee_round(monster& enemy) {
	for(auto& player : players) {
		if(!player.iscombatable())
			continue;
		if(!enemy)
			return;
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
	// ��� ������ ���������� ������ ��� ������ ���������
	for(auto& player : players) {
		if(!enemy)
			return true;
		if(!player.iscombatable() || !enemy)
			continue;
		if(!player.prepareweapon(enemy))
			continue;
		if(!player.weapon.is(enemy.distance) || !player.isammo(player.weapon.getammo()))
			continue;
		player.volley(enemy);
		logs::add(1, "���� ���� �� �����.");
		switch(player.whatdo()) {
		case 1:
			player.volley(enemy);
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
	logs::add(0, "������ ���� �� ������");
	if(!logs::input())
		return false;
	return true;
}

bool game::combat(monster& enemy) {
	int regroup = 0;
	while(true) {
		while(!isgameover() && enemy) {
			description(enemy);
			if(enemy.distance >= Near) {
				if(!range_combat(enemy))
					return false;
			} else
				melee_round(enemy);
		}
		if(isgameover())
			return false;
		if(regroup == 0 && enemy.effect == Regroup) {
			logs::add("������ ������ ����� �������, �� ������ ��������� � ������ �� ������ � �������������.");
			logs::add(1, "�������� �� ������ �����");
			logs::add(0, "������ ������ ���� ���� �����������");
			auto id = whatdo();
			if(!id)
				return false;
			logs::add("������������������� ��� ������ �����.");
			enemy.set(enemy.type);
			enemy.distance = Near;
			enemy.effect = NoEffect;
			regroup++;
			continue;
		}
		break;
	}
	logs::add("������ ��� ����� ���������.");
	logs::next();
	auto hoard = enemy.getdamage().roll();
	lootinfo loot;
	loot.clear();
	loot.generate(hoard);
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