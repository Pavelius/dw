#include "main.h"

static season_s year_season[] = {
	Spring, Spring, Spring,
	Summer, Summer, Summer, Summer,
	Autum, Autum,
	Winter, Winter, Winter, Winter, Winter
};
static weather_s year_weather[sizeof(year_season) / sizeof(year_season[0])];
static int season_index = 0;

static struct season_i {
	const char*	name[2];
	char		obstacle;
} season_data[] = {{"Spring", "�����", 6},
{"Summer", "����", 4},
{"Autum", "�����", 5},
{"Winter", "����", 7},
};

static struct weather_info {
	const char*		id;
	const char*		name;
	const char*		now_text;
	const char*		start_text;
	char			chance;
	season_s		season;
	season_s		season_link;
	adat<condition_s, 5> conditions;
	bool			weather_factor_for_outdoor;
	char			obstacle_for_tired;
	char			obstacle_for_sick;
	skilla			skills;
} weather_data[] = {{"Clear and warm weather", "����� � ������ ������", "����� ����� � ������ ������", "���� ����� ������ � ������������ ����� � ������ ������.", 3, Spring, Spring},
{"Spring snow", "�������� ����", "���� ������ �������� ����", "�������� ����� ������ ����.", 1, Spring, Spring, {Tired, Sick}, true, 0, 3},
{"Spring rain", "�������� �����", "�� ���� �������� � ���� ������� ����� �����", "������� ������ �����.", 1, Spring, Spring, {}, true, 3},
{"Spring strom", "������� �����", "���� ������� ������ � ���� ������ ��� �� �����. �������� ������ � ������ ������� �����", "����� ���� ����������� ������� ������. ����������� ��������� �������� �����. ������ �����-�� ����� ����� ����� � �������� ��������� ������, ���������������� ������ � ��������.", 1, Spring, Spring, {Injured}},
{"Unseasonably cold", "�����������", 0, 0, 1, Spring, Winter},
{"Unseasonably warm", "����������", 0, 0, 1, Spring, Summer},
//
{"Warm and humid weather", "������ � ������� ������", "����� ������ � ������� ������", "���� ����� ������. �� ��� �� ���� �� ������ �������.", 3, Summer, Summer},
{"Summer rain", "������ �����", "�� ���� ����, �� ������� �����", "������ � ���� ����� �����.", 1, Summer, Summer, {}, false, 0, 0, {Pathfinder, Scout}},
{"Thunderstorm", "�����", "���� �������� ������� ������, ���� ������ ��� �� �����, �������� ������ � ��������� �������� �����", "���� ������ �������� ������� ������. ����� ������� �����. ��������� ����� �����. � ������� ���������� ������.", 1, Summer, Summer},
{"Heat waves", "����", "���� ����� �����", 0, 1, Summer, Summer},
//
{"Autum storm", "������� �����", "��� �����", 0, 2, Autum, Autum},
{"Cold rain", "�������� �����", "���� ����� ������� � ��� �����", 0, 1, Autum, Autum},
{"Unseasonably cold", "�����������", 0, 0, 1, Autum, Winter},
{"Unseasonably warm", "����������", 0, 0, 1, Autum, Summer},
//
{"Clear and cold weather", "����� � �������� ������", "��� ����� �������� ����", "���� ����������� � ������ ���������� ������ ������.", 3, Winter, Winter},
{"Snow", "����", "�� ����� ��� ����", "������ � ���� ����� ������ ����.", 1, Winter, Winter},
{"Blizzard", "������", "������ ���� ��������� ������ - ������� ����� ��� � ����� ��������", 0, 1, Winter, Winter},
{"Cold Snap", "���������", "�� ����� ���� ����� �������", 0, 1, Winter, Winter},
{"Ice Storm", "�����", "", 0, 1, Winter, Winter},
{"Unseasonably warm", "����������", "", 0, 1, Winter, Autum},
};
assert_enum(weather, WinterUnseasonablyWarm);
getstr_enum(weather);

int next_season() {
	return (season_index + 1) % (sizeof(year_season) / sizeof(year_season[0]));
}

int hero::getobstacle(season_s value) {
	return season_data[value].obstacle;
}

static weather_s getrandomweather(season_s season, weather_s current, weather_s current2, bool strict_season) {
	weather_s source[(LastWeather + 1) * 2];
	auto pa = source;
	for(auto i = FirstWeather; i <= LastWeather; i = (weather_s)(i + 1)) {
		if(weather_data[i].season != season)
			continue;
		if(strict_season && weather_data[i].season_link != season)
			continue;
		if(current == i || current2==i)
			continue;
		for(int j = 0; j < weather_data[i].chance; j++)
			*pa++ = i;
	}
	auto count = pa - source;
	if(!count)
		return ClearAndCold;
	return source[rand() % count];
}

bool hero::isfactor(weather_s object, skill_s value) {
	return weather_data[object].skills.is(value);
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
		if(weather_data[current].season != weather_data[current].season_link)
			current = getrandomweather(weather_data[current].season_link, current, not_first, true);
		year_weather[i] = current;
	}
}

season_s hero::getseason() {
	return year_season[season_index];
}

void hero::weatherwatch() {
	logs::add("������ %1.", weather_data[getweather()].now_text);
	logs::add("�� ������������ � ������� �������, ����� ������ ����� ������.");
	if(passtest(WeatherWatcher, getobstacle(getseason()))) {
		auto ni = next_season();
		for(auto i = FirstWeather; i <= LastWeather; i = (weather_s)(i + 1)) {
			if(weather_data[i].season != year_season[ni])
				continue;
			if(weather_data[i].season != weather_data[i].season_link)
				continue;
			logs::add(i, getstr(i));
		}
		year_weather[ni] = (weather_s)logs::input(true, true, "����� ������ ����� ���������?");
	} else {
	}
}

void hero::twistweather(bool interactive, skill_s skill, hero** helps) {
	season_index = next_season();
	if(interactive)
		logs::add(weather_data[season_index].start_text);
}