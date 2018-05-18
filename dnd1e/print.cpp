#include "main.h"

logs::state logc;

logs::state::state() {
	memcpy(this, &logc, sizeof(*this));
}

logs::state::~state() {
	memcpy(&logc, this, sizeof(*this));
}

int logs::getwidth(int index) {
	return logc.width;
}

const char* logs::getpanel(int index) {
	return logc.information;
}

struct logs_driver : stringcreator {

	struct variable {
		const char*	id;
		void		(logs_driver::*proc)(char* result);
	};

	const character* player;
	const character* opponent;

	static void gender(const character* player, char* result, const char* text_male, const char* text_female, const char* text_pluar) {
		//if(player->getcount() > 1) {
		//	if(text_pluar)
		//		zcpy(result, text_pluar);
		//}
		if(player->getgender() == Female) {
			if(text_female)
				zcpy(result, text_female);
		}
		else {
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
		for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
			if(i != Strenght)
				print(zend(result), ", ");
			print(zend(result), "%1 [%2i]", getstr(i), player->get(i));
		}
	}

	void skills(char* result) {
		result[0] = 0;
		auto p = result;
		for(auto i = PickPockets; i <= ReadLanguages; i = (skill_s)(i + 1)) {
			auto level = player->get(i);
			if(level<=0)
				continue;
			if(p != result)
				zcpy(p, ", ");
			print(zend(p), "%1 [%2i%%]", getstr(i), level);
			p = zend(p);
		}
		if(p != result)
			zcat(p, ". ");
	}

	void saving_throws(char* result) {
		result[0] = 0;
		auto p = result;
		for(auto i = SaveVsParalization; i <= SaveVsSpells; i = (save_s)(i + 1)) {
			auto level = player->get(i);
			if(level <= 0)
				continue;
			level = imax(1, 20 - level + 1) * 5;
			if(p != result)
				zcpy(p, ", ");
			print(zend(p), "%1 [%2i%%]", getstr(i), level);
			p = zend(p);
		}
		if(p != result)
			zcat(p, ". ");
	}

	static aref<variable> getvariables() {
		static variable methods[] = {
			{"способности", &ability},
			{"навыки", &skills},
			{"спас_броски", &saving_throws},
		};
		return methods;
	}

	static variable* find(const char* identifier) {
		for(auto& e : getvariables()) {
			if(strcmp(e.id, identifier) == 0)
				return &e;
		}
		return 0;
	}

	static character::variable* findc(const char* identifier) {
		for(auto& e : character::getvariables()) {
			if(strcmp(e.id, identifier) == 0)
				return &e;
		}
		return 0;
	}

	void parseidentifier(char* result, const char* result_max, const char* identifier) override {
		if(strcmp(identifier, "герой") == 0) {
			auto name = player ? player->getname() : 0;
			if(name)
				zcpy(result, name);
			else
				zcpy(result, "[-герой]");
		} else if(strcmp(identifier, "группа") == 0) {
			if(player)
				player->getname(result, result_max);
			else
				zcpy(result, "[-группа]");
		} else if(strcmp(identifier, "враг") == 0) {
			auto name = opponent ? opponent->getname() : 0;
			if(name)
				zcpy(result, name);
			else
				zcpy(result, "[-враг]");
		} else if(strcmp(identifier, "оружием") == 0) {
			auto v = player->get(MeleeWeapon);
			if(v)
				zcpy(result, v.getnameby());
			else
				zcpy(result, "[-оружием]");
		} else if(strcmp(identifier, "ась") == 0)
			gender(player, result, "ся", identifier, "ись");
		else if(strcmp(identifier, "а") == 0)
			gender(player, result, "", identifier, "и");
		else if(strcmp(identifier, "ла") == 0)
			gender(player, result, "", identifier, "ли");
		else {
			auto p = find(identifier);
			if(p)
				(this->*(p->proc))(result);
			else {
				auto p = findc(identifier);
				if(p) {
					auto value = (player->*(p->proc))();
					auto pr = p->present;
					if(!pr)
						pr = "%1i";
					print(result, pr, value);
				}
				else {
					zcat(result, "[-");
					zcat(result, identifier);
					zcat(result, "]");
				}
			}
		}
	}

	logs_driver() : player(0), opponent(0) {
	}

};

void character::actvs(const character& opponent, const char* format, ...) const {
	logs_driver driver;
	driver.player = this;
	driver.opponent = &opponent;
	logs::addv(driver, format, xva_start(format));
}

void character::act(const char* format, ...) const {
	logs_driver driver;
	driver.player = this;
	logs::addv(driver, format, xva_start(format));
}

void character::say(const char* format, ...) const {
	logs::add("\n");
	logs_driver driver;
	driver.player = this;
	logs::addv(driver, format, xva_start(format));
	logs::add("\n");
}