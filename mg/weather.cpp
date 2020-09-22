#include "main.h"

template<> weatheri bsmeta<weatheri>::elements[] = {{"Clear and warm weather", "Ясная и жаркая погода", "Стояла ясная и теплая погода.", "Небо стало чистым и установилась ясная и теплая погода.", 3, Spring, Spring},
{"Spring snow", "Весенний снег", "Вокруг идет легкий весенний снег.", "Внезапно пошел легкий снег.", 1, Spring, Spring, {Tired, Sick}, true, 0, 3},
{"Spring rain", "Весенний дождь", "На небе пасмурно и моросит слабый дождь.", "Начался мелкий дождь.", 1, Spring, Spring, {}, true, 3},
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

bool hero::isfactor(weather_s object, skill_s value) {
	return bsmeta<weatheri>::elements[object].skills.is(value);
}

void hero::weatherwatch() {
	party.addweather();
	sb.adds("Вы остановились в попытке угадать, какая погода будет дальше.");
	if(passtest(WeatherWatcher, getobstacle(party.getseason()))) {
		auto ni = party.getnext();
		auto ns = party.getseason(ni);
		for(auto& e : bsmeta<weatheri>()) {
			if(e.nonseason())
				continue;
			if(e.season != ns)
				continue;
			an.add(e.getid(), e.name);
		}
		auto nw = (weather_s)an.choosev(true, true, false, "Какая погода будет следующей?");
		party.set(nw);
	} else {
	}
}

void hero::twistweather(bool interactive, skill_s skill, heroa& helps) {
	auto ns = party.getnext();
	//if(interactive)
	//	sb.add(bsmeta<weatheri>::elements[season_index].start_text);
}