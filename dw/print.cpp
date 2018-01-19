#include "main.h"
#include "stringcreator.h"

int logs::getwidth(int panel) {
	return 0;
}

const char* logs::getpanel(int panel) {
	return 0;
}

struct logs_driver : stringcreator {

	const char*		name;
	gender_s		gender;
	const char*		weapon;

	static void msg(gender_s gender, char* result, const char* text_male, const char* text_female, const char* text_pluar) {
		if(gender == Female) {
			if(text_female)
				zcpy(result, text_female);
		} else {
			if(text_male)
				zcpy(result, text_male);
		}
	}

	void parseidentifier(char* result, const char* result_max, const char* identifier) override {
		if(strcmp(identifier, "�����") == 0)
			zcpy(result, name);
		else if(strcmp(identifier, "�����") == 0)
			grammar::of(result, name);
		else if(strcmp(identifier, "�������") == 0) {
			if(weapon)
				grammar::by(result, weapon);
			else
				zcpy(result, "������");
		} else if(strcmp(identifier, "���") == 0)
			msg(gender, result, "��", identifier, "���");
		else if(strcmp(identifier, "�") == 0)
			msg(gender, result, "", identifier, "�");
		else if(strcmp(identifier, "��") == 0)
			msg(gender, result, "", identifier, "��");
		else if(strcmp(identifier, "���") == 0)
			msg(gender, result, "��", identifier, "���");
		else if(strcmp(identifier, "��") == 0)
			msg(gender, result, "���", identifier, "��");
		else if(strcmp(identifier, "���") == 0)
			msg(gender, result, "����", identifier, "���");
		else {
			zcat(result, "[-");
			zcat(result, identifier);
			zcat(result, "]");
		}
	}

	logs_driver(const char* name, gender_s gender, const char* weapon) : name(name), gender(gender), weapon(weapon) {
	}

	logs_driver(const hero& player) : name(player.getname()), gender(player.gender), weapon(player.weapon ? getstr(player.weapon.type) : "") {
	}

};

void hero::act(const char* format, ...) const {
	logs_driver driver(*this);
	logs::addv(driver, format, xva_start(format));
}

void monster::act(const char* format, ...) const {
	logs_driver driver(getstr(type), Male, getweapon());
	logs::addv(driver, format, xva_start(format));
}

void hero::say(const char* format, ...) const {
	logs_driver driver(*this);
	logs::add("\n");
	logs::addv(driver, format, xva_start(format));
	logs::add("\n");
}