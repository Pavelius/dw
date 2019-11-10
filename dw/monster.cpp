#include "main.h"

static mastermove kobold_moves[] = {
	{"%����� �������%��� � ������%� � ������ ��������������� �������� ������.", Damage, {2, 6}, {"������ �������, ��� � �� ������ %����� - � ��������� ������ %��� ���������� � �������.", Dexterity}},
	{"��������, ���������� �������� ��������� � �������� �� ����. ������ ����� ��� ��������� ���-�� ��������.", Regroup},
	{"������� ������������� ������� ������� � ������� � ��-�� �������� ����� ����� �������� ��� ���� ������� � ������������� � �����.", Summon, {1}},
};
static mastermove goblin_moves[] = {
	{"\n- ����� ���!!! ��� ����!! - ������ ���� ������, ����� ������� ������.\n�� ������� ������� ��������� ��� ���� �������� ��������.", Summon, {2}},
	{"\n- ����������!! - ������� ������� � ���������� ���� ����� �� ������ �� ���������� %�����.", Damage, {1, 10, 1}, 0},
	{"\n- ��������!!! ��� �����, ������� �� ����� � �������� ��!! - ������� ������� � �������� �� ����.\n- ������� ��?? - ���������� ����������� %�����.", Regroup},
};
static mastermove bandit_moves[] = {
	{"������ ����, ����� ������� ���� ��������, ������ ������� %����� � �������� � %��� ������� � ������������ ��������.", LooseMoney, {2, 6}},
};
static mastermove zombi_moves[] = {
	{"�������� ���� �� ����������� ����� ����� ����.", Summon, {1}},
	{"����� ������ %����� � ���� � ������ ����� �� �����.", Damage, {1, 10}},
};
monsteri bsmeta<monsteri>::elements[] = {
	{"Bandit", "������", Horde, Small, {Intellegent, Organized}, 1, "������", {1, 6}, 3, {Close}, bandit_moves},
	{"Goblin", "������", Horde, Small, {Intellegent, Organized}, 1, "�����", {1, 6}, 3, {Close, Reach}, goblin_moves},
	{"Kobold", "�������", Horde, Small, {Stealthy, Intellegent, Organized}, 1, "�����", {1, 6}, 3, {Close, Reach}, kobold_moves},
	{"Zombie", "�����", Horde, Small, {Undead}, 0, "����� �� �����", {1, 6}, 11, {Close}, zombi_moves},
};
assert_enum(monster, LastMonster);

static char regrouping[LastMonster + 1];

static int add_regrouping(monster_s type) {
	auto r = regrouping[type];
	regrouping[type] = 0;
	return r;
}

monster::monster(monster_s type) : effect() {
	set(type);
}

bool monster::is(monster_tag_s id) const {
	for(auto e : bsmeta<monsteri>::elements[type].tags) {
		if(e == id)
			return true;
	}
	return false;
}

const char* monster::getweapon() const {
	return bsmeta<monsteri>::elements[type].name;
}

gender_s monster::getgender() const {
	return Male;
}

int monster::getmaxhits() const {
	return bsmeta<monsteri>::elements[type].hp;
}

int	monster::getarmor() const {
	return bsmeta<monsteri>::elements[type].armor;
}

int	monster::getharm() const {
	int result = 0;
	int maximum = imin(count, (char)3);
	for(int i = 0; i < maximum; i++)
		result = imax(result, getdamage().roll());
	return result;
}

dice monster::getdamage() const {
	return bsmeta<monsteri>::elements[type].damage;
}

void monster::set(monster_s value) {
	type = value;
	switch(bsmeta<monsteri>::elements[type].organization) {
	case Horde: count = xrand(3, 7); break;
	case Group: count = xrand(2, 3); break;
	default: count = 1; break;
	}
	count += add_regrouping(type);
	distance = Far;
	hp = getmaxhits();
}

const char* monster::getname() const {
	return bsmeta<monsteri>::elements[type].name;
}

const char* monster::getname(const stringbuilder& sb) const {
	stringbuilder sbn = sb;
	sbn.get(bsmeta<monsteri>::elements[type].name, count);
	return sb;
}

bool monster::is(distance_s id) const {
	for(auto e : bsmeta<monsteri>::elements[type].distance) {
		if(e == id)
			return true;
	}
	return false;
}

void monster::regroup() {
	regrouping[type] = count + count / 2;
}

aref<mastermove> monster::getmoves() const {
	return bsmeta<monsteri>::elements[type].moves;
}

void monster::act(const char* format, ...) const {
	driver dr(sb);
	dr.name = getstr(type);
	dr.gender = Male;
	dr.addv(format, xva_start(format));
	sb = dr;
}