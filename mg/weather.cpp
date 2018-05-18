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
} season_data[] = {{"Spring", "Весна", 6},
{"Summer", "Лето", 4},
{"Autum", "Осень", 5},
{"Winter", "Зима", 7},
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
} weather_data[] = {{"Clear and warm weather", "Ясная и жаркая погода", "стоит ясная и теплая погода", "Небо стало чистым и установилась ясная и теплая погода.", 3, Spring, Spring},
{"Spring snow", "Весенний снег", "идет легкий весенний снег", "Внезапно пошел легкий снег.", 1, Spring, Spring, {Tired, Sick}, true, 0, 3},
{"Spring rain", "Весенний дождь", "на небе пасмурно и идет моросит слабы дождь", "Начался мелкий дождь.", 1, Spring, Spring, {}, true, 3},
{"Spring strom", "Осенняя гроза", "небо закрыто тучами и вода льется как из ведра. Сверкают молнии и слышны раскаты грома", "Вдруг небо заполнилось темными тучами. Послышались несколько раскатов грома. Супстя какое-то время подул ветер и началься проливной ливень, сопровождающийся громом и молниями.", 1, Spring, Spring, {Injured}},
{"Unseasonably cold", "Похолодание", 0, 0, 1, Spring, Winter},
{"Unseasonably warm", "Потепление", 0, 0, 1, Spring, Summer},
//
{"Warm and humid weather", "Жаркая и влажная погода", "стоит жаркая и влажная погода", "Небо стало чистым. На нем не было ни одного облачка.", 3, Summer, Summer},
{"Summer rain", "Летний дождь", "на небе ясно, но моросит дождь", "Вскоре с неба пошел дождь.", 1, Summer, Summer, {}, false, 0, 0, {Pathfinder, Scout}},
{"Thunderstorm", "Гроза", "небо затянуто темными тучами, вода льется как из ведра, сверкают молнии и раздаются расскаты грома", "Небо быстро затянуло черными тучами. Подул сильный ветер. Раздались удары грома. И начался тяжелейший ливень.", 1, Summer, Summer},
{"Heat waves", "Зной", "было очень жарко", 0, 1, Summer, Summer},
//
{"Autum storm", "Осенний дождь", "шел дождь", 0, 2, Autum, Autum},
{"Cold rain", "Холодный дождь", "было очень холодно и шел дождь", 0, 1, Autum, Autum},
{"Unseasonably cold", "Похолодание", 0, 0, 1, Autum, Winter},
{"Unseasonably warm", "Потепление", 0, 0, 1, Autum, Summer},
//
{"Clear and cold weather", "Ясная и холодная погода", "был ясный морозный день", "Небо прояснилось и начало пригревать зимнее солнце.", 3, Winter, Winter},
{"Snow", "Снег", "на улице шел снег", "Вскоре с неба начал падать снег.", 1, Winter, Winter},
{"Blizzard", "Метель", "вокруг была настоящая метель - сильный ветер выл и носил снежинки", 0, 1, Winter, Winter},
{"Cold Snap", "Заморозки", "на улице было очень холодно", 0, 1, Winter, Winter},
{"Ice Storm", "Буран", "", 0, 1, Winter, Winter},
{"Unseasonably warm", "Потепление", "", 0, 1, Winter, Autum},
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
		// Если сезон сменился, выбираем погоду, которой не должно быть в начале
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
	logs::add("Сейчас %1.", weather_data[getweather()].now_text);
	logs::add("Вы остановились в попытке угадать, какая погода будет дальше.");
	if(passtest(WeatherWatcher, getobstacle(getseason()))) {
		auto ni = next_season();
		for(auto i = FirstWeather; i <= LastWeather; i = (weather_s)(i + 1)) {
			if(weather_data[i].season != year_season[ni])
				continue;
			if(weather_data[i].season != weather_data[i].season_link)
				continue;
			logs::add(i, getstr(i));
		}
		year_weather[ni] = (weather_s)logs::input(true, true, "Какая погода будет следующей?");
	} else {
	}
}

void hero::twistweather(bool interactive, skill_s skill, hero** helps) {
	season_index = next_season();
	if(interactive)
		logs::add(weather_data[season_index].start_text);
}