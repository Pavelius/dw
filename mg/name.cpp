#include "main.h"

static struct name_i {
	gender_s	gender;
	const char*	name[2];
} name_data[] = {{Male, {"Abram", "�����"}},
{Male, {"Aengus", "�������"}},
{Male, {"Algomin", "�������"}},
{Male, {"Beagan", "�����"}},
{Male, {"Brand", "�����"}},
{Male, {"Cale", "����"}},
{Male, {"Caley", "�����"}},
{Male, {"Connor", "������"}},
{Male, {"Curt", "����"}},
{Male, {"Faolan", "������"}},
{Male, {"Finn", "����"}},
{Male, {"Folker", "������"}},
{Male, {"Gamlion", "�������"}},
{Male, {"Garnier", ""}},
{Male, {"Garrow", "������"}},
{Male, {"Grahame", "�������"}},
{Male, {"Gurney", "�����"}},
{Male, {"Hannidy", "�������"}},
{Male, {"Henson", "������"}},
{Male, {"Jasper", "�������"}},
{Male, {"Joseff", "������"}},
{Male, {"Kole", "����"}},
{Male, {"Laird", "�����"}},
{Male, {"Noelan", "�����"}},
{Male, {"Seyth", "���"}},
{Male, {"Siemon", "�����"}},
{Male, {"Sloan", "�����"}},
{Male, {"Tander", "������"}},
{Male, {"Thom", "���"}},
{Male, {"Thurstan", "�������"}},
{Male, {"Trevor", "������"}},
{Male, {"Vidar", "�����"}},
{Male, {"Walmond", "�������"}},
{Female, {"Autumn", "�����"}},
{Female, {"Aynssle", "������"}},
{Female, {"Baeylie", "�������"}},
{Female, {"Brynn", "����"}},
{Female, {"Caley", "�����"}},
{Female, {"Clove", "����"}},
{Female, {"Daewn", "����"}},
{Female, {"Dalia", "�����"}},
{Female, {"Daye", "���"}},
};

static unsigned select(unsigned char* pa, unsigned char* pb, gender_s gender) {
	auto source = pa;
	for(unsigned char index = 0; index < sizeof(name_data) / sizeof(name_data[0]); index++) {
		if(name_data[index].gender != gender)
			continue;
		if(pa < pb)
			*pa++ = index;
	}
	return pa - source;
}

void hero::choosename(bool interactive) {
	unsigned char source[256];
	auto count = select(source, source + sizeof(source) / sizeof(source[0]), gender);
	if(count)
		name = source[rand() % count];
}

const char* hero::getname() const {
	if(type == Mouse)
		return name_data[name].name[1];
	return getstr(type);
}