#include "main.h"

struct namei {
	race_s		race;
	gender_s	gender;
	class_s		cls;
	const char*	name[2];
};
BSDATA(namei) = {{Human, NoGender, Fighter, {"Hawke", "Хавки"}},
{Human, Male, Fighter, {"Rudiger", "Рудигер"}},
{Human, Male, Fighter, {"Gregor", "Грегор"}},
{Human, Female, Fighter, {"Brianne", "Бриан"}},
{Human, Male, Fighter, {"Walton", "Вальтон"}},
{Human, Male, Fighter, {"Castor", "Кастор"}},
{Human, Female, Fighter, {"Shanna", "Шанна"}},
{Human, Male, Fighter, {"Ajax", "Айакс"}},
{Human, NoGender, Fighter, {"Hob", "Хоб"}},
{Halfling, NoGender, Fighter, {"Finnegan", "Финганн"}},
{Halfling, Female, Fighter, {"Olive", "Оливия"}},
{Halfling, Male, Fighter, {"Randolph", "Рэндольф"}},
{Halfling, NoGender, Fighter, {"Bartleby", "Батлбай"}},
{Halfling, Male, Fighter, {"Aubrey", "Аурбей"}},
{Halfling, Male, Fighter, {"Baldwin", "Балдвин"}},
{Halfling, Female, Fighter, {"Becca", "Бэкки"}},
{Elf, NoGender, Fighter, {"Elohiir", "Эйлохир"}},
{Elf, Female, Fighter, {"Sharaseth", "Харасез"}},
{Elf, Male, Fighter, {"Hasrith", "Хазрич"}},
{Elf, Male, Fighter, {"Shevara", "Шеварал"}},
{Elf, Male, Fighter, {"Cadeus", "Кадиус"}},
{Elf, Male, Fighter, {"Eldar", "Эльдар"}},
{Elf, Female, Fighter, {"Kithracet", "Котораса"}},
{Elf, Female, Fighter, {"Thelian", "Фелианна"}},
{Dwarf, Male, Fighter, {"Ozruk", "Озрук"}},
{Dwarf, Male, Fighter, {"Surtur", "Суртур"}},
{Dwarf, Female, Fighter, {"Brunhilda", "Брундилла"}},
{Dwarf, Female, Fighter, {"Annika", "Анника"}},
{Dwarf, Male, Fighter, {"Janos", "Джанос"}},
{Dwarf, Female, Fighter, {"Greta", "Гретта"}},
{Dwarf, Male, Fighter, {"Dim", "Дим"}},
{Dwarf, Male, Fighter, {"Rundrig", "Рундриг"}},
{Dwarf, Male, Fighter, {"Jar", "Жарл"}},
{Dwarf, Male, Fighter, {"Xotoq", "Ксоток"}},
//
{Dwarf, Female, Cleric, {"Durga", "Дурга"}},
{Dwarf, Male, Cleric, {"Aelfar", "Ольфар"}},
{Dwarf, Female, Cleric, {"Gerda", "Герда"}},
{Dwarf, Male, Cleric, {"Rurgosh", "Ругрош"}},
{Dwarf, Male, Cleric, {"Bjorn", "Бьерн"}},
{Dwarf, Male, Cleric, {"Drummond", "Друмонд"}},
{Dwarf, Female, Cleric, {"Helga", "Хельга"}},
{Dwarf, Female, Cleric, {"Siggrun", "Сигрин"}},
{Dwarf, Female, Cleric, {"Freya", "Фрея"}},
{Human, Male, Cleric, {"Wesley", "Вислей"}},
{Human, Male, Cleric, {"Brinton", "Бринтон"}},
{Human, Male, Cleric, {"Jon", "Йон"}},
{Human, Female, Cleric, {"Sara", "Сара"}},
{Human, Male, Cleric, {"Hawthorn", "Хавторн"}},
{Human, Female, Cleric, {"Elise", "Элис"}},
{Human, Male, Cleric, {"Clarke", "Кларк"}},
{Human, Male, Cleric, {"Lenore", "Линор"}},
{Human, Male, Cleric, {"Piotr", "Петр"}},
{Human, Male, Cleric, {"Dahlia", "Данила"}},
{Human, Female, Cleric, {"Carmine", "Кармин"}},
};
BSDECL(namei);

static int select(unsigned char* elements, class_s* type, race_s* race, gender_s gender) {
	auto p = elements;
	for(auto& e : bsdata<namei>()) {
		if(e.gender != NoGender && gender != gender)
			continue;
		if(type && e.cls != *type)
			continue;
		if(race && e.race != *race)
			continue;
		*p++ = &e - bsdata<namei>::elements;
	}
	return p - elements;
}

void nameable::setname(race_s race, gender_s gender) {
	unsigned char elements[sizeof(bsdata<namei>::elements) / sizeof(bsdata<namei>::elements[0])];
	int count = select(elements, 0, &race, gender);
	if(!count)
		count = select(elements, 0, 0, gender);
	if(!count)
		return;
	name = elements[rand() % count];
}

void nameable::setname(class_s type, race_s race, gender_s gender) {
	unsigned char elements[sizeof(bsdata<namei>::elements) / sizeof(bsdata<namei>::elements[0])];
	int count = select(elements, &type, &race, gender);
	if(!count)
		count = select(elements, 0, &race, gender);
	if(!count)
		count = select(elements, 0, 0, gender);
	if(!count)
		return;
	name = elements[rand() % count];
}

const char* nameable::getname() const {
	return bsdata<namei>::elements[name].name[1];
}

gender_s nameable::getnamegender() const {
	return bsdata<namei>::elements[name].gender;
}