#include "main.h"

bool hero::volley(monster& enemy, bool run)
{
	if(!enemy.isalive() || !weapon.is(enemy.distance) || !isammo(weapon.getammo()))
		return false;
	if(run)
	{
		auto bonus = get(Dexterity);
		auto result = roll(bonus);
		logs::add("%1 ������%2 ��������� ���������.", getname(), getA());
		switch(result)
		{
		case Fail:
			logs::add("�� ��� ������ ����� ���� ����.");
			if(enemy.is(enemy.distance))
			{
				logs::add("%1 ���������%2 � �����.", enemy.getname(), enemy.getA());
				sufferharm(enemy.getharm());
			}
			break;
		case PartialSuccess:
			if(enemy.is(enemy.distance))
				logs::add(1, "���� �������� ������� ����� ������ � ������������ ��� ����.");
			logs::add(2, "��, ���� �� ����� ���� �������� ����� ����, -1d6 �����");
			logs::add(3, "�������� ������� ������� ����� ���������, �������� ���������� �� �������");
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
				logs::add("%1 ���������%2 � �����.", enemy.getname(), enemy.getA());
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
		logs::add("%1 �����%2 ����, �� ��������%3.", getname(), getLA(), getA());
		sufferharm(enemy.getharm());
		break;
	case PartialSuccess:
		logs::add("%1 � %2 ������� �������� ����� �������.", getname(), enemy.getname());
		inflictharm(enemy, getharm());
		sufferharm(enemy.getharm());
		break;
	default:
		logs::add("%1 �����%2 ����������� ����. %3 ������%4 � ��������%4.", getname(), getA(), enemy.getname(), enemy.getA());
		logs::add(2, "�������� ����� �����");
		logs::add(1, "������� ����� ������������� +1d6 �����");
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
		logs::add(HackAndSlash, "������ � ������� �� ����.");
		player.ask(SpellMagicMissile);
		player.ask(SpellFireball);
		player.ask(SpellInvisibility);
		switch(player.whatdo())
		{
		case SpellMagicMissile:
			player.cast(SpellMagicMissile, &enemy);
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
	logs::add("�� ��������� ������.", enemy.getname());
	for(auto& player : players)
	{
		if(!player.iscombatable())
			continue;
		auto id = player.defydanger(Dexterity);
		switch(id)
		{
		case Fail:
			logs::add("%1 �����%2 � ���������.", player.getname(), player.getA());
			player.sufferharm(enemy.getharm());
			break;
		case PartialSuccess:
			logs::add("%1 �����%2 ��� ����, �� � ����� �������%2 ���������.", player.getname(), player.getA());
			player.sufferharm(enemy.getharm());
			player.set(Escape);
			break;
		default:
			logs::add("%1 ������ �������%2 ���� ������� � �����%3 �� ����.", player.getname(), player.getA(), player.getAS());
			player.set(Escape);
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
			logs::add("������ ������� �� �������� %1.", enemy.getname(temp));
			break;
		default:
			logs::add("������� �� �������� %1.", enemy.getname(temp));
			break;
		}
		// ��� ������ ���������� ������ ��� ������ ���������
		for(auto& player : players)
		{
			if(!player.iscombatable() || !enemy.isalive())
				continue;
			if(!player.prepareweapon(enemy))
				continue;
			if(player.volley(enemy, false))
				logs::add(1, "���� ���� �� �����.");
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
			logs::add("%1 ���%2 ����.", enemy.getname(), enemy.getA());
			for(auto& e : players)
			{
				if(!e)
					continue;
				if(e.defydanger(Dexterity))
					logs::add("%1 �������%2 ���������.", e.getname(), e.getA());
				else
					e.sufferharm(enemy.getharm());
			}
		}
		enemy.distance = (distance_s)(enemy.distance - 1);
		logs::add("���� ������� �����.");
		logs::add(1, "��������� ��������� �����");
		logs::add(2, "������ ���� �� ������");
		if(logs::input() == 2)
			return;
	}
	if(enemy.isalive())
	{
		logs::add("����� ��� ��������� %1.", enemy.getname(temp));
		while(!isgameover() && enemy)
		{
			melee_round(enemy);
			if(enemy && !isgameover())
			{
				logs::add(1, "���������� ���������");
				logs::add(2, "��������� ������");
				auto id = logs::input(true, true, "��� ������ ������?");
				if(id == 2)
					escape_combat(enemy);
			}
		}
	}
	if(!enemy)
		logs::add("������ ��� ����� ���������.");
	logs::next();
	if(!enemy)
	{
		loot_i loot; loot.clear();
		enemy.getloot(loot);
		if(loot)
		{
			logs::add("����������� � �� �������� �� �����: ");
			loot.getitems(logs::getptr(), false);
			logs::add(1, "����� ��� � �����.");
			logs::add(2, "�� ����� ������. ��� �������� �����.");
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