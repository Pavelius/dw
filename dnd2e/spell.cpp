#include "main.h"

enum target_s : unsigned char {
	TargetNone,
	TargetAlly, TargetAllAlly,
	TargetEnemy,
	TargetCreature,
};

static struct spell {
	const char*			id;
	const char*			name;
	school_s			school[2];
	char				levels[3]; // Cleric, Mage, Druid
	distance_s			distance;
	duration_s			duration;
	saveinfo			save;
	target_s			target;
	magic_power_s		state;
} spell_data[] = {
	{"Bless", "�������������", {Conjuration, Summoning}, {1}, Range6, Duration6Round, {}, TargetAllAlly, Blessed},
	{"Command", "�������", {Enchantment, Charm}, {1}, Range1, Duration1Round, {}, TargetEnemy, HumanControl},
	{"Create Water", "������� ����", {Alteration}, {1}, Range1, Permanent},
	{"Cure Light Wounds", "������ ������ �������", {Necromantic}, {1}, Touch, Instantaneous, {}, TargetAlly, Healing},
	{"Detect Evil", "���������� ���", {Divination}, {1}, Range12, Duration1TurnPlus1Per2Level},
	{"Detect Magic", "���������� �����", {Divination}, {1}, Range3, Duration1Turn},
	{"Light", "����", {Alteration}, {1}, Range12, Duration6TurnPlus1PerLevel},
	{"Protection From Evil", "������ �� ���", {Abjuration}, {1}, Touch, Duration5RoundPerLevel},
	{"Purify Food and Drink", "�������� ��� � ����", {Alteration}, {1}, Range3, Instantaneous},
	{"Remove Fear", "������ �����", {Abjuration}, {1}, Touch, Instantaneous},
	{"Resist Cold", "������������� ������", {Alteration}, {1}, Touch, Duration1TurnPerLevel},
	{"Sanctuary", "�������", {Abjuration}, {1}, Touch, Duration2RoundPlus1RoundPerLevel},
	//
	{"Augury", "�������", {Divination}, {1}, Self},
	{"Chant", "����������", {Conjuration, Summoning}, {1}, Self, Concetration, {}, TargetAllAlly},
	{"Detect Charm", "���������� ����������", {Divination}, {1}, Range3, Duration1Turn},
	{"Find Traps", "����� �������", {Divination}, {1}, Range3, Duration5Turn},
	{"Hold Person", "����������� �������", {Enchantment, Charm}, {1}, Range6, Duration4RoundPlus1RoundPerLevel, {SaveVsParalization, Negate}},
	{"Know Alignment", "������ ������������", {Divination}, {1}, Range1},
	{"Resist Fire", "������������� ����", {Alteration}, {1}, Touch},
	{"Silence, 15 Radius", "������, 15 ������", {Alteration}, {1}, Range12},
	{"Slow Poison", "��������� ��", {Necromantic}, {1}, Touch},
	{"Snake Charm", "��������� ����", {Enchantment, Charm}, {1}, Range3},
	{"Speak With Animals", "�������� � ���������", {Alteration}, {1}, Self},
	{"Spiritual Hammer", "�������� �����", {Invocation}, {1}, Range3},
};
assert_enum(spell, SpellSpiritualHammer);
getstr_enum(spell);