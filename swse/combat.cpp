#include "main.h"

static bool isenemy(const location& area, const creature* player, const creature* opponent) {
	return player->isenemy(opponent);
}

static bool isenemymelee(const location& area, const creature* player, const creature* opponent) {
	if(!isenemy(area, player, opponent))
		return false;
	return player->getindex() == opponent->getindex();
}

static bool ischarge(const location& area, const creature* player, const creature* opponent) {
	if(!isenemy(area, player, opponent))
		return false;
	return player->getindex() != opponent->getindex();
}

static bool melee(activityi& a, creature* player, location& area, bool run, bool interactive) {
	if(!area.match(player, isenemymelee))
		return false;
	if(run) {
		auto enemy = area.choose(player, isenemymelee, interactive);
		if(enemy) {
			player->attack(*enemy, Melee, interactive);
			player->setmelee(*enemy);
		}
	}
	return true;
}

static bool charge(activityi& a, creature* player, location& area, bool run, bool interactive) {
	if(!area.match(player, ischarge))
		return false;
	if(run) {
		auto enemy = area.choose(player, isenemymelee, interactive);
		if(enemy) {
			player->add(Reflexes, -2);
			player->attack(*enemy, Melee, interactive, 2);
		}
	}
	return true;
}

static bool range(activityi& a, creature* player, location& area, bool run, bool interactive) {
	if(!player->get(Ranged))
		return false;
	if(run) {
		auto enemy = area.choose(player, isenemy, interactive);
		if(enemy)
			player->attack(*enemy, Ranged, interactive);
	}
	return true;
}

static bool standup(activityi& a, creature* player, location& area, bool run, bool interactive) {
	if(!player->is(LayingDown))
		return false;
	if(run)
		player->remove(LayingDown, interactive);
	return true;
}

static bool move(activityi& a, creature* player, location& area, bool run, bool interactive) {
	return true;
}

static activityi combat_actions[] = {{{StandartAction, Melee}, "Нанести удар противнику", melee},
{{StandartAction, Ranged}, "Стрелять по противнику", range},
{{StandartAction, Melee}, "Нанести удар противнику из защитной стойки"},
{{FullRoundAction, Melee}, "С криками броситься на врага", charge},
{{StandartAction}, "Попытаться обезоружить врага"},
{{StandartAction, LayingDown}, "Подняться на ноги", standup},
{{StandartAction}, "Схватить оппонента"},
{{MoveAction}, "Двигаться в сторону врага", move},
{{StandartAction}, "Сменить оружие"},
};

static int compare_initiative(const void* p1, const void* p2) {
	return (*((creature**)p2))->getinitiative()
		- (*((creature**)p1))->getinitiative();
}

void location::combat(bool interactive) {
	// 1 - roll initiative
	for(auto p : creatures)
		p->rollinitiative();
	qsort(creatures.data, creatures.count, sizeof(creatures.data[0]), compare_initiative);
	// 2 - run combat
	while(iscombat()) {
		getdescription(sb);
		for(auto p : creatures) {
			if(!p->isactive())
				continue;
			p->setready();
			while(p->is(StandartAction)) {
				ask(p, combat_actions);
				//ask(p, standart_actions);
				input(p, interactive);
			}
		}
	}
	logs::next();
}