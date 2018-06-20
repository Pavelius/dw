#include "main.h"

static struct skill_i
{
	const char*			name[2];
	char				class_skills[Soldier + 1];
	ability_s			ability;
} skill_data[] = {
	{{"Acrobatic", "Акробатика"}, {1, 0, 1, 0, 0}, Dexterity},
	{{"Climb", "Лазить"}, {0, 0, 0, 1, 1}, Strenght},
	{{"Deception", "Обман"}, {0, 1, 1, 0, 0}, Charisma},
	{{"Endurance", "Выносливость"}, {1, 0, 0, 1, 1}, Constitution},
	{{"Gather Information", "Добывание информации"}, {0, 1, 1, 0, 0}, Charisma},
	{{"Initiative", "Инициатива"}, {1, 1, 1, 1, 1}, Dexterity},
	{{"Jump", "Прыжки"}, {1, 0, 0, 1, 1}, Strenght},
	{{"Buerocracy", "Бюрократия"}, {1, 1, 1, 1, 0}, Intellegence},
	{{"Galactic Lore", "Знание галактики"}, {1, 1, 1, 1, 0}, Intellegence},
	{{"Life Sciences", "Биологические науки"}, {1, 1, 1, 1, 0}, Intellegence},
	{{"Physical Sciences", "Физические науки"}, {1, 1, 1, 1, 0}, Intellegence},
	{{"Social Sciences", "Социальные науки"}, {1, 1, 1, 1, 0}, Intellegence},
	{{"Tactics", "Тактика"}, {1, 1, 1, 1, 1}, Intellegence},
	{{"Technology", "Технологии"}, {0, 1, 0, 0, 0}, Intellegence},
	{{"Mechanics", "Механика"}, {0, 0, 1, 1, 1}, Intellegence},
	{{"Perception", "Внимательность"}, {1, 1, 1, 1, 1}, Wisdow},
	{{"Persuasion", "Убеждение"}, {0, 1, 1, 0, 0}, Charisma},
	{{"Pilot", "Пилот"}, {1, 1, 1, 1, 1}, Intellegence},
	{{"Ride", "Езда верхом"}, {0, 1, 0, 1, 0}, Dexterity},
	{{"Stealth", "Скрытность"}, {0, 0, 1, 1, 0}, Dexterity},
	{{"Survival", "Выживание"}, {0, 0, 0, 1, 0}, Wisdow},
	{{"Swim", "Плавание"}, {0, 0, 0, 1, 1}, Strenght},
	{{"Treat Injury", "Лечить ранения"}, {0, 1, 0, 0, 1}, Wisdow},
	{{"Use Computer", "Использовать компьютер"}, {0, 1, 1, 0, 1}, Intellegence},
	{{"Use Force", "Использовать силу"}, {1, 0, 0, 0, 0}, Charisma},
};

bool creature::isclass(feat_s id) const
{
	if(id >= FirstSkill && id <= LastSkill)
	{
		for(auto i = Jedi; i <= Soldier; i = (class_s)(i + 1))
		{
			if(classes[i] && skill_data[id - FirstSkill].class_skills[i])
				return true;
		}
	}
	return false;
}

ability_s game::getability(feat_s id)
{
	if(id >= FirstSkill && id <= LastSkill)
		return skill_data[id-FirstSkill].ability;
	return Dexterity;
}