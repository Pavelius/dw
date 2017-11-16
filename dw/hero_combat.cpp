#include "main.h"

void hero::volley(monster& enemy)
{
	auto bonus = get(Dexterity);
	while(true)
	{
		if(!isammo() || !enemy.isalive() || !weapon.is(enemy.distance))
			return;
		auto result = roll(bonus);
		logs::add("%1 ������%2 ��������� ���������.", getname(), getA());
		switch(result)
		{
		case Fail:
			logs::add("�� ��� ������ ����� ���� ����.");
			logs::next();
			return;
		case PartialSuccess:
			logs::add(1, "���� �������� ������� ����� ������.");
			logs::add(2, "��, ���� �� ����� ���� �������� ����� ����, -1d6 �����");
			logs::add(3, "�������� ������� ������� ����� ���������, �������� ���������� �� �������");
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
		logs::add(1, "������� ����� ������������� +1d6 �����");
		logs::add(2, "�������� ����� �����");
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
			logs::add("������ �� �������� ���� ������.");
			logs::next();
			return;
		}
		logs::add(1, "������ � ������� �� ����.");
		logs::add(10, "������ ������ �����.");
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
				logs::add("�� ���������� ������, �� ��� �� �������. �� ������������� � ���������. %opponent ����� ����.");
				player.sufferharm(enemy.getharm());
				continue;
			}
			else if(result==PartialSuccess)
			{
				logs::add("�� ���������� �� ���������� ����� ����� � ������� �����. %opponent ����� ���� ��� �����.");
				player.sufferharm(enemy.getharm());
				if(!player.isalive())
					logs::add("����, ��� ���� �� �������. ���� ���� ��� ����.");
				else
					logs::add("������ ��� �� �������.");
			}
			else
				logs::add("�� ������ ���������� �� ���������� ����� ����� � ������� �����. %opponent ����� ���� ��� �����, �� �����������. ������ ��� �� �������.");
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
			logs::add("������ ������� �� �������� %1.", enemy.getname(temp));
			break;
		default:
			logs::add("������� �� �������� %1.", enemy.getname(temp));
			if(enemy.weapon)
				logs::add("������ �� ��� ����� %1.", enemy.weapon.getname(temp, false));
			break;
		}
		// ��� ������ ���������� ������ ��� ������ ���������
		for(auto& player : players)
		{
			if(!player)
				continue;
			if(!player.prepareweapon(enemy))
				continue;
			if(player.weapon.is(enemy.distance) && player.isammo())
				logs::add(1, "���� ���� �� �����.");
			logs::add(100, "������ �� ������.");
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
		logs::add("���� ������� �����.");
		logs::add(1, "��������� ��������� �����");
		logs::add(2, "������ ���� �� ������");
		if(logs::input() == 2)
			return;
	}
	logs::add("����� ��� ��������� %1.", enemy.getname(temp));
	while(!isgameover() && enemy)
		melee_round(enemy);
}

void hero::combat(monster_s id)
{
	monster enemy(id);
	combat(enemy);
}