#include "main.h"

hero::hero(talent_s id) {
	set(id);
	raise();
}

result_s hero::roll(stat_s id, bool interactive, int bonus) {
	auto result = Fail;
	auto d = 2 + (rand() % 6) + (rand() % 6);
	auto r = d + bonus;
	if(r <= 6) {
		if(interactive)
			logs::add("[-{%1i%+2i=%3i}]", d, bonus, r);
		return Fail;
	}
	else if(r <= 9) {
		if(interactive)
			logs::add("{%1i%+2i=%3i}", d, bonus, r);
		return PartialSuccess;
	}
	if(interactive)
		logs::add("[+{%1i%+2i=%3i}]", d, bonus, r);
	return Success;
}

void hero::set(talent_s id) {
}

int hero::gethpmax() const {
	auto result = 8 + 4 * level;
	if(is(Tought))
		result += 6;
	return result;
}

void hero::raise() {
	level++;
}

result_s hero::combat(thing& enemy) {
	act(enemy, "Впереди, около ящика %герой заметил%а %оппонента.");
	logs::add(1, "Выхватить пистолет и начать стрельбу.");
	logs::add(2, "Быстро нырнуть назад и спрятаться в корридоре.");
	auto id = whatdo();
	switch(id) {
	case 1:
		while(true) {
			volley(enemy);
			if(!*this)
				return Fail;
			if(!enemy)
				logs::add(1, "Закончить бой");
			else
				logs::add(1, "Продолжить стрельбу");
			if(*this)
				logs::add(2, "Бежать отсюда");
			auto id = whatdo();
			switch(id) {
			case 1: return Success;
			default: return Fail;
			}
		}
		break;
	default:
		return Fail;
	}
}

result_s hero::volley(thing& enemy) {
	auto result = roll(Dexterity);
	act(enemy, "%герой и %оппонент начали палить друг в друга.");
	switch(result) {
	case Fail:
		act(enemy, "Но %оппонент сумел%а прижать %героя в угол.");
		sufferharm(enemy.getharm().roll());
		break;
	case PartialSuccess:
		enemy.sufferharm(getharm().roll());
		sufferharm(enemy.getharm().roll());
		break;
	case Success:
		act(enemy, "%герой сумел%а удержать инициативу.");
		enemy.sufferharm(getharm().roll());
		break;
	}
	return result;
}

int hero::whatdo() const {
	return logs::input(true, true, "[Что будете делать?]");
}