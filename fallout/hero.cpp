#include "main.h"

hero::hero(talent_s id) {
	set(id);
	raise();
}

result_s hero::roll(stat_s id, bool interactive, int bonus) {
	auto result = Fail;
	auto d = 2 + (rand() % 6) + (rand() % 6);
	auto r = d + bonus;
	if(r <= 6) {
		if(interactive)
			logs::add("[-{%1i%+2i=%3i}]", d, bonus, r);
		return Fail;
	}
	else if(r <= 9) {
		if(interactive)
			logs::add("{%1i%+2i=%3i}", d, bonus, r);
		return PartialSuccess;
	}
	if(interactive)
		logs::add("[+{%1i%+2i=%3i}]", d, bonus, r);
	return Success;
}

void hero::set(talent_s id) {
}

int hero::gethpmax() const {
	auto result = 8 + 4 * level;
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

result_s hero::volley(thing& enemy) {
	auto result = roll(Dexterity);
	act(enemy, "%����� � %�������� ������ ������ ���� � �����.");
	switch(result) {
	case Fail:
		act(enemy, "�� %�������� �����%� ������� %����� � ����.");
		sufferharm(enemy.getharm().roll());
		break;
	case PartialSuccess:
		enemy.sufferharm(getharm().roll());
		sufferharm(enemy.getharm().roll());
		break;
	case Success:
		act(enemy, "%����� �����%� �������� ����������.");
		enemy.sufferharm(getharm().roll());
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