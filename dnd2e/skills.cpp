#include "main.h"

struct skill {
	const char*		id;
	const char*		name;
	classa			allowed;
} skill_data[] = {
	{"Pick Pockets", "Очищать карманы", {Theif}},
	{"Open Locks", "Взламывать замки", {Theif}},
	{"Find/Remove Traps", "Находить ловушки", {Theif}},
	{"Move Silently", "Двигаться тихо", {Theif, Ranger}},
	{"Hide in Shadows", "Прятаться в тенях", {Theif, Ranger}},
	{"Detect Noise", "Различать звуки", {Theif}},
	{"Climb Walls", "Лазить по стенам", {Theif}},
	{"Read Languages", "Читать языки", {Theif}},
	//
	{"Open door", "Открыть дверь"},
	{"Open locked door", "Выбить закрытую дверь"},
	{"Find secret doors", "Найти секретный двери"},
	{"Learn spell", "Изучить заклинание", {MagicUser}},
};
assert_enum(skill, LearnSpell);
getstr_enum(skill);

const classa& character::getclasses(skill_s id) {
	return skill_data[id].allowed;
}