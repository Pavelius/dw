#include "main.h"

static deck decks[UniqueItem - Ally + 1];

void deck::add(card_s id) {
	if(id)
		adat::add(id);
}

card_s deck::draw() {
	if(!count)
		return NoItem;
	auto i = data[0];
	if(count)
		memmove(data, data + 1, count - 1);
	count--;
	return i;
}

card_s deck::draw(feature_s filter) {
	auto maximum = count;
	while(maximum-- > 0) {
		auto i = draw();
		if(item::is(i, filter))
			return i;
		add(i);
	}
	return NoItem;
}

card_s deck::drawb() {
	if(!count)
		return NoItem;
	count--;
	return data[count];
}

void deck::draw(deck& source, int count, feature_s filter) {
	for(auto i = 0; i < count; i++)
		add(source.draw(filter));
}

void deck::draw(deck& source, int count) {
	for(auto i = 0; i < count; i++)
		add(source.draw());
}

void deck::drawb(deck& source, int count) {
	for(auto i = 0; i < count; i++)
		add(source.drawb());
}

deck& deck::getdeck(stat_s id) {
	if(id >= Ally && id <= UniqueItem)
		return decks[id - Ally];
	return decks[0];
}

void deck::discard(card_s id) {
	getdeck(item::getgroup(id)).add(id);
}

void deck::initialize() {
	for(auto i = Ally; i <= UniqueItem; i = (stat_s)(i + 1))
		getdeck(i).create(i);
}