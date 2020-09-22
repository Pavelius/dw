#include "main.h"

struct namei {
	gender_s	gender;
	const char*	name[2];
};

BSDATA(namei) = {{Male, {"Abram", "�����"}},
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
{Male, {"Garnier", "�������"}},
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
{Female, {"Gale", "����"}},
{Female, {"Ingrid", "������"}},
{Female, {"Ivy", "����"}},
{Female, {"Josephine", "��������"}},
{Female, {"Julyia", "����"}},
{Female, {"Kearra", "������"}},
{Female, {"Laurel", "������"}},
{Female, {"Lilly", "����"}},
{Female, {"Loonis", "�����"}},
{Female, {"Loralai", "�������"}},
{Female, {"Maren", "�����"}},
{Female, {"Millicent", "���������"}},
{Female, {"Moira", "�����"}},
{Female, {"Nola", "����"}},
{Female, {"Quinn", "�����"}},
{Female, {"Rona", "����"}},
{Female, {"Rosalee", "������"}},
{Female, {"Sayblee", "�������"}},
{Female, {"Serra", "����"}},
{Female, {"Sloan", "�����"}},
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
	return "������";
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