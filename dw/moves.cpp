#include "main.h"

struct move_info {
	const char*		id;
	const char*		name;
	stat_s			stat;
} move_data[] = {
	{"Arcane Art"},
	{"Bardic Lore"},
	{"Charming and Open"},
	{"Port in The Storm", "������� �� ����� ����"},
	{"Deity", "��������"},
	{"Divine guidance", "������ ���������������"},
	{"Turn Undead", "��������� �������"},
	{"Commune", ""},
	{"Cast a Spell", ""},
	{"Born of The Soil", ""},
	{"By Nature Sustained", ""},
	{"Spirit Tongue", ""},
	{"Shapeshifter", ""},
	{"Studied Essence", ""},
	{"Bend Bars Lift Gates", ""},
	{"Armored", ""},
	{"Signature Weapon", "������� ������"},
	{"Lay on Hands", "���������� ���"},
	{"I am The Law", "� ���� �����"},
	{"Quest", "������"},
	{"Hunt and Track", ""},
	{"Called Shot", ""},
	{"Animal Companion", ""},
	{"Command", ""},
	{"Trap Expert", "������� �� ��������", Dexterity},
	{"Tricks of The Trade", "������ ��������"},
	{"Backstab", "���� � �����"},
	{"Flexible Morals", "������ ������"},
	{"Poisoner", ""},
	{"Spellbook", "����� ����������"},
	{"Prepare spells", ""},
	{"Spell defense", ""},
	{"Ritual", "������"},
	//
	{"Merciless", ""},
	{"Heirloom", ""},
	{"Improved Weapon", ""},
	{"Seeing Red", ""},
	{"Interrogator", ""},
	{"Scent of Blood", ""},
	{"Iron Hide", ""},
	{"Blacksmith", ""},
	{"Superior Warrior", ""},
	//
	{"Prodigy", ""},
	{"Empowered Magic", ""},
	{"Fount of Knowledge", ""},
	{"Known It All", ""},
	{"Expanded Spellbook", ""},
	{"Enchanter", ""},
	{"Logical", ""},
	{"Arcane Ward", ""},
	{"Counterspell", ""},
	{"Quick Study", ""},
	//
	{"Hack and Slash", ""},
	{"Defy Danger", "", Strenght},
	{"Defy Danger", "", Dexterity},
	{"Defy Danger", "", Constitution},
	{"Defy Danger", "", Intellegence},
	{"Defy Danger", "", Wisdow},
	{"Defy Danger", "", Charisma},
	{"Parley", "", Charisma},
	{"Spout Lore", "���������� � ������", Intellegence},
	{"Discern Realities", "������� ����������", Wisdow},
	{"Supply", "", Charisma},
	{"Show charsheet sheet", "������� ������ ���������"},
	{"Examine Feature", "������� ���������� �������"},
	{"Go Back", "��������� �����"},
	{"Go Next", "��������� ������"},
	{"Make Camp", "������� ������"},
	{"All run away", "���� ������ ������ �����"},
};
assert_enum(move, RunAway);
getstr_enum(move);

bool game::isnoplayer(move_s id) {
	if(id >= MakeCamp)
		return true;
	return false;
}

stat_s hero::getstat(move_s id) const {
	switch(id) {
	case CastASpell:
		return (type == Wizard) ? Intellegence : Wisdow;
	default:
		return move_data[id].stat;
	}
}