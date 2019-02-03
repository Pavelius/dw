#include "main.h"

using namespace game;

static const char* text_golds[] = {"золотых", "золотой", "золотых"};
static const char* text_hits[] = {"повреждений", "повреждение", "повреждени€", "повреждени€", "повреждени€", "повреждений"};
static char stats_modifiers[] = {-4,
-3, -3, -3, -2, -2, -1, -1, -1, 0, 0,
0, 0, 1, 1, 1, 2, 2, 3
};

static int party_coins;
hero players[8];

hero::hero() {
	clear();
}

void hero::clear() {
	memset(this, 0, sizeof(hero));
}

void hero::addcoins(int count, bool interactive) {
	party_coins += count;
	if(interactive && count)
		logs::add("ѕарти€ получила [%1i] монет.", count);
}

int hero::getcoins() {
	return party_coins;
}

bool hero::is(move_s value) const {
	return (moves[value / (sizeof(moves[0]) * 8)] & (1 << (value % (sizeof(moves[0]) * 8)))) != 0;
}

void hero::setdebilities(stat_s value, bool state) {
	if(state)
		debilities |= (1 << value);
	else
		debilities &= ~(1 << value);
}

void hero::set(move_s value, bool interactive) {
	moves[value / (sizeof(moves[0]) * 8)] |= 1 << (value % (sizeof(moves[0]) * 8));
	// —просим про знаковое оружие
	if(value == SignatureWeapon && !signature_weapon) {
		logs::add(SwordLong, getstr(SwordLong));
		logs::add(Warhammer, getstr(Warhammer));
		logs::add(Spear, getstr(Spear));
		signature_weapon.set((item_s)logs::input(interactive, true, "¬аше [знаковое оружие]:"));
		for(int count = 0; count < 2; count++) {
			for(auto e = Spiked; e <= WellCrafted; e = (tag_s)(e + 1)) {
				if(signature_weapon.is(e))
					continue;
				logs::add(e, getstr(e));
			}
			auto id = (tag_s)logs::input(interactive, true, "¬ыберите улучшени€ (%1i/2):", count + 1);
			signature_weapon.set(id);
			switch(id) {
			case Versatile:
				for(auto d = Hand; d <= Reach; d = (distance_s)(d + 1)) {
					if(signature_weapon.is(d))
						continue;
					logs::add(d, getstr(d));
				}
				signature_weapon.set((distance_s)logs::input(interactive, true, "Ќа какой дистанции?"));
				break;
			}
		}
		weapon = signature_weapon;
	}
}

bool hero::set(item value) {
	if(value.iscoins()) {
		addcoins(value.getuses());
		return true;
	}
	if(value.isarmor() && !armor) {
		armor = value;
		return true;
	}
	if(value.isweapon() && !weapon) {
		weapon = value;
		return true;
	}
	for(auto& e : gear) {
		if(e)
			continue;
		e = value;
		return true;
	}
	return false;
}

bool hero::isammo(item_s value) const {
	for(auto& e : gear) {
		if(e.isammo(value) && e.getuses())
			return true;
	}
	return false;
}

bool hero::isallow(tag_s id) const {
	for(auto& e : gear) {
		if(e.is(id) && e.getuses())
			return true;
	}
	return false;
}

bool hero::isallow(item_s id) const {
	for(auto& e : gear) {
		if(e.type == id)
			return true;
	}
	return false;
}

bool hero::use(tag_s id, bool interactive) {
	char temp[260];
	for(auto& e : gear) {
		if(e.is(id) && e.getuses()) {
			if(interactive) {
				stringbuilder sb(temp);
				e.getname(sb, false);
				act("%герой использовал%а %1.", temp);
			}
			e.use();
			return true;
		}
	}
	return false;
}

bool hero::use(item_s id, bool interactive) {
	for(auto& e : gear) {
		if(e.type == id) {
			e.clear();
			return true;
		}
	}
	return false;
}

bool hero::useammo(item_s id, bool run, bool interactive) {
	char temp[260];
	for(auto& e : gear) {
		if(e.isammo(id) && e.getuses()) {
			if(run) {
				if(interactive)
					act("%герой израсходовал%а %1.", e.getname(temp, zendof(temp), false));
				e.use();
			}
			return true;
		}
	}
	return false;
}

bool hero::isclumsy() const {
	if(armor && !is(Armored) && armor.is(Clumsy))
		return true;
	return false;
}

bool hero::remove(item it) {
	for(auto& e : gear) {
		if(memcmp(&e, &it, sizeof(item)) == 0) {
			e.clear();
			return true;
		}
	}
	return false;
}

int	hero::get(stat_s stat) const {
	auto result = stats_modifiers[stats[stat]];
	if(isdebilities(stat))
		result--;
	return result;
}

int	hero::get(forward_s id) const {
	return forward[id];
}

bool hero::isequipment() const {
	for(auto& e : gear) {
		if(e)
			return true;
	}
	return armor || weapon || shield;
}

char* hero::getequipment(char* result, const char* result_maximum, const char* title) const {
	bool description = false;
	result[0] = 0;
	if(!isequipment())
		return result;
	zcat(result, title);
	auto p = zend(result);
	if(armor) {
		if(p[0])
			zcat(p, ", ");
		armor.getname(zend(p), result_maximum, description);
	}
	if(weapon) {
		if(p[0])
			zcat(p, ", ");
		weapon.getname(zend(p), result_maximum, description);
	}
	if(shield) {
		if(p[0])
			zcat(p, ", ");
		shield.getname(zend(p), result_maximum, description);
	}
	for(auto& e : gear) {
		if(!e)
			continue;
		if(p[0])
			zcat(p, ", ");
		e.getname(zend(p), result_maximum, description);
	}
	zcat(p, ".");
	return result;
}

bool hero::iscombatable() const {
	return *this
		&& isalive()
		&& !is(SpellInvisibility);
}

bool hero::isalive() const {
	return hp > 0;
}

int hero::getharm() const {
	return getdamage().roll();
}

item* hero::getweapon(distance_s distance) {
	for(auto& e : gear) {
		if(!e)
			continue;
		if(!e.is(distance))
			continue;
		if(e.getammo())
			return &e;
	}
	return 0;
}

item* hero::getitem(item_s type) {
	for(auto& e : gear) {
		if(!e)
			continue;
		if(e.type == type)
			return &e;
	}
	return 0;
}

result_s hero::roll(int bonus, int* result, bool show_result) {
	char temp[64];
	int dr = 2 + (rand() % 6) + (rand() % 6);
	int tr = dr + bonus;
	szprints(temp, temp + sizeof(temp) - 1, "{%2i%+3i=%1i}", tr, dr, bonus);
	if(result)
		*result = tr;
	auto ds = Fail;
	if(tr >= 10)
		ds = Success;
	else if(tr >= 7)
		ds = PartialSuccess;
	switch(ds) {
	case Fail:
		experience++;
		if(show_result)
			logs::add("[-%1]", temp);
		break;
	case Success:
		if(show_result)
			logs::add("[+%1]", temp);
		break;
	default:
		if(show_result)
			logs::add(temp);
		break;
	}
	return ds;
}

int hero::addbonus(forward_s id) {
	auto i = get(id);
	set(id, 0);
	return i;
}

result_s hero::roll(move_s id) {
	auto bonus = get(getstat(id));
	switch(id) {
	case HackAndSlash:
	case Volley:
		if(is(SpellBless))
			bonus++;
		bonus += addbonus(CombatRoll);
		break;
	}
	bonus += addbonus(AnyRoll);
	if(bonus > 3)
		bonus = 3;
	else if(bonus < -3)
		bonus = -3;
	return roll(bonus, 0, true);
}

result_s hero::defydanger(stat_s stat) {
	auto bonus = get(stat);
	return roll(bonus);
}

result_s hero::spoutlore() {
	auto bonus = get(Intellegence);
	return roll(bonus);
}

result_s hero::discernrealities() {
	auto bonus = get(Wisdow);
	return roll(bonus);
}

result_s hero::parley() {
	auto bonus = get(Charisma);
	return roll(bonus);
}

int hero::whatdo(bool clear_text) {
	if(!logs::getcount())
		return 0;
	return logs::input(true, clear_text, "„то будет делать [%1]?", getname());
}

int hero::getarmor() const {
	auto result = armor.getarmor();
	if(is(ArcaneWard) && getpreparedlevels() > 0)
		result += 2;
	return 0;
}

int hero::getload() const {
	auto result = getload(type);
	result += get(Strenght);
	return result;
}

int hero::getmaxhits() const {
	auto result = gethits(type);
	result += stats[Constitution];
	return result;
}

dice hero::getdamage() const {
	dice result;
	result.c = 1;
	result.d = getdamage(type);
	result.b = (char)weapon.getdamage();
	result.m = 0;
	return result;
}

bool hero::prepareweapon(monster& enemy) {
	char temp[260];
	if(weapon.is(enemy.distance))
		return true;
	auto p = getweapon(enemy.distance);
	if(p) {
		iswap(weapon, *p);
		logs::add("%1 достал%2 %3.", getname(), getA(), weapon.getname(temp, zendof(temp), false));
		return true;
	}
	return false;
}

void hero::inflictharm(monster& enemy, int count) {
	if(count <= 0)
		return;
	auto armor = enemy.getarmor();
	count -= armor;
	if(count <= 0) {
		logs::add("”дар не смог пробить броню.");
		return;
	}
	enemy.hp -= count;
	if(enemy.hp > 0) {
		enemy.act("%герой получил%а [%1i] урона.", count);
		return;
	}
	enemy.act("%герой получил%а [%1i] урона и упал%а.", count);
	enemy.hp = 0;
	switch(--enemy.count) {
	case 0: return;
	case 1: logs::add("ќсталс€ еще [один]."); break;
	case 2: logs::add("ќсталось еще [двое]."); break;
	case 3: logs::add("ќсталось еще [трое]."); break;
	default: logs::add("ќсталось еще [%1i].", enemy.count); break;
	}
	enemy.hp = enemy.getmaxhits();
}

void hero::sufferharm(int count, bool ignore_armor) {
	if(!ignore_armor) {
		auto armor = getarmor();
		count -= armor;
		if(count <= 0) {
			logs::add("Ѕрон€ спасла вас от удара.");
			return;
		}
	}
	if(is(SpellDefense) && getongoing()) {
		for(unsigned i = 0; i < spell_state_data.count; i++) {
			logs::add(i, "%1 снизит урон на %2i.",
				getstr(spell_state_data.data[i].spell),
				getlevel(spell_state_data.data[i].spell));
		}
		logs::add(1000, "Ќехочу убирать никаких заклинаний.");
		auto i = logs::input(true, false, "[%1] получит [2i] урона, но может пожертвовать действующим заклинанием, чтобы снизить урон.",
			getname(), count);
		if(i != 1000) {
			count -= getlevel(spell_state_data.data[i].spell);
			spell_state_data.data[i].clear();
		}
	}
	if(count <= 0)
		return;
	hp -= count;
	if(hp > 0)
		logs::add("%2 получил%3 [%1i] урона.", count, getname(), getA());
	else {
		logs::add("%2 получил%3 [%1i] урона и упал%3.", count, getname(), getA());
		if(isgameover())
			logs::next();
	}
}

result_s hero::sell(prosperty_s prosperty) {
	char temp[260];
	while(true) {
		for(auto i = 0; i < sizeof(gear) / sizeof(gear[0]); i++) {
			auto pi = gear + i;
			if(!*pi)
				continue;
			if(pi->getprosperty() > prosperty)
				continue;
			auto cost = pi->getsellcost();
			if(cost <= 0)
				continue;
			logs::add(i, "%1 за [%2i] %3.",
				pi->getname(temp, zendof(temp), true),
				pi->getsellcost(),
				maptbl(text_golds, cost));
		}
		if(logs::getcount() <= 0) {
			logs::add(" - я сожелею, но у вас нет товаров, которые € могу позволить себе купить - сказал владелец магазина.");
			logs::next();
			return Success;
		}
		logs::sort();
		logs::add(500, "Ќичего не продавать");
		auto id = logs::input(true, true, "„то хочет продать [%1]?", getname());
		if(id == 500)
			return Success;
		auto cost = gear[id].getsellcost();
		logs::add(" - ¬ы хотите продать %1? - спросил владелец магазина - я готов дам за него [%2i] монет.",
			gear[id].getname(temp, zendof(temp), false),
			cost);
		if(logs::yesno()) {
			gear[id].clear();
			addcoins(-cost);
		}
	}
	return Success;
}

int hero::getspellpenalty() const {
	return getongoing() + castpenalty;
}

void hero::healharm(int count) {
	auto mhp = getmaxhits();
	if(hp + count > mhp)
		count = mhp - hp;
	if(count == 0)
		return;
	hp += count;
	act("%герой востановил%а %1i %2.", count, maptbl(text_hits, count));
}

void hero::hunger() {
	logs::add("%1 голодает.", getname());
	sufferharm(xrand(1, 6));
}

void hero::apply(lootinfo& loot) {
	if(loot.coins)
		addcoins(loot.coins);
	for(auto e : loot.items)
		set(e);
}

int	hero::getencumbrance() const {
	auto result = weapon.getweight();
	result += armor.getweight();
	result += shield.getweight();
	for(auto& e : gear)
		result += e.getweight();
	return result;
}

void hero::set(forward_s id, char value) {
	forward[id] = value;
}

bool hero::isallow(tid id) const {
	switch(id.type) {
	case Spells: return isprepared((spell_s)id.value);
	case Moves: return is((move_s)id.value);
	case Items: return isallow((item_s)id.value);
	case ItemTags: return isallow((tag_s)id.value);
	case Alignments: return type == (alignment_s)id.value;
	case Classes: return type == (class_s)id.value;
		//case Actions: return type == (action_s)id.value;
	default: return true;
	}
}

void hero::act(const char* format, ...) const {
	logs::printer driver(getname(), gender);
	logs::addv(driver, format, xva_start(format));
}

void hero::say(const char* format, ...) const {
	logs::printer driver(getname(), gender);
	logs::add("\n");
	logs::addv(driver, format, xva_start(format));
	logs::add("\n");
}