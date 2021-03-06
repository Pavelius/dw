#include "main.h"

const char* thing::getname() const {
	switch(type) {
	case Booklet: return nameablei::getname(); break;
	case Thug: return bsmeta<thugi>::elements[subtype].name;
	default: return "Безымянный";
	}
}

gender_s thing::getgender() const {
	switch(type) {
	case Booklet: return nameablei::getgender();
	case Thug: return bsmeta<thugi>::elements[subtype].gender;
	default: return NoGender;
	}
}

void thing::act(const char* format, ...) const {
	driver dr(sb);
	dr.name = getname();
	dr.gender = getgender();
	dr.opponent_name = 0;
	dr.opponent_gender = Male;
	dr.addsep(' ');
	dr.addv(format, xva_start(format));
	sb = dr;
}

void thing::act(thing& enemy, const char* format, ...) const {
	driver dr(sb);
	dr.name = getname();
	dr.gender = getgender();
	dr.opponent_name = enemy.getname();
	dr.opponent_gender = enemy.getgender();
	dr.addsep(' ');
	dr.addv(format, xva_start(format));
	sb = dr;
}