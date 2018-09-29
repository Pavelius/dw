#include "main.h"

race_info race_data[] = {{NoRace, "No race", "��� ����"},
{NoRace, "dwarf", "�����", {0, 0, 2, 0, 0, 0}, 25, Medium, {Darkvision, DwarvenResilience, DwarvenWeaponTrain, Stonecunning}, {LanguageDwarvish}},
{NoRace, "elf", "����", {0, 2, 0, 0, 0, 0}, 30, Medium, {Darkvision, KeenSences, FeyAncestry, TranceInsteadSleep}, {LanguageElvish}},
{NoRace, "halfling", "����������", {0, 2, 0, 0, 0, 0}, 25, Small, {Lucky, Brave}, {}},
{NoRace, "human", "�������", {1, 1, 1, 1, 1, 1}, 30, Medium, {}, {}},
//
{Dwarf, "hill", "���������", {0, 0, 0, 0, 1, 0}, 30, Medium, {DwarvenToughness}},
{Dwarf, "mountain", "������", {2, 0, 0, 0, 0, 0}, 30, Medium, {LightArmorProficiency, MediumArmorProficiency}},
{Elf, "high", "������", {0, 0, 0, 1, 0, 0}, 30, Medium, {ElfWeaponTrain}, {}, 1, 1},
{Elf, "wood", "������", {0, 0, 0, 0, 1, 0}, 35, Medium, {MaskOfTheWild}, {}},
{Halfling, "lightfoot", "�����������", {0, 0, 0, 0, 0, 1}, 30, Medium, {NaturallyStealthy}, {}},
{Halfling, "stout", "�������", {0, 0, 1, 0, 0, 0}, 35, Medium, {DwarvenResilience}, {}},
};
assert_enum(race, HalflingStout);
getstr_enum(race);

void creature::apply(race_s id, bool interactive) {
	if(race_data[id].basic)
		apply(race_data[id].basic, interactive);
	for(auto i=Strenght; i<=Charisma; i = (ability_s)(i+1))
		ability[i] += race_data[id].abilities[i];
	for(auto e : race_data[id].traits)
		set(e);
}