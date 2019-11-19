#include "main.h"

DECLDATA(spelleffecti, 31);

static spelleffecti* find(const variant caster, spell_s spell) {
	for(auto& e : bsmeta<spelleffecti>()) {
		if(e.caster == caster && e.spell == spell)
			return &e;
	}
	return 0;
}

static void corrent() {
	auto p = bsmeta<spelleffecti>::elements + (bsmeta<spelleffecti>::source.getcount() - 1);
	while(p >= bsmeta<spelleffecti>::elements) {
		if(*p)
			break;
		p--;
		bsmeta<spelleffecti>::source.remove(bsmeta<spelleffecti>::source.getcount() - 1, 1);
	}
}

void hero::add(spell_s id) {
	auto p = find(*this, id);
	if(!p) {
		p = bsmeta<spelleffecti>::add();
		p->caster = *this;
	}
	p->spell = id;
}

void hero::remove(spell_s id) {
	for(auto& e : bsmeta<spelleffecti>()) {
		if(e.spell == id)
			e.clear();
	}
	corrent();
}

bool hero::isactive(spell_s id) {
	for(auto& e : bsmeta<spelleffecti>()) {
		if(e.spell == id)
			return true;
	}
	return false;
}

int	hero::getongoing() const {
	auto result = 0;
	for(auto& e : bsmeta<spelleffecti>()) {
		if(e.caster == *this)
			result++;
	}
	return result;
}

//void spell_state::remove() {
//	if(caster && bsmeta<spelli>::elements[spell].remove)
//		caster->act(bsmeta<spelli>::elements[spell].remove);
//	clear();
//}