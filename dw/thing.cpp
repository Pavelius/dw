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

int thing::getmaxhits() const {
	switch(type) {
	case TargetMonster: return bsmeta<monsteri>::elements[subtype].hp;
	default: return 4;
	}
}

const char* thing::getname() const {
	switch(type) {
	case Monster:
		return bsmeta<monsteri>::elements[subtype].name;
	default:
		return nameable::getname();
	}
}

int	thing::getdice() const {
	switch(type) {
	case Class: return bsmeta<classi>::elements[subtype].damage;
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

void thing::act(move_s move) const {
	adat<monstermovei*> source;
	for(auto& e : bsmeta<monstermovei>()) {
		if(e.move == move && e.id == *this)
			source.add(&e);
	}
	if(!source)
		return;
	auto p = source.data[rand() % source.count];
	act(p->name);
}