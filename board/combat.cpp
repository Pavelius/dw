#include "main.h"

void combat::roll() {
	for(auto& e : actions)
		e = xrand(1, 6);
}

void combat::apply(forcei& attacker, forcei& defender) const {
	for(auto e : actions) {
		switch(e) {
		case 1: defender.defence++; break;
		case 2: defender.attack++; break;
		case 3: defender.attack++; break;
		case 4: attacker.attack++; break;
		case 5: attacker.attack++; break;
		case 6: attacker.defence++; break;
		}
	}
}