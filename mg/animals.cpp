#include "main.h"

animali bsmeta<animali>::elements[] = {{{}},
{"Badger", "Барсук", Male, 8},
{"Bear", "Медведь", Male, 12, PredatorWise},
{"Crab", "Краб", Male, 6},
{"Deer", "Олень", Male, 7},
{"Frog", "Лягушка", Female, 4},
{"Fox", "Лиса", Female, 7, PredatorWise},
{"Hawk", "Ястреб", Male, 7, BirdsWise},
{"Moose", "Лось", Male, 12, MammalsWise},
{"Mouse", "Мышь", Female, 2},
{"Owl", "Сова", Female, 7, BirdsWise},
{"Racoon", "Енот", Male, 8},
{"Snake", "Змея", Female, 6},
{"Suqirrel", "Белка", Female, 5},
{"Turtle", "Черепаха", Female, 8},
{"Weasel", "Ласка", Female, 4},
{"Wolf", "Волк", Male, 10, PredatorWise},
};
assert_enum(animal, Wolf);

hero::hero(animal_s type) {
	clear();
	auto& e = bsmeta<animali>::elements[type];
	this->type = type;
	gender = e.gender;
	skills[Nature] = e.nature;
	skills[Will] = e.nature;
	skills[Health] = e.nature;
}

bool hero::ismatch(animal_s id, wise_s wise) {
	if(id)
		return bsmeta<animali>::elements[id].wise == wise;
	return false;
}