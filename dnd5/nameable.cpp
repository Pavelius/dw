#include "main.h"

race_s nameable::getrace() const {
	switch(type) {
	case Monster: return bsmeta<monsteri>::elements[value].race;
	case Race: return bsmeta<racei>::elements[value].basic ? bsmeta<racei>::elements[value].basic : (race_s)value;
	default: return Human;
	}
}

race_s nameable::getsubrace() const {
	switch(type) {
	case Monster: return bsmeta<monsteri>::elements[value].race;
	case Race: return (race_s)value;
	default: return Human;
	}
}

const char* nameable::getname() const {
	switch(type) {
	case Monster: return bsmeta<monsteri>::elements[value].name;
	default: return "Джон";
	}
}

void nameable::actv(stringbuilder& sb, const char* format, const char* format_param) const {
	if(format && format[0] != '.' && format[0] != '?' && format[0] != '!' && format[0] != ',')
		sb.addsep(' ');
	logs::driver e(sb);
	e.name = getname();
	e.gender = getgender();
	e.addv(format, format_param);
	sb = e;
}