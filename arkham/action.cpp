#include "main.h"

static struct action_info {
	stat_s		stat;
	int			count;
	void		(hero::*set)(stat_s stat, card_s card, location_s location, int count, bool interactive);
	card_s		card;
	location_s	location;
} action_data[] = {{},
{Clue, 1, &hero::add},
{Clue, 2, &hero::add},
{Clue, 3, &hero::add},
{Clue, 4, &hero::add},
{Clue, 5, &hero::add},
{Clue, OneDice, &hero::add},
{Clue, -1, &hero::add},
{Clue, -2, &hero::add},
{Clue, -3, &hero::add},
{Clue, -4, &hero::add},
{Clue, -5, &hero::add},
{Money, 1, &hero::add},
{Money, 2, &hero::add},
{Money, 3, &hero::add},
{Money, 4, &hero::add},
{Money, 5, &hero::add},
{Money, 6, &hero::add},
{Money, 7, &hero::add},
{Money, 8, &hero::add},
{Money, 9, &hero::add},
{Money, 10, &hero::add},
{Money, -1, &hero::add},
{Money, -2, &hero::add},
{Money, -3, &hero::add},
{Money, -4, &hero::add},
{Money, -5, &hero::add},
{Sanity, 1, &hero::add},
{Sanity, 2, &hero::add},
{Sanity, 3, &hero::add},
{Sanity, -1, &hero::add},
{Sanity, -2, &hero::add},
{Sanity, -3, &hero::add},
{Sanity, OneDiceMinus, &hero::add},
{Stamina, 1, &hero::add},
{Stamina, 2, &hero::add},
{Stamina, 3, &hero::add},
{Stamina, HalfDiceOrNone, &hero::add},
{Stamina, -1, &hero::add},
{Stamina, -2, &hero::add},
{Stamina, -3, &hero::add},
{Stamina, OneDiceMinus, &hero::add},
{Movement, -1, &hero::add},
{Movement, -2, &hero::add},
{Movement, -3, &hero::add},
//
{Movement, 1, &hero::restoreall},
{Stamina, 1, &hero::restoreall},
{Sanity, 1, &hero::restoreall},
{Movement, 1, &hero::skipturn},
{Movement, 1, &hero::leaveoutside},
{Movement, 1, &hero::arrested},
{Movement, 1, &hero::losememory},
//
{Fight, 1, &hero::monsterappear},
{Blessed, 1, &hero::monsterappear},
//
{NoStat, 1, &hero::encounter, NoItem, Abyss},
{NoStat, 1, &hero::encounter, NoItem, ArkhamAsylum},
{NoStat, 1, &hero::encounter, NoItem, TheDreamlands},
{NoStat, 1, &hero::encounterany},
{NoStat, 2, &hero::encounter1ofX, NoItem, Woods},
{NoStat, 2, &hero::encounter1ofX, NoItem, BlackCave},
{NoStat, 1, &hero::encounterandmove, NoItem, AnyLocation},
//
{Ally, 1, &hero::addally, AnnaKaslow},
{Ally, 1, &hero::addally, Duke},
{Ally, 1, &hero::addally, JohnLegrasse},
{Ally, 1, &hero::addally, ProfessorArmitage},
//
{Blessed, -1, &hero::addmagic},
{Blessed, 1, &hero::addmagic},
{Blessed, 1, &hero::addmagic},
{Blessed, -1, &hero::addmagic},
{NoStat, -1, &hero::addretainer},
//
{CommonItem, 1, &hero::choose},
{CommonItem, 2, &hero::choose},
//
{CommonItem, 1, &hero::buy},
{CommonItem, 1, &hero::buy1expence},
{UniqueItem, 3, &hero::buy1ofX},
{CommonItem, 3, &hero::buyXofXCU},
//
{UniqueItem, 1, &hero::choose},
{UniqueItem, 1, &hero::choosetome},
{Skill, 1, &hero::choose},
{Spell, 1, &hero::choose},
{Spell, 2, &hero::chooseone},
{Spell, 3, &hero::choosespellorclue},
{CommonItem, 1, &hero::finditem, Whiskey},
{}, {},
};
assert_enum(action, Discard);

static struct case_info {
	stat_s		id;
	const char*	increment;
	const char*	decrement;
	const char*	numbers[3];
	const char*	get(int count) const {
		if(!numbers[0])
			return "";
		switch(count) {
		case 1: return numbers[1];
		case 2: case 3: case 4: return numbers[2];
		default: return numbers[0];
		}
	}
} case_data[] = {{Clue, "Получить [%3i] %2.", "Потерять [%3i] %2.", {"улик", "улику", "улики"}},
{Money, "Получить [%3i] %2.", "Потерять [%3i] %2.", {"долларов", "доллар", "доллара"}},
{Sanity, "Получить [%3i] %2.", "Потерять [%3i] %2.", {"рассудка", "рассудок", "рассудка"}},
{Stamina, "Получить [%3i] %2.", "Потерять [%3i] %2.", {"здоровья", "здоровье", "здоровья"}},
{Movement, "Получить [%3i] %2.", "Потерять [%3i] %2.", {"движения", "движения", "движения"}},
};

case_info* getcase(stat_s id) {
	for(auto& e : case_data) {
		if(e.id == id)
			return &e;
	}
	return 0;
}

bool hero::isallow(action_s id) const {
	switch(id) {
	case RestoreStamina: return get(Stamina) < get(StaminaMaximum);
	case Add1Stamina:
	case Add2Stamina:
	case Add3Stamina:
		return get(StaminaMaximum) - get(Stamina) >= action_data[id].count;
	case Add1Sanity:
	case Add2Sanity:
	case Add3Sanity:
		return get(SanityMaximum) - get(Sanity) >= action_data[id].count;
	case Lose1Money: case Lose2Money: case Lose3Money: case Lose4Money: case Lose5Money:
		return get(Money) >= action_data[id].count;
	case Lose1Movement: case Lose2Movement: case Lose3Movement:
		return get(Movement) >= action_data[id].count;
	case Discard: return true;
	case UsePart: return true;
	case BuyCommonItem: case BuyCommonItem1Expence: case BuyUniqueItem1of3: return true;
	default: return false;
	}
}

bool hero::isallow(const action_s* actions) const {
	for(auto p = actions; *p; p++) {
		if(!isallow(*p))
			return false;
	}
	return true;
}

char hero::getmaximum(stat_s id) const {
	switch(id) {
	case Stamina: return get(StaminaMaximum);
	case Sanity: return get(SanityMaximum);
	default: return 100;
	}
}

char hero::getcount(stat_s id, char value) const {
	switch(value) {
	case Half: return get(id) / 2;
	case All: return get(id);
	case OneDice: return 1 + rand() % 6;
	case OneDiceMinus: return -(1 + rand() % 6);
	case HalfDiceOrNone:
		switch(1 + rand() % 6) {
		case 1: return 1;
		case 2: return 2;
		case 3: return 3;
		default: return 0;
		}
	case TwoDice: return 2 + rand() % 6 + rand() % 6;
	default: return value;
	}
}

void hero::apply(const action_s* actions, bool interactive, bool* discard, bool* usepart) {
	for(auto p = actions; *p; p++)
		apply(*p, interactive, discard, usepart);
}

void hero::apply(action_s id, bool interactive, bool* discard, bool* usepart) {
	if(!id)
		return;
	auto& e = action_data[id];
	if(e.set)
		(this->*e.set)(e.stat, e.card, e.location, e.count, interactive);
	if(discard) {
		if(id==Discard)
			*discard = true;
	}
	if(usepart) {
		if(id==UsePart)
			*usepart = true;
	}
}

void hero::add(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	count = getcount(stat, count);
	auto pe = getcase(stat);
	if(count == 0)
		logs::add(1, "Продолжить");
	else if(count > 0) {
		if(pe)
			logs::add(1, pe->increment, getstr(stat), pe->get(count), count);
		else
			logs::add(1, "Получить [%2i] %1.", getstr(stat), count, count);
	}
	else {
		if(pe)
			logs::add(1, pe->decrement, getstr(stat), pe->get(-count), -count);
		else
			logs::add(1, "Потерять [%2i] %1.", getstr(stat), -count, count);
	}
	auto armor = 0;
	if(stat==Stamina && get(EnchantedJewelry) && count<0) {
		armor = item::getmark(EnchantedJewelry) - getmark(EnchantedJewelry);
		if(armor > (-count))
			armor = (-count);
		logs::add(EnchantedJewelry, "Использовать [%1] чтобы убрать урон здоровья на [%2i] удиницы.", getstr(EnchantedJewelry), armor);
	}
	if((stat == Stamina || stat == Sanity) && get(ObsidianStatue) && count<0)
		logs::add(ObsidianStatue, "Использовать [%1] чтобы она поглатила весь урон. После этого она будет сброшена.", getstr(ObsidianStatue));
	auto result = whatdo(interactive, false);
	auto maximum_value = getmaximum(stat);
	switch(result) {
	case EnchantedJewelry:
		count += armor;
		counter[result] += armor;
		if(counter[result] >= item::getmark((card_s)result))
			discard((card_s)result);
		result = 1;
		break;
	case ObsidianStatue:
		discard((card_s)result);
		return;
	}
	if(result==1) {
		auto value = get(stat) + count;
		if(value < 0)
			value = 0;
		if(value > maximum_value)
			value = maximum_value;
		set(stat, value);
	}
}

void hero::restoreall(stat_s stat, card_s card, location_s location, int value, bool interactive) {
	if(stat == Movement)
		logs::add(1, "Востановить здоровье и энергию до максимума.");
	else
		logs::add(1, "Востановить [%1] до максимума.", getstr(stat));
	logs::input(interactive, false, "Что будете делать?");
	if(stat == Movement) {
		set(Stamina, getmaximum(Stamina));
		set(Sanity, getmaximum(Sanity));
	} else
		set(stat, getmaximum(stat));
}

void hero::skipturn(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	logs::add(1, "Пропустить следующий ход");
	whatdo(interactive, false);
	stats[TurnToSkip]++;
}

void hero::leaveoutside(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	logs::add(1, "Выйти наружу");
	whatdo(interactive, false);
	position = location_data[position].neightboard[0];
}

void hero::arrested(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	logs::add(1, "Отправиться в полицейский участок");
	whatdo(interactive, false);
	stats[TurnToSkip]++;
	set(Money, get(Money) / 2);
	position = PoliceStation;
}

void hero::losememory(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	if(get(Clue) >= 4)
		logs::add(1, "Потерять [4] улики");
	if(getspells() >= 2)
		logs::add(2, "Потерять [2] заклинания");
	if(getskills() >= 1)
		logs::add(3, "Потерять [1] навык");
	card_s item;
	switch(logs::input(interactive, false, "Что делать?")) {
	case 1:
		set(Clue, get(Clue) - 4);
		break;
	case 2:
		for(int i = 0; i < 2; i++) {
			item = chooseexist("Какое заклинание сбросить?", BindMonster, Wither, interactive);
			if(cards[item] > 0)
				cards[item]--;
		}
		break;
	case 3:
		item = chooseexist("Какой навык сбросить?", SkillBarvery, SkillLuck, interactive);
		if(cards[item] > 0)
			cards[item]--;
		break;
	}
}

void hero::monsterappear(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	auto pm = monster::getfromcup();
	if(!pm)
		return;
	combat(*pm);
}

void hero::finditem(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	auto& d = deck::getdeck(item::getgroup(card));
	auto i = d.indexof(card);
	if(i == -1) {
		logs::next();
		return;
	} else {
		logs::add(1, "Получить [%1].", getstr(card));
	}
	auto id = whatdo(interactive);
	add(card);
	d.remove(i);
}

void hero::addally(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	char temp[512];
	if(get(card)) {
		switch(card) {
		case JohnLegrasse:
			break;
		case ProfessorArmitage:
			break;
		case Duke:
			break;
		}
		return;
	}
	logs::driver driver;
	driver.gender = Male;
	driver.name = getstr(card);
	//driver.prints(temp, zendof(temp), "Это был%а [%герой] и %она решил%а присоединиться к вам.");
	logs::add(temp);
	logs::next(interactive);
	cards[card] = 1;
}

void hero::chooselocation(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	for(auto i = AdministrationBuilding; i <= Uptown; i = (location_s)(i + 1)) {
		logs::add(i, getstr(i));
	}
	logs::sort();
	position = (location_s)logs::input(interactive, false, "Куда вы хотите переместиться?");
}

card_s hero::chooseexist(const char* text, card_s from, card_s to, bool interactive) const {
	for(auto i = from; i <= to; i = (card_s)(i + 1)) {
		if(get(i) == 0)
			continue;
		logs::add(i, getstr(i));
	}
	if(!logs::getcount())
		return NoItem;
	logs::sort();
	return (card_s)logs::input(interactive, false, text);
}

void hero::encounter(stat_s stat, card_s card, location_s location, int value, bool interactive) {
	if(location == AnyLocation)
		location = position;
	run(getquest(location));
}

void hero::encounterany(stat_s stat, card_s card, location_s location, int value, bool interactive) {
	chooselocation(stat, card, location, 0, interactive);
	if(location_data[position].text)
		logs::add(location_data[position].text);
	logs::next();
	encounter(stat, card, position, 0, interactive);
}

void hero::encounter1ofX(stat_s stat, card_s card, location_s location, int value, bool interactive) {
	questa result; getquest(result, location);
	run(choosebest(result, value, interactive));
}

void hero::encounterandmove(stat_s stat, card_s card, location_s location, int value, bool interactive) {
	if(location==AnyLocation)
		location = (location_s)xrand(AdministrationBuilding, YeOldeMagickShoppe);
	position = location;
	run(getquest(location));
}

void hero::addmagic(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	auto value = get(Blessed) + count;
	if(value < -1 || value > 1) {
		logs::next();
		return;
	}
	switch(value) {
	case 1:
		logs::add(1, "Получить благословение");
		break;
	case -1:
		logs::add(1, "Получить проклятие");
		break;
	default:
		if(get(Blessed) > 0)
			logs::add(1, "Снять благословение");
		else
			logs::add(1, "Снять проклятие");
		break;
	}
	whatdo(interactive, false);
	set(Blessed, value);
}

void hero::choose(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	choose(stat, count, count, 0, interactive);
}

void hero::chooseone(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	choose(stat, 1, count, 0, interactive);
}

void hero::choosespellorclue(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	logs::add(1, "Взять [1] заклинание");
	logs::add(2, "Взять [%1i] улик", count);
	switch(whatdo(interactive, false)) {
	case 1:
		choose(Spell, NoItem, AnyLocation, 1, interactive);
		break;
	default:
		add(Clue, NoItem, AnyLocation, count, false);
		break;
	}
}

void hero::choosetome(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	auto filter = Tome;
	choose(stat, count, count, 0, interactive, &filter);
}

void hero::buy(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	choose(stat, count, count, 0, interactive, 0, true);
}

void hero::buy1ofX(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	choose(stat, 1, count, 0, interactive, 0, true);
}

void hero::buyXofXCU(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	choose(stat, count, count, 0, interactive, 0, true);
}

void hero::buy1expence(stat_s stat, card_s card, location_s location, int count, bool interactive) {
	choose(stat, count, count, 0, interactive, 0, true, 1);
}

void hero::required(char* result, const char* result_maximum, action_s id) {
	if(action_data[id].count < 0) {
		auto pe = getcase(action_data[id].stat);
		if(!pe)
			return;
		szprints(zend(result), result_maximum, " ");
		szprints(zend(result), result_maximum, pe->decrement, getstr(action_data[id].stat), pe->get(-action_data[id].count), -action_data[id].count);
	}
}

void hero::required(char* result, const char* result_maximum, const action_s* actions) {
	auto pe = zend(result);
	for(auto p = actions; *p; p++)
		required(pe, result_maximum, *p);
}

void hero::addretainer(stat_s stat, card_s card, location_s location, int value, bool interactive) {
	logs::add(1, "Получить постоянный [Доход].");
	whatdo(interactive);
}