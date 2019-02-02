#include "main.h"

static struct skill_info {
	const char*			id;
	const char*			name;
} skill_data[] = {{"Might", "Мощь"},
{"Endurance", "Выносливость"},
{"Melee", "Рукопашная"},
{"Crafting", "Создание"},
{"Stealth", "Скрытность"},
{"SleightOfHand", "Ловкость рук"},
{"Move", "Движение"},
{"Marksmanship", "Меткость"},
{"Scouting", "Разведка"},
{"Lore", "Знания"},
{"Survival", "Выживание"},
{"Insight", "Проницательность"},
{"Manipulation", "Манипуляция"},
{"Performance", "Выступление"},
{"Healing", "Лечение"},
{"AnimalHandling", "Обращение с животными"},
};
getstr_enum(skill);
assert_enum(skill, AnimalHandling);
