#include "main.h"

static struct name_i {
	gender_s	gender;
	const char*	name[2];
} name_data[] = {{Male, {"Abram", "Абрам"}},
{Male, {"Aengus", "Авенгус"}},
{Male, {"Algomin", "Алгомин"}},
{Male, {"Beagan", "Биган"}},
{Male, {"Brand", "Бренд"}},
{Male, {"Cale", "Кейл"}},
{Male, {"Caley", "Калей"}},
{Male, {"Connor", "Коннор"}},
{Male, {"Curt", "Курт"}},
{Male, {"Faolan", "Фаолан"}},
{Male, {"Finn", "Финн"}},
{Male, {"Folker", "Фолкер"}},
{Male, {"Gamlion", "Гамлион"}},
{Male, {"Garnier", ""}},
{Male, {"Garrow", "Гарров"}},
{Male, {"Grahame", "Грейхэм"}},
{Male, {"Gurney", "Гурни"}},
{Male, {"Hannidy", "Хэннеди"}},
{Male, {"Henson", "Хенсон"}},
{Male, {"Jasper", "Джаспер"}},
{Male, {"Joseff", "Джозеф"}},
{Male, {"Kole", "Коул"}},
{Male, {"Laird", "Леирд"}},
{Male, {"Noelan", "Нулан"}},
{Male, {"Seyth", "Сит"}},
{Male, {"Siemon", "Симон"}},
{Male, {"Sloan", "Слоан"}},
{Male, {"Tander", "Тандер"}},
{Male, {"Thom", "Том"}},
{Male, {"Thurstan", "Хурстан"}},
{Male, {"Trevor", "Тревор"}},
{Male, {"Vidar", "Видар"}},
{Male, {"Walmond", "Валмонд"}},
{Female, {"Autumn", "Весна"}},
{Female, {"Aynssle", "Айнсле"}},
{Female, {"Baeylie", "Бейлиин"}},
{Female, {"Brynn", "Брин"}},
{Female, {"Caley", "Кейли"}},
{Female, {"Clove", "Клув"}},
{Female, {"Daewn", "Даен"}},
{Female, {"Dalia", "Дейля"}},
{Female, {"Daye", "Дая"}},
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