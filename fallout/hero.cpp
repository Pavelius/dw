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
			sb.add("[-{%1i%+2i=%3i}]", d, bonus, r);
		return Fail;
	} else if(r <= 9) {
		if(interactive)
			sb.add("{%1i%+2i=%3i}", d, bonus, r);
		return PartialSuccess;
	}
	if(interactive)
		sb.add("[+{%1i%+2i=%3i}]", d, bonus, r);
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

void hero::look(scenery_s id, thing& enemy, label_s distance) {
	//char temp[260]; geti(temp, zendof(temp), "�������, ����� %1", id);
	//act(enemy, "%1 %����� �������%� %���������.", temp);
}

result_s hero::combat(thing& enemy, label_s distance) {
	look(Box, enemy, distance);
	while(true) {
		if(!enemy)
			return Success;
		// TODO: ������� ������ ����� ���.
		// �������� ����� ������ ������� ��� ��������� � ����������? � ����� ��������� ������?
		if(!enemy || !*this)
			an.add(1, "��������� �������");
		else {
			an.add(1, "��������� �������� � ������ ��������.");
			an.add(2, "������ ������� ����� � ���������� � ���������.");
		}
		auto id = whatdo();
		if(id == 2)
			return Fail;
		if(!*this)
			return Fail;
		if(distance == Hand)
			hackandslash(enemy);
		else
			volley(enemy, distance);
	}
	return Fail;
}

static void showattack(thing& player, thing opponent) {
	auto weapon = player.getweapon();
	//if(!weapon)
	//	player.act(opponent, "������������� � ����������� %����� ����� ���� ����� %���������.");
	//else
	//	player.act(opponent, weapon->gettextsuccess());
}

result_s hero::hackandslash(thing& enemy) {
	auto result = roll(Dexterity);
	switch(result) {
	case Fail:
		showattack(enemy, *this);
		sufferharm(enemy.getharm().roll(), enemy.is(ArmorPierce));
		break;
	case PartialSuccess:
		//act(enemy, "%����� � %�������� ������ ������ ���� � �����.");
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

static label_s closer(label_s id) {
	switch(id) {
	case Far: return Close;
	case Close: return Hand;
	default: return id;
	}
}

result_s hero::volley(thing& enemy, label_s& distance) {
	auto result = roll(Dexterity);
	switch(result) {
	case Fail:
		showattack(enemy, *this);
		sufferharm(enemy.getharm().roll(), enemy.is(ArmorPierce));
		break;
	case PartialSuccess:
		if(enemy.is(distance)) {
			//act(enemy, "%����� � %�������� ������ ������ ���� � �����.");
			enemy.sufferharm(getharm().roll(), is(ArmorPierce));
			sufferharm(enemy.getharm().roll(), enemy.is(ArmorPierce));
		} else {
			showattack(*this, enemy);
			enemy.sufferharm(getharm().roll(), is(ArmorPierce));
			if(enemy) {
				enemy.act("%����� ������ ���������%���.");
				distance = closer(distance);
			}
		}
		break;
	case Success:
		showattack(*this, enemy);
		enemy.sufferharm(getharm().roll(), is(ArmorPierce));
		break;
	}
	return result;
}

int hero::whatdo() const {
	return an.choosev(true, true, true, "[��� ������ ������?]");
}