#include "main.h"

conditioni bsmeta<conditioni>::elements[] = {{"Healthy", "��������"},
{"Hunger and Thirsty", "��������", "� ��� ��� ����������, �� � �������� ���������� %1 �������%2 ����."},
{"Angry", "����", "� ���������� ��� ����� ��� ����, �� ������� ������ ������� ��������� %1.", {Administrator, Orator, Deceiver, Persuader, Haggler, Baker, Smith}, {Will}, 2},
{"Tired", "��������", "���� ���� � ���� �������, �� �� ������� ������ %1 �������%2 �������������.", {Cartographer, Scientist, Archivist, Pathfinder, Hunter, Scout, Nature}, {Health}, 3},
{"Injured", "��������", "�� ����� ���������� %1 �������%2 �������.", {Fighter}, {Health}, 4},
{"Sick", "�������", "� �������� %1 �����������%2 ���� ����� � ������ ����� �������%2.", {}, {Health}, 4},
{"Dead", "�������", "�� ������ �� ��, ��� ��� ������� �������� ����� ����, � �������� %1 ������%2."},
};

static bool is_skill(condition_s value, skill_s skill) {
	for(auto e : bsmeta<conditioni>::elements[value].skills) {
		if(e == skill)
			return true;
	}
	return false;
}

void hero::get(adat<condition_s, 8>& conditions, skill_s skill) {
	conditions.clear();
	conditions.add(HungerAndThirsty);
	for(auto i = HungerAndThirsty; i <= Dead; i = (condition_s)(i + 1)) {
		if(conditions.is(i))
			continue;
		if(is_skill(i, skill))
			conditions.add(i);
	}
}

void hero::twistconditions(bool interactive, skill_s skill, hero** helps) {
	adat<condition_s, 8> conditions;
	get(conditions, skill);
	if(!conditions.count)
		return;
	auto condition = conditions.data[rand() % conditions.count];
	for(auto pp = helps; *pp; pp++) {
		auto p = *pp;
		if(!p)
			break;
		p->set(condition);
	}
	if(interactive) {
		if(bsmeta<conditioni>::elements[condition].text) {
			auto count = zlen(helps);
			if(count > 1) {
				char temp[512];
				sb.add(bsmeta<conditioni>::elements[condition].text, getmembers(temp, helps), "�");
			} else
				sb.add(bsmeta<conditioni>::elements[condition].text, helps[0]->getname(), helps[0]->getLA());
		}
	}
}

bool hero::passtest(skill_s skill, int obstacle) {
	hero* helps[8]; helps[0] = 0;
	auto was_weather_twist = false;
	while(true) {
		auto player = choose(skill);
		if(!player)
			return false;
		auto result = player->roll(skill, obstacle, 0, 0, true, StandartRoll, 0, 0, helps);
		zcat(helps, player);
		if(result >= 0)
			return true;
		// If there is some twist story
		if((rand()%100) < 30)
			return false;
		if(!was_weather_twist && (rand() % 100) < 35) {
			was_weather_twist = true;
			twistweather(true, skill, helps);
			continue;
		}
		twistconditions(true, skill, helps);
		return true;
	}
}

void hero::recover() {
	static condition_s conditions[] = {HungerAndThirsty, Angry, Tired, Injured, Sick};
	for(auto e : conditions) {
		if(is(e)) {
			recover(e);
			break;
		}
	}
}

void hero::recover(condition_s value) {
	if(roll(bsmeta<conditioni>::elements[value].recover[0], bsmeta<conditioni>::elements[value].recover_ob))
		remove(value);
	else {

	}
}