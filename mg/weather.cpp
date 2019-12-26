#include "main.h"

static season_s year_season[] = {
	Spring, Spring, Spring,
	Summer, Summer, Summer, Summer,
	Autum, Autum,
	Winter, Winter, Winter, Winter, Winter
};
static weather_s	year_weather[sizeof(year_season) / sizeof(year_season[0])];
static int			season_index = 0;

template<> weatheri bsmeta<weatheri>::elements[] = {{"Clear and warm weather", "����� � ������ ������", "������ ����� � ������ ������.", "���� ����� ������ � ������������ ����� � ������ ������.", 3, Spring, Spring},
{"Spring snow", "�������� ����", "������ ���� ������ �������� ����.", "�������� ����� ������ ����.", 1, Spring, Spring, {Tired, Sick}, true, 0, 3},
{"Spring rain", "�������� �����", "�� ���� �������� � ���� ������� ������ �����.", "������� ������ �����.", 1, Spring, Spring, {}, true, 3},
{"Spring strom", "������� �����", "�� ����� ���� ������� �������� ������� ������.", "����� ���� ����������� ������� ������. ����������� ��������� �������� �����. ������ �����-�� ����� ����� ����� � �������� ��������� ������, ���������������� ������ � ��������.", 1, Spring, Spring, {Injured}},
{"Unseasonably cold", "�����������", 0, 0, 1, Spring, Winter},
{"Unseasonably warm", "����������", 0, 0, 1, Spring, Summer},
//
{"Warm and humid weather", "������ � ������� ������", "�� ����� ����� ������ � ������� ������.", "���� ����� ������. �� ��� �� ���� �� ������ �������.", 3, Summer, Summer},
{"Summer rain", "������ �����", "�� ���� ����, �� ������ ������� ����������������� ������ �����.", "������ � ���� ����� �����.", 1, Summer, Summer, {}, false, 0, 0, {Pathfinder, Scout}},
{"Thunderstorm", "�����", "�� ���� ���� ��������, ���� ���� ���� �����.", "���� ������ �������� ������� ������. ����� ������� �����. ��������� ����� �����. � ������� ���������� ������.", 1, Summer, Summer},
{"Heat waves", "����", "������ ������ ����������� ����.", 0, 1, Summer, Summer},
//
{"Autum storm", "������� �����", "�� ����� ��� �����, ���� ���� �������� ����� �������.", 0, 2, Autum, Autum},
{"Cold rain", "�������� �����", "���� ����� ������� � ��� �����.", 0, 1, Autum, Autum},
{"Unseasonably cold", "�����������", 0, 0, 1, Autum, Winter},
{"Unseasonably warm", "����������", 0, 0, 1, Autum, Summer},
//
{"Clear and cold weather", "����� � �������� ������", "�� ����� ����� ����, ���� ��� �����, ���� �������� �����.", "���� ����������� � ������ ���������� ������ ������.", 3, Winter, Winter},
{"Snow", "����", "�� ����� ��� ����.", "������ � ���� ����� ������ ����.", 1, Winter, Winter},
{"Blizzard", "������", "������ ���� ��������� ������, ������� ������ ����� ������ ���� �����.", 0, 1, Winter, Winter},
{"Cold Snap", "���������", "�� ����� ���� ����� �������.", 0, 1, Winter, Winter},
{"Ice Storm", "�����", "�� ����� ���� ����� ��������� ���� - �������� ������� ������� ��������� ��� ������.", 0, 1, Winter, Winter},
{"Unseasonably warm", "����������", "", 0, 1, Winter, Autum},
};
assert_enum(weather, WinterUnseasonablyWarm);

weather_s weatheri::getid() const {
	return weather_s(this - bsmeta<weatheri>::elements);
}

static int next_season() {
	return (season_index + 1) % (sizeof(year_season) / sizeof(year_season[0]));
}

static weather_s getrandomweather(season_s season, weather_s current, weather_s current2, bool strict_season) {
	weather_s source[(LastWeather + 1) * 2];
	auto pa = source;
	for(auto& e : bsmeta<weatheri>()) {
		if(e.season != season)
			continue;
		if(strict_season && e.season_link != season)
			continue;
		if(current == e.getid() || current2==e.getid())
			continue;
		for(int j = 0; j < e.chance; j++)
			*pa++ = e.getid();
	}
	auto count = pa - source;
	if(!count)
		return ClearAndCold;
	return source[rand() % count];
}

bool hero::isfactor(weather_s object, skill_s value) {
	return bsmeta<weatheri>::elements[object].skills.is(value);
}

weather_s hero::getweather() {
	return year_weather[season_index];
}

void hero::setyearweather() {
	auto current = SpringStorms;
	auto current_season = Spring;
	for(int i = 0; i < sizeof(year_weather) / sizeof(year_weather[0]); i++) {
		// ���� ����� ��������, �������� ������, ������� �� ������ ���� � ������
		weather_s not_first;
		if(current_season != year_season[i]) {
			switch(year_season[i]) {
			case Spring: not_first = SpringStorms; break;
			case Summer: not_first = Thunderstorms; break;
			case Autum: not_first = AutumUnseasonablyCold; break;
			case Winter: not_first = Blizzard; break;
			}
			current_season = year_season[i];
		} else
			not_first = current;
		current = getrandomweather(year_season[i], current, not_first, false);
		auto& ei = bsmeta<weatheri>::elements[current];
		if(ei.season != ei.season_link)
			current = getrandomweather(ei.season_link, current, not_first, true);
		year_weather[i] = current;
	}
}

season_s hero::getseason() {
	return year_season[season_index];
}

void hero::weatherwatch() {
	sb.adds("������ %1.", bsmeta<weatheri>::elements[getweather()].now_text);
	sb.adds("�� ������������ � ������� �������, ����� ������ ����� ������.");
	if(passtest(WeatherWatcher, getobstacle(getseason()))) {
		auto ni = next_season();
		for(auto& e : bsmeta<weatheri>()) {
			if(e.season != year_season[ni])
				continue;
			if(e.season != e.season_link)
				continue;
			an.add(e.getid(), e.name);
		}
		year_weather[ni] = (weather_s)an.choosev(true, true, false, "����� ������ ����� ���������?");
	} else {
	}
}

void hero::twistweather(bool interactive, skill_s skill, heroa& helps) {
	season_index = next_season();
	if(interactive)
		sb.add(bsmeta<weatheri>::elements[season_index].start_text);
}