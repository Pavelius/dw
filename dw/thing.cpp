#include "main.h"

void thing::actv(stringbuilder& sb, const char* format, const char* format_param) const {
	driver dr(sb);
	dr.name = getname();
	dr.gender = getgender();
	dr.addsep(' ');
	dr.addv(format, format_param);
	sb = dr;
}

void thing::say(const char* format, ...) const {
	driver dr(sb);
	dr.name = getname();
	dr.gender = getgender();
	dr.addn(format, xva_start(format));
	dr.addn("");
}

int	thing::choosev(bool interactive, bool clear_text, const char* format, const char* format_param) const {
	char temp[512]; driver dr(temp);
	dr.name = getname();
	dr.gender = getgender();
	dr.addv(format, format_param);
	return an.choosev(interactive, true, false, temp);
}

gender_s thing::getgender() const {
	switch(type) {
	case Class: return getnamegender();
	default: return Male;
	}
}