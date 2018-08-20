#include "main.h"

hero::hero(talent_s id) : hp(0), level(0), stats() {
	weapon = Pistol;
	set(id);
	raise();
	sethp(gethpmax());
}

result_s hero::roll(stat_s id, bool interactive, int bonus) {
	auto result = Fail;
	auto d = 2 + (rand() % 6) + (rand() % 6);
	auto r = d + bonus;
	if(r <= 6) {
		if(interactive)
			logs::add("[-{%1i%+2i=%3i}]", d, bonus, r);
		return Fail;
	} else if(r <= 9) {
		if(interactive)
			logs::add("{%1i%+2i=%3i}", d, bonus, r);
		return PartialSuccess;
	}
	if(interactive)
		logs::add("[+{%1i%+2i=%3i}]", d, bonus, r);
	return Success;
}

void hero::set(talent_s id) {}

int hero::gethpmax() const {
	auto result = 4 * (level + 1) + get(Strenght);
	if(is(Tought))
		result += 6;
	return result;
}

void hero::raise() {
	level++;
}

result_s hero::combat(thing& enemy) {
	act(enemy, "�������, ����� ����� %����� �������%� %���������.");
	logs::add(1, "��������� �������� � ������ ��������.");
	logs::add(2, "������ ������� ����� � ���������� � ���������.");
	auto id = whatdo();
	if(id == 2)
		return Fail;
	while(true) {
		volley(enemy);
		if(!enemy || !*this)
			logs::add(1, "��������� �������");
		else {
			logs::add(1, "���������� �������");
			logs::add(2, "������ ������");
		}
		auto id = whatdo();
		if(id == 2)
			return Fail;
		if(!*this)
			return Fail;
		if(!enemy)
			return Success;
	}
	return Fail;
}

static void showattack(thing& player, thing opponent) {
	auto weapon = player.getweapon();
	if(!weapon)
		player.act(opponent, "������������� � ����������� %����� ����� ���� ����� %���������.");
	else
		player.act(opponent, weapon->gettextsuccess());
}

result_s hero::volley(thing& enemy) {
	auto result = roll(Dexterity);
	switch(result) {
	case Fail:
		//act(enemy, "�� %�������� �����%� ������� %����� � ����.");
		showattack(enemy, *this);
		sufferharm(enemy.getharm().roll(), enemy.is(ArmorPierce));
		break;
	case PartialSuccess:
		act(enemy, "%����� � %�������� ������ ������ ���� � �����.");
		enemy.sufferharm(getharm().roll(), is(ArmorPierce));
		sufferharm(enemy.getharm().roll(), enemy.is(ArmorPierce));
		break;
	case Success:
		//act(enemy, "%����� �����%� �������� ����������.");
		showattack(*this, enemy);
		enemy.sufferharm(getharm().roll(), is(ArmorPierce));
		break;
	}
	return result;
}

result_s hero::volley(thinga& enemy) {
	if(enemy.getcount() == 1)
		return volley(*enemy[0]);
	return Success;
}

int hero::whatdo() const {
	return logs::input(true, true, "[��� ������ ������?]");
}