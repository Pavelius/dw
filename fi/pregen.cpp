#include "main.h"

enum target_s : unsigned char {
	MostStrenged, LeastStrenged, AllEnemies, OneEnemy, TwoEnemy,
};
struct attack_context {
	struct attack_info*	attack;
	character*			monster;
	character*			enemy;
	int					value;
};
struct attack_info {
	typedef void (*callback)(attack_context& e);
	const char*			name;
	range_s				range;
	target_s			target;
	callback			proc;
	char				base;
	char				count;
	feature_s			damage_type;
};

static void strenght(attack_context& e) {
}

static void fear(attack_context& e) {
}

static void strenght_push(attack_context& e) {
	strenght(e);
	if(e.value)
		e.enemy->remove(ArmsHand);
}

static void move_save_prone(attack_context& e) {
	e.enemy->set(Prone);
	e.value = e.enemy->roll(Move, 0, 0);
	if(e.value <= 0)
		strenght(e);
}

static void devoure(attack_context& e) {
}

static void fall_prone(attack_context& e) {
	e.enemy->set(Prone);
}

struct pregen_info {
	const char*			id;
	const char*			name;
	race_s				race;
	profession_s		profession;
	char				ability[4];
	adat<skill_set, 8>	skills;
	item_s				gear[8];
	char				movement;
	attack_info			attacks[6];
};
pregen_info pregen_data[] = {{""},
{"Aliander", "����������", Human, Fighter, {3, 3, 3, 3}, {{Melee, 2}, {Move, 2}, {Marksmanship, 2}, {Healing, 1}}, {Shortsword, ShortBow}},
{"Frailer", "�������", HalfElf, Druid, {2, 3, 4, 4}, {{Lore, 2}, {Insight, 2}, {Manipulation, 2}}, {Dagger}},
{"Bear", "�������", Animal, Fighter, {6, 2}, {{Melee, 3}, {Scouting, 3}}},
{"Wolf", "����", Animal, Fighter, {4, 4}, {{Move, 3}, {Melee, 3}, {Scouting, 5}}},
{"YoungWorm", "������� �����", Monster, Fighter, {14, 2}, {}, {}, 1, {
	{"����� ��� ������ �������� � ��������� �� %����� ������� ��� ������� ����� �������� ������.", Arm, OneEnemy, strenght_push, 8, 2, Blunt},
{"������ ������������ ��� ������ � ������ ������ ������ ���.", Near, AllEnemies, fear, 5, 0, Blunt},
{"���������� ����� ����������� � ���� �������� ������ ����� �������� ������. ����� ����� �� ��������� ���� ����� �� ������.", Near, AllEnemies, move_save_prone, 12, 1, Blunt},
{"��������� ����� ������ �������� ����� � ��������� ���������� %�����.", Arm, MostStrenged, devoure, 10, 1, Edged},
{"������ ������ ���������� ", Near, AllEnemies, move_save_prone, 12, 1, Blunt},
{"�������� ������ ����� ��������� � ����� ���� ��� �����. ����� ��� ������ ������ ������� ���� � �� ����� � �������� ���.", Near, AllEnemies, fall_prone, 2, 12, Blunt},
}},
};
assert_enum(pregen, AbbysWorm);

void character::create(pregen_s id) {
	clear();
	race = pregen_data[id].race;
	profession = pregen_data[id].profession;
	memcpy(ability, pregen_data[id].ability, sizeof(ability));
	memcpy(ability_damage, ability, sizeof(ability));
	for(auto& e : pregen_data[id].skills)
		set(e.type, e.value);
}