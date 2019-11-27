#include "main.h"

skilli bsmeta<skilli>::elements[] = {{"Might", "Мощь", Strenght},
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
assert_enum(skill, AnimalHandling);

ability_s character::getkey(skill_s id) {
	return bsmeta<skilli>::elements[id].attribute;
}