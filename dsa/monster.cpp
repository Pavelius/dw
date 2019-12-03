#include "main.h"

monsteri bsmeta<monsteri>::elements[] = {{"Ork", "Орк", Male, 8, 15, 9, 7, 2, W1p4, 8, {Saber}},
{"Goblin", "Гоблин", Male, 5, 12, 7, 6, 2, W1p2, 5, {Club}},
{"Orge", "Огр", Male, 22, 40, 6, 5, 3, W2p4, 18},
{"Troll", "Троль", Male, 25, 50, 8, 8, 3, W3p0, 50},
};

void creature::create(monster_s v) {
	clear();
	type = Monster;
	value = v;
	auto& ei = bsmeta<monsteri>::elements[v];
	for(auto& e : abilities)
		e = 9;
	abilities[Courage] = ei.mu;
	set(LE, ei.le);
	set(AV, ei.at);
	set(PV, ei.pa);
	set(RS, ei.rs);
	unarmed = ei.damage;
	for(auto e : ei.gear) {
		if(!e)
			continue;
		equip(e);
	}
	// Финальные значения
	memcpy(abilities_maximum, abilities, sizeof(abilities));
	memcpy(parameters_maximum, parameters, sizeof(parameters));
}