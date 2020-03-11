#include "main.h"

static struct combat_action {
	const char*		name;
	variant			id;
} combat_action_data[] = {{"��������� ����� %1", MeleeWeapon},
{"�������� ����� �������� � ������", UnarmedAttack},
{"�������� �� ����� �� %1", RangedWeapon},
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
			creaturea enemies(creatures);
			enemies.match(p->gethostile());
			if(!enemies)
				break;
			auto pe = enemies[0];
			if(!pe)
				break;
			for(auto& e : bsmeta<actioni>()) {
			}
			for(auto i = AcidSplash; i <= LastSpell; i = (spell_s)(i + 1))
				p->add(i, "������� ��������� \"%1\"", pe);
			auto active = interactive && p->isplayer();
			auto id = (variant)an.choose(active, false, "��� ����� ������ [%1]?", p->getname());
			switch(id.type) {
			case Action:
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