#include "main.h"

BSDATA(animali) = {{{}},
{"Badger", "������", Male, 8, MammalsWise},
{"Bear", "�������", Male, 12, PredatorWise},
{"Crab", "����", Male, 6, BurrowWise},
{"Deer", "�����", Male, 7, MammalsWise},
{"Frog", "�������", Female, 4, BurrowWise},
{"Fox", "����", Female, 7, PredatorWise},
{"Hawk", "������", Male, 7, BirdsWise},
{"Moose", "����", Male, 12, MammalsWise},
{"Mouse", "����", Female, 2, MammalsWise},
{"Owl", "����", Female, 7, BirdsWise},
{"Racoon", "����", Male, 8, BurrowWise},
{"Snake", "����", Female, 6, BurrowWise},
{"Suqirrel", "�����", Female, 5, MammalsWise},
{"Turtle", "��������", Female, 8, BurrowWise},
{"Weasel", "�����", Female, 4, PredatorWise},
{"Wolf", "����", Male, 10, PredatorWise},
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