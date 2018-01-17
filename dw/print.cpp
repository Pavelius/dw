#include "main.h"
#include "stringcreator.h"

int logs::getwidth(int panel) {
	return 0;
}

const char* logs::getpanel(int panel) {
	return 0;
}

struct logs_driver : stringcreator {

	const hero* player;

	static void gender(const hero* player, char* result, const char* text_male, const char* text_female, const char* text_pluar) {
		if(player->gender == Female) {
			if(text_female)
				zcpy(result, text_female);
		} else {
			if(text_male)
				zcpy(result, text_male);
		}
	}

	static char* szrating(char* result, const char* text, int level) {
		zcpy(result, text);
		auto p = zend(result);
		for(int i = 1; i < level; i++)
			*p++ = '+';
		*p = 0;
		return result;
	}

	void ability(char* result) {
		result[0] = 0;
		for(auto i = Strenght; i <= Charisma; i = (stat_s)(i + 1)) {
			if(i != Strenght)
				print(zend(result), ", ");
			print(zend(result), "%1 [%2i]", getstr(i), player->get(i));
		}
	}

	void parseidentifier(char* result, const char* result_max, const char* identifier) override {
		if(strcmp(identifier, "герой") == 0) {
			auto name = player ? player->getname() : 0;
			if(name)
				zcpy(result, name);
			else
				zcpy(result, "[-герой]");
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

	constexpr logs_driver(const hero* player) : player(player) {
	}

};

void hero::act(const char* format, ...) const {
	logs_driver sc(this);
	logs::addv(sc, format, xva_start(format));
}