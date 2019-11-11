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
		for(auto& e : bsmeta<hero>()) {
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
		an.add(variant(i), "������������ ���������� '%1'", getstr(i));
	}
}

void hero::volley(monster& enemy) {
	auto result = roll(Volley);
	act("%1 ������%2 ��������� ���������.", getname(), getA());
	switch(result) {
	case Fail:
		sb.add("�� ��� ������ ����� ���� ����.");
		if(enemy.is(enemy.distance)) {
			enemy.act("%����� ���������%� � �����.");
			sufferharm(enemy.getharm());
		}
		break;
	case PartialSuccess:
		if(enemy.is(enemy.distance))
			an.add(1, "���� �������� ������� ����� ������ � ������������ ��� ����.");
		an.add(2, "��, ���� �� ����� ���� �������� ����� ����, -1d6 �����");
		if(weapon.getammo())
			an.add(3, "�������� ������� ������� ����� ���������, �������� ���������� �� �������");
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

void hero::turnundead(monster& enemy) {
	char temp[260];
	auto result = roll(TurnUndead);
	act("%����� ��������%� ������ ������ ������ ��������%��:\n");
	act(" - �� ���, %1 ������� � ��� ����������!\n", getstr(diety));
	switch(result) {
	case Fail:
		enemy.act("%1 �������%� �� ������ � ������%��� � �����.", enemy.getname(temp));
		sufferharm(enemy.getharm());
		break;
	case PartialSuccess:
		act("��� �������� ������ ������ ����� ����� � �������� ������.");
		enemy.count = 0;
		break;
	default:
		act("��� �������� ������ ������ ����� ����� � �������� ������.");
		enemy.count = 0;
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
		sb.add("%1 � %2 ������� �������� ����� �������.", getname(), enemy.getname());
		inflictharm(enemy, getharm());
		sufferharm(enemy.getharm());
		break;
	default:
		act("%����� �����%�� ����������� ����."); enemy.act("%����� ������%� � ��������%�.");
		an.add(2, "�������� ����� �����");
		an.add(1, "������� ����� ������������� +1d6 �����");
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
	for(auto& player : bsmeta<hero>()) {
		if(!player.iscombatable())
			continue;
		if(!enemy)
			return;
		an.add(variant(HackAndSlash), "������ � ������� �� ����.");
		if(player.is(TurnUndead) && enemy.is(Undead))
			an.add(variant(TurnUndead), "��������� �������.");
		ask_spells(player, enemy);
		variant id = player.whatdo();
		if(id.type == Spells)
			player.cast((spell_s)id.value, &enemy);
		else {
			switch(id) {
			case variant(HackAndSlash): player.hackandslash(enemy); break;
			case variant(TurnUndead): player.turnundead(enemy); break;
			}
		}
	}
}

static void description(monster& enemy) {
	char temp[260];
	switch(enemy.distance) {
	case Far:
		sb.add("������ ������� �� �������� %1.", enemy.getname(temp));
		break;
	case Near:
		sb.add("�������� �� ��� �� �������� %1.", enemy.getname(temp));
		break;
	default:
		sb.add("����� ��� ��������� %1.", enemy.getname(temp));
		break;
	}
}

static bool range_combat(monster& enemy) {
	for(auto& player : bsmeta<hero>()) {
		if(!enemy)
			return true;
		if(!player.iscombatable() || !enemy)
			continue;
		if(!player.prepareweapon(enemy))
			continue;
		if(!player.weapon.is(enemy.distance) || !player.isammo(player.weapon.getammo()))
			continue;
		an.add(variant(Volley), "���� ���� �� �����.");
		ask_spells(player, enemy);
		variant id = player.whatdo();
		if(id.type == Spells)
			player.cast((spell_s)id.value, &enemy);
		else {
			switch(id) {
			case variant(Volley): player.volley(enemy); break;
			}
		}
	}
	if(!enemy)
		return true;
	// ��� ������
	if(enemy.is(enemy.distance)) {
		enemy.act("%����� ���%� ����.");
		for(auto& e : bsmeta<hero>()) {
			if(!e)
				continue;
			auto result = e.defydanger(Dexterity);
			if(result>=PartialSuccess)
				e.act("%����� �������%� ���������.");
			else
				e.sufferharm(enemy.getharm());
		}
	}
	sb.add("���� ������� �����."); enemy.distance = (distance_s)(enemy.distance - 1);
	an.add(1, "������ � ���������");
	an.add(0, "������ ���� �� ������");
	if(!an.choose())
		return false;
	return true;
}

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

static bool main_combat(monster& enemy) {
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
		sb.add("���� �����, �� ����� �������� ����� � �� ����� ������.");
		logs::next();
		return true;
	} else if(enemy) {
		sb.add("��� ������� ������.");
		logs::next();
		return false;
	}
	sb.add("������ ��� ����� ���������.");
	logs::next();
	auto hoard = enemy.getdamage().roll();
	looti loot;
	loot.clear();
	loot.generate(hoard);
	if(loot) {
		sb.add("����������� � �� �������� �� �����: ");
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