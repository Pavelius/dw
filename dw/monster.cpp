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
static struct monster_info {
	const char*		id;
	const char*		name;
	organization_s	organization;
	size_s			size;
	monster_tag_s	tags[4];
	int				armor;
	const char*		weapon;
	dice			damage;
	char			hp;
	distance_s		distance[4];
	aref<mastermove> moves;
} monster_data[] = {
	{"Bandit", "������", Horde, Small, {Intellegent, Organized}, 1, "������", {1, 6}, 3, {Close}, bandit_moves},
	{"Goblin", "������", Horde, Small, {Intellegent, Organized}, 1, "�����", {1, 6}, 3, {Close, Reach}, goblin_moves},
	{"Kobold", "�������", Horde, Small, {Stealthy, Intellegent, Organized}, 1, "�����", {1, 6}, 3, {Close, Reach}, kobold_moves},
	{"Zombie", "�����", Horde, Small, {Undead}, 0, "����� �� �����", {1, 6}, 11, {Close}, zombi_moves},
};
assert_enum(monster, LastMonster);
getstr_enum(monster);

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
	for(auto e : monster_data[type].tags) {
		if(e == id)
			return true;
	}
	return false;
}

const char* monster::getweapon() const {
	return monster_data[type].name;
}

gender_s monster::getgender() const {
	return Male;
}

int monster::getmaxhits() const {
	return monster_data[type].hp;
}

int	monster::getarmor() const {
	return monster_data[type].armor;
}

int	monster::getharm() const {
	int result = 0;
	int maximum = imin(count, (char)3);
	for(int i = 0; i < maximum; i++)
		result = imax(result, getdamage().roll());
	return result;
}

dice monster::getdamage() const {
	return monster_data[type].damage;
}

void monster::set(monster_s value) {
	type = value;
	switch(monster_data[type].organization) {
	case Horde: count = xrand(3, 7); break;
	case Group: count = xrand(2, 3); break;
	default: count = 1; break;
	}
	count += add_regrouping(type);
	distance = Far;
	hp = getmaxhits();
}

const char* monster::getname() const {
	return monster_data[type].name;
}

char* monster::getname(char* result, const char* result_maximum) const {
	//return grammar::get(result, result_maximum, monster_data[type].name, count);
	return result;
}

bool monster::is(distance_s id) const {
	for(auto e : monster_data[type].distance) {
		if(e == id)
			return true;
	}
	return false;
}

void monster::regroup() {
	regrouping[type] = count + count/2;
}

aref<mastermove> monster::getmoves() const {
	return monster_data[type].moves;
}

void monster::act(const char* format, ...) const {
	auto& driver = logs::getbuilder();
	driver.name = getstr(type);
	driver.gender = Male;
	logs::addv(format, xva_start(format));
}