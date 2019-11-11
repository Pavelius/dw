#include "main.h"

void thing::actv(stringbuilder& sb, const char* format, const char* format_param) const {
	driver dr(sb);
	dr.name = getname();
	dr.gender = gender;
	dr.addsep(' ');
	dr.addv(format, format_param);
	sb = dr;
}

void thing::say(const char* format, ...) const {
	driver dr(sb);
	dr.name = getname();
	dr.gender = gender;
	dr.addn(format, xva_start(format));
	dr.addn("");
}

int	thing::choosev(bool interactive, bool clear_text, const char* format, const char* format_param) const {
	char temp[512]; driver dr(temp);
	dr.name = getname();
	dr.gender = gender;
	dr.addv(format, format_param);
	return an.choosev(interactive, true, false, temp);
}