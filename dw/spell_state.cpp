#include "main.h"

adat<spell_state, 48> spell_state_data;

static spell_state* find(const npc* caster, spell_s spell) {
	for(auto& e : spell_state_data) {
		if(e.caster == caster && e.spell == spell)
			return &e;
	}
	return 0;
}

static void corrent() {
	auto p = spell_state_data.data + (spell_state_data.count - 1);
	while(p >= spell_state_data.data) {
		if(*p)
			break;
		p--;
		spell_state_data.count--;
	}
}

void hero::add(spell_s id, targetinfo target) {
	auto p = find(this, id);
	if(!p) {
		p = spell_state_data.add();
		p->caster = this;
	}
	p->target = target;
	p->date = game::getround();
}

void hero::remove(spell_s id) {
	auto p = find(this, id);
	if(!p)
		return;
	p->remove();
	corrent();
}

void hero::removetarget(spell_s id) {
	for(auto& e : spell_state_data) {
		if(e.target.hero == this && e.spell == id) {
			e.remove();
			corrent();
			return;
		}
	}
}

bool hero::is(spell_s id) const {
	for(auto& e : spell_state_data) {
		if(e.target.hero == this)
			return true;
	}
	return false;
}

int	hero::getongoing() const {
	auto result = 0;
	for(auto& e : spell_state_data) {
		if(e.caster == this)
			result++;
	}
	return result;
}