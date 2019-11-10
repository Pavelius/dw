#include "main.h"

using namespace game;

steading			steadings[64];
static const char*	text_golds[] = {"�������", "�������", "�������"};

steading::steading(steading_type_s type) {
	create(type);
}

steading::steading() {
}

void steading::clear() {
	memset(this, 0, sizeof(*this));
}

static god_s getrandomgod() {
	return (god_s)(rand() % (Tempus + 1));
}

void steading::correct() {
	if(prosperty < Dirt)
		prosperty = Dirt;
	if(prosperty > Rich)
		prosperty = Rich;
	if(population < Exodus)
		population = Exodus;
	if(population >= Booming)
		population = Booming;
}

void steading::addfeature() {
	switch(type) {
	case Village:
		switch(rand() % 6) {
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
		switch(rand() % 6) {
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
		switch(rand() % 6) {
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
			need.clear();
			break;
		case 5:
			defence = (defence_s)(defence + 1);
			setenmity();
			break;
		}
		break;
	}
}

void steading::addproblem() {
	switch(type) {
	case Village:
		switch(rand() % 6) {
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
		switch(rand() % 6) {
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
		switch(rand() % 6) {
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
		switch(rand() % 6) {
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

void steading::create(steading_type_s type) {
	clear();
	setrandomname();
	// Set basic values
	this->type = type;
	habbitants = Human;
	population = bsmeta<steading_typei>::elements[type].population;
	prosperty = bsmeta<steading_typei>::elements[type].prosperty;
	defence = bsmeta<steading_typei>::elements[type].defence;
	switch(type) {
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

void steading::set(steading* owner) {
	oath = owner;
	switch(type) {
	case Village:
		break;
	}
}

void steading::lookaround(stringbuilder& sb) {
	//char tem2[260]; grammar::of(tem2, zendof(tem2), steading_type_data[type].name); szlower(tem2, 1);
	char temp[260]; stringbuilder sbn(temp);
	sb.add("�� ���������� � %-2 %1.", getname(sbn), "������");
	//sb.add(bsdata::gets(prosperty_type, prosperty, "text"));
	//logs::add(bsdata::gets(population_type, population, "text"));
	if(habbitants != Human)
		sb.add("����� ����, ���� �� ��������� ����� ���� %1���.", getstr(habbitants));
}

//void steading::getmarket(resource_a& result) {
//	result = resources;
//	result.initialize();
//	unsigned max_count = 2;
//	if(type == City)
//		max_count = 4;
//	else if(type == Town)
//		max_count = 3;
//	for(auto i = Foods; i <= Species && result.count < max_count; i = (resource_s)(i + 1)) {
//		if(result.is(i))
//			continue;
//		result.add(i);
//	}
//	if(defence >= Garrison) {
//		if(!result.is(Weapons))
//			result.add(Weapons);
//	}
//}

static unsigned add_items(item* pb, item* pe, resource_s type, prosperty_s prosperty) {
	auto p = pb;
	for(auto i = RaggedBow; i < SilverCoins; i = (item_s)(i + 1)) {
		item it(i);
		if(it.getprosperty() > prosperty)
			continue;
		if(p < pe)
			*p++ = it;
	}
	return p - pb;
}

void hero::supply(item* source, unsigned count) {
	while(true) {
		char temp[260];
		auto cup = getcoins();
		for(unsigned i = 0; i < count; i++) {
			auto cost = source[i].getcost();
			if(cost > cup)
				continue;
			stringbuilder sbn(temp); source[i].getname(sbn, true);
			an.add(tid(Actions, i), "%1. ���� [%2i] %3.", sbn.begin(), cost, maptbl(text_golds, cost));
		}
		if(!an) {
			sb.add(" - � �������, �� � ���� ��� �������, ������� ��� �������� ��� ������� �� ������ ���� ��������� - ������ �������� ��������.");
			logs::next();
			return;
		}
		an.sort();
		an.add(tid(GoBack), "������ �� ����");
		tid id = an.choose(true, true, "��� �� ������ (���� %1i �����)?", getcoins());
		if(id.type == DungeonMoves) {
			switch(id.value) {
			case GoBack: return;
			}
		} else if(id.type == Actions) {
			auto& it = source[id.value];
			auto cost = it.getcost();
			stringbuilder sbn(temp); it.getname(sbn, false);
			sb.add(" - �� ������ ������ %1 �� [%2i] �����? - ������� �������� ��������.", sbn.begin(), cost);
			if(logs::yesno()) {
				addcoins(-cost);
				pickup(it);
			}
		}
	}
}

static const char* shop_data[] = {
	"���",
	"������������",
	"����������",
	"������ � ���������",
	"������",
	"����������� ������"
};

enum weapon_type_s { WeaponMelee, RangeWeapon, WeaponArmor };

static weapon_type_s gettype(item it) {
	if((it.is(Near) || it.is(Far) || it.isammo()) && !it.is(Thrown))
		return RangeWeapon;
	if(it.isarmor() || it.isshield())
		return WeaponArmor;
	return WeaponMelee;
}

static bool is(adat<item>& source, weapon_type_s type) {
	for(auto& it : source) {
		if(gettype(it) == type)
			return true;
	}
	return false;
}

static bool select(adat<item>& result, adat<item>& source, weapon_type_s type) {
	for(auto& it : source) {
		if(gettype(it) != type)
			continue;
		result.add(it);
	}
	return result.count != 0;
}

static void supply(adat<item>& source) {
	adat<resource_s> resources; resources.clear();
	for(auto& it : source) {
		auto r = it.getresource();
		if(r >= Clues)
			continue;
		if(resources.indexof(r) == -1)
			resources.add(r);
	}
	if(!source.count)
		return;
	if(source.count < 10 || resources.count == 1) {
		passtime(Duration10Minute);
		sb.add("�� �������� ������������ ������� � ���������.");
		hero::supply(source.data, source.count);
	} else {
		for(auto e : resources)
			an.add(e, "�������� ������� %1", shop_data[e]);
		auto resource = (resource_s)an.choose(true, true, "� ������ ���� ��������� ���������. ���� ������ �� ������ �����������?");
		while(true) {
			adat<item> filter; filter.clear();
			for(auto& e : source) {
				if(e.getresource() == resource)
					filter.add(e);
			}
			passtime(Duration10Minute);
			sb.add("�� �������� ������� %1.", shop_data[resource]);
			if(resource != Weapons) {
				hero::supply(filter.data, filter.count);
				break;
			} else {
				sb.add("\n- ��� �� ������ ����������? - ������� ������� �������� ��������.");
				if(is(source, WeaponMelee))
					an.add(WeaponMelee, "- ��� ���������� ������ �������� ���.");
				if(is(source, RangeWeapon))
					an.add(RangeWeapon, "- ��� ���������� ������������� ������.");
				if(is(source, WeaponArmor))
					an.add(WeaponArmor, "- ����� ��� ����.");
				an.add(1000, "- ������ �� ����. ������� ����� �� ������.");
				auto id = an.choose();
				if(id == 1000)
					break;
				adat<item> weapon_filter; weapon_filter.clear();
				select(weapon_filter, filter, (weapon_type_s)id);
				hero::supply(weapon_filter.data, weapon_filter.count);
			}
		}
	}
}

static void visit_power(steading& e) {
	sb.add("� ����� ������ ��� �� ������� ������.");
}

void steading::adventure() {
	adat<item> market; market.clear();
	market.count += add_items(market.data, zendof(market.data), Weapons, prosperty);
	while(true) {
		lookaround(sb);
		if(market.count)
			an.add(1, "����������� �� ���������");
		an.add(2, "�������� ������� ������");
		an.add(3, "���������� ���������� � �����������");
		an.add(100, "�������� ���������");
		tid result = an.choose(true, true, "��� ������ ������?");
		switch(result) {
		case 1: supply(market); break;
		case 2: visit_power(*this); break;
		case 100: return;
		}
	}
}

bool steading::isoath(const steading* suzern) const {
	if(suzern == this)
		return false;
	for(auto p = oath; p; p = p->oath) {
		if(p == suzern)
			return true;
	}
	return false;
}

bool steading::isemnity(const steading* value) const {
	for(auto p : emnity) {
		if(p == value)
			return true;
	}
	return false;
}

bool steading::istrade(const steading* value) const {
	for(auto p : trade) {
		if(p == value)
			return true;
	}
	return false;
}

void steading::setoath() {
	steading* source[sizeof(steadings) / sizeof(steadings[0])];
	if(oath)
		return;
	auto ps = source;
	for(auto& e : steadings) {
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

void steading::setoathme() {
	steading* source[sizeof(steadings) / sizeof(steadings[0])];
	auto ps = source;
	for(auto& e : steadings) {
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

void steading::setenmity() {
	steading* source[sizeof(steadings) / sizeof(steadings[0])];
	auto ps = source;
	for(auto& e : steadings) {
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

void steading::settrade() {
	steading* source[sizeof(steadings) / sizeof(steadings[0])];
	auto ps = source;
	for(auto& e : steadings) {
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

void steading::setresource() {
	static resource_s r[] = {Foods, Tools, Weapons, Potions, Species, Gems};
	resources.add(maprnd(r));
}

void steading::createworld() {
	steading* source[sizeof(steadings) / sizeof(steadings[0])];
	auto ps = source;
	for(auto& e : steadings) {
		e.clear();
		*ps++ = &e;
	}
	zshuffle(source, sizeof(steadings) / sizeof(steadings[0]));
	int count_city = 6;
	int count_town = 12;
	int count_keep = 12;
	for(auto p : source) {
		if(count_city) {
			p->create(City);
			count_city--;
		} else if(count_town) {
			p->create(Town);
			count_town--;
		} else if(count_keep) {
			p->create(Town);
			count_keep--;
		} else
			p->create(Village);
	}
}