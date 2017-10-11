#include "main.h"

static struct item_i
{
	const char*			name[2];
	int					cost;
	unsigned char		weight;
	prosperty_s			prosperty;
	resource_s			resource;
	adat<tag_s, 4>		tags;
	adat<distance_s, 2>	distance;
	unsigned char		uses;
	unsigned char		damage;
	unsigned char		armor;
	unsigned char		piercing;
	bool is(distance_s value) const
	{
		for(auto& e : distance)
		{
			if(value == e)
				return true;
		}
		return false;
	}
	bool is(tag_s value) const
	{
		for(auto& e : tags)
		{
			if(value == e)
				return true;
		}
		return false;
	}
} item_data[] = {
	{{"Empthy", "Пусто"}},
	// Оружие
	{{"Ragged bow", "Потрепанный лук"}, 15, 2, Dirt, Weapons, {}, {Near}},
	{{"Fine bow", "Хороший лук"}, 60, 2, Wealthy, Weapons, {}, {{Near, Far}, 2}},
	{{"Hunter's bow", "Охотничий лук"}, 100, 1, Wealthy, Weapons, {}, {{Near, Far}, 2}},
	{{"Crossbow", "Арбалет"}, 35, 3, Rich, Weapons, {{Reloaded}, 1}, {{Near}, 1}, 0, 1},
	{{"Bundle of Arrows", "Стрелы"}, 1, 1, Dirt, Weapons, {{Ammo}, 1}, {}, 3},
	{{"Elven arrows", "Эльфийские стрелы"}, 20, 1, Moderate, Weapons, {{Ammo}, 1}, {}, 4},
	{{"Club", "Дубинка"}, 1, 2, Dirt, Weapons, {}, {{Close}, 1}},
	{{"Staff", "Посох"}, 1, 1, Poor, Weapons, {{TwoHanded}, 1}, {{Close}, 1}},
	{{"Knife", "Нож"}, 2, 1, Dirt, Weapons, {}, {{Hand}, 1}},
	{{"Throwing Dagger", "Метательный нож"}, 2, 0, Moderate, Weapons, {{Thrown}, 1}, {{Near}, 1}},
	{{"Short sword", "Короткий меч"}, 8, 1, Moderate, Weapons, {}, {{Close}, 1}},
	{{"Mace", "Булава"}, 8, 1, Poor, Weapons, {}, {{Close}, 1}},
	{{"Warhammer", "Молот"}, 8, 1, Moderate, Weapons, {}, {{Close}, 1}},
	{{"Spear", "Копье"}, 5, 1, Poor, Weapons, {{Thrown}, 1}, {{Reach, Near}, 2}},
	{{"Long sword", "Длинный меч"}, 15, 2, Wealthy, Weapons, {}, {{Close}, 1}, 0, 1},
	{{"Halberd", "Алебарда"}, 9, 2, Rich, Weapons, {{TwoHanded}, 1}, {{Reach}, 1}, 0, 1},
	{{"Rapier", "Рапира"}, 25, 1, Wealthy, Weapons, {{Precise}, 1}, {{Close}, 1}},
	{{"Dueling Rapier", "Рапира дулянта"}, 50, 2, Rich, Weapons, {{Precise}, 1}, {{Close}, 1}, 0, 0, 0, 1},
	//
	{{"Fine Clothing", "Роскошная одежда"}, 10, 1, Wealthy, Dress, {}, {}},
	{{"Leather", "Кожанная броня"}, 10, 1, Poor, Dress, {}, {}, 0, 0, 1},
	{{"Chainmail", "Кольчуга"}, 10, 1, Moderate, Dress, {}, {}, 0, 0, 1},
	{{"Scalemail", "Чешуйчатый доспех"}, 50, 3, Wealthy, Dress, {{Clumsy}, 1}, {}, 0, 0, 2},
	{{"Plate", "Латный доспех"}, 350, 4, Rich, Dress, {{Clumsy}, 1}, {}, 0, 0, 3},
	{{"Shield", "Щит"}, 15, 2, Poor, Weapons, {}, {}, 0, 0, 1},
	//
	{{"Adventuring Gear", "Снаряжение для приключений"}, 20, 1, Poor, Tools, {}, {}, 5},
	{{"Bandages", "Бинты"}, 5, 0, Poor, Tools, {{Slow}, 1}, {}, 3},
	{{"Herbs", "Травы и припарки"}, 10, 1, Moderate, Species, {{Slow}, 1}, {}, 2},
	{{"Healing Potion", "Лечебное зелье"}, 50, 0, Wealthy, Potions},
	{{"Keg of Dwarven Stout", "Боченок Дварфийского Алкоголя"}, 10, 4, Rich, Species},
	{{"Bag of Books", "Сумка с книгами"}, 10, 2, Wealthy, Tools, {}, {}, 5},
	{{"Antitoxin", "Антитоксин"}, 10, 0, Rich, Potions},
	//
	{{"Dungeon Ration", "Сухпаек"}, 3, 1, Dirt, Foods, {{Ration}, 1}, {}, 5},
	{{"Personal Feast", "Шикарная еда"}, 10, 1, Wealthy, Foods, {{Ration}, 1}, {}, 1},
	{{"Dwarven Hardtack", "Сухари дварфов"}, 3, 1, Moderate, Foods, {{Ration}, 1}, {}, 7},
	{{"Elven Bread", "Эльфийский хлеб"}, 10, 1, Wealthy, Foods, {{Ration}, 1}, {}, 7},
	{{"Halfling Pipeleaf", "Пирог хоббитов"}, 5, 0, Rich, Foods, {}, {}, 6},
	//
	{{"Mandoline", "Мандолина"}, 40, 0, Rich, Tools},
	{{"Lute", "Лютня"}, 40, 0, Rich, Tools},
	{{"Pipes", "Свирель"}, 40, 0, Rich, Tools},
	//
	{{"Holy Symbol", "Святой символ"}, 5, 0, Wealthy, Tools},
	{{"Spell Book", "Книга заклинаний"}, 5, 0, Wealthy, Tools},
	//
	{{"Bloodstone", "Кроваый камень"}, 5, 0, Moderate, Gems},
	{{"Chrysoprase", "Хризопраз"}, 5, 0, Moderate, Gems},
	{{"Iolite", "Иолит"}, 5, 0, Moderate, Gems},
	{{"Jasper", "Джаспер"}, 5, 0, Moderate, Gems},
	{{"Moonstone", "Лунный камень"}, 5, 0, Moderate, Gems},
	{{"Onyx", "Оникс"}, 5, 0, Moderate, Gems},
	// Улики
	{{"Map", "Карта"}, 5, 0, Moderate, Clues},
	{{"Note", "Заметки"}, 5, 0, Moderate, Clues},
	{{"Journal", "Дневник"}, 5, 0, Moderate, Clues},
	// Драгоценности
	{{"Alexandrite", "Александрит"}, 5, 0, Rich, Gems},
	{{"Aquamarine", "Аквамарин"}, 5, 0, Rich, Gems},
	{{"Black Pearl", "Черная жемчужина"}, 5, 0, Rich, Gems},
	{{"Topaz", "Топаз"}, 5, 0, Rich, Gems},
	//
	{{"Poison", "Яд"}, 5, 0, Wealthy, Potions},
	//
	{{"Coin", "Монета"}, 5, 0, Dirt, Gems},
};
assert_enum(item, Coin);
getstr_enum(item);

struct tag_i
{
	const char*			name[2];
} tag_data[] = {
	{{"ammo", "аммуниция"}},
	{{"awkward", "опасное"}},
	{{"clumsy", "неуклюжее"}},
	{{"messy", "кровавое"}},
	{{"ration", "паек"}},
	{{"reloaded", "перезарядка"}},
	{{"precise", "точное"}},
	{{"slow", "медленно"}},
	{{"thrown", "метательное"}},
	{{"two-handed", "двуручное"}},
};
assert_enum(tag, TwoHanded);
template<> const char* getstr<tag_s>(tag_s value)
{
	return tag_data[value].name[1];
}

template<> const char* getstr<enchantment_s>(enchantment_s value)
{
	static const char* info[][2] = {
		{"spiked", "шипастое"},
		{"sharp", "острое"},
		{"perfectly weighted", "отлично сбалансированное"},
		{"serrated edge", "зазубренное"},
		{"glows", "светится"},
		{"huge", "огромное"},
		{"versatile", "разностороннее"},
		{"well crafted", "отлично сделанное"},
	};
	static_assert((sizeof(info) / sizeof(info[0])) == (WellCrafted + 1), "Item Enchantments count invalid");
	return info[value][1];
}

template<> const char* getstr<distance_s>(distance_s value)
{
	static const char* info[][2] = {
		{"hand", "рука"},
		{"close", "взмах меча"},
		{"reach", "удар копья"},
		{"near", "близко"},
		{"far", "далеко"},
	};
	static_assert((sizeof(info) / sizeof(info[0])) == (Far + 1), "Item Tags count invalid");
	return info[value][1];
}

item::item()
{
	clear();
}

item::item(item_s type)
{
	set(type);
}

void item::clear()
{
	memset(this, 0, sizeof(*this));
}

int item::getmaxuses() const
{
	return item_data[type].uses;
}

int item::getdamage() const
{
	auto r = item_data[type].damage;
	if(is(Spiked))
		r++;
	if(is(SerratedEdges))
		r++;
	return r;
}

int item::getweight() const
{
	int r = item_data[type].weight;
	if(is(Spiked))
		r++;
	if(is(WellCrafted))
		r--;
	return imax(r, 0);
}

int item::getarmor() const
{
	return item_data[type].armor;
}

int item::getcost() const
{
	return item_data[type].cost;
}

int item::getsellcost(int charisma) const
{
	return item_data[type].cost/2;
}

bool item::is(tag_s value) const
{
	return tags.is(value);
}

bool item::is(enchantment_s value) const
{
	return enchant.is(value);
}

bool item::is(distance_s value) const
{
	return distance.is(value);
}

void item::set(item_s value)
{
	clear();
	type = value;
	uses = item_data[type].uses;
	auto& e = item_data[value];
	for(auto v : e.distance)
		set(v);
	for(auto v : e.tags)
		set(v);
}

void item::set(enchantment_s value)
{
	enchant.set(value);
}

void item::set(distance_s value)
{
	distance.set(value);
}

void item::set(tag_s value)
{
	tags.set(value);
}

bool item::use()
{
	if(!uses)
		return false;
	if((--uses) == 0)
		type = NoItem;
	return true;
}

char* item::getname(char* result, bool description, int cost) const
{
	zcpy(result, getstr(type));
	if(description)
		getdescription(result, cost);
	return result;
}

bool item::iscoins() const
{
	return type == Coin;
}

bool item::isarmor() const
{
	return type >= FineClothing && type <= PlateMail;
}

bool item::isweapon() const
{
	return type >= RaggedBow && type <= DuelingRapier;
}

bool item::isshield() const
{
	return type == Shield;
}

bool item::isgems() const
{
	return (type >= Bloodstone && type <= Onyx)
		|| (type >= Alexandrite && type <= Topaz);
}

bool item::isclumsy() const
{
	return is(Clumsy);
}

bool item::isprecise() const
{
	return is(Precise) || is(PerfectlyWeighted);
}

int item::getpiercing() const
{
	auto r = item_data[type].piercing;
	if(is(Sharp))
		r += 2;
	return r;
}

static char* addsep(char* result)
{
	if(result[0])
		zcat(result, ", ");
	return zend(result);
}

static void addtag(char* result, distance_s value)
{
	zcat(addsep(result), getstr(value));
}

static void addtag(char* result, tag_s value)
{
	if(value)
		zcat(addsep(result), getstr(value));
}

static void addtag(char* result, const char* name, int count, bool plus_minus = false, bool test_zero = true)
{
	if(test_zero && !count)
		return;
	if(plus_minus)
		szprint(addsep(result), "%1%+2i", name, count);
	else
		szprint(addsep(result), "%2i %1", name, count);
}

char* item::getdescription(char* result, int cost) const
{
	zcat(result, " (");
	auto p = zend(result);
	for(auto t = Awkward; t <= TwoHanded; t = (tag_s)(t + 1))
	{
		if(is(t))
			addtag(p, t);
	}
	addtag(p, "броня", getarmor());
	addtag(p, "пробивание", getpiercing());
	if(isweapon())
	{
		for(auto d = Hand; d <= Far; d = (distance_s)(d + 1))
		{
			if(is(d))
				addtag(p, d);
		}
	}
	if(getmaxuses())
	{
		if(is(Ammo))
			addtag(p, "боезапас", uses);
		else
			addtag(p, "использований", uses);
	}
	addtag(p, "урон", getdamage(), true);
	addtag(p, "вес", getweight(), false, false);
	if(cost)
	{
		switch(cost)
		{
		case 1:
			addtag(p, "цена", getcost());
			break;
		case 2:
			addtag(p, "цена продажи", getsellcost());
			break;
		}
	}
	zcat(result, ")");
	return result;
}

prosperty_s	item::getprosperty() const
{
	int result = item_data[type].prosperty;
	if(enchant)
		result++;
	if(result < Dirt)
		result = Dirt;
	if(result > Rich)
		result = Rich;
	return (prosperty_s)result;
}

resource_s item::getresource() const
{
	return item_data[type].resource;
}