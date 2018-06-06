#include "main.h"

monster monster_data[128];

void monster::initialize() {
	auto index = 0;
	for(auto i = Byakhee; i <= Zombie; i = (card_s)(i+1)) {
		auto count = item::getcount(i);
		for(auto j = 0; j < count; j++) {
			monster_data[index] = i;
			monster_data[index].set(Cup);
			index++;
		}
	}
	zshuffle(monster_data, index);
}

monster* monster::getfromcup() {
	adat<monster*, 128> source; source.count = select(source.data, zendof(source.data), Cup);
	if(source.count)
		return source.data[rand() % source.count];
	return 0;
}

unsigned monster::select(monster** result, monster** result_maximum, location_s value) {
	auto p = result;
	for(auto& e : monster_data) {
		if(!e)
			continue;
		if(e.position != value)
			continue;
		if(p < result_maximum)
			*p++ = &e;
	}
	return p - result;
}

void monster::discard() {
	position = Cup;
	owner = 0;
}

void monster::trophy(hero* owner) {
	position = InvestigatorTrophy;
	this->owner = owner;
}

char hero::gettrophy() const {
	char result = 0;
	for(auto& e : monster_data) {
		if(!e)
			continue;
		if(e.gettrophy() != this)
			continue;
		result += e.get(Fight);
	}
	return result;
}