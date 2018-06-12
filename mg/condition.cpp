#include "main.h"

static struct condition_i {
	const char*	name[2];
	const char*	text;
	skilla		skills;
	skilla		recover;
	char		recover_ob;
} condition_data[] = {{{"Healthy", "Здоровый"}},
{{"Hunger and Thirsty", "Голодный"}, "У вас все получилось, но в процессе выполнения %1 захотел%2 есть."},
{{"Angry", "Злой"}, "В результате все пошло как надо, но чертова рутина безумно разозлила %1.", {Administrator, Orator, Deceiver, Persuader, Haggler, Baker, Smith}, {Will}, 2},
{{"Tired", "Уставший"}, "Хоть дело и было сделано, но от тяжелой работы %1 испытал%2 переутомление.", {Cartographer, Scientist, Archivist, Pathfinder, Hunter, Scout, Nature}, {Health}, 3},
{{"Injured", "Раненный"}, "Во время выполнения %1 получил%2 ранение.", {Fighter}, {Health}, 4},
{{"Sick", "Больной"}, "В процессе %1 почуствовал%2 себя плохо и скорее всего заболел%2.", {}, {Health}, 4},
{{"Dead", "Мертвый"}, "Не смотря на то, что вам удалось добиться своей цели, в процессе %1 погибл%2."},
};

template<> const skilla& getskills<condition_s>(condition_s value) {
	return condition_data[value].skills;
}

static bool is_skill(condition_s value, skill_s skill) {
	for(auto e : condition_data[value].skills) {
		if(e == skill)
			return true;
	}
	return false;
}

void hero::get(adat<condition_s, 8>& conditions, skill_s skill) {
	conditions.clear();
	conditions.add(HungerAndThirsty);
	for(auto i = HungerAndThirsty; i <= Dead; i = (condition_s)(i + 1)) {
		if(conditions.is(i))
			continue;
		if(is_skill(i, skill))
			conditions.add(i);
	}
}

void hero::twistconditions(bool interactive, skill_s skill, hero** helps) {
	adat<condition_s, 8> conditions;
	get(conditions, skill);
	if(!conditions.count)
		return;
	auto condition = conditions.data[rand() % conditions.count];
	for(auto pp = helps; *pp; pp++) {
		auto p = *pp;
		if(!p)
			break;
		p->set(condition);
	}
	if(interactive) {
		if(condition_data[condition].text) {
			auto count = zlen(helps);
			if(count > 1) {
				char temp[512];
				logs::add(condition_data[condition].text, getmembers(temp, helps), "и");
			} else
				logs::add(condition_data[condition].text, helps[0]->getname(), helps[0]->getLA());
		}
	}
}

bool hero::passtest(skill_s skill, int obstacle) {
	const auto twist_chance = 20;
	hero* helps[8]; helps[0] = 0;
	auto was_weather_twist = false;
	while(true) {
		auto player = choose(skill);
		if(!player)
			return false;
		auto result = player->roll(skill, obstacle, 0, 0, true, StandartRoll, 0, 0, helps);
		zcat(helps, player);
		if(result >= 0)
			return true;
		if(!was_weather_twist && d100() < twist_chance) {
			was_weather_twist = true;
			twistweather(true, skill, helps);
			continue;
		}
		twistconditions(true, skill, helps);
		return true;
	}
}

void hero::recover() {
	static condition_s conditions[] = {HungerAndThirsty, Angry, Tired, Injured, Sick};
	for(auto e : conditions) {
		if(is(e)) {
			recover(e);
			break;
		}
	}
}

void hero::recover(condition_s value) {
	if(roll(condition_data[value].recover[0], condition_data[value].recover_ob))
		remove(value);
	else {

	}
}