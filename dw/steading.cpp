#include "main.h"

using namespace game;

steading	steadings[64];

static struct resource_i
{
	const char*		id;
	const char*		name;
} resource_data[] = {
	{"Foods", "Еда"},
	{"Tools", "Инструменты"},
	{"Weapons", "Оружие"},
	{"Dress", "Одежда"},
	{"Potions", "Зелья"},
	{"Species", "Специи"},
	{"Gems", "Драгоценности"},
	{"Clues", "Улики"},
	//
	{"Wood", "Дерево"},
	{"Furs", "Меха"},
	{"Ore", "Руда"},
};
assert_enum(resource, Ore);
getstr_enum(resource);

static struct prosperty_i
{
	const char*		id;
	const char*		name;
	const char*		text;
} prosperty_data[] = {
	{"Dirt", "Трущебы", "Вокруг вас находились грязные и убогие лачуги, собранные из подручного хлама."},
	{"Poor", "Бедный", "В основном вы видели убогие лачуги, собранные из подручного материала, хотя изредка попадались крепкие дома."},
	{"Moderate", "Средний", "Вокруг были расположены акуратные дома, с ухоженными двориками."},
	{"Wealth", "Богатый", "Вокруг были расположены дома, некоторые из них были двухэтажными или богато украшенными."},
	{"Rich", "Шикарный", "В основном здесь были двухэтажные дома с богатой резьбой и сделаны из дорогого материала. Ухожанные дороги, наличие скамеек и вкусный запах еды говорили о высоком достатке обитателей."},
};
assert_enum(prosperty, Rich);
getstr_enum(prosperty);

static struct population_i
{
	const char*		id;
	const char*		name;
	const char*		text;
} population_data[] = {
	{"Exodus", "Заброшенный", "Большинство домов выглядели заброшеными и скорее всего в них никто не жил."},
	{"Shrinking", "Гинущий", "Многие дома были заброшены."},
	{"Steady", "Населенный", ""},
	{"Growing", "Растущий", "На улице было много народу."},
	{"Booming", "Переполненный", "Здесь было очень много народу. Множество палаток и тентов покрывали улицы - в них жили люди."},
};
assert_enum(population, Booming);
getstr_enum(population);

static struct steading_type_i
{
	const char*		id;
	const char*		name;
	prosperty_s		prosperty;
	population_s	population;
	defence_s		defence;
} steading_type_data[] = {
	{"Village", "Деревня", Poor, Steady, Militia},
	{"Town", "Город", Moderate, Steady, Watch},
	{"Keep", "Цитадель", Poor, Shrinking, Guard},
	{"City", "Мегаполис", Moderate, Steady, Guard},
};
assert_enum(steading_type, City);
getstr_enum(steading_type);

steading::steading(steading_type_s type)
{
	create(type);
}

steading::steading()
{
}

void steading::clear()
{
	memset(this, 0, sizeof(*this));
}

god_s getrandomgod()
{
	return (god_s)(rand() % (Tempos + 1));
}

void steading::correct()
{
	if(prosperty < Dirt)
		prosperty = Dirt;
	if(prosperty > Rich)
		prosperty = Rich;
	if(population < Exodus)
		population = Exodus;
	if(population >= Booming)
		population = Booming;
}

void steading::addfeature()
{
	switch(type)
	{
	case Village:
		switch(rand() % 6)
		{
		case 0:
			defence = (defence_s)(defence - 1);
			setsafe();
			break;
		case 1:
			population = (population_s)(population + 1);
			setresource();
			setenmity();
			break;
		case 2:
			defence = (defence_s)(defence + 1);
			setoathme();
			break;
		case 3:
			prosperty = (prosperty_s)(prosperty + 1);
			settrade();
			break;
		case 4:
			personage.create(Wizard);
			personage.level = xrand(3, 6);
			// Blight (arcane)
			break;
		case 5:
			sethistory();
			// Divine
			break;
		}
		break;
	case Town:
		switch(rand() % 6)
		{
		case 0:
			population = Booming;
			setlawless();
			break;
		case 1:
			setmarket();
			prosperty = (prosperty_s)(prosperty + 1);
			break;
		case 2:
			defence = (defence_s)(defence + 1);
			setoathme();
			break;
		case 3:
			// Power (Divine)
			break;
		case 4:
			// Craft
			setresource();
			break;
		case 5:
			defence = (defence_s)(defence + 1);
			break;
		}
		break;
	case Keep:
		switch(rand() % 6)
		{
		case 0:
			prosperty = (prosperty_s)(prosperty + 1);
			// Power (Political);
			break;
		case 1:
			defence = (defence_s)(defence + 1);
			personage.create(Fighter);
			personage.level = xrand(4, 8);
			break;
		case 2:
			prosperty = (prosperty_s)(prosperty + 1);
			setguild();
			break;
		case 3:
			// Arcane
			population = (population_s)(population - 1);
			break;
		case 4:
			need.count = 0;
			break;
		case 5:
			defence = (defence_s)(defence + 1);
			setenmity();
			break;
		}
		break;
	}
}

void steading::addproblem()
{
	switch(type)
	{
	case Village:
		switch(rand() % 6)
		{
		case 0:
			need.add(Foods);
			break;
		case 1:
			religions.add(getrandomgod());
			setenmity();
			break;
		case 2: // There is a war nearby
			population = (population_s)(population - 1);
			if(d100() < 30) // If they fight to the end
				prosperty = (prosperty_s)(prosperty - 1);
			if(d100() < 40) // If they lost
				defence = (defence_s)(defence - 1);
			break;
		case 3:
			blight.add(Goblin);
			need.add(Heroes);
			break;
		case 4:
			population = (population_s)(population + 1);
			setlawless();
			break;
		case 5:
			prosperty = (prosperty_s)(prosperty - 1);
			if(d100() < 50)
				habbitants = Dwarf;
			else
				habbitants = Elf;
			break;
		}
		break;
	case Town:
		switch(rand() % 6)
		{
		case 0:
			if(d100() < 30)
				need.add(Ore);
			else
				need.add(Wood);
			// Trade
			break;
		case 1:
			setoath();
			defence = (defence_s)(defence - 1);
			break;
		case 2:
			personage.create(Theif);
			personage.level = xrand(7, 10);
			personage.alignment = (alignment_s)xrand(Neutral, Evil);
			setenmity();
			break;
		case 3:
			// Exoitc
			setenmity();
			break;
		case 4:
			population = (population_s)(population - 1);
			break;
		case 5:
			population = (population_s)(population + 1);
			setlawless();
			break;
		}
		break;
	case Keep:
		switch(rand() % 6)
		{
		case 0:
			population = (population_s)(population - 1);
			setsafe();
			break;
		case 1:
			setenmity();
			break;
		case 2:
			setlawless();
			break;
		case 3:
			// Bilght (thread)
			break;
		case 4:
			sethistory();
			// Blight (spirits)
			break;
		case 5:
			// Need (Skilled workers)
			break;
		}
		break;
	case City:
		switch(rand() % 6)
		{
		case 0:
			population = (population_s)(population + 1);
			need.add(Foods);
			break;
		case 1:
			defence = (defence_s)(defence + 1);
			setenmity();
			break;
		case 2:
			defence = (defence_s)(defence - 1);
			// Power (Divine)
			break;
		case 3:
			defence = (defence_s)(defence - 1);
			population = (population_s)(population + 1);
			break;
		case 4:
			defence = (defence_s)(defence + 1);
			// Blight (supernatural)
			break;
		case 5:
			// Aracane
			personage.create(Wizard);
			personage.level = xrand(7, 10);
			// Blight (creatures)
			break;
		}
		break;
	}
}

void steading::create(steading_type_s type)
{
	clear();
	setrandomname();
	// Set basic values
	this->type = type;
	habbitants = Human;
	population = steading_type_data[type].population;
	prosperty = steading_type_data[type].prosperty;
	defence = steading_type_data[type].defence;
	switch(type)
	{
	case Village:
		setresource();
		break;
	case Town:
		settrade();
		settrade();
		break;
	case Keep:
		if(d100() < 30)
			need.add(Foods);
		else if(d100() < 40)
			need.add(Ore);
		else
			need.add(Weapons);
		settrade();
		setoath();
		break;
	case City:
		setmarket();
		setguild();
		break;
	}
	addfeature();
	addproblem();
}

void steading::set(steading* owner)
{
	oath = owner;
	switch(type)
	{
	case Village:
		break;
	}
}

void steading::lookaround()
{
	char temp[260];
	char tem2[260];
	logs::add("Вы находитесь в %2 %1.", getname(temp), grammar::of(tem2, steading_type_data[type].name));
	logs::add(prosperty_data[prosperty].text);
	logs::add(population_data[population].text);
	if(habbitants != Human)
		logs::add("Почти всех, кого вы встретили здесь были %1ами.", getstr(habbitants));
}

void steading::getmarket(resource_a& result)
{
	result = resources;
	result.initialize();
	unsigned max_count = 2;
	if(type == City)
		max_count = 4;
	else if(type == Town)
		max_count = 3;
	for(auto i = Foods; i <= Species && result.count < max_count; i = (resource_s)(i + 1))
	{
		if(result.is(i))
			continue;
		result.add(i);
	}
	if(defence >= Garrison)
	{
		if(!result.is(Weapons))
			result.add(Weapons);
	}
}

static void make_supply(adat<item, 128>& source)
{
	auto player = whodo(Charisma, 0, "Кто будет скупаться?");
	adat<resource_s, 15> resources; resources.initialize();
	for(auto& e : source)
	{
		if(resources.is(e.getresource()))
			continue;
		resources.add(e.getresource());
	}
	if(resources.count == 1 || source.count <= 8)
	{
		logs::add("%1 посетил%2 единственный магазин в городе.", player->getname(), player->getA());
		player->supply(source.data, source.count);
	}
	else
	{
		static const char* shop_data[] = {
			"еды",
			"инструментов",
			"оружейника",
			"портного",
			"Зельев и Элексиров",
			"специй",
			"драгоценных камней"
		};
		assert_enum(shop, Gems);
		for(auto e : resources)
			logs::add(e, "Посетить %1", shop_data[e]);
		auto resource = (resource_s)logs::input(true, false, "В городе было множество магазинов. Куда именно вы хотите отправиться?");
		adat<item, 128> filter; filter.initialize();
		for(auto& e : source)
		{
			if(e.getresource() == resource)
				filter.add(e);
		}
		logs::add("%1 посетил%2 магазин %3", player->getname(), player->getA(), shop_data[resource]);
		player->supply(filter.data, filter.count);
	}
}

void steading::adventure()
{
	resource_a market_resource; getmarket(market_resource);
	adat<item, 128>	market;
	market.count = select(market.data, sizeof(market.data) / sizeof(market.data[0]), prosperty, &market_resource);
	lookaround();
	if(market.count)
		logs::add(Supply, "Отправиться по магазинам");
	//if(prosperty >= Moderate)
	//	logs::add(SupplySell, "Попытается что-то продать");
	logs::add(Parley, "Попытается поговорить с окружающими");
	auto result = logs::input(true, false, "Что будете делать?");
	switch(result)
	{
	case Supply:
		make_supply(market);
		//players[i].supply(market.data, market.count);
		break;
	//case SupplySell:
	//	//sell(prosperty);
	//	break;
	}
}

bool steading::isoath(const steading* suzern) const
{
	if(suzern == this)
		return false;
	for(auto p = oath; p; p = p->oath)
	{
		if(p == suzern)
			return true;
	}
	return false;
}

bool steading::isemnity(const steading* value) const
{
	for(auto p : emnity)
	{
		if(p == value)
			return true;
	}
	return false;
}

bool steading::istrade(const steading* value) const
{
	for(auto p : trade)
	{
		if(p == value)
			return true;
	}
	return false;
}

void steading::setoath()
{
	steading* source[sizeof(steadings) / sizeof(steadings[0])];
	if(oath)
		return;
	auto ps = source;
	for(auto& e : steadings)
	{
		if(&e == this)
			continue;
		if(e.isoath(this))
			continue;
		*ps++ = &e;
	}
	auto count = ps - source;
	if(count)
		oath = source[rand() % count];
}

void steading::setoathme()
{
	steading* source[sizeof(steadings) / sizeof(steadings[0])];
	auto ps = source;
	for(auto& e : steadings)
	{
		if(&e == this)
			continue;
		if(e.oath && e.isoath(this))
			continue;
		*ps++ = &e;
	}
	auto count = ps - source;
	if(count)
		source[rand() % count]->oath = this;
}

void steading::setenmity()
{
	steading* source[sizeof(steadings) / sizeof(steadings[0])];
	auto ps = source;
	for(auto& e : steadings)
	{
		if(&e == this)
			continue;
		if(isemnity(&e) || e.isemnity(this))
			continue;
		if(isoath(&e) || e.isoath(this))
			continue;
		*ps++ = &e;
	}
	auto count = ps - source;
	if(count)
		emnity.add(source[rand() % count]);
}

void steading::settrade()
{
	steading* source[sizeof(steadings) / sizeof(steadings[0])];
	auto ps = source;
	for(auto& e : steadings)
	{
		if(&e == this)
			continue;
		if(isemnity(&e) || e.isemnity(this))
			continue;
		if(istrade(&e))
			continue;
		*ps++ = &e;
	}
	auto count = ps - source;
	if(count)
		emnity.add(source[rand() % count]);
}

void steading::setresource()
{
	item items[2];
	resource_s source[32];
	auto ps = source;
	for(auto e = Foods; e < Clues; e = (resource_s)(e + 1))
	{
		if(resources.is(e))
			continue;
		if(!select(items, 1, prosperty))
			continue;
		*ps++ = e;
	}
	auto count = ps - source;
	if(count)
		resources.add(source[rand() % count]);
}

int	steading::select(item* source, unsigned maximum, prosperty_s prosperty, resource_a* resources)
{
	auto pb = source;
	auto pe = source + maximum;
	for(auto i = RaggedBow; i < SilverCoins; i = (item_s)(i + 1))
	{
		if(pb >= pe)
			break;
		item it(i);
		if(resources && !resources->is(it.getresource()))
			continue;
		if(it.getprosperty() > prosperty)
			continue;
		*pb++ = it;
	}
	return pb - source;
}

void steading::createworld()
{
	steading* source[sizeof(steadings) / sizeof(steadings[0])];
	auto ps = source;
	for(auto& e : steadings)
	{
		e.clear();
		*ps++ = &e;
	}
	zshuffle(source, sizeof(steadings) / sizeof(steadings[0]));
	int count_city = 6;
	int count_town = 12;
	int count_keep = 12;
	for(auto p : source)
	{
		if(count_city)
		{
			p->create(City);
			count_city--;
		}
		else if(count_town)
		{
			p->create(Town);
			count_town--;
		}
		else if(count_keep)
		{
			p->create(Town);
			count_keep--;
		}
		else
			p->create(Village);
	}
}