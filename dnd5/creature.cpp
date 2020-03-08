#include "main.h"

adat<creature, 256>	creature_data;
adat<creature*, 8>	players;
static char proficiency_bonus[] = {1,
2, 2, 2, 2, 3, 3, 3, 3, 4, 4,
4, 4, 5, 5, 5, 5, 6, 6, 6, 6};

void* creature::operator new(unsigned size) {
	for(auto& e : creature_data) {
		if(!e)
			return &e;
	}
	return creature_data.add();
}

void creature::operator delete (void* data) {
	((creature*)data)->ability[0] = 0;
}

creature::creature(race_s race, gender_s gender, class_s type, background_s background, char* ability, bool interactive) {
	char temp_ability[6];
	clear();
	auto& ci = bsmeta<classi>::elements[type];
	this->race = race;
	this->gender = gender;
	this->background = background;
	if(!ability) {
		char random[6]; ability = temp_ability;
		choose_ability(random, false);
		for(auto i = 0; i < 6; i++)
			ability[ci.abilities[i]] = random[i];
	}
	memcpy(this->ability, ability, sizeof(this->ability));
	apply(race, interactive);
	apply(background, interactive);
	if(interactive)
		show_ability();
	apply(type, interactive);
	choose_skills(type, interactive);
	choose_languages(type, interactive);
	choose_equipment(type, interactive);
	hp = gethpmax();
	prepare(interactive);
	rest(true);
}

void creature::clear() {
	domain = NoDomain;
	background = NoBackground;
	monster = NoMonster;
	hp_rolled = hp = 0;
	skills = languages = 0;
	initiative = 0;
	memset(ability, 0, sizeof(ability));
	memset(feats, 0, sizeof(feats));
	memset(spells, 0, sizeof(spells));
	memset(spells_known, 0, sizeof(spells_known));
	memset(slots, 0, sizeof(slots));
	memset(classes, 0, sizeof(classes));
	memset(wears, 0, sizeof(wears));
}

static int compare_char(const void* v1, const void* v2) {
	return *((char*)v2) - *((char*)v1);
}

static char roll_4d6() {
	char result[4];
	result[0] = 1 + (rand() % 6);
	result[1] = 1 + (rand() % 6);
	result[2] = 1 + (rand() % 6);
	result[3] = 1 + (rand() % 6);
	qsort(result, sizeof(result), sizeof(result[0]), compare_char);
	return result[0] + result[1] + result[2];
}

void creature::random_ability(char* result) {
	for(auto i = 0; i < 6; i++)
		result[i] = roll_4d6();
	qsort(result, 6, 1, compare_char);
}

int	creature::gethpmax() const {
	auto result = hp_rolled;
	auto level = getlevel();
	result += get(Constitution)*level;
	if(is(DwarvenToughness))
		result += level;
	if(result < level)
		result = level;
	return result;
}

int creature::getproficiency() const {
	auto r = getlevel();
	return maptbl(proficiency_bonus, r);
}

int creature::getac() const {
	auto r = 10;
	auto m = wears[Armor].getdex();
	if(!wears[Armor])
		m = 20;
	else {
		auto a = wears[Armor].getac();
		r += a;
		if(a && is(StyleDefense))
			r++;
	}
	r += imin(m, get(Dexterity));
	r += wears[MeleeWeapon].getac();
	r += wears[OffhandWeapon].getac();
	r += wears[Head].getac();
	r += wears[Gridle].getac();
	r += wears[Legs].getac();
	return r;
}

int	creature::getlevel() const {
	auto result = 0;
	for(auto e : classes)
		result += e;
	return result;
}

race_s creature::getrace() const {
	return bsmeta<racei>::elements[race].basic ? bsmeta<racei>::elements[race].basic : race;
}

int	creature::roll() const {
	auto r = 1 + (rand() % 20);
	if(r == 1 && is(Lucky))
		r = 1 + (rand() % 20);
	return r;
}

int	creature::roll(roll_s type) const {
	int r1, r2;
	switch(type) {
	case Advantage:
		r1 = roll();
		r2 = roll();
		return imax(r1, r2);
	case Disadvantage:
		r1 = roll();
		r2 = roll();
		return imin(r1, r2);
	default:
		return roll();
	}
}

void creature::roll(rolli& result, bool interactive) {
	result.rolled = roll(result.get());
	result.result = result.rolled + result.bonus;
	if(is(Guided)) {
		remove(Guided);
		result.result += xrand(1, 4);
	}
	if(interactive)
		sb.add("[~{%1i vs %2i}] ", result.result, result.dc);
}

void creature::get(attacki& result, wear_s slot) const {
	memset(&result, 0, sizeof(result));
	auto& weapon = wears[slot];
	if(weapon) {
		static_cast<dice&>(result) = weapon.getattack();
		result.weapon = (item*)&weapon;
		if(weapon.isranged()) {
			result.bonus += get(Dexterity);
			if(is(StyleArchery))
				result.bonus += 2;
		} else {
			result.bonus += get(Strenght);
			if(slot == MeleeWeapon && !wears[OffhandWeapon] && is(StyleDueling))
				result.b += 2;
		}
		if(isproficient(weapon))
			result.bonus += getproficiency();
	} else {
		result.type = Bludgeon;
		result.c = 0;
		result.d = imax(1, 1 + get(Strenght));
	}
	if(is(ImprovedCritical))
		result.critical++;
	if(is(SuperiorCritical))
		result.critical++;
}

void creature::get(attacki& result, wear_s slot, const creature& enemy) const {
	get(result, slot);
	result.dc = enemy.getac();
}

void creature::attack(wear_s slot, creature& enemy) {
	auto interactive = true;
	attacki ai;
	get(ai, slot, enemy);
	roll(ai, false);
	if(interactive) {
		act("%герой ");
		switch(ai.type) {
		case Pierce: act("ткнул%а "); break;
		case Slashing: act("рубанул%а "); break;
		default: act("нанес%ла удар "); break;
		}
		if(ai.weapon) {
			sb.addsep(' ');
			ai.weapon->addnameby(sb);
		} else
			sb.add(" рукой");
		if(!ai.issuccess())
			act(", но промазал%а");
		sb.add(".");
	}
	if(!ai.issuccess())
		return;
	auto reroll = 0;
	if(ai.weapon) {
		if((ai.weapon->is(TwoHanded) || ai.weapon->is(Versatile)) && is(StyleGreatWeaponFighting))
			reroll = 2;
	}
	auto value = ai.roll(reroll);
	enemy.damage(value, ai.type, interactive);
}

void creature::action(variant id, creature& enemy) {
	switch(id.type) {
	case Wear:
		attack(id.wear, enemy);
		break;
	case Spell:
		cast(id.spell, enemy, true, true);
		break;
	}
}

bool creature::add(const item it) {
	for(auto i = Head; i <= Ammunition; i = (wear_s)(i + 1)) {
		if(wears[i])
			continue;
		if(it.is(i) && isproficient(it)) {
			wears[i] = it;
			return true;
		}
	}
	for(auto i = FirstInvertory; i < Head; i = (wear_s)(i + 1)) {
		if(wears[i])
			continue;
		wears[i] = it;
		return true;
	}
	return false;
}

const char* creature::getname() const {
	if(monster)
		return getstr(monster);
	return "Павел";
}

void creature::act(const char* format, ...) const {
	logs::driver e(sb);
	e.name = getname();
	e.gender = gender;
	sb.addv(format, xva_start(format));
}

bool creature::has(item_s id) const {
	for(auto e : wears) {
		if(e.type == id)
			return true;
	}
	return false;
}

void creature::damage(int value, damage_type_s type, bool interactive) {
	if(value >= 0) {
		hp -= value;
		if(interactive) {
			act(bsmeta<damage_typei>::elements[type].damage_action, value);
			if(hp <= 0)
				act("и %она упал%а");
			act(".");
		}
		if(hp <= 0) {
			hp = 0;
			if(isplayer())
				set(Dying);
			else
				clear();
		}
	} else {
		auto mhp = gethpmax();
		value = -value;
		if(hp + value > mhp)
			value = mhp - hp;
		if(value > 0) {
			hp += value;
			if(interactive)
				act("%герой восстановил%а %1i хитов.", value);
		}
	}
}

bool creature::is(variant id) const {
	int level;
	switch(id.type) {
	case Spell:
		if(!is(id.spell))
			return false;
		level = getlevel(id.spell);
		if(level && !get(slot_s(SpellSlot1 + level - 1)))
			return false;
		return true;
	default:
		return isallow(id);
	}
}

bool creature::isallow(variant it) const {
	switch(it.type) {
	case Item:
		if(!isproficient(it.item))
			return false;
		//if(has(it.item))
		//	continue;
		break;
	case Feat:
		if(is(it.feat))
			return false;
		break;
	case Language:
		if(is(it.language))
			return false;
		break;
	case Skill:
		if(is(it.skill))
			return false;
		break;
	case Spell:
		if(isknown(it.spell))
			return false;
		break;
	}
	return true;
}

variant* creature::add(variant* result, const variant* result_maximum, variant it) const {
	if(!it)
		return result;
	else if(it.type == Pack) {
		for(auto e : bsmeta<packi>::elements[it.pack].elements)
			result = add(result, result_maximum, e);
	} else if(isallow(it)) {
		if(result < result_maximum)
			*result++ = it;
	}
	return result;
}

void creature::set(variant it) {
	switch(it.type) {
	case Feat: set(it.feat); break;
	case Item: add(it.item); break;
	case Language: set(it.language); break;
	case Skill: set(it.skill); break;
	case Spell: setknown(it.spell); break;
	}
}

void creature::setinitiative() {
	initiative = roll();
	initiative += get(Dexterity);
}

bool creature::isenemy(const creature* p) const {
	if(!p->isready())
		return false;
	auto e1 = getreaction();
	auto e2 = p->getreaction();
	switch(e1) {
	case Helpful: return e2 == Hostile;
	case Hostile: return e2 == Helpful;
	default: return false;
	}
}

creature* creature::getenemy(aref<creature*> elements) const {
	for(auto p : elements) {
		if(isenemy(p))
			return p;
	}
	return 0;
}

void creature::add(variant id, const char* text, const creature* enemy) const {
	char temp[260]; stringbuilder sc(temp);
	switch(id.type) {
	case Wear:
		if(!wears[id.wear])
			break;
		sc.clear(); wears[id.wear].addnameby(sc);
		an.add(id, text, temp);
		break;
	case Spell:
		if(is(id)
			&& const_cast<creature*>(this)->cast(id.spell, *const_cast<creature*>(enemy), false, false))
			an.add(id, text, getstr(id));
		break;
	default:
		if(is(id))
			an.add(id, text, getstr(id));
		break;
	}
}

void creature::addcoins(stringbuilder& sb, int value) {
	if(value >= GP)
		return sb.add("%1i золотых", value / GP);
	else if(value >= SP)
		return sb.add("%1i серебрянных", value / SP);
	return sb.add("%1i медных", value);
}

int	creature::getspellcaster() const {
	return classes[Cleric] + classes[Wizard];
}

int creature::getspellprepared() const {
	return get(Wisdow) + getspellcaster();
}

void creature::rest(bool long_rest) {
	if(long_rest) {
		if(getspellcaster()) {
			// Подготовим слоты заклинаний
			for(auto i = 1; i <= 9; i++) {
				auto count = getslots(i);
				set((slot_s)(SpellSlot1 + i - 1), count);
			}
		}
	}
}

void creature::prepare(bool interactive) {
	auto count = getspellprepared();
	if(!count)
		return;
	memset(spells, 0, sizeof(spells));
	while(count > 0) {
		for(auto i = FirstSpell; i <= LastSpell; i = (spell_s)(i + 1)) {
			if(isknown(i))
				an.add(i, getstr(i));
		}
		an.sort();
		if(!an)
			break;
		auto result = (spell_s)an.choose(interactive, false, "Какое заклинание заучит [%1]? (осталось %2i)", getname(), count);
		set(result);
		count--;
	}
}

int	creature::getslots(int level) const {
	static char slot_level_0[] = {0, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5};
	static char slot_level_1[] = {0, 2, 3, 4};
	static char slot_level_2[] = {0, 0, 0, 2, 3};
	static char slot_level_3[] = {0, 0, 0, 0, 0, 2, 3};
	static char slot_level_4[] = {0, 0, 0, 0, 0, 0, 0, 1, 2, 3};
	static char slot_level_5[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3};
	static char slot_level_6[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2};
	static char slot_level_7[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2};
	static char slot_level_8[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
	static char slot_level_9[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
	auto caster_level = getspellcaster();
	switch(level) {
	case 0: return maptbl(slot_level_0, caster_level);
	case 1: return maptbl(slot_level_1, caster_level);
	case 2: return maptbl(slot_level_2, caster_level);
	case 3: return maptbl(slot_level_3, caster_level);
	case 4: return maptbl(slot_level_4, caster_level);
	case 5: return maptbl(slot_level_5, caster_level);
	case 6: return maptbl(slot_level_6, caster_level);
	case 7: return maptbl(slot_level_7, caster_level);
	case 8: return maptbl(slot_level_8, caster_level);
	case 9: return maptbl(slot_level_9, caster_level);
	default: return 0;
	}
}

bool creature::isplayer() const {
	return players.is((creature*)this);
}

void creature::make_death_save() {
	if(!is(Dying))
		return;
	auto chance = 1 + (rand() % 20);
	if(chance >= 10)
		death_save[1]++;
	else
		death_save[0]++;
	if(death_save[0] >= 3) {
		act("%герой умер%ла не приходя в сознание.");
		clear();
	} else {
		act("Состояние %героя стабилизировалось.");
		death_save[0] = death_save[1] = 0;
		remove(Dying);
	}
}