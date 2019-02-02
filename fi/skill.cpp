#include "main.h"

static struct skill_info {
	const char*			id;
	const char*			name;
	ability_s			attribute;
} skill_data[] = {{"Might", "Мощь", Strenght},
{"Endurance", "Выносливость", Strenght},
{"Melee", "Рукопашная", Strenght},
{"Crafting", "Создание", Strenght},
{"Stealth", "Скрытность", Agility},
{"SleightOfHand", "Ловкость рук", Agility},
{"Move", "Движение", Agility},
{"Marksmanship", "Меткость", Agility},
{"Scouting", "Разведка", Wits},
{"Lore", "Знания", Wits},
{"Survival", "Выживание", Wits},
{"Insight", "Проницательность", Wits},
{"Manipulation", "Манипуляция", Empathy},
{"Performance", "Выступление", Empathy},
{"Healing", "Лечение", Empathy},
{"AnimalHandling", "Обращение с животными", Empathy},
};
getstr_enum(skill);
assert_enum(skill, AnimalHandling);