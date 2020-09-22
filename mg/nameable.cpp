#include "main.h"

struct namei {
	gender_s	gender;
	const char*	name[2];
};

BSDATA(namei) = {{Male, {"Abram", "Абрам"}},
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
{Male, {"Garnier", "Гарниер"}},
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
{Female, {"Gale", "Гейл"}},
{Female, {"Ingrid", "Ингрид"}},
{Female, {"Ivy", "Лоза"}},
{Female, {"Josephine", "Жозефина"}},
{Female, {"Julyia", "Юлия"}},
{Female, {"Kearra", "Кьярра"}},
{Female, {"Laurel", "Лаурел"}},
{Female, {"Lilly", "Лили"}},
{Female, {"Loonis", "Лунис"}},
{Female, {"Loralai", "Лоралаи"}},
{Female, {"Maren", "Марен"}},
{Female, {"Millicent", "Милисента"}},
{Female, {"Moira", "Мойра"}},
{Female, {"Nola", "Нола"}},
{Female, {"Quinn", "Квинн"}},
{Female, {"Rona", "Рона"}},
{Female, {"Rosalee", "Розали"}},
{Female, {"Sayblee", "Сайблин"}},
{Female, {"Serra", "Сера"}},
{Female, {"Sloan", "Слоан"}},
};

struct namea : adat<unsigned short, 128> {
	void select(gender_s gender) {
		auto pa = data;
		auto pb = endof();
		for(auto& e : bsdata<namei>::elements) {
			if(e.gender != gender)
				continue;
			if(pa < pb)
				*pa++ = &e - bsdata<namei>::elements;
		}
		count = pa - data;
	}
};

void nameable::setname(gender_s gender) {
	namea source; source.select(gender);
	if(source)
		name = source.data[rand() % source.count];
}

void nameable::setkind(variant v) {
	type = v.type;
	value = v.value;
}

const char* nameable::getname() const {
	if(type == Animal) {
		if(value==Mouse)
			return bsdata<namei>::elements[name].name[1];
		return bsdata<animali>::elements[value].name;
	}
	return "Объект";
}

gender_s nameable::getgender() const {
	if(type == Animal) {
		if(value == Mouse)
			return bsdata<namei>::elements[name].gender;
		return bsdata<animali>::elements[value].gender;
	}
	return NoGender;
}

void nameable::act(const char* format, ...) const {
	actv(sb, format, xva_start(format));
}

void nameable::actv(stringbuilder& sb, const char* format, const char* format_param) const {
	driver sc = sb;
	sc.name = getname();
	sc.gender = getgender();
	sc.addsep(' ');
	sc.addv(format, format_param);
	sb = sc;
}