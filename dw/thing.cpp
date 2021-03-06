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
	char temp[512]; driver sb(temp);
	sb.name = getname();
	sb.gender = getgender();
	sb.addv(format, format_param);
	return an.choosev(interactive, clear_text, false, temp);
}

gender_s thing::getgender() const {
	switch(type) {
	case Class: return getnamegender();
	default: return Male;
	}
}

int thing::getmaxhits() const {
	return 4;
}

const char* thing::getname() const {
	switch(type) {
	case Monster:
		return "������";
	default:
		return nameable::getname();
	}
}

int	thing::getdice() const {
	switch(type) {
	case Class: return 6;
	default: return 6;
	}
}

int	thing::getharm() const {
	auto m = imin(getcount(), 3);
	auto d = getdice();
	auto r = xrand(1, d);
	r += (m - 1);
	r += getdamage();
	return r;
}

static const monstermovei* random(move_s move, variant id) {
	adat<monstermovei*> source;
	for(auto& e : bsdata<monstermovei>()) {
		if(e.move == move && e.id == id)
			source.add(&e);
	}
	if(!source)
		return 0;
	return source.data[rand() % source.count];
}

void thing::act(move_s move) const {
	auto p = random(move, *this);
	if(!p)
		return;
	act(p->name);
}