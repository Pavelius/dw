#include "main.h"

void character::actv(const char* format, const char* param) const {
	driver dr(sb);
	dr.name = getname();
	dr.gender = gender;
	dr.addx('\n', format, param);
}

void character::actv(const character* opponent, const char* format, const char* param) const {
	driver dr(sb);
	dr.name = getname();
	dr.gender = gender;
	dr.opponent_gender = opponent->gender;
	dr.opponent_name = opponent->getname();
	dr.weapon = wears[Hand].getname();
	dr.addx('\n', format, param);
}