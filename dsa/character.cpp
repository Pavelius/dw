#include "main.h"

characteri bsmeta<characteri>::elements[] = {{"Adventurer", "�����������", {}, {30, 0, 11, 8}},
{"Warrior", "����", {12, 0, 0, 0, 12}, {30, 0, 12, 9}},
{"Dwarf", "������", {0, 0, 0, 12, 12}, {40, 0, 11, 9}},
{"Elf", "����", {0, 12, 0, 12, 0}, {25, 25, 11, 8}},
{"Magicien", "���", {0, 12, 12, 0, 0}, {20, 30, 9, 8}},
};
assert_enum(character, Magician);

static int compare_char(const void* v1, const void* v2) {
	return *((char*)v2) - *((char*)v1);
}

void creature::random_ability() {
	for(auto i = 0; i < 5; i++)
		abilities[i] = 8 + (rand() % 6);
}

void creature::choose_ability(bool interactive) {
	char temp[6];
	while(true) {
		for(auto i = 0; i < 6; i++)
			temp[i] = 8 + (rand() % 6);
		qsort(temp, sizeof(temp), sizeof(temp[0]), compare_char);
		sb.add("�� ��������� ");
		for(auto i = 0; i < 6; i++) {
			if(i == 5)
				sb.add(" � ");
			else if(i)
				sb.add(", ");
			sb.add("%1i", temp[i]);
		}
		sb.add(".");
		an.add(1, "������ ��� ��������");
		an.add(2, "�������� ����������� �����");
		auto r = an.choose(interactive, true, "��� ������ ������?");
		if(r == 1)
			break;
	}
	place_ability(interactive, temp);
}

void creature::print_ability(stringbuilder& sb) const {
	auto count = 0;
	for(auto i = Courage; i <= Strenght; i = (ability_s)(i + 1)) {
		auto v = abilities[i];
		if(!v)
			continue;
		if(count)
			sb.add(", ");
		sb.add("%1:%2i", bsmeta<abilityi>::elements[i].name, v);
		count++;
	}
	if(count)
		sb.add(".");
}

void creature::status(stringbuilder& sb) const {
	sb.add(getname());
	auto lp = get(LE);
	auto lpm = getmaximum(LE);
	if(lp < lpm) {
		if(lp < lpm/2)
			sb.add("([-%1i/%2i])", lp, lpm);
		else
			sb.add("(%1i/%2i)", lp, lpm);
	}
	if(wears[Weapon])
		sb.adds("������ %-1", wears[Weapon].getinfo().name);
}

void creature::place_ability(bool interactive, char* temp) {
	for(auto i = 0; i < 5; i++) {
		print_ability(sb);
		for(auto i = Courage; i <= Strenght; i = (ability_s)(i + 1)) {
			if(abilities[i])
				continue;
			an.add(i, bsmeta<abilityi>::elements[i].name);
		}
		auto r = an.choose(interactive, true, "���� ������ ����������� [%1i]?", temp[i]);
		abilities[r] = temp[i];
	}
}

static bool match(const abilitya& e1, const abilitya& e2) {
	for(auto i = 0; i < sizeof(e1) / sizeof(e1[0]); i++) {
		if(!e2[i])
			continue;
		if(e1[i] < e2[i])
			return false;
	}
	return true;
}

void creature::choose_character(bool interactive) {
	for(auto i = Adventurer; i <= Magician; i = (character_s)(i + 1)) {
		if(match(abilities, bsmeta<characteri>::elements[i].abilities))
			an.add(i, bsmeta<characteri>::elements[i].name);
	}
	auto r = (character_s)an.choose(interactive, true, "��� �� ������ ������?");
	apply(r);
}

void creature::apply(character_s v) {
	type = Character; value = v;
	for(auto i = Courage; i <= Strenght; i = (ability_s)(i + 1)) {
		if(abilities[i] < bsmeta<characteri>::elements[v].abilities[i])
			abilities[i] = bsmeta<characteri>::elements[v].abilities[i];
	}
	memcpy(parameters, bsmeta<characteri>::elements[v].parameters, sizeof(parameters));
	memcpy(abilities_maximum, abilities, sizeof(abilities));
	memcpy(parameters_maximum, parameters, sizeof(parameters));
}

void creature::create(bool interactive) {
	choose_ability(interactive);
	choose_character(interactive);
	choose_gender(interactive);
}

void creature::create(character_s character, gender_s gender) {
	random_name(character, gender);
	random_ability();
	apply(character);
}

void creature::choose_gender(bool interactive) {
	an.add(Male, bsmeta<genderi>::elements[Male].name);
	an.add(Female, bsmeta<genderi>::elements[Female].name);
	auto r = (gender_s)an.choose(interactive, true, "��� ��?");
	random_name((character_s)value, r);
}