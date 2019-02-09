#include "main.h"

static char	text_buffer[256 * 4 * 8];
static logs::driver text(text_buffer, text_buffer + sizeof(text_buffer) / sizeof(text_buffer[0]) - 1);

stringbuilder& logs::getbuilder() {
	return text;
}

const char* logs::getpanel(int index) {
	return 0;
}

int logs::getwidth(int index) {
	return 0;
}

void character::actv(const char* format, const char* param) const {
	auto name_push = text.name;
	auto gender_push = text.gender;
	text.name = getname();
	text.gender = gender;
	text.addx('\n', format, param);
	text.name = name_push;
	text.gender = gender_push;
}

void character::actv(const character* opponent, const char* format, const char* param) const {
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