#include "main.h"

static quest quests[] = {{ArkhamAsylum, "В кабинете доктора вы нашли книгу с записями видений пациентов.", {Lore}, {{"Записи жутковаты, но польза от этого чтения несомненна.", {Add1Clue, Lose1Sanity}},
{"Вы наши важные фрагменты головоломки.", {Add2Clue}},
{"Вы наши важные фрагменты головоломки.", {Add2Clue}},
{"Одна запись содержит жизненно важные данные.", {Add3Clue}},
}},
{ArkhamAsylum, "Сестра Хизер идет! Надо прятаться.", {Speed, -1}, {{"Она вышвырнула вас вон.", {LeaveOutside}},
{"В процессе хотьбы она что-то обронила.", {AddUniqueItem}},
}},
{ArkhamAsylum, "Сестра Хизер случайно ввела вам снотворное. Хотите сопротивляться, чтобы не уснуть?", {Fight, -2, 0, true}, {{"Вы заснули как ребенок.", {Add2Sanity, SkipTurn}},
{"Ничего не произошло."},
}},
{ArkhamAsylum, "\"Все будет хорошо,\" - говорит вам пациент в приемном покое. На вид он вполне вменяемый. Поднявшись, он хлопает вас по руке и уходит. Удивительно, но вы почему-то тоже начали верить в лучшее.", {}, {{0, {Add3Sanity}},
}},
{ArkhamAsylum, "В пыльном шкафу вы обнаруживаете странный препарат, маркированный как \"Усовершенствователь Снов\". Выпить его?", {Lore, -1, 0, true}, {{"Ничего не произошло."},
{"Вас посетили весьма странные и страшные видения, в которых вы смогли научиться новому ритуалу.", {AddSpell}},
}},
{ArkhamAsylum, "Вы слышите крик. Когда вы отворяете тяжелую дверь палаты с целью прояснить происходящее, вам навстречу бросается темная фигура! Ею оказывается сумасшедший в смирительной рубашке, бормочащий что-то о невидимых кошмарах.", {Lore, -2}, {{"Со злостью того что вы его не поняли сумасшедший набросился на вас и сильно побил, перед тем как убежал далее.", {Lose1Stamina}},
{"Похоже вы поняли о чем он говорил.", {Add1Clue}},
}},
};

quest& hero::getquest(location_s value, int index) {
	adat<quest*, 32> result;
	for(auto& q : quests) {
		if(q.type == value)
			result.add(&q);
	}
	if(result.count) {
		if(index == -1)
			index = rand() % result.count;
		if(index >= (int)result.count)
			index = result.count - 1;
		return *result.data[index];
	}
	return quests[0];
}

void hero::run(const quest& e) {
	logs::clear(true);
	logs::add(e.text);
	auto result = 0;
	if(e.roll.optional) {
		char skill_temp[128]; e.roll.getname(skill_temp, zendof(skill_temp));
		if(!logs::yesno(true, "Будете делать бросок [%1]?", skill_temp))
			return;
	}
	switch(e.roll.action.type) {
	case Stats:
		result = roll((stat_s)e.roll.action.value, e.roll.bonus, e.roll.difficult, true);
		break;
	}
	auto result_maximum = zlen(e.results);
	if(result_maximum < 1)
		result_maximum = 1;
	if(result >= result_maximum)
		result = result_maximum - 1;
	bool discard = false;
	auto apply_actions = 0;
	if(e.results[result].text)
		logs::add(e.results[result].text);
	for(auto a : e.results[result].results) {
		if(!a)
			break;
		apply(a, &discard);
		apply_actions++;
	}
	if(!apply_actions)
		logs::next();
}