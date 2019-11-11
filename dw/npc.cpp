#include "main.h"

void npc::create(class_s type) {
	this->type = type;
	this->race = Human;
	this->gender = (gender_s)(xrand(Male, Female));
	this->alignment = (alignment_s)(xrand(Good, Evil));
	this->level = 1;
	this->name = getrandomname(race, gender);
}

void npc::act(const char* format, ...) const {
	driver dr(sb);
	dr.name = getname();
	dr.gender = gender;
	dr.addsep(' ');
	dr.addv(format, xva_start(format));
	sb = dr;
}

void npc::actv(stringbuilder& sb, const char* format, ...) const {
	driver dr(sb);
	dr.name = getname();
	dr.gender = gender;
	dr.addsep(' ');
	dr.addv(format, xva_start(format));
	sb = dr;
}

void npc::say(const char* format, ...) const {
	driver dr(sb);
	dr.name = getname();
	dr.gender = gender;
	dr.addn(format, xva_start(format));
	dr.addn("");
}