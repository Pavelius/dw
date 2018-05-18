#include "main.h"

struct scene_adventure : scene {
	
	unsigned adventure() {
		unsigned distance = 0;
		unsigned distance_maximum = 30;
		auto chances = getencounterchance(enviroment);
		unsigned speed_per_time = getmoverate() / 6;
		if(speed_per_time == 0)
			speed_per_time = 1;
		auto difference = 0;
		auto round = getround();
		while(isparty(&character::isready) && distance < distance_maximum) {
			auto timezone = (timezone_s)(((round + difference) % RDay) / (4 * RHour));
			auto chance = chances[timezone];
			if(chance && d10() <= chance) {
				passtime(true, difference); difference = 0; round = getround();
				logs::add(getstrmovement(enviroment));
				ask(getactions(enviroment));
				auto result = resolve();
				continue;
			}
			if(timezone == Evening || timezone == Midnight) {
				passtime(true, difference); difference = 0; round = getround();
				logs::add(getstrmovement(enviroment));
				logs::add("Но, вскоре наступил вечер пришло время сделать привал.");
				if(logs::yesno(true))
					makecamp();
				continue;
			}
			difference += 4 * RHour;
			distance += speed_per_time;
		}
		return distance_maximum - distance;
	}

	scene_adventure(landscape_s type) : scene(type) {
	}

};

unsigned scene::adventure(landscape_s type) {
	scene_adventure e(type);
	return e.adventure();
}