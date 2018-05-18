#include "main.h"

//static adat<character*, 24>	parcipants;
//static unsigned				combat_start;

//PRINTPLG(combat_round) {
//	return szprint(result, "###Раунд %1i\n", scene::getround() - combat_start);
//}
//
//PRINTPLG(parcipants) {
//	result[0] = 0;
//	for(auto p : parcipants) {
//		char temp[260];
//		char colorize[260];
//		szprint(temp, "%1 (%2i hp)", p->getname(), p->gethp()); szupper(temp, 1);
//		if(!p->isready())
//			szprint(colorize, "[~%1]", temp);
//		else
//			zcpy(colorize, temp);
//		szadd(result, colorize, "###Участники боя:\n", "\n");
//	}
//	return result;
//}

static int compare(const void* v1, const void* v2) {
	return (*((character**)v1))->getinitiative() - (*((character**)v2))->getinitiative();
}

static void rollinitiative(aref<character*> parcipants) {
	for(auto p : parcipants) {
		if(!p->isready())
			p->setinitiative(d10());
		else
			p->setinitiative(0);
	}
	qsort(parcipants.data, parcipants.count, sizeof(parcipants.data[0]), compare);
}

void scene::combat(bool interactive, aref<character*> parcipants) {
	//logs::state push;
	//logc.information = "%parcipants\n";
	auto combat_start = getround();
	rollinitiative(parcipants);
	while(true) {
		for(auto p : parcipants) {
			if(!p->isready())
				continue;
			auto pe = p->getenemy(parcipants);
			if(!pe) {
				if(interactive) {
					if(p->isplayer())
						logs::add("Все враги мертвы.");
					else
						logs::add("Все игроки мертвы.");
					logs::next();
				}
				return;
			}
			auto attack_type = MeleeWeapon;
			logs::add(1, "Атаковать %1", p->get(MeleeWeapon).getnameby());
			auto action = logs::input(p->isplayer() && interactive, false, "Что будет делать [%1]?", p->getname());
			p->attack(interactive, *pe, attack_type);
		}
		logs::next();
		passtime(false, RRound);
	}
}

void scene::combat(bool interactive, character& enemy) {
	character* source[16];
	auto parcipants = character::getparty(source);
	enemy.set(EnemySide);
	parcipants.add(&enemy);
	combat(interactive, parcipants);
}

void scene::combat(bool interactive, monster_s type, unsigned count) {
	character e(type);
	e.setcount(count);
	combat(interactive, e);
}