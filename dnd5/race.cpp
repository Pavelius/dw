#include "main.h"

racei bsmeta<racei>::elements[] = {{NoRace, "No race", "Нет расы"},
{NoRace, "dwarf", "дварф", {0, 0, 2, 0, 0, 0}, 25, Medium, {Darkvision, DwarvenResilience, DwarvenWeaponTrain, Stonecunning}, {LanguageDwarvish}},
{NoRace, "elf", "эльф", {0, 2, 0, 0, 0, 0}, 30, Medium, {Darkvision, FeyAncestry, TranceInsteadSleep}, {LanguageElvish}},
{NoRace, "halfling", "полурослик", {0, 2, 0, 0, 0, 0}, 25, Small, {Lucky, Brave}, {}},
{NoRace, "human", "человек", {1, 1, 1, 1, 1, 1}, 30, Medium, {}, {}},
//
{Dwarf, "hill", "холмистый", {0, 0, 0, 0, 1, 0}, 30, Medium, {DwarvenToughness}},
{Dwarf, "mountain", "горный", {2, 0, 0, 0, 0, 0}, 30, Medium, {LightArmorProficiency, MediumArmorProficiency}},
{Elf, "high", "высший", {0, 0, 0, 1, 0, 0}, 30, Medium, {ElfWeaponTrain}, {}, {1}, 1},
{Elf, "wood", "лесной", {0, 0, 0, 0, 1, 0}, 35, Medium, {MaskOfTheWild}, {}},
{Halfling, "lightfoot", "лекгоступый", {0, 0, 0, 0, 0, 1}, 30, Medium, {NaturallyStealthy}, {}},
{Halfling, "stout", "стойкий", {0, 0, 1, 0, 0, 0}, 35, Medium, {DwarvenResilience}, {}},
};
assert_enum(race, HalflingStout);

void creature::apply(race_s id, bool interactive) {
	if(bsmeta<racei>::elements[id].basic)
		apply(bsmeta<racei>::elements[id].basic, interactive);
	for(auto i=Strenght; i<=Charisma; i = (ability_s)(i+1))
		ability[i] += bsmeta<racei>::elements[id].abilities[i];
	for(auto e : bsmeta<racei>::elements[id].traits)
		set(e);
	for(auto e : bsmeta<racei>::elements[id].languages)
		set(e);
	apply(id, 1, interactive);
}