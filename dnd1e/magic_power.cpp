#include "main.h"

static struct magic_power_info {
	const char*		id;
	const char*		name;
	const char*		visual;
} magic_power_data[] = {
	{"", ""},
	{"Animal Control", "���������� ���������"},
	{"Clairaudience", "������������"},
	{"Clairvoyance", "�����������"},
	{"Climbing", "�������"},
	{"Delusion", "������"},
	{"Diminution", "����������"},
	{"Dragon Control", "���������� ���������"},
	{"Elixir of Health", "������� ��������"},
	{"Elixir of Madness", "������� �����������"},
	{"Elixir of Youth", "������� ���������"},
	{"ESP", "���������"},
	{"Extra Healing", "������ �������"},
	{"Fire Breath", "��������� �������"},
	{"Fire Resistance", "������������� ����"},
	{"Flying", "������"},
	{"Gaseous Form", "������������ �����"},
	{"Giant Control", "���������� ���������"},
	{"Giant Strength", "���� �������"},
	{"Growth", "�����"},
	{"Healing", "�������"},
	{"Heroism", "��������"},
	{"Human Control", "���������� ������"},
	{"Invisibility", "�����������"},
	{"Invulnerability", "������������"},
	{"Levitation", "���������"},
	{"Longevity", "����������"},
	{"Acid Resistance", "������������� �������"},
	{"Disenchantment", "�������������"},
	{"Elemental Invulnerability", "����������� � ���������"},
	{"Etherealness", "���������"},
	{"Fiery Burning", "������� �������"},
	{"Fumbling", "�����������"},
	{"Impact", "�����"},
	{"Slipperiness", "�����������"},
	{"Timelessness", ""},
	{"Glibness", ""},
	{"Love", ""},
	{"Persuasiveness", ""},
	{"Stammering and Stuttering", ""},
	{"Plant Control", ""},
	{"Poison", ""},
	{"Polymorph", ""},
	{"Rainbow Hues", ""},
	{"Speed", ""},
	{"Super-heroism", ""},
	{"Sweet Water", ""},
	{"Treasure Finding", ""},
	{"Undead Control", ""},
	{"Ventriloquism", ""},
	{"Vitality", ""},
	{"Water Breathing", ""},
	//
	{"Blinking", ""},
	{"Chameleon Power", ""},
	{"Clumsiness", ""},
	{"Contrariness", ""},
	{"Djinni Summoning", ""},
	{"Elemental Command", ""},
	{"Feather Falling", ""},
	{"Free Action", ""},
	{"Jumping", ""},
	{"Mind Shielding", ""},
	{"Protection", ""},
	{"Ram", ""},
	{"Regeneration", ""},
	{"Shocking Grasp", ""},
	{"Shooting Stars", ""},
	{"Spell Storing", ""},
	{"Spell Turning", ""},
	{"Sustenance", ""},
	{"Swimming", ""},
	{"Telekinesis", ""},
	{"Truth", ""},
	{"Warmth", ""},
	{"Water Walking", ""},
	{"Weakness", ""},
	{"Wizardry", ""},
	{"Darkvision", ""},
	//
	{"Surprise", ""},
};
assert_enum(magic_power, Surprised);
getstr_enum(magic_power);
metadc_enum(magic_power);