#include "main.h"

static short unsigned day;

int hero::whatdo(bool interactive, bool clear_text) {
	return logs::input(interactive, clear_text, "Что будете делать?");
}

void hero::focusing() {
	static const stat_s statinfo[][2] = {
		{Speed, Sneak},
	{Fight, Will},
	{Lore, Luck},
	};
	for(auto& e : statinfo) {
		auto i = &e - statinfo;
		if(focus[i] < 3)
			logs::add(i * 2, "Сделать %1 %2i, но %3 %4i", getstr(e[0]), get(e[0]) + 1, getstr(e[1]), get(e[1]) - 1);
		if(focus[i] > 0)
			logs::add(i * 2 + 1, "Сделать %1 %2i, но %3 %4i", getstr(e[0]), get(e[0]) - 1, getstr(e[1]), get(e[1]) + 1);
	}
	auto i = logs::input(true, false, "Как вы хотите поменять характеристики?");
	auto& e = focus[i / 2];
	if((i % 2) == 0)
		e++;
	else
		e--;
}

void hero::upkeep() {
	day++;
	if(get(TurnToSkip) > 0) {
		set(TurnToSkip, get(TurnToSkip) - 1);
		return;
	}
	memset(exhause, 0, sizeof(exhause));
	auto focus_count = get(Focus);
	set(Movement, get(Speed));
	while(true) {
		if(day > 1)
			logs::add("Наступил [%1i] день вашего расследования.", day);
		logs::add("На улице было прекрасное утро.");
		logs::add("Утренние газеты не писали ничего интересного.");
		if(focus_count > 0)
			logs::add(1, "Переосмыслить некоторые вещи и изменить характеристики. Можно сделать еще [%1i] раз.", focus_count);
		logs::add(100, "Продолжить расследование");
		switch(whatdo()) {
		case 1:
			focusing();
			focus_count--;
			break;
		case 100:
			return;
		}
	}
}

struct special_info {
	location_s	position;
	const char*	text;
	action_s	actions[4];
} special_data[] = {{StMarysHospital, "Восстановить 1 здоровье бесплатно.", {Add1Stamina}},
{StMarysHospital, "Восстановить здоровье до максимума за 2$.", {RestoreStamina, Lose2Money}},
{ArkhamAsylum, "Восстановить 1 рассудок бесплатно.", {Add1Sanity}},
{ArkhamAsylum, "Восстановить рассудок до максимума за 2$.", {RestoreSanity, Lose2Money}},
};

void hero::movement() {
	char temp[512];
	const int special = 1000;
	const int itemuse = 2000;
	while(isready()) {
		if(location_data[position].text)
			logs::add(location_data[position].text);
		auto movement = get(Movement);
		for(auto i = PistolDerringer18; i <= WardingStatue; i = (card_s)(i + 1)) {
			if(!get(i))
				continue;
			auto& ti = item::getuse(i);
			if(ti.script && ti.movement <= movement && ti.sanity < get(Sanity)) {
				if(item::is(i, Tome))
					szprints(temp, zendof(temp), "Прочитать [%1].", getstr(i));
				else
					szprints(temp, zendof(temp), "Изучить [%1].", getstr(i));
				if(ti.movement)
					szprints(zend(temp), zendof(temp), " Потребует %1i движения.", ti.movement);
				if(ti.sanity)
					szprints(zend(temp), zendof(temp), " Потребует %1i рассудка.", ti.sanity);
				logs::add(itemuse + i, temp);
			}
		}
		for(auto& a : special_data) {
			if(a.position != position)
				continue;
			int allow_count = 0;
			for(auto& aa : a.actions) {
				if(isallow(aa))
					allow_count++;
			}
			if(!allow_count)
				continue;
			logs::add(special + (&a - special_data), a.text);
		}
		logs::add(100, "Остаться здесь на ночь");
		auto neightboard_count = zlen(location_data[position].neightboard);
		if(movement > 0) {
			for(auto& e : location_data[position].neightboard) {
				if(!e)
					break;
				auto index = &e - location_data[position].neightboard;
				logs::add(200 + index, "Посетить [%1].", getstr(e));
			}
		}
		auto id = logs::input(true, false, "Что будете делать?");
		switch(id) {
		case 100:
			logs::clear();
			run(getquest(position));
			return;
		case 200:
		case 201:
		case 202:
		case 203:
		case 204:
		case 205:
			logs::clear();
			position = location_data[position].neightboard[id - 200];
			add(Movement, NoItem, AnyLocation, -1, false);
			break;
		default:
			if(id >= special && id < special + sizeof(special_data) / sizeof(special_data[0])) {
				auto& e = special_data[id - special];
				for(auto a : e.actions) {
					if(!a)
						break;
					apply(a, true, 0);
				}
			} else if(id >= itemuse && id <= itemuse + LastItem) {
				auto i = (card_s)(id - itemuse);
				auto& ti = item::getuse(i);
				if(ti.movement)
					set(Movement, get(Movement) - ti.movement);
				if(ti.sanity)
					add(Sanity, NoItem, AnyLocation, -ti.sanity, false);
				if(item::is(i, ExhaustToEffect))
					exhausecard(i);
				use(i);
				logs::clear();
				continue;
			}
			logs::clear();
			return;
		}
	}
}

void hero::play() {
	while(isready()) {
		upkeep();
		movement();
		logs::clear(true);
	}
}