#include "main.h"

static adat<history, 2048>	elements;

void action::addhistory(const character* player) const {
	if(!player || !useonce())
		return;
	if(gethistory(player))
		return;
	auto p = elements.add();
	if(!p)
		return;
	p->who = player;
	p->what = this;
	p->when = scene::getround();
	//p->level = getHD();
}

history* action::gethistory(const character* player) const {
	for(auto& e : elements) {
		if(e.who == player && e.what == this)
			return &e;
	}
	return 0;
}

const char*	action::getskill() const {
	return getstr(type);
}

bool action::useonce() const {
	auto& e = character::getinfo(type);
	return (e.type==TestSkill || e.type==TestAbility) && exp!=0;
}

bool action::isallow(const character* player) const {
	// If we can do this untrained
	auto& e = character::getinfo(type);
	if(e.type == TestSkill && player->get(type) <= 0)
		return false;
	// if one use
	if(useonce() && gethistory(player))
		return false;
	// If action need tools find one tool from list
	//if(tool) {
	//	auto pw = player->getwear(skill.tool);
	//	if(!pw)
	//		return false;
	//}
	return true;
}