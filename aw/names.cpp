#include "main.h"

static struct nameinfo {
	booklet_s		type;
	gender_s		gender;
	const char*		id;
	const char*		name;
} objects[] = {
	{TheAngel, Transgender, "Dou", "��"},
	{TheAngel, Male, "Bon", "���"},
	{TheAngel, Female, "Abe", "���"},
	{TheAngel, Male, "Boo", ""},
	{TheAngel, Transgender, "T", "��"},
	{TheAngel, Male, "Kal", "����"},
	{TheAngel, Male, "Bai", "���"},
	{TheAngel, Transgender, "Char", "�����"},
	{TheAngel, Male, "Jav", "����"},
	{TheAngel, Female, "Ruth", "����"},
	{TheAngel, Female, "Wei", "���"},
	{TheAngel, Male, "Jay", "����"},
	{TheAngel, Transgender, "Nee", "��"},
	{TheAngel, Male, "Kim", "���"},
	{TheAngel, Female, "Lan", "���"},
	{TheAngel, Male, "Di", "��"},
	{TheAngel, Female, "Dez", "���"},
	{TheAngel, Transgender, "Doc", "���"},
	{TheAngel, Male, "Core", "�����"},
	{TheAngel, Female, "Wheels", "�������"},
	{TheAngel, Male, "Buzz", "������"},
	{TheAngel, Male, "Key", "����"},
	{TheAngel, Female, "Gabe", "����"},
	{TheAngel, Female, "Biz", "���"},
	{TheAngel, Transgender, "Bish", "�����"},
	{TheAngel, Female, "Line", "�������"},
	{TheAngel, Male, "Inch", "����"},
	{TheAngel, Male, "Grip", "�����"},
	{TheAngel, Male, "Setter", "��������"},
	//
	{TheBattleBaby, Female, "Snow", "��������"},
	{TheBattleBaby, Female, "Crimson", "����"},
	{TheBattleBaby, Female, "Shadow", "����"},
	{TheBattleBaby, Female, "Azure", "������"},
	{TheBattleBaby, Transgender, "Midnight", "�������"},
	{TheBattleBaby, Female, "Scarlet", "������"},
	{TheBattleBaby, Female, "Violetta", "��������"},
	{TheBattleBaby, Female, "Amber", "������"},
	{TheBattleBaby, Female, "Rouge", "���"},
	{TheBattleBaby, Female, "Damson", "��������"},
	{TheBattleBaby, Female, "Sunset", "�����"},
	{TheBattleBaby, Female, "Emerald", "�����"},
	{TheBattleBaby, Female, "Ruby", "�������"},
	{TheBattleBaby, Female, "Raksha", "�����"},
	{TheBattleBaby, Female, "Kickskirt", "������"},
	{TheBattleBaby, Transgender, "Kite", "������"},
	{TheBattleBaby, Female, "Monsoon", "������"},
	{TheBattleBaby, Female, "Smith", "����"},
	{TheBattleBaby, Female, "Beastie", "������"},
	{TheBattleBaby, Female, "Baaba", "�������"},
	{TheBattleBaby, Female, "Melody", "�������"},
	{TheBattleBaby, Female, "Mar", "�����"},
	{TheBattleBaby, Female, "Tavi", "����"},
	{TheBattleBaby, Female, "Absinthe", "������"},
	{TheBattleBaby, Female, "Honeytree", "�������"},
	//
	{TheGunlugger, Male, "Vonk the Sculptor", "���� '���������'"},
	{TheGunlugger, Female, "Batty", "�����"},
	{TheGunlugger, Male, "Jonker", "������"},
	{TheGunlugger, Male, "A.T.", "��-��"},
	{TheGunlugger, Male, "Rue Wakeman", "�� ������"},
	{TheGunlugger, Transgender, "Navarre", "�������"},
	{TheGunlugger, Male, "Man", "�����"},
	{TheGunlugger, Male, "Kartak", "������"},
	{TheGunlugger, Male, "Barbarossa", "����������"},
	{TheGunlugger, Transgender, "Keeler", "������"},
	{TheGunlugger, Male, "Grekkor", "�������"},
	{TheGunlugger, Male, "Crille", "������"},
	{TheGunlugger, Male, "Doom", "���"},
	{TheGunlugger, Male, "Chaplain", "��������"},
	{TheGunlugger, Male, "Rex", "����"},
	{TheGunlugger, Transgender, "Fido", "����"},
	{TheGunlugger, Transgender, "Spot", "����"},
	{TheGunlugger, Male, "Boxer", "������"},
	{TheGunlugger, Transgender, "Doberman", "��������"},
	{TheGunlugger, Male, "Trey", "����"},
	{TheGunlugger, Male, "Killer", "�������"},
	{TheGunlugger, Male, "Butch", "������"},
	{TheGunlugger, Female, "Fifi", "����"},
	{TheGunlugger, Female, "Fluffy", "�����"},
	{TheGunlugger, Male, "Duke", "���"},
	{TheGunlugger, Male, "Wolf", "����"},
	{TheGunlugger, Transgender, "Rover", "����"},
	{TheGunlugger, Male, "Max", "����"},
	{TheGunlugger, Male, "Buddy", "������"},
};

static int select(short unsigned* result, gender_s gender, booklet_s type) {
	auto p = result;
	for(auto& e : objects) {
		if(e.gender != Transgender && e.gender != gender)
			continue;
		if(e.type != type)
			continue;
		*p++ = &e - objects;
	}
	return p - result;
}

const char*	thing::getname(gender_s gender, booklet_s type) {
	short unsigned result[128];
	auto count = select(result, gender, type);
	if(!count)
		return 0;
	return objects[rand() % count].name;
}

void hero::choosename(bool interactive) {
	short unsigned result[128];
	int count = select(result, getgender(), type);
	for(int i = 0; i < count; i++)
		logs::add(result[i], objects[result[i]].name);
	setname(objects[logs::input(interactive, true, "��� ������ �������� ���:")].name);
}