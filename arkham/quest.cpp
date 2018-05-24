#include "main.h"

static quest quests[] = {
	{ArkhamAsylum, "В пыльном шкафу вы обнаруживаете странный препарат, маркированный как \"Усовершенствователь Снов\". Выпить его?", {Lore, -1, 0, true}, {
		{"Ничего не произошло."},
		{"Вас посетили весьма странные и страшные видения, в которых вы смогли научиться новому ритуалу.", {AddSpell}},
	}},
	{ArkhamAsylum, "Вы слышите крик. Когда вы отворяете тяжелую дверь палаты с целью прояснить происходящее, вам навстречу бросается темная фигура! Ею оказывается сумасшедший в смирительной рубашке, бормочащий что-то о невидимых кошмарах.", {Lore, -2}, {
		{"Со злостью того что вы его не поняли сумасшедший набросился на вас и сильно побил, перед тем как убежал далее.", {Lose1Stamina}},
		{"Похоже вы поняли о чем он говорил.", {Add1Clue}},
	}},
};

quest& hero::getquest(location_s value) {
	adat<quest*, 32> result;
	for(auto& q : quests) {
		if(q.type == value)
			result.add(&q);
	}
	if(result.count)
		return *result.data[rand() % result.count];
	return quests[0];
}

void hero::run(const quest& e) {
	logs::clear(true);
	logs::add(e.text);
	auto result = 0;
	if(e.roll.optional) {
		char skill_temp[128]; e.roll.getname(skill_temp, zendof(skill_temp));
		if(!logs::yesno(true, "Будете делать броско [%1]?", skill_temp))
			return;
	}
	switch(e.roll.action.type) {
	case Stats:
		result = roll((stat_s)e.roll.action.value, e.roll.bonus, e.roll.difficult, true);
		break;
	}
	auto result_maximum = zlen(e.results);
	if(!result_maximum)
		return;
	if(result >= result_maximum)
		result = result_maximum - 1;
	bool discard = false;
	for(auto a : e.results[result].results)
		apply(a, &discard);
}