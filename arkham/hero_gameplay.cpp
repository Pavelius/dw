#include "main.h"

static short unsigned day;

int hero::whatdo() {
	return logs::input(true, true, "��� ������ ������?");
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
			logs::add(i * 2, "������� %1 %2i, �� %3 %4i", getstr(e[0]), get(e[0]) + 1, getstr(e[1]), get(e[1]) - 1);
		if(focus[i] > 0)
			logs::add(i * 2 + 1, "������� %1 %2i, �� %3 %4i", getstr(e[0]), get(e[0]) - 1, getstr(e[1]), get(e[1]) + 1);
	}
	auto i = logs::input(true, false, "��� �� ������ �������� ��������������?");
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
			logs::add("�������� [%1i] ���� ������ �������������.", day);
		logs::add("�� ����� ���� ���������� ����.");
		logs::add("�������� ������ �� ������ ������ �����������.");
		if(focus_count > 0)
			logs::add(1, "������������� ��������� ���� � �������� ��������������. ����� ������� ��� [%1i] ���.", focus_count);
		logs::add(100, "���������� �������������");
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
} special_data[] = {{StMarysHospital, "������������ 1 �������� ���������.", {Add1Stamina}},
{StMarysHospital, "������������ �������� �� ��������� �� 2$.", {RestoreStamina, Lose2Money}},
{ArkhamAsylum, "������������ 1 �������� ���������.", {Add1Sanity}},
{ArkhamAsylum, "������������ �������� �� ��������� �� 2$.", {RestoreSanity, Lose2Money}},
};

void hero::movement() {
	const int special = 1000;
	while(isready()) {
		if(location_data[position].text)
			logs::add(location_data[position].text);
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
		logs::add(100, "�������� ����� �� ����");
		auto neightboard_count = zlen(location_data[position].neightboard);
		if(get(Movement) > 0) {
			for(auto& e : location_data[position].neightboard) {
				if(!e)
					break;
				auto index = &e - location_data[position].neightboard;
				logs::add(200 + index, "�������� [%1].", getstr(e));
			}
		}
		auto id = logs::input(true, false, "��� ������ ������?");
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