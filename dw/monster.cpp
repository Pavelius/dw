#include "main.h"
#include "grammar.h"

static mastermove kobold_moves[] = {
	{"%����� �������%��� � ������%� � ������ ��������������� �������� ������.", Damage, {2, 6}, 0, {"������ �������, ��� � �� ������ %����� - � ��������� ������ %��� ���������� � �������.", Dexterity}},
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
static struct monsterinfo {
	const char*				id;
	const char*				name;
	organization_s			organization;
	size_s					size;
	monster_tag_s			tags[4];
	int						armor;
	const char*				weapon;
	dice					damage;
	char					hp;
	distance_s				distance[4];
	aref<mastermove>		moves;

	bool is(monster_tag_s id) const {
		for(auto e : tags) {
			if(e == id)
				return true;
		}
		return false;
	}

} monster_data[] = {
	{"goblin", "������", Horde, Small, {Intellegent, Organized}, 1, "�����", {1, 6}, 3, {Close, Reach}, AREF(goblin_moves)},
	{"kobold", "�������", Horde, Small, {Stealthy, Intellegent, Organized}, 1, "�����", {1, 6}, 3, {Close, Reach}, AREF(kobold_moves)},
	{"bandit", "������", Horde, Small, {Intellegent, Organized}, 1, "������", {1, 6}, 3, {Close}, AREF(bandit_moves)},
};
assert_enum(monster, Bandit);
getstr_enum(monster);

monster::monster(monster_s type) : regroup(0) {
	set(type);
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
	case Horde: count = xrand(5, 10); break;
	case Group: count = xrand(3, 6); break;
	default: count = 1; break;
	}
	distance = Far;
	hp = getmaxhits();
}

const char* monster::getname() const {
	return monster_data[type].name;
}

char* monster::getname(char* result) const {
	return grammar::get(result, monster_data[type].name, count);
}

bool monster::is(distance_s id) const {
	for(auto e : monster_data[type].distance) {
		if(e == id)
			return true;
	}
	return false;
}

aref<mastermove> monster::getmoves() const {
	return monster_data[type].moves;
}