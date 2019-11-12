#include "main.h"

void npc::create(class_s type) {
	this->type = Class;
	this->subtype = type;
	this->race = Human;
	this->level = 1;
	setcount(1);
	setname(race, (gender_s)xrand(Male, Female));
}

void npc::setalignment() {
	alignment = (alignment_s)(xrand(Good, Evil));
}

race_s npc::chooserace(const racea& source, bool interactive) {
	for(auto e = Human; e <= Human; e = (race_s)(e + 1))
		an.add(e, getstr(e));
	return (race_s)an.choose(interactive, true, "Кто вы?");
}

class_s npc::chooseclass(bool interactive) {
	for(auto e = Bard; e <= Wizard; e = (class_s)(e + 1)) {
		if(game::isallow(e, false))
			continue;
		an.add(e, getstr(e));
	}
	return (class_s)an.choose(interactive, true, "Кем вы будете играть?");
}

alignment_s npc::choosealignment(const alignmenta& source, bool interactive) {
	for(auto e = Good; e <= Evil; e = (alignment_s)(e + 1)) {
		if(source.is(e))
			an.add(e, getstr(e));
	}
	return (alignment_s)an.choose(interactive, true, "Каково ваше [мировозрение]?");
}

gender_s npc::choosegender(bool interactive) {
	an.add(Male, getstr(Male));
	an.add(Female, getstr(Female));
	return (gender_s)an.choose(interactive, true, "Кто вы?");
}