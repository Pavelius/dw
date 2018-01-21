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

void hero::add(spell_s id) {
	auto p = find(this, id);
	if(!p) {
		p = spell_state_data.add();
		p->caster = this;
	}
	p->spell = id;
	p->date = game::getround();
}

void hero::remove(spell_s id) {
	for(auto& e : spell_state_data) {
		if(e.spell == id)
			e.remove();
	}
	corrent();
}

bool hero::is(spell_s id) {
	for(auto& e : spell_state_data) {
		if(e.spell == id)
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

unsigned hero::select(spell_state** result, spell_state** result_maximum) const {
	auto ps = result;
	for(auto& e : spell_state_data) {
		if(!e)
			continue;
		if(e.caster != this)
			continue;
		if(ps >= result_maximum)
			break;
		*ps++ = &e;
	}
	return ps - result;
}