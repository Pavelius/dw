#include "main.h"
#include "stringcreator.h"

int logs::getwidth(int panel) {
	return 0;
}

const char* logs::getpanel(int panel) {
	return 0;
}

struct logs_driver : stringcreator {

	const hero& player;

	static void gender(const hero& player, char* result, const char* text_male, const char* text_female, const char* text_pluar) {
		if(player.gender == Female) {
			if(text_female)
				zcpy(result, text_female);
		} else {
			if(text_male)
				zcpy(result, text_male);
		}
	}

	void race(char* result) {
		zcpy(result, getstr(player.race));
		szlower(result, 1);
	}

	void alignment(char* result) {
		zcpy(result, getstr(player.alignment));
		szlower(result, 1);
	}

	void gender(char* result) {
		zcpy(result, getstr(player.gender));
		szlower(result, 1);
	}

	void parseidentifier(char* result, const char* result_max, const char* identifier) override {
		if(strcmp(identifier, "герой") == 0) {
			zcpy(result, player.getname());
		} else if(strcmp(identifier, "оружием") == 0) {
			auto v = player.weapon;
			if(v)
				grammar::by(result, getstr(v.type));
			else
				zcpy(result, "руками");
		} else if(strcmp(identifier, "ась") == 0)
			gender(player, result, "ся", identifier, "ись");
		else if(strcmp(identifier, "а") == 0)
			gender(player, result, "", identifier, "и");
		else if(strcmp(identifier, "ла") == 0)
			gender(player, result, "", identifier, "ли");
		else {
			zcat(result, "[-");
			zcat(result, identifier);
			zcat(result, "]");
		}
	}

	logs_driver(const hero& player) : player(player) {
	}

};

void hero::act(const char* format, ...) const {
	logs_driver driver(*this);
	logs::addv(driver, format, xva_start(format));
}

void hero::say(const char* format, ...) const {
	logs_driver driver(*this);
	logs::add("\n");
	logs::addv(driver, format, xva_start(format));
	logs::add("\n");
}