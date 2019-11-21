#include "main.h"

DECLDATA(hero, max_players);

static int rolln(int bonus, int f, int ps, int s) {
	auto result = hero::roll(bonus);
	switch(result) {
	case PartialSuccess: return ps;
	case Fail: return f;
	default: return s;
	}
}

result_s hero::roll(int bonus, int* result, bool interactive) {
	auto d = (rand() % 6) + (rand() % 6) + 2;
	auto r = d + bonus;
	if(r <= 6) {
		if(interactive)
			sb.add("[-{%1i%+2i=%3i}]", d, bonus, r);
		return Fail;
	} else if(r <= 9) {
		if(interactive)
			sb.add("{%1i%+2i=%3i}", d, bonus, r);
		return PartialSuccess;
	} else {
		if(interactive)
			sb.add("[+{%1i%+2i=%3i}]", d, bonus, r);
		return Success;
	}
}

bool hero::is(move_s value) const {
	return (moves & (1 << value)) != 0;
}

void hero::set(move_s value) {
	moves |= 1 << value;
	switch(value) {
	case InsanoLikeDrano: stats[Hard] = imin(stats[Hard] + 1, 3); break;
	case PreparedForTheInevitable: angelkit = 2; break;
	default: break;
	}
}

bool hero::add(item value) {
	if(value.isweapon() && !weapon) {
		weapon = value;
		return true;
	}
	return false;
}

result_s hero::actunderfire() {
	int bonus = get(Cool);
	if(is(BattleHardened))
		bonus = imax(bonus, get(Hard));
	return roll(bonus);
}

result_s hero::goaggro(thing& enemy) {
	int bonus = get(Hard);
	if(is(IceCold))
		bonus = imax(bonus, get(Cool));
	auto result = roll(bonus);
	if(result >= Success) {
		if(!weapon)
			act(enemy, "%����� ����� ������%� %��������� ������� � ���. �� ���� %��� �c�������%� � ����%�� �����. ����� ���������� ������ ���� � �����, ������� � ��� � ������ ������� �� �����. �� ����� ������ %�������� �����%� �� �����. %����� �� �����%� ������� ���� %�� ������.");
		else
			act(enemy, "%����� ���������%� � %���������.");
		inflictharm(enemy, getharm());
		act("\n- � �� ������ ���� ������ ����� ����! - ������%� %�����. - ������ �����, ��� ����� � ������!");
	} else if(result == PartialSuccess) {
		enemy.act("- �����! - ��������%� %�����. � ������ %��� � �� ��� � %��� �������� �� ����.");
	} else {
		enemy.act("- �� �� � ������! - ��������%� %�����.\n");
		combat(enemy);
	}
	return result;
}

result_s hero::readasitch() {
	int bonus = get(Sharp);
	return roll(bonus);
}

result_s hero::readaperson() {
	int bonus = get(Sharp);
	return roll(bonus);
}

result_s hero::openyourbrain() {
	int bonus = get(Weird);
	return roll(bonus);
}

int hero::whatdo() const {
	return an.choose(true, true, "��� ����� ������ [%1]?", getname());
}

item* hero::getweapon(distance_s distance) {
	for(auto& e : weapons) {
		if(!e)
			continue;
		if(e.is(distance))
			return &e;
	}
	return 0;
}

void hero::prepareweapon(distance_s distance) {
	if(weapon.is(distance))
		return;
	auto p = getweapon(distance);
	if(p) {
		char temp[260]; iswap(weapon, *p);
		act("%����� ������%� %1.", weapon.getname(temp, false));
	}
}

void hero::choose(aref<const char*> strings, const char* title, char* result, int answer_count) {
	result[0] = 0;
	for(auto i = 0; i < answer_count; i++) {
		for(unsigned j = 1; j <= strings.count; j++) {
			if(zchr(result, (char)j))
				continue;
			an.add(j, strings.data[j - 1]);
		}
		zcat(result, (char)an.choose(true, false, ((answer_count - i) > 1) ? "%1 (�������� [%2i])" : title, title, answer_count - i));
	}
}

bool hero::seizbyforce(thing& enemy, const char* goal) {
	auto bonus = get(Hard);
	act(enemy, "%����� �����%� ��������, %�������� �����%� � �����. � �� ��������� ��������� ��������� ��.");
	auto ca = rolln(bonus, 1, 2, 3);
	auto ph = getharm();
	auto eh = enemy.getharm();
	auto control = false;
	char answers[4];
	static const char* answers_text[] = {
		"������� ������� ���� (+1 ���� �����).",
		"�� �������� �� ����� ����� (-1 ���� ���).",
		goal,
		"�� ���������, ������� ��� ��������� � ������� �����."
	};
	choose(answers_text, "��� �� �����������?", answers, ca + addchoice());
	for(auto e : answers) {
		switch(e) {
		case 1: ph++; break;
		case 2: eh--; break;
		case 3: enemy.set(Frighten); break;
		case 4: control = true; break;
		}
	}
	inflictharm(enemy, ph);
	sufferharm(eh);
	return control;
}

bool hero::keephold(thing& enemy) {
	return seizbyforce(enemy, "�� ������ �������� ���� ������� � ��� �� �������� ���������.");
}

bool hero::laydownfire(thing& enemy) {
	auto bonus = get(Hard);
	act("%����� �����%� �������� � ������� ������, ������� ������� �� �������� � �������� �� ������.");
	auto ca = rolln(bonus, 1, 2, 3);
	//auto ph = getharm();
	//auto eh = enemy.getharm();
	char answers[4];
	static const char* answers_text[] = {
		"�� ���������� ����� ���������, ����� ������ �������� ���� ��������� �������� �������� � ��� �����������.",
		"�� ���������� �������������� �����, ����� ������ �������� ������� +1 ����� � ����� ������ ����.",
		"�� ���������� ����������� �����, �������� ����� ������������� ��� ���-�� ������.",
		"���� � ����� ���� ������ �������� ��������� ���� �� ��� (-1 � �����)."
	};
	choose(answers_text, "����� ��������� ����� ��������?", answers, ca + addchoice());
	bool cover = false;
	for(auto e : answers) {
		switch(e) {
		case 1: cover = true; break;
		case 2: break;
		case 3: enemy.set(ActingUnderFire); break;
		case 4: inflictharm(enemy, getharm() - 1); break;
		}
	}
	return cover;
}

bool hero::combat(thing& enemy) {
	if(!isalive())
		return false;
	if(!enemy.isalive())
		return true;
	while(true) {
		auto bonus = get(Hard);
		auto result = roll(bonus);
		act(enemy, "%����� �����%� ��������, %�������� �����%� � �����. � �� ��������� ��������� ��������� ��.");
		auto ph = getharm();
		auto eh = enemy.getharm();
		switch(result) {
		case Success:
			ph++; eh--;
			break;
		case PartialSuccess:
			an.add(1, "������� ������� ���� (+1 ���� �����).");
			an.add(2, "�� �������� �� ����� ����� (-1 ���� ���).");
			if(an.choose(true, false, "��� �����������?") == 1)
				ph++;
			else
				eh--;
			break;
		case Fail:
			if(d100() < 50)
				ph--;
			else
				eh++;
			break;
		}
		inflictharm(enemy, ph);
		sufferharm(eh);
		if(isalive() && enemy.isalive())
			an.add(1, "���������� ��������");
		if(!enemy.isalive())
			an.add(2, "��������� �������� �������");
		else if(!isalive() || enemy.iswounded())
			an.add(3, "��������� ��������");
		switch(an.choose(true, true, "��� ������ ������?")) {
		case 2: return true;
		case 3: return false;
		}
	}
}

void hero::sufferharm(int bonus) {
	bonus -= getarmor();
	if(bonus > 0) {
		sethealth(gethealth() - bonus);
		if(!isalive())
			act("%����� �������%� [%1i] ����� � ����%�.", bonus);
		else if(iswounded())
			act("%����� �������%� [%1i] ����� � ��������%� �� ����.", bonus);
		else
			act("%����� �������%� [%1i] �����.", bonus);
	} else {
		if(getarmor())
			act("����� ������ %����� �� �����.", bonus);
	}
	switch(roll(bonus, 0, false)) {
	case Success:
		if(gethealth() > 0) {
			sethealth(gethealth() - 1);
			act("��� ���� �� ��� �����, ���� %����� �� ���������%� ����� ������� �� ������ ��� ������ ��� 1 �����.");
		}
		break;
	case PartialSuccess:
		break;
    default:
        break;
	}
}

int	hero::gethistory(const hero& player) const {
	return history[player.getindex()];
}

void hero::inflictharm(thing& enemy, int count) {
	count -= enemy.getarmor();
	if(count <= 0) {
		enemy.act("%����� �������%�� ���� ��� ����������.");
		return;
	} else
		enemy.act("%����� �������%� [%1i] �����", count);
	sethealth(gethealth() - count);
	switch(gethealth()) {
	case 3: if(d100() < 25) enemy.kill(); break;
	case 2: if(d100() < 50) enemy.kill(); break;
	case 1: if(d100() < 75) enemy.kill(); break;
	}
	if(!enemy.isalive())
		act(" � ������ %�� �����.");
	else if(enemy.iswounded())
		enemy.act(" � ������%� �� ����.");
	else
		sb.add(".");
}

int	hero::getindex() const {
	return this - bsmeta<hero>::elements;
}

bool hero::is(booklet_s v) {
	for(auto& e : bsmeta<hero>())
		if(e.type == v)
			return true;
	return false;
}