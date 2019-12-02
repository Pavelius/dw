#include "main.h"

struct namei {
	gender_s			gender;
	character_s			character;
	const char*			name;
};

namei bsmeta<namei>::elements[] = {{Male, Adventurer, "Гаврон"},
{Male, Adventurer, "Дарион"},
{Female, Adventurer, "Соня"},
{Female, Adventurer, "Алара"},
{Female, Adventurer, "Дегель"},
{Male, Elf, "Артерион"},
{Male, Warrior, "Брудер"},
{Male, Warrior, "Дерегорн"},
{Male, Adventurer, "Дер"},
{Male, Magician, "Праодан"},
};
DECLFULL(namei);

static int select(unsigned short* elements, character_s* character, gender_s gender) {
	auto p = elements;
	for(auto& e : bsmeta<namei>()) {
		if(e.gender != gender)
			continue;
		if(character && e.character != *character)
			continue;
		*p++ = &e - bsmeta<namei>::elements;
	}
	return p - elements;
}

void nameable::random_name(character_s character, gender_s gender) {
	const unsigned emax = sizeof(bsmeta<namei>::elements) / sizeof(bsmeta<namei>::elements[0]);
	short unsigned elements[emax];
	name = 0;
	auto count = select(elements, &character, gender);
	if(!count)
		count = select(elements, 0, gender);
	if(count)
		name = elements[rand() % count];
}

void nameable::actv(const char* format, const char* format_param) const {
	driver dr = sb;
	dr.gender = getgender();
	dr.name = getname();
	dr.addsep(' ');
	dr.addv(format, format_param);
	sb = dr;
}

void nameable::act(const char* format, ...) const {
	actv(format, xva_start(format));
}

void nameable::actv(const nameable& opponent, const char* format, const char* format_param) const {
	driver dr = sb;
	dr.name = getname();
	dr.gender = getgender();
	dr.opponent_name = opponent.getname();
	dr.opponent_gender = opponent.getgender();
	dr.addsep(' ');
	dr.addv(format, format_param);
	sb = dr;
}

void nameable::act(const nameable& opponent, const char* format, ...) const {
	actv(opponent, format, xva_start(format));
}

gender_s nameable::getgender() const {
	switch(type) {
	case Character: return bsmeta<namei>::elements[name].gender;
	default: return Male;
	}
}

const char* nameable::getname() const {
	switch(type) {
	case Character: return bsmeta<namei>::elements[name].name;
	default: return "Безимянный";
	}
}