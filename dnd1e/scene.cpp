#include "main.h"

static unsigned	current_round;

void scene::lookaround() const {
	logs::add(getstr(enviroment));
}

void scene::ask(aref<action> source) const {
	for(auto& a : source) {
		if(isallow(a))
			logs::add((int)&a, a.text);
	}
}

void scene::ask(action& a) const {
	if(isallow(a))
		logs::add((int)&a, a.text);
}

bool scene::isallow(const action& a) const {
	if(a.success && !isallow(a.success))
		return false;
	if(a.fail && !isallow(a.fail))
		return false;
	for(auto p : party) {
		if(!p->isready())
			continue;
		if(a.isallow(p))
			return true;
	}
	return false;
}

bool scene::isallow(const effect& e) const {
	return true;
}

int scene::getspeed() {
	auto result = 0;
	for(auto p : party) {
		if(!p->isready())
			continue;
		if(result == 0 || result > p->getspeed())
			result = p->getspeed();
	}
	return result;
}

int	scene::getmoverate() {
	auto value = getspeed() * 2;
	return value;
}

outcome scene::resolve() {
	auto a = (const action*)logs::input(true, false, "Что будете делать?");
	return resolve(*a);
}

outcome scene::resolve(const action& a) {
	outcome	test;
	player = 0;
	auto& e = character::getinfo(a.type);
	// Action need player
	if(e.type == TestSkill || e.type == TestAbility) {
		for(auto p : party) {
			if(!p->isready())
				continue;
			if(!a.isallow(p))
				continue;
			if(e.type == TestSkill) {
				logs::add((int)p, "%1 (успех [%2i%%])",
					p->getname(),
					p->get(a.type));
			} else if(e.type == TestAbility) {
				logs::add((int)p, "%1 (%2 [%3i]%+4i)",
					p->getname(),
					getstr(e.ability),
					p->get(e.ability),
					e.bonus);
			}
		}
		player = (character*)logs::input(true, false, "Кто сделает бросок [%1]?", a.getskill());
		if(!player)
			return test;
		// Use one time used actions
		a.addhistory(player);
	}
	logs::clear(true);
	// Pass time
	passtime(true, get(a.duration));
	// Make action test if action have one
	test.success = true;
	test.result = 0;
	test.bonus = 0;
	test.result = 1 + (rand() % 100) - test.bonus;
	if(test.result < 1)
		test.result = 1;
	else if(test.result > 100)
		test.result = 100;
	test.difficult = player->get(a.type);
	test.success = (test.result <= test.difficult);
	// Show action result text
	if(test.success) {
		// Gain experience to player
		if(player) {
			if(a.exp)
				player->addexp(true, a.exp);
		}
		resolve(a.success);
	} else
		resolve(a.fail);
	return test;
}

void scene::resolve(const effect& e) {
	// Show effect text
	if(e.text) {
		if(player)
			player->act(e.text);
		else
			logs::add(e.text);
		logs::add(" ");
	}
}

int	scene::gethour() {
	return (getround() / get(Day)) / (24 * 60);
}

timezone_s scene::getzone() {
	return (timezone_s)((getround() % RDay) / (4 * RHour));
}

int	scene::getday() {
	return (getround() % get(Month)) / (24 * 60);
}

int	scene::getyear() {
	return getround() / RYear;
}

int	scene::getmonth() {
	return (getround() % RYear) / get(Month);
}

int	scene::getminimum(int (character::*proc)() const) {
	auto result = 100;
	for(auto p : party) {
		if(!p->isready())
			continue;
		auto i = (p->*proc)();
		if(i < result)
			result = i;
	}
	return result;
}

void scene::passtime(bool interactive, unsigned rounds) {
	if(!rounds)
		return;
	if(interactive) {
		if(rounds < 2) {
		} else if(rounds <= RHour / 6)
			logs::add("Прошло %1i минут.", rounds);
		else if(rounds < 40)
			logs::add("Прошло около %1i минут.", ((rounds + 9) / 10) * 10);
		else if(rounds <= RHour)
			logs::add("Прошел час.");
		else if(rounds <= RDay / 4)
			logs::add("Прошло несколько часов.");
		else if(rounds < RDay)
			logs::add("Прошло больше половины дня.");
		else if(rounds < 2 * RDay)
			logs::add("Прошел день.");
		else if(rounds < 5 * RDay)
			logs::add("Прошло несколько дней.");
		else
			logs::add("Прошло много дней.");
	}
	current_round += rounds;
}

unsigned scene::getround() {
	return current_round;
}

bool scene::isparty(feat_s value) {
	for(auto p : party) {
		if(p && p->is(value))
			return true;
	}
	return false;
}

bool scene::isparty(magic_power_s value) {
	for(auto p : party) {
		if(p && !p->is(value))
			return false;
	}
	return true;
}

bool scene::isparty(bool (character::*proc)() const) {
	for(auto p : party) {
		if(p && (p->*proc)())
			return true;
	}
	return false;
}

reaction_s scene::reduce(reaction_s id) {
	switch(id) {
	case Hostile: return Hostile;
	case Threatening: return Hostile;
	case Cautions: return Threatening;
	case Indifferent: return Cautions;
	default: return Indifferent;
	}
}

void scene::loosemoney() {
	if(player)
		player->addmoney(player->getmoney());
}

void scene::pickpockets() {
	static struct theft_effect {
		const char*		text;
		dice			count;
	} effects[] = {
		{"На одном из столов кто-то забыл парочку медяков. %герой исправил%а это недоразумение, незаметно переместив их себе в карманы.", {2, 6, 0, CP}},
		{"Один пьяный клиент, которому %герой помог%ла добраться до выхода лишился своего кошелька.", {2, 6, 0, SP}},
		{"Во время спора с двумя пьяными посетителями %герой стащил%а у них со стола кошель с деньгами.", {3, 6, 0, SP}},
		{"Один богатый клиент, который еле держался на ногах лишился своего кошелька.", {2, 6, 0, GP}},
	};
	auto& e = maprnd(effects);
	auto value = e.count.roll();
	if(value) {
		logs::add(e.text);
		player->act("%герой добыл%а [%1i] медяков.", value);
		player->addmoney(value);
	}
}

//void scene::testcatched() {
//	auto opponent_level = 3;
//	auto chance_catch = 100 - opponent_level * 3;
//	if(test.result >= chance_catch) {
//		logs::add("\n - Воры - закричал кто-то - держи вора!!\n");
//		logs::add("Несколько головорезов кинулись на вас и быстро скрутили.");
//		logs::add("Затем они отобрали все ваши деньги и выкинули вас на улицу.");
//		logs::next();
//		badreaction();
//		moveaway();
//	}
//}

void scene::charsheet() {
	player = character::chooseplayer(true);
	player->charsheet();
}