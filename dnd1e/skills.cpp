#include "main.h"

struct skill {
	const char*			id;
	const char*			name;
	classa				allowed;
	testinfo			test;
} skill_data[] = {
	{"Pick Pockets", "Очищать карманы", {Theif, Bard}, {TestSkill}},
	{"Open Locks", "Взламывать замки", {Theif}, {TestSkill}},
	{"Find/Remove Traps", "Находить ловушки", {Theif}, {TestSkill}},
	{"Move Silently", "Двигаться тихо", {Theif, Ranger}, {TestSkill}},
	{"Hide in Shadows", "Прятаться в тенях", {Theif, Ranger}, {TestSkill}},
	{"Detect Noise", "Различать звуки", {Theif, Bard}, {TestSkill}},
	{"Climb Walls", "Лазить по стенам", {Theif, Bard}, {TestSkill}},
	{"Read Languages", "Читать языки", {Theif, Bard}, {TestSkill}},
	//
	{"Open door", "Открыть дверь",{},{TestSkill}},
	{"Getting lost", "Шанс залудиться"},
	//
	{"Herbalism", "Травознавство", {Mage, Cleric, Druid}, {TestAbility, Wisdow}},
	{"Hunting", "Охота", {Fighter, Paladin, Ranger}, {TestAbility, Wisdow}},
	{"Tracking", "Выслеживание", {Ranger}, {TestAbility, Wisdow}},
	//
	{"Go away", "Выйти наружу"},
	{"Go inside", "Зайти внутрь"},
};
assert_enum(skill, GoInside);
getstr_enum(skill);

const classa& character::getclasses(skill_s id) {
	return skill_data[id].allowed;
}

const testinfo& character::getinfo(skill_s id) {
	return skill_data[id].test;
}