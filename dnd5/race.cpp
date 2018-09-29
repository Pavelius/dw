#include "main.h"

race_info race_data[] = {{NoRace, "No race", "Нет расы"},
{NoRace, "dwarf", "дварф", {0, 0, 2, 0, 0, 0}, 25, Medium, {Darkvision, DwarvenResilience, DwarvenWeaponTrain, Stonecunning}, {LanguageDwarvish}},
{NoRace, "elf", "эльф", {0, 2, 0, 0, 0, 0}, 30, Medium, {Darkvision, KeenSences, FeyAncestry, TranceInsteadSleep}, {LanguageElvish}},
{NoRace, "halfling", "полурослик", {0, 2, 0, 0, 0, 0}, 25, Small, {Lucky, Brave}, {}},
{NoRace, "human", "человек", {1, 1, 1, 1, 1, 1}, 30, Medium, {}, {}},
//
{Dwarf, "hill", "холмистый", {0, 0, 0, 0, 1, 0}, 30, Medium, {DwarvenToughness}},
{Dwarf, "mountain", "горный", {2, 0, 0, 0, 0, 0}, 30, Medium, {LightArmorProficiency, MediumArmorProficiency}},
{Elf, "high", "высший", {0, 0, 0, 1, 0, 0}, 30, Medium, {ElfWeaponTrain}, {}, 1, 1},
{Elf, "wood", "лесной", {0, 0, 0, 0, 1, 0}, 35, Medium, {MaskOfTheWild}, {}},
{Halfling, "lightfoot", "лекгоступый", {0, 0, 0, 0, 0, 1}, 30, Medium, {NaturallyStealthy}, {}},
{Halfling, "stout", "стойкий", {0, 0, 1, 0, 0, 0}, 35, Medium, {DwarvenResilience}, {}},
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