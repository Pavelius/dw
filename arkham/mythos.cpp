#include "main.h"

enum myth_type_s : unsigned char {
	EnvironmentMystic, EnvironmentUrban, EnvironmentWeather,
	Headline, Rumor,
};

static quest all_quete = {AnyLocation, "Какой солнечный день. Сегодня стоит надеятся на чудо.", {Luck, -1}, {{"Но чуда не случилось."},
{"Небеса были благосклонны к вам.", {AddBless}}
}};

struct mythos {
	
	const char*		id;
	const char*		name;
	myth_type_s		type;
	location_s		position;
	location_s		clue;
	myth_s			effect;
	quest*			script;
	location_s		location[4];
	card_s			cards[4];
	void			(mythos::*ability)() const;

	void removefromlocations() const {
	}

	void removemonsters() const {
		int remove_count = 0;
		for(auto& e : location_data) {
			if(!e.isarkham())
				continue;
		}
	}

} myth_data[] = {{"A Strange Plague", "Странная хворь", EnvironmentMystic, IndependenceSquare, TheUnnamable, StrangePlague},
{"Alien Technology", "Чужеродная технология", EnvironmentUrban, UnvisitedIsle, ScienceBuilding, AlienTechnology},
{"All Quiet in Arkham!", "В Арекхэме все спокойно!", Headline, Woods, HistoricalSociety, NoMyth, &all_quete},
{"An Evil Fog", "", EnvironmentWeather, Graveyard, UnvisitedIsle, AnEvilFog},
{"Big Storm Sweeps Arkham!", "", Headline, Graveyard, TheUnnamable, NoMyth, 0, {Outskirt, Sky}, {}, &mythos::removefromlocations},
{"Bizarre Dreams Plague Citizens!", "", Headline, ScienceBuilding, TheWitchHouse, NoMyth, 0, {}, {}, &mythos::removemonsters},
};