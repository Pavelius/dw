#include "main.h"

using namespace game;

DECLDATA(hero, 4);

static const char* text_golds[] = {"золотых", "золотой", "золотых"};
static const char* text_hits[] = {"повреждений", "повреждение", "повреждени€", "повреждени€", "повреждени€", "повреждений"};
static char stats_modifiers[] = {-4,
-3, -3, -3, -2, -2, -1, -1, -1, 0, 0,
0, 0, 1, 1, 1, 2, 2, 3
};

static int party_coins;

hero::hero() {
	clear();
}

void hero::clear() {
	memset(this, 0, sizeof(hero));
}

const classi& hero::getclass() const {
	return bsmeta<classi>::elements[subtype];
}

void hero::addcoins(int count, bool interactive) {
	party_coins += count;
	if(interactive && count)
		sb.add("ѕарти€ получила [%1i] монет.", count);
}

int hero::getcoins() {
	return party_coins;
}

bool hero::is(move_s subtype) const {
	return (moves[subtype / (sizeof(moves[0]) * 8)] & (1 << (subtype % (sizeof(moves[0]) * 8)))) != 0;
}

void hero::setdebilities(stat_s subtype, bool state) {
	if(state)
		debilities |= (1 << subtype);
	else
		debilities &= ~(1 << subtype);
}

void hero::set(move_s subtype, bool interactive) {
	moves[subtype / (sizeof(moves[0]) * 8)] |= 1 << (subtype % (sizeof(moves[0]) * 8));
	// —просим про знаковое оружие
	if(subtype == SignatureWeapon && !signature_weapon) {
		an.add(SwordLong, getstr(SwordLong));
		an.add(Warhammer, getstr(Warhammer));
		an.add(Spear, getstr(Spear));
		signature_weapon.set((item_s)choose(interactive, true, "¬аше [знаковое оружие]:"));
		for(int count = 0; count < 2; count++) {
			for(auto e = Spiked; e <= WellCrafted; e = (tag_s)(e + 1)) {
				if(signature_weapon.is(e))
					continue;
				an.add(e, getstr(e));
			}
			auto id = (tag_s)choose(interactive, true, "¬ыберите улучшени€ (%1i/2):", count + 1);
			signature_weapon.set(id);
			switch(id) {
			case Versatile:
				for(auto d = Hand; d <= Reach; d = (distance_s)(d + 1)) {
					if(signature_weapon.is(d))
						continue;
					an.add(d, getstr(d));
				}
				signature_weapon.set((distance_s)choose(interactive, true, "Ќа какой дистанции?"));
				break;
			}
		}
		weapon = signature_weapon;
	}
}

bool hero::set(item subtype) {
	if(subtype.iscoins()) {
		addcoins(subtype.getuses());
		return true;
	}
	if(subtype.isarmor() && !armor) {
		armor = subtype;
		return true;
	}
	if(subtype.isweapon() && !weapon) {
		weapon = subtype;
		return true;
	}
	for(auto& e : gear) {
		if(e)
			continue;
		e = subtype;
		return true;
	}
	return false;
}

bool hero::isammo(item_s subtype) const {
	for(auto& e : gear) {
		if(e.isammo(subtype) && e.getuses())
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
		if(e == id)
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
				act("%герой потратил%а %1.", temp);
			}
			e.use();
			return true;
		}
	}
	return false;
}

bool hero::use(item_s id, bool interactive) {
	for(auto& e : gear) {
		if(e == id) {
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
				if(interactive) {
					stringbuilder sb(temp);
					act("%герой использовал%а %1.", temp, false);
				}
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

static void addit(stringbuilder& sb, const char* title, item it, bool description) {
	if(!it)
		return;
	if(sb)
		sb.add(", ");
	else
		sb.add(title);
	it.getname(sb, description);
}

char* hero::getequipment(stringbuilder& sb, const char* title) const {
	bool description = false;
	if(!isequipment())
		return sb;
	addit(sb, title, armor, description);
	addit(sb, title, weapon, description);
	addit(sb, title, shield, description);
	for(auto& e : gear) {
		if(!e)
			continue;
		addit(sb, title, e, description);
	}
	if(sb)
		sb.add(".");
	return sb;
}

bool hero::iscombatable() const {
	return *this
		&& isalive()
		&& !is(SpellInvisibility);
}

bool hero::isalive() const {
	return gethp() > 0;
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
		if(e == type)
			return &e;
	}
	return 0;
}

result_s hero::roll(int bonus, int* result, bool show_result) {
	char temp[64]; stringbuilder sbn(temp);
	int dr = 2 + (rand() % 6) + (rand() % 6);
	int tr = dr + bonus;
	sbn.add("{%2i%+3i=%1i}", tr, dr, bonus);
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
			sb.add("[-%1]", temp);
		break;
	case Success:
		if(show_result)
			sb.add("[+%1]", temp);
		break;
	default:
		if(show_result)
			sb.add(temp);
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
	if(!an)
		return 0;
	return choose(true, clear_text, "„то будет делать [%герой]?");
}

int hero::getarmor() const {
	auto result = armor.getarmor();
	if(is(ArcaneWard) && getpreparedlevels() > 0)
		result += 2;
	return 0;
}

int hero::getload() const {
	auto result = getclass().load;
	result += get(Strenght);
	return result;
}

int hero::getmaxhits() const {
	auto result = getclass().hp;
	result += stats[Constitution];
	return result;
}

dice hero::getdamage() const {
	dice result;
	result.c = 1;
	result.d = getclass().damage;
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
		stringbuilder sb(temp);
		iswap(weapon, *p);
		act("%герой достал%а %1.", temp);
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
		sb.add("”дар не смог пробить броню.");
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
	case 1: sb.add("ќсталс€ еще [один]."); break;
	case 2: sb.add("ќсталось еще [двое]."); break;
	case 3: sb.add("ќсталось еще [трое]."); break;
	default: sb.add("ќсталось еще [%1i].", enemy.count); break;
	}
	enemy.hp = enemy.getmaxhits();
}

void hero::sufferharm(int count, bool ignore_armor) {
	if(!ignore_armor) {
		auto armor = getarmor();
		count -= armor;
		if(count <= 0) {
			sb.add("Ѕрон€ спасла вас от удара.");
			return;
		}
	}
	if(is(SpellDefense) && getongoing()) {
		for(unsigned i = 0; i < spell_state_data.count; i++) {
			an.add(i, "%1 снизит урон на %2i.",
				getstr(spell_state_data.data[i].spell),
				getlevel(spell_state_data.data[i].spell));
		}
		an.add(1000, "Ќехочу убирать никаких заклинаний.");
		auto i = choose(true, false, "[%герой] получит [2i] урона, но может пожертвовать действующим заклинанием, чтобы снизить урон.", count);
		if(i != 1000) {
			count -= getlevel(spell_state_data.data[i].spell);
			spell_state_data.data[i].clear();
		}
	}
	if(count <= 0)
		return;
	sethp(gethp() - count);
	if(gethp() > 0)
		act("%герой получил%а [%1i] урона.", count);
	else {
		act("%герой получил%а [%1i] урона и упал%а.", count);
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
			stringbuilder sb(temp);
			pi->getname(sb, true);
			an.add(i, "%1 за [%2i] %3.", sb, pi->getsellcost(), maptbl(text_golds, cost));
		}
		if(!an) {
			sb.add(" - я сожелею, но у вас нет товаров, которые € могу позволить себе купить - сказал владелец магазина.");
			logs::next();
			return Success;
		}
		an.sort();
		an.add(500, "Ќичего не продавать");
		auto id = choose(true, true, "„то хочет продать [%герой]?");
		if(id == 500)
			return Success;
		auto cost = gear[id].getsellcost();
		stringbuilder sb(temp);
		gear[id].getname(sb, false),
		sb.add(" - ¬ы хотите продать %1? - спросил владелец магазина - я готов дам за него [%2i] монет.", temp, cost);
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
	auto hp = gethp();
	if(hp + count > mhp)
		count = mhp - hp;
	if(count == 0)
		return;
	sethp(hp + count);
	act("%герой востановил%а %1i %2.", count, maptbl(text_hits, count));
}

void hero::hunger() {
	act("%герой голодает.");
	sufferharm(xrand(1, 6));
}

void hero::apply(const looti& loot) {
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

void hero::set(forward_s id, char subtype) {
	forward[id] = subtype;
}

bool hero::isallow(variant id) const {
	switch(id.type) {
	case Spell: return isprepared((spell_s)id.subtype);
	case Move: return is((move_s)id.subtype);
	case Item: return isallow((item_s)id.subtype);
	case Tag: return isallow((tag_s)id.subtype);
	case Alignment: return type == (alignment_s)id.subtype;
	case Class: return subtype == (class_s)id.subtype;
	default: return true;
	}
}