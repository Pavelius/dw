#include "main.h"

using namespace game;

static unsigned				combat_start;
static adat<character*, 20> parcipants;

//PRINTPLG(combat_round) {
//	return szprint(result, "###����� %1i\n", getround() - combat_start);
//}

PRINTPLG(parcipants) {
	result[0] = 0;
	for(auto p : parcipants) {
		char temp[260];
		char colorize[260];
		szprints(temp, zendof(temp), "%1 (%2i hp)", p->getname(), p->gethp()); szupper(temp, 1);
		if(p->getcount() > 1)
			szprints(zend(temp), zendof(temp), ": %1i ��", p->getcount());
		if(!p->isready())
			szprints(colorize, zendof(temp), "[~%1]", temp);
		else
			zcpy(colorize, temp);
		szadd(result, colorize, "###��������� ���:\n", "\n");
	}
	return result;
}

static int compare(const void* v1, const void* v2) {
	return (*((character**)v1))->getinitiative() - (*((character**)v2))->getinitiative();
}

static void rollinitiative() {
	for(auto p : parcipants) {
		if(!p->isready())
			p->setinitiative(d10());
		else
			p->setinitiative(0);
	}
	qsort(parcipants.data, parcipants.count, sizeof(parcipants.data[0]), compare);
}

void character::addparty() {
	parcipants.clear();
	for(auto p : party) {
		if(!p->isready())
			continue;
		p->addcombat(PartySide);
	}
}

void character::addcombat(side_s side) {
	parcipants.add(this);
	this->side = side;
}

character* character::getenemy() const {
	aref<character*> a;
	a.data = parcipants.data;
	a.count = parcipants.count;
	return get(a, &character::isenemy);
}

void game::combat(bool interactive) {
	logs::state push;
	logc.information = "%parcipants\n";
	combat_start = getround();
	rollinitiative();
	while(true) {
		for(auto p : parcipants) {
			if(!p->isready())
				continue;
			auto pe = p->getenemy();
			if(!pe) {
				if(interactive) {
					if(p->isplayer())
						logs::add("��� ����� ������.");
					else
						logs::add("��� ������ ������.");
					logs::next();
				}
				return;
			}
			auto attack_type = MeleeWeapon;
			logs::add(1, "��������� %1", p->get(MeleeWeapon).getnameby());
			auto action = logs::input(p->isplayer() && interactive, false, "��� ����� ������ [%1]?", p->getname());
			p->attack(interactive, *pe, attack_type);
		}
		logs::next();
		passtime(false, RRound);
	}
}

void game::combat(bool interactive, character& enemy) {
	character::addparty();
	enemy.addcombat(EnemySide);
	combat(interactive);
}

void game::combat(bool interactive, monster_s type, unsigned count) {
	character e(type);
	e.setcount(count);
	combat(interactive, e);
}