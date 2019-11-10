#include "main.h"

using namespace game;

static const char* text_golds[] = {"�������", "�������", "�������"};
static const char* text_hits[] = {"�����������", "�����������", "�����������", "�����������", "�����������", "�����������"};
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
		sb.add("������ �������� [%1i] �����.", count);
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
	// ������� ��� �������� ������
	if(value == SignatureWeapon && !signature_weapon) {
		an.add(SwordLong, getstr(SwordLong));
		an.add(Warhammer, getstr(Warhammer));
		an.add(Spear, getstr(Spear));
		signature_weapon.set((item_s)an.choose(interactive, true, "���� [�������� ������]:"));
		for(int count = 0; count < 2; count++) {
			for(auto e = Spiked; e <= WellCrafted; e = (tag_s)(e + 1)) {
				if(signature_weapon.is(e))
					continue;
				an.add(e, getstr(e));
			}
			auto id = (tag_s)an.choose(interactive, true, "�������� ��������� (%1i/2):", count + 1);
			signature_weapon.set(id);
			switch(id) {
			case Versatile:
				for(auto d = Hand; d <= Reach; d = (distance_s)(d + 1)) {
					if(signature_weapon.is(d))
						continue;
					an.add(d, getstr(d));
				}
				signature_weapon.set((distance_s)an.choose(interactive, true, "�� ����� ���������?"));
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
				act("%����� �����������%� %1.", temp);
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
				if(interactive) {
					stringbuilder sb(temp);
					act("%����� ������������%� %1.", temp, false);
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

char* hero::getequipment(char* result, const char* result_maximum, const char* title) const {
	bool description = false;
	result[0] = 0;
	if(!isequipment())
		return result;
	zcat(result, title);
	auto p = zend(result);
	stringbuilder sb(result, result_maximum);
	if(armor) {
		if(p[0])
			zcat(p, ", ");
		armor.getname(sb, description);
	}
	if(weapon) {
		if(p[0])
			zcat(p, ", ");
		weapon.getname(sb, description);
	}
	if(shield) {
		if(p[0])
			zcat(p, ", ");
		shield.getname(sb, description);
	}
	for(auto& e : gear) {
		if(!e)
			continue;
		if(p[0])
			zcat(p, ", ");
		e.getname(sb, description);
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
	return an.choose(true, clear_text, "��� ����� ������ [%1]?", getname());
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
		stringbuilder sb(temp);
		iswap(weapon, *p);
		sb.add("%1 ������%2 %3.", getname(), getA(), temp, false);
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
		sb.add("���� �� ���� ������� �����.");
		return;
	}
	enemy.hp -= count;
	if(enemy.hp > 0) {
		enemy.act("%����� �������%� [%1i] �����.", count);
		return;
	}
	enemy.act("%����� �������%� [%1i] ����� � ����%�.", count);
	enemy.hp = 0;
	switch(--enemy.count) {
	case 0: return;
	case 1: sb.add("������� ��� [����]."); break;
	case 2: sb.add("�������� ��� [����]."); break;
	case 3: sb.add("�������� ��� [����]."); break;
	default: sb.add("�������� ��� [%1i].", enemy.count); break;
	}
	enemy.hp = enemy.getmaxhits();
}

void hero::sufferharm(int count, bool ignore_armor) {
	if(!ignore_armor) {
		auto armor = getarmor();
		count -= armor;
		if(count <= 0) {
			sb.add("����� ������ ��� �� �����.");
			return;
		}
	}
	if(is(SpellDefense) && getongoing()) {
		for(unsigned i = 0; i < spell_state_data.count; i++) {
			an.add(i, "%1 ������ ���� �� %2i.",
				getstr(spell_state_data.data[i].spell),
				getlevel(spell_state_data.data[i].spell));
		}
		an.add(1000, "������ ������� ������� ����������.");
		auto i = an.choose(true, false, "[%1] ������� [2i] �����, �� ����� ������������ ����������� �����������, ����� ������� ����.",
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
		sb.add("%2 �������%3 [%1i] �����.", count, getname(), getA());
	else {
		sb.add("%2 �������%3 [%1i] ����� � ����%3.", count, getname(), getA());
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
			an.add(i, "%1 �� [%2i] %3.", sb, pi->getsellcost(), maptbl(text_golds, cost));
		}
		if(!an) {
			sb.add(" - � �������, �� � ��� ��� �������, ������� � ���� ��������� ���� ������ - ������ �������� ��������.");
			logs::next();
			return Success;
		}
		an.sort();
		an.add(500, "������ �� ���������");
		auto id = an.choose(true, true, "��� ����� ������� [%1]?", getname());
		if(id == 500)
			return Success;
		auto cost = gear[id].getsellcost();
		stringbuilder sb(temp);
		gear[id].getname(sb, false),
		sb.add(" - �� ������ ������� %1? - ������� �������� �������� - � ����� ��� �� ���� [%2i] �����.", temp, cost);
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
	act("%����� ����������%� %1i %2.", count, maptbl(text_hits, count));
}

void hero::hunger() {
	sb.add("%1 ��������.", getname());
	sufferharm(xrand(1, 6));
}

void hero::apply(looti& loot) {
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
	driver dr(sb);
	dr.name = getname();
	dr.gender = gender;
	dr.addsep(' ');
	dr.addv(format, xva_start(format));
	sb = dr;
}

void hero::say(const char* format, ...) const {
	driver dr(sb);
	dr.name = getname();
	dr.gender = gender;
	dr.addn(format, xva_start(format));
	dr.addn("");
}