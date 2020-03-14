#include "main.h"

static struct combat_action {
	const char*		name;
	variant			id;
} combat_action_data[] = {{"Атаковать врага %1", MeleeWeapon},
{"Наносить удары кулаками и ногами", UnarmedAttack},
{"Стрелять по врагу из %1", RangedWeapon},
};

static int compare_initiative(const void* p1, const void* p2) {
	auto c1 = (*((variant*)p1)).getcreature();
	auto c2 = (*((variant*)p2)).getcreature();
	return c1->getinitiative() - c2->getinitiative();
}

void scene::rollinititative() {
	for(auto v : creatures) {
		auto p = v.getcreature();
		p->setinitiative();
	}
	qsort(creatures.data, creatures.count, sizeof(creatures.data[0]), compare_initiative);
}

void scene::combat(bool interactive) {
	static state_s clear_flags[] = {Disengaged, Dodged};
	rollinititative();
	while(isenemy()) {
		for(auto v : creatures) {
			auto p = v.getcreature();
			p->set(FootSpeed, p->getmove());
		}
		for(auto v : creatures) {
			auto p = v.getcreature();
			if(!p->isready())
				continue;
			for(auto e : clear_flags)
				p->remove(e);
			auto active = interactive && p->isplayer();
			for(auto& e : bsmeta<actioni>()) {
				if(p->use(e.getid(), creatures, false))
					an.add(variant(e.getid()), e.name);
			}
			//for(auto i = AcidSplash; i <= LastSpell; i = (spell_s)(i + 1))
			//	an.add(i, "Создать заклиание \"%1\"", getstr(i));
			auto id = (variant)an.choose(active, false, "Что будет делать [%1]?", p->getname());
			switch(id.type) {
			case CombatAction:
				p->use(action_s(id.value), creatures, true);
				break;
			case Spell:
				//p->cast((spell_s)id.value, *pe, true, true);
				break;
			}
		}
		next(interactive);
		an.clear();
	}
}

bool scene::isenemy() const {
	reaction_s reaction = Undifferent;
	for(auto v : creatures) {
		auto p = v.getcreature();
		if(!p->isready())
			continue;
		auto r = p->getreaction();
		if(r == Hostile || r == Helpful) {
			if(reaction == Undifferent)
				reaction = r;
			else if(reaction != r)
				return true;
		}
	}
	return false;
}