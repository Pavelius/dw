#include "main.h"

using namespace game;

void game::makecamp() {
	sb.add("¬скоре вы нашли хорошее место дл€ привала.");
	partyrest(false);
	//auto guardian = whodo(Wisdow, 0, 0, " то будет охран€ть лагерь?");
	passtime(Duration8Hour);
}

void game::partyrest(bool forfree) {
	for(auto& e : players) {
		if(!e)
			continue;
		if(!forfree && !useparty(Ration, true, true)) {
			e.act("%герой проголодал%ась.");
			continue;
		}
		e.healharm(e.getmaxhits() / 2);
		if(e.is(Commune) || e.is(PrepareSpells))
			e.preparespells(true);
	}
}

void game::eatrations(int count) {
	while(count > 0) {
		if(!useparty(Ration, true, true)) {
		}
	}
}

void game::journey() {
	monster_s wander_monster = Bandit;
	hero* exclude[4] = {0};
	auto consume_days = 4;
	auto pathfinder = whodo(Wisdow, 0, " то будет вести партию?"); zcat(exclude, pathfinder);
	auto scout = whodo(Wisdow, exclude, " то будет разведывать путь впереди?"); zcat(exclude, scout);
	auto hunter = whodo(Wisdow, exclude, " то будет следить за количеством еды?");
	sb.add("» вот, вы отправились в дорогу.");
	auto hunter_result = hunter ? hunter->roll(hunter->get(Wisdow)) : Fail;
	switch(hunter_result) {
	case Success:
		sb.adds("%1 раздобыл по дороге немного еды.",
			hunter->getname());
		pickup(DungeonRation);
		break;
	case PartialSuccess:
		sb.adds("%1 охотилс€ по пути, но не сумел поймать дичь.",
			hunter->getname());
		break;
	case Fail:
		sb.adds("ѕо дороге у вас испортилось немного еды.");
		useparty(Ration, true, true);
		break;
	}
	auto scout_result = scout ? scout->roll(pathfinder->get(Wisdow)) : Fail;
	switch(scout_result) {
	case Success:
		sb.adds("%1 разведывал%2 местность и сумел%2 избежать встреч с непри€тност€ми.",
			scout->getname(), scout->getA());
		break;
	case PartialSuccess:
		combat(wander_monster, Far);
		break;
	case Fail:
		sb.adds("» вдруг по дороге вы попали в засаду!");
		combat(wander_monster, Close);
		break;
	}
	auto pathfinder_result = pathfinder ? pathfinder->roll(pathfinder->get(Wisdow)) : Fail;
	switch(pathfinder_result) {
	case Success:
		sb.adds("%1 сумел%2 найти короткий путь.",
			pathfinder->getname(), pathfinder->getA());
		consume_days--;
		break;
	case PartialSuccess:
		sb.adds("%1 нашел верный путь.",
			pathfinder->getname(), pathfinder->getA());
		break;
	case Fail:
		sb.adds("¬ы не сумели найти дорогу, поэтому заблудились и блукали на несколько дней больше.");
		consume_days += xrand(1, 3);
		break;
	}
	logs::next();
}