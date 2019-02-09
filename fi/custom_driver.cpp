#include "main.h"

void character::actv(const char* format, const char* param) const {
	auto& text = logs::getbuilder();
	auto name_push = text.name;
	auto gender_push = text.gender;
	text.name = getname();
	text.gender = gender;
	text.addx('\n', format, param);
	text.name = name_push;
	text.gender = gender_push;
}

void character::actv(const character* opponent, const char* format, const char* param) const {
	auto& text = logs::getbuilder();
	auto name_push = text.name;
	auto gender_push = text.gender;
	auto opponent_name_push = text.opponent_name;
	auto opponent_gender_push = text.opponent_gender;
	auto weapon_push = text.weapon;
	text.name = getname();
	text.gender = gender;
	text.opponent_gender = opponent->gender;
	text.opponent_name = opponent->getname();
	text.weapon = wears[Hand].getname();
	text.addx('\n', format, param);
	text.name = name_push;
	text.gender = gender_push;
	text.opponent_name = opponent_name_push;
	text.opponent_gender = opponent_gender_push;
	text.weapon = weapon_push;
}