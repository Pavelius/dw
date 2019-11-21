#include "main.h"

namei bsmeta<namei>::elements[] = {{TheAngel, NoGender, "Dou", "��"},
{TheAngel, Male, "Bon", "���"},
{TheAngel, Female, "Abe", "���"},
{TheAngel, Male, "Boo", ""},
{TheAngel, Male, "T", "��"},
{TheAngel, Male, "Kal", "����"},
{TheAngel, Male, "Bai", "���"},
{TheAngel, Male, "Char", "�����"},
{TheAngel, Male, "Jav", "����"},
{TheAngel, Female, "Ruth", "����"},
{TheAngel, Female, "Wei", "���"},
{TheAngel, Male, "Jay", "����"},
{TheAngel, Female, "Nee", "��"},
{TheAngel, Male, "Kim", "���"},
{TheAngel, Female, "Lan", "���"},
{TheAngel, Male, "Di", "��"},
{TheAngel, Female, "Dez", "���"},
{TheAngel, Male, "Doc", "���"},
{TheAngel, Male, "Core", "�����"},
{TheAngel, Female, "Wheels", "�������"},
{TheAngel, Male, "Buzz", "������"},
{TheAngel, Male, "Key", "����"},
{TheAngel, Female, "Gabe", "����"},
{TheAngel, Female, "Biz", "���"},
{TheAngel, Male, "Bish", "�����"},
{TheAngel, Female, "Line", "�������"},
{TheAngel, Male, "Inch", "����"},
{TheAngel, Male, "Grip", "�����"},
{TheAngel, Male, "Setter", "��������"},
//
{TheBattleBaby, Female, "Snow", "��������"},
{TheBattleBaby, Female, "Crimson", "����"},
{TheBattleBaby, Female, "Shadow", "����"},
{TheBattleBaby, Female, "Azure", "������"},
{TheBattleBaby, Female, "Midnight", "�������"},
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
{TheBattleBaby, Female, "Kite", "������"},
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
{TheGunlugger, Female, "Navarre", "�������"},
{TheGunlugger, Male, "Man", "�����"},
{TheGunlugger, Male, "Kartak", "������"},
{TheGunlugger, Male, "Barbarossa", "����������"},
{TheGunlugger, Female, "Keeler", "������"},
{TheGunlugger, Male, "Grekkor", "�������"},
{TheGunlugger, Male, "Crille", "������"},
{TheGunlugger, Male, "Doom", "���"},
{TheGunlugger, Male, "Chaplain", "��������"},
{TheGunlugger, Male, "Rex", "����"},
{TheGunlugger, Male, "Fido", "����"},
{TheGunlugger, Male, "Spot", "����"},
{TheGunlugger, Male, "Boxer", "������"},
{TheGunlugger, Male, "Doberman", "��������"},
{TheGunlugger, Male, "Trey", "����"},
{TheGunlugger, Male, "Killer", "�������"},
{TheGunlugger, Male, "Butch", "������"},
{TheGunlugger, Female, "Fifi", "����"},
{TheGunlugger, Female, "Fluffy", "�����"},
{TheGunlugger, Male, "Duke", "���"},
{TheGunlugger, Male, "Wolf", "����"},
{TheGunlugger, Female, "Rover", "����"},
{TheGunlugger, Male, "Max", "����"},
{TheGunlugger, Male, "Buddy", "������"},
};
DECLFULL(namei);

static int select(short unsigned* result, gender_s gender, booklet_s type) {
	auto p = result;
	for(auto& e : bsmeta<namei>()) {
		if(e.gender != NoGender && e.gender != gender)
			continue;
		if(e.type != type)
			continue;
		*p++ = &e - bsmeta<namei>::elements;
	}
	return p - result;
}

static short unsigned random_name(booklet_s type, gender_s gender) {
	short unsigned result[128];
	auto count = select(result, gender, type);
	if(!count)
		return 0;
	return result[rand() % count];
}

void hero::choosename(bool interactive, booklet_s booklet, gender_s gender) {
	short unsigned result[128];
	int count = select(result, gender, type);
	for(int i = 0; i < count; i++)
		an.add(result[i], bsmeta<namei>::elements[result[i]].name);
	auto v = an.choose(interactive, true, "��� ������ �������� ���:");
	setname(v);
}

const char* nameablei::getname() const {
	return bsmeta<namei>::elements[data].name;
}

gender_s nameablei::getgender() const {
	return bsmeta<namei>::elements[data].gender;
}