#include "main.h"

enum myth_type_s : unsigned char {
	EnvironmentMystic, EnvironmentUrban, EnvironmentWeather,
	Headline, Rumor,
};

static quest all_quete = {AnyLocation, "Какой солнечный день. Сегодня стоит надеятся на чудо.", {Luck, -1}, {{"Но чуда не случилось."},
{"Небеса были благосклонны к вам.", {AddBless}}
}};

struct mythos;
static mythos*				current_myth;
static adat<mythos*, 128>	myth_deck;

struct mythos {
	
	const char*		id;
	const char*		name;
	myth_type_s		type;
	location_s		gate;
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
			remove_count += monster::remove(e.getid());
		}
		if(remove_count)
			game.addterror();
	}

	void removemonstersnoterror() const {
		int remove_count = 0;
		for(auto& e : location_data) {
			if(!e.isarkham())
				continue;
			remove_count += monster::remove(e.getid());
		}
		if(remove_count)
			game.addterror();
	}

} myth_data[] = {{"A Strange Plague", "Странная хворь", EnvironmentMystic, IndependenceSquare, TheUnnamable, StrangePlague},
{"Alien Technology", "Чужеродная технология", EnvironmentUrban, UnvisitedIsle, ScienceBuilding, AlienTechnology},
{"All Quiet in Arkham!", "В Арекхэме все спокойно!", Headline, Woods, HistoricalSociety, NoMyth, &all_quete},
{"An Evil Fog", "", EnvironmentWeather, Graveyard, UnvisitedIsle, AnEvilFog},
{"Big Storm Sweeps Arkham!", "", Headline, Graveyard, TheUnnamable, NoMyth, 0, {Outskirt, Sky}, {}, &mythos::removefromlocations},
{"Bizarre Dreams Plague Citizens!", "", Headline, ScienceBuilding, TheWitchHouse, NoMyth, 0, {}, {Gug, Nightgaunt}, &mythos::removemonsters},
{"Blackest Night", "", EnvironmentMystic, BlackCave, HibbsRoadhouse, NoMyth, 0, {}, {Gug, Nightgaunt}, &mythos::removemonsters},
{"Blood magic", "", EnvironmentMystic, IndependenceSquare, TheUnnamable, NoMyth, 0, {Rivertown}, {}},
{"Blue Flu!", "", Headline, TheUnnamable, Woods, NoMyth, 0, {Jail}, {}},
{"Campus Security Increased!", "", Headline, TheUnnamable, Woods, NoMyth, 0, {MiskatonicUniversity, Library, ScienceBuilding, AdministrationBuilding}, {}, &mythos::removemonstersnoterror},
{"Church Group Reclaims Southside!", "", Headline, BlackCave, HibbsRoadhouse, NoMyth, 0, {SouthChurch, SouthSide}, {}, &mythos::removemonstersnoterror},
{"Church Group Reclaims Southside!", "", Headline, BlackCave, HibbsRoadhouse, NoMyth, 0, {SouthChurch}, {}, &mythos::removemonstersnoterror},
};

void shuffle_myth_deck() {
	myth_deck.clear();
	for(auto& e : myth_data)
		myth_deck.add(&e);
	zshuffle(myth_deck.data, myth_deck.count);
}

static mythos* drawcard() {
	if(!myth_deck.count)
		return 0;
	auto i = myth_deck.data[0];
	if(myth_deck.count)
		memmove(myth_deck.data, myth_deck.data + 1, myth_deck.count - 1);
	myth_deck.count--;
	return i;
}

static void discard(mythos* p) {
	myth_deck.add(p);
}

bool game_info::is(myth_s value) const {
	if(!current_myth)
		return false;
	return current_myth->effect == value;
}

void game_info::mything() {
	auto p = drawcard();
	if(p->gate)
		opengate(p->gate);
}