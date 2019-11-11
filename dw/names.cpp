#include "main.h"

struct namei {
	race_s		race;
	gender_s	gender;
	class_s		cls;
	const char*	name[2];
};
static namei objects[] = {{Human, NoGender, Fighter, {"Hawke", "�����"}},
{Human, Male, Fighter, {"Rudiger", "�������"}},
{Human, Male, Fighter, {"Gregor", "������"}},
{Human, Female, Fighter, {"Brianne", "�����"}},
{Human, Male, Fighter, {"Walton", "�������"}},
{Human, Male, Fighter, {"Castor", "������"}},
{Human, Female, Fighter, {"Shanna", "�����"}},
{Human, Male, Fighter, {"Ajax", "�����"}},
{Human, NoGender, Fighter, {"Hob", "���"}},
{Halfling, NoGender, Fighter, {"Finnegan", "�������"}},
{Halfling, Female, Fighter, {"Olive", "������"}},
{Halfling, Male, Fighter, {"Randolph", "��������"}},
{Halfling, NoGender, Fighter, {"Bartleby", "�������"}},
{Halfling, Male, Fighter, {"Aubrey", "������"}},
{Halfling, Male, Fighter, {"Baldwin", "�������"}},
{Halfling, Female, Fighter, {"Becca", "�����"}},
{Elf, NoGender, Fighter, {"Elohiir", "�������"}},
{Elf, Female, Fighter, {"Sharaseth", "�������"}},
{Elf, Male, Fighter, {"Hasrith", "������"}},
{Elf, Male, Fighter, {"Shevara", "�������"}},
{Elf, Male, Fighter, {"Cadeus", "������"}},
{Elf, Male, Fighter, {"Eldar", "������"}},
{Elf, Female, Fighter, {"Kithracet", "��������"}},
{Elf, Female, Fighter, {"Thelian", "��������"}},
{Dwarf, Male, Fighter, {"Ozruk", "�����"}},
{Dwarf, Male, Fighter, {"Surtur", "������"}},
{Dwarf, Female, Fighter, {"Brunhilda", "���������"}},
{Dwarf, Female, Fighter, {"Annika", "������"}},
{Dwarf, Male, Fighter, {"Janos", "������"}},
{Dwarf, Female, Fighter, {"Greta", "������"}},
{Dwarf, Male, Fighter, {"Dim", "���"}},
{Dwarf, Male, Fighter, {"Rundrig", "�������"}},
{Dwarf, Male, Fighter, {"Jar", "����"}},
{Dwarf, Male, Fighter, {"Xotoq", "������"}},
//
{Dwarf, Female, Cleric, {"Durga", "�����"}},
{Dwarf, Male, Cleric, {"Aelfar", "������"}},
{Dwarf, Female, Cleric, {"Gerda", "�����"}},
{Dwarf, Male, Cleric, {"Rurgosh", "������"}},
{Dwarf, Male, Cleric, {"Bjorn", "�����"}},
{Dwarf, Male, Cleric, {"Drummond", "�������"}},
{Dwarf, Female, Cleric, {"Helga", "������"}},
{Dwarf, Female, Cleric, {"Siggrun", "������"}},
{Dwarf, Female, Cleric, {"Freya", "����"}},
{Human, Male, Cleric, {"Wesley", "������"}},
{Human, Male, Cleric, {"Brinton", "�������"}},
{Human, Male, Cleric, {"Jon", "���"}},
{Human, Female, Cleric, {"Sara", "����"}},
{Human, Male, Cleric, {"Hawthorn", "�������"}},
{Human, Female, Cleric, {"Elise", "����"}},
{Human, Male, Cleric, {"Clarke", "�����"}},
{Human, Male, Cleric, {"Lenore", "�����"}},
{Human, Male, Cleric, {"Piotr", "����"}},
{Human, Male, Cleric, {"Dahlia", "������"}},
{Human, Female, Cleric, {"Carmine", "������"}},
};

static int selectnames(unsigned char* elements, class_s* type, race_s* race, gender_s gender) {
	auto p = elements;
	for(int i = 0; i < sizeof(objects) / sizeof(objects[0]); i++) {
		if(objects[i].gender != NoGender && objects[i].gender != gender)
			continue;
		if(type && objects[i].cls != *type)
			continue;
		if(race && objects[i].race != *race)
			continue;
		*p++ = i;
	}
	return p - elements;
}

unsigned char npc::getrandomname(race_s race, gender_s gender) {
	unsigned char elements[sizeof(objects) / sizeof(objects[0])];
	int count = selectnames(elements, 0, &race, gender);
	if(!count)
		count = selectnames(elements, 0, 0, gender);
	if(!count)
		return 0;
	return elements[rand() % count];
}

unsigned char npc::getrandomname(class_s type, race_s race, gender_s gender) {
	unsigned char elements[sizeof(objects) / sizeof(objects[0])];
	int count = selectnames(elements, &type, &race, gender);
	if(!count)
		count = selectnames(elements, 0, &race, gender);
	if(!count)
		count = selectnames(elements, 0, 0, gender);
	if(!count)
		return 0;
	return elements[rand() % count];
}

const char* npc::getname() const {
	return objects[name].name[1];
}