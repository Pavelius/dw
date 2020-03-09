#include "main.h"

static struct combat_action {
	const char*		name;
	variant			id;
} combat_action_data[] = {{"Атаковать врага %1", MeleeWeapon},
{"Наносить удары кулоками и ногами", UnarmedAttack},
{"Стрелять по врагу из %1", RangedWeapon},
};

static int compare_initiative(const void* p1, const void* p2) {
	return (*((creature**)p2))->getinitiative() - (*((creature**)p1))->getinitiative();
}

void scene::rollinititative() {
	for(auto p : creatures)
		p->setinitiative();
	qsort(creatures.data, creatures.count, sizeof(creatures.data[0]), compare_initiative);
}

void scene::combat(bool interactive) {
	rollinititative();
	while(isenemy()) {
		for(auto p : creatures) {
			if(!p->isready())
				continue;
			auto pe = p->getenemy(creatures);
			if(!pe)
				break;
			for(unsigned i = 0; i < sizeof(combat_action_data) / sizeof(combat_action_data[0]); i++)
				p->add(combat_action_data[i].id, combat_action_data[i].name, pe);
			for(auto i = AcidSplash; i <= LastSpell; i = (spell_s)(i + 1))
				p->add(i, "Создать заклиание \"%1\"", pe);
			auto active = interactive && p->isplayer();
			auto id = (variant)an.choose(active, false, "Что будет делать [%1]?", p->getname());
			switch(id.type) {
			case Feat:
				break;
			case Wear:
				switch(id.value) {
				case MeleeWeapon: p->attack((wear_s)id.value, *pe); break;
				case RangedWeapon: p->attack((wear_s)id.value, *pe); break;
				case UnarmedAttack: p->attack((wear_s)id.value, *pe); break;
				}
				break;
			case Spell:
				p->cast((spell_s)id.value, *pe, true, true);
				break;
			}
		}
		next(interactive);
		an.clear();
	}
}

bool scene::isenemy() const {
	reaction_s reaction = Undifferent;
	for(auto p : creatures) {
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