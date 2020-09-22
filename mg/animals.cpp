#include "main.h"

BSDATA(animali) = {{{}},
{"Badger", "Барсук", Male, 8, MammalsWise},
{"Bear", "Медведь", Male, 12, PredatorWise},
{"Crab", "Краб", Male, 6, BurrowWise},
{"Deer", "Олень", Male, 7, MammalsWise},
{"Frog", "Лягушка", Female, 4, BurrowWise},
{"Fox", "Лиса", Female, 7, PredatorWise},
{"Hawk", "Ястреб", Male, 7, BirdsWise},
{"Moose", "Лось", Male, 12, MammalsWise},
{"Mouse", "Мышь", Female, 2, MammalsWise},
{"Owl", "Сова", Female, 7, BirdsWise},
{"Racoon", "Енот", Male, 8, BurrowWise},
{"Snake", "Змея", Female, 6, BurrowWise},
{"Suqirrel", "Белка", Female, 5, MammalsWise},
{"Turtle", "Черепаха", Female, 8, BurrowWise},
{"Weasel", "Ласка", Female, 4, PredatorWise},
{"Wolf", "Волк", Male, 10, PredatorWise},
};
assert_enum(animali, Wolf)

void hero::create(animal_s type) {
	auto& e = bsdata<animali>::elements[type];
	setkind(type);
	skills[Nature] = e.nature;
	skills[Will] = e.nature;
	skills[Health] = e.nature;
}

bool hero::ismatch(animal_s id, wise_s wise) {
	if(id)
		return bsdata<animali>::elements[id].wise == wise;
	return false;
}