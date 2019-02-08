#include "main.h"

int logs::getwidth(int panel) {
	return 300;
}

const char* logs::getpanel(int panel) {
	return 0;
}

//PRINTPLG(party) {
//	char temp[260];
//	result[0] = 0;
//	auto p = result;
//	for(auto& e : players) {
//		if(!e)
//			continue;
//		spell_state* spell_active[32];
//		logs::printer sc(e.getname(), e.gender);
//		sc.prints(p, result_maximum, "%герой");
//		p = zend(p);
//		if(!e.isalive())
//			sc.prints(p, result_maximum, " погиб%ла");
//		else {
//			if(e.hp < e.getmaxhits())
//				sc.prints(p, result_maximum, " ([-%1i]/%2i)", e.hp, e.getmaxhits());
//		}
//		auto p1 = zend(p); p = p1;
//		if(e.armor) {
//			sc.prints(p, result_maximum, " носит %1", e.armor.getname(temp, zendof(temp), false, true));
//			p = zend(p);
//		}
//		if(e.weapon) {
//			sc.prints(p, result_maximum, " держит %1", e.weapon.getname(temp, zendof(temp), false, true));
//			p = zend(p);
//		}
//		auto spell_count = e.select(spell_active, spell_active + lenghtof(spell_active));
//		for(unsigned i = 0; i < spell_count; i++) {
//			if(i == 0) {
//				if(p1!=p)
//					zcat(p, ", ");
//				zcat(p, " поддерживает");
//			}
//			else if(i>0 && i == spell_count - 1)
//				zcat(p, " и ");
//			else
//				zcat(p, ", ");
//			p = zend(p);
//			zcpy(p, getstr(spell_active[i]->spell));
//		}
//		zcat(p, ".\n");
//		p = zend(p);
//	}
//	return result;
//}