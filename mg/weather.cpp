#include "main.h"

static season_s year_season[] = {
	Spring, Spring, Spring,
	Summer, Summer, Summer, Summer,
	Autum, Autum,
	Winter, Winter, Winter, Winter, Winter
};
static weather_s	year_weather[sizeof(year_season) / sizeof(year_season[0])];
static int			season_index = 0;

template<> weatheri bsmeta<weatheri>::elements[] = {{"Clear and warm weather", "Ясная и жаркая погода", "Стояла ясная и теплая погода.", "Небо стало чистым и установилась ясная и теплая погода.", 3, Spring, Spring},
{"Spring snow", "Весенний снег", "Вокруг идет легкий весенний снег.", "Внезапно пошел легкий снег.", 1, Spring, Spring, {Tired, Sick}, true, 0, 3},
{"Spring rain", "Весенний дождь", "На небе пасмурно и идет моросит слабый дождь.", "Начался мелкий дождь.", 1, Spring, Spring, {}, true, 3},
{"Spring strom", "Осенняя гроза", "На улице небо закрыто тяжелыми темными тучами.", "Вдруг небо заполнилось темными тучами. Послышались несколько раскатов грома. Спустя какое-то время подул ветер и началься проливной ливень, сопровождающийся громом и молниями.", 1, Spring, Spring, {Injured}},
{"Unseasonably cold", "Похолодание", 0, 0, 1, Spring, Winter},
{"Unseasonably warm", "Потепление", 0, 0, 1, Spring, Summer},
//
{"Warm and humid weather", "Жаркая и влажная погода", "На улице стоит жаркая и влажная погода.", "Небо стало чистым. На нем не было ни одного облачка.", 3, Summer, Summer},
{"Summer rain", "Летний дождь", "На небе ясно, но иногда моросит непродолжительный летний дождь.", "Вскоре с неба пошел дождь.", 1, Summer, Summer, {}, false, 0, 0, {Pathfinder, Scout}},
{"Thunderstorm", "Гроза", "На небе было пасмурно, весь день идет дождь.", "Небо быстро затянуло черными тучами. Подул сильный ветер. Раздались удары грома. И начался тяжелейший ливень.", 1, Summer, Summer},
{"Heat waves", "Зной", "Вокруг стояла невероятная жара.", 0, 1, Summer, Summer},
//
{"Autum storm", "Осенний дождь", "На улице шел дождь, небо было затянуто серой пеленой.", 0, 2, Autum, Autum},
{"Cold rain", "Холодный дождь", "Было очень холодно и шел дождь.", 0, 1, Autum, Autum},
{"Unseasonably cold", "Похолодание", 0, 0, 1, Autum, Winter},
{"Unseasonably warm", "Потепление", 0, 0, 1, Autum, Summer},
//
{"Clear and cold weather", "Ясная и холодная погода", "На улице лежал снег, день был ясный, хотя ощущался мороз.", "Небо прояснилось и начало пригревать зимнее солнце.", 3, Winter, Winter},
{"Snow", "Снег", "На улице шел снег.", "Вскоре с неба начал падать снег.", 1, Winter, Winter},
{"Blizzard", "Метель", "Вокруг была настоящая метель, сильные порывы ветра несили кучи снега.", 0, 1, Winter, Winter},
{"Cold Snap", "Заморозки", "На улице было очень холодно.", 0, 1, Winter, Winter},
{"Ice Storm", "Буран", "На улице была самая настоящая зима - огромные снежные сугробы покрывали все вокруг.", 0, 1, Winter, Winter},
{"Unseasonably warm", "Потепление", "", 0, 1, Winter, Autum},
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
	sb.adds("Сейчас %1.", bsmeta<weatheri>::elements[getweather()].now_text);
	sb.adds("Вы остановились в попытке угадать, какая погода будет дальше.");
	if(passtest(WeatherWatcher, getobstacle(getseason()))) {
		auto ni = next_season();
		for(auto& e : bsmeta<weatheri>()) {
			if(e.season != year_season[ni])
				continue;
			if(e.season != e.season_link)
				continue;
			an.add(e.getid(), e.name);
		}
		year_weather[ni] = (weather_s)an.choosev(true, true, false, "Какая погода будет следующей?");
	} else {
	}
}

void hero::twistweather(bool interactive, skill_s skill, heroa& helps) {
	season_index = next_season();
	if(interactive)
		sb.add(bsmeta<weatheri>::elements[season_index].start_text);
}