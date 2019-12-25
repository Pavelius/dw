#include "main.h"

animali bsmeta<animali>::elements[] = {{{}},
{"Badger", "������", Male, 8},
{"Bear", "�������", Male, 12, PredatorWise},
{"Crab", "����", Male, 6},
{"Deer", "�����", Male, 7},
{"Frog", "�������", Female, 4},
{"Fox", "����", Female, 7, PredatorWise},
{"Hawk", "������", Male, 7, BirdsWise},
{"Moose", "����", Male, 12, MammalsWise},
{"Mouse", "����", Female, 2},
{"Owl", "����", Female, 7, BirdsWise},
{"Racoon", "����", Male, 8},
{"Snake", "����", Female, 6},
{"Suqirrel", "�����", Female, 5},
{"Turtle", "��������", Female, 8},
{"Weasel", "�����", Female, 4},
{"Wolf", "����", Male, 10, PredatorWise},
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