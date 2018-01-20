#include "main.h"

int logs::getwidth(int panel) {
	return 300;
}

const char* logs::getpanel(int panel) {
	return "%party%party_money";
}

static void msg(gender_s gender, char* result, const char* text_male, const char* text_female, const char* text_pluar) {
	if(gender == Female) {
		if(text_female)
			zcpy(result, text_female);
	} else {
		if(text_male)
			zcpy(result, text_male);
	}
}

void logs::driver::parseidentifier(char* result, const char* result_max, const char* identifier) {
	if(strcmp(identifier, "герой") == 0)
		zcpy(result, name);
	else if(strcmp(identifier, "героя") == 0)
		grammar::of(result, name);
	else if(strcmp(identifier, "оружием") == 0) {
		if(weapon)
			grammar::by(result, weapon);
		else
			zcpy(result, "руками");
	} else if(strcmp(identifier, "ась") == 0)
		msg(gender, result, "ся", identifier, "ись");
	else if(strcmp(identifier, "а") == 0)
		msg(gender, result, "", identifier, "и");
	else if(strcmp(identifier, "ла") == 0)
		msg(gender, result, "", identifier, "ли");
	else if(strcmp(identifier, "она") == 0)
		msg(gender, result, "он", identifier, "они");
	else if(strcmp(identifier, "ее") == 0)
		msg(gender, result, "его", identifier, "их");
	else if(strcmp(identifier, "нее") == 0)
		msg(gender, result, "него", identifier, "них");
	else {
		zcat(result, "[-");
		zcat(result, identifier);
		zcat(result, "]");
	}
}

logs::driver::driver(const char* name, gender_s gender, const char* weapon) : name(name), gender(gender), weapon(weapon) {
}

logs::driver::driver(const hero& player) : name(player.getname()), gender(player.gender), weapon(player.weapon ? getstr(player.weapon.type) : "") {
}

PRINTPLG(party) {
	result[0] = 0;
	auto p = result;
	for(auto& e : players) {
		if(!e)
			continue;
		spell_state* spell_active[32];
		logs::driver sc(e);
		if(!e.isalive())
			sc.print(p, "%герой погиб%ла");
		else if(e.hp < e.getmaxhits())
			sc.print(p, "%герой ранен%а ([-%1i]/%2i)", e.hp, e.getmaxhits());
		else
			sc.print(p, "%герой полностью здоров%а");
		auto spell_count = e.select(spell_active, spell_active + lenghtof(spell_active));
		for(unsigned i = 0; i < spell_count; i++) {
			if(i == 0)
				zcat(p, ", поддерживает ");
			else if(i == spell_count - 1)
				zcat(p, " и ");
			else
				zcat(p, ", ");
			p = zend(p);
			zcpy(p, getstr(spell_active[i]->spell));
		}
		zcat(p, ".\n");
		p = zend(p);
	}
	return result;
}

PRINTPLG(party_money) {
	if(!hero::getcoins())
		szprint(result, "У вас вообще нет денег.");
	else
		szprint(result, "У вас есть [%1i] монет.", hero::getcoins());
	zcat(result, "\n");
	return result;
}

void hero::act(const char* format, ...) const {
	logs::driver driver(*this);
	logs::addv(driver, format, xva_start(format));
}

void monster::act(const char* format, ...) const {
	logs::driver driver(getstr(type), Male, getweapon());
	logs::addv(driver, format, xva_start(format));
}

void hero::say(const char* format, ...) const {
	logs::driver driver(*this);
	logs::add("\n");
	logs::addv(driver, format, xva_start(format));
	logs::add("\n");
}