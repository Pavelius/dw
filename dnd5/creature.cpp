#include "main.h"

DECLDATA(creature, 256);

static char proficiency_bonus[] = {1,
2, 2, 2, 2, 3, 3, 3, 3, 4, 4,
4, 4, 5, 5, 5, 5, 6, 6, 6, 6};

void creature::clear() {
	memset(this, 0, sizeof(*this));
}

void creature::create(race_s race, gender_s gender, class_s type, background_s background, char* ability, bool interactive) {
	char temp_ability[6];
	clear();
	auto& ci = bsmeta<classi>::elements[type];
	this->type = Race;
	this->value = race;
	setgender(gender);
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

int	creature::roll() const {
	auto r = 1 + (rand() % 20);
	if(r == 1 && is(Lucky))
		r = 1 + (rand() % 20);
	return r;
}

int	creature::roll(int advantages) const {
	if(advantages > 0) {
		auto r1 = roll();
		auto r2 = roll();
		return imax(r1, r2);
	} else if(advantages < 0) {
		auto r1 = roll();
		auto r2 = roll();
		return imin(r1, r2);
	}
	return roll();
}

void creature::roll(rolli& result, bool interactive) {
	result.rolled = roll(result.advantages);
	result.result = result.rolled + result.bonus;
	if(is(Guided)) {
		remove(Guided);
		result.result += xrand(1, 4);
	}
	if(interactive)
		sb.add("[~{%1i%+3i vs %2i}] ", result.rolled, result.dc, result.result - result.rolled);
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
	roll(ai, interactive);
	if(interactive) {
		act("%�����");
		switch(ai.type) {
		case Pierce: act("�����%�"); break;
		case Slashing: act("�������%�"); break;
		default: act("�����%�� ����"); break;
		}
		if(ai.weapon) {
			sb.addsep(' ');
			ai.weapon->addnameby(sb);
		} else
			act("�����");
		if(!ai.issuccess())
			act(", �� ��������%�");
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
		attack((wear_s)id.value, enemy);
		break;
	case Spell:
		cast((spell_s)id.value, enemy, true, true);
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
	for(auto i = Equipment; i < Head; i = (wear_s)(i + 1)) {
		if(wears[i])
			continue;
		wears[i] = it;
		return true;
	}
	return false;
}

bool creature::has(item_s id) const {
	for(auto e : wears) {
		if(e.is(id))
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
				act("� ����%�");
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
				act("%����� �����������%� %1i �����.", value);
		}
	}
}

bool creature::is(variant id) const {
	int level;
	switch(id.type) {
	case Spell:
		if(!is((spell_s)id.value))
			return false;
		level = getlevel((spell_s)id.value);
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
		if(!isproficient((item_s)it.value))
			return false;
		//if(has(it.item))
		//	continue;
		break;
	case Feat:
		if(is((feat_s)it.value))
			return false;
		break;
	case Language:
		if(is((language_s)it.value))
			return false;
		break;
	case Skill:
		if(is((skill_s)it.value))
			return false;
		break;
	case Spell:
		if(isknown((spell_s)it.value))
			return false;
		break;
	}
	return true;
}

variant* creature::add(variant* result, const variant* result_maximum, variant it) const {
	if(!it)
		return result;
	else if(it.type == Pack) {
		for(auto e : bsmeta<packi>::elements[it.value].elements)
			result = add(result, result_maximum, e);
	} else if(isallow(it)) {
		if(result < result_maximum)
			*result++ = it;
	}
	return result;
}

void creature::set(variant it) {
	switch(it.type) {
	case Feat: set((feat_s)it.value); break;
	case Item: add((item_s)it.value); break;
	case Language: set((language_s)it.value); break;
	case Skill: set((skill_s)it.value); break;
	case Spell: setknown((spell_s)it.value); break;
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

void creature::addcoins(stringbuilder& sb, int value) {
	if(value >= GP)
		return sb.add("%1i �������", value / GP);
	else if(value >= SP)
		return sb.add("%1i �����������", value / SP);
	return sb.add("%1i ������", value);
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
			// ���������� ����� ����������
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
	spells.clear();
	while(count > 0) {
		for(auto i = FirstSpell; i <= LastSpell; i = (spell_s)(i + 1)) {
			if(isknown(i))
				an.add(i, getstr(i));
		}
		an.sort();
		if(!an)
			break;
		auto result = (spell_s)an.choose(interactive, false, "����� ���������� ������ [%1]? (�������� %2i)", getname(), count);
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

void creature::make_death_save() {
	if(!is(Dying))
		return;
	auto chance = 1 + (rand() % 20);
	if(chance >= 10)
		death_save[1]++;
	else
		death_save[0]++;
	if(death_save[0] >= 3) {
		act("%����� ����%�� �� ������� � ��������.");
		clear();
	} else {
		act("��������� %����� �����������������.");
		death_save[0] = death_save[1] = 0;
		remove(Dying);
	}
}

variant	creature::getvar() const {
	return this ? variant(Creature, this - bsmeta<creature>::elements) : variant();
}

bool creature::isreach(reaction_s v, int distance) const {
	for(auto& e : bsmeta<creature>()) {
		if(!e)
			continue;
		if(e.getreaction() == v && isreach(e, distance))
			return true;
	}
	return false;
}

bool creature::use(action_s id, creature& target, bool run) {
	switch(id) {
	case MakeAttack:
		if(wears[MeleeWeapon].isranged()) {
			return false;
		} else {
			if(!isreach(target, getreach()))
				return false;
		}
		if(run)
			attack(MeleeWeapon, target);
		break;
	case MakeMove:
		if(!get(FootSpeed))
			return false;
		if(run) {
			set(FootSpeed, 0);
			act("%����� ������%��� ����� %1.", target.getname());
			setposition(target.getposition());
		}
		break;
	case Dash:
		if(run) {
			act("%����� ������%���.");
			set(FootSpeed, get(FootSpeed) + getmove());
		}
		break;
	case Dodge:
		if(is(Dodged))
			return false;
		if(run) {
			act("%����� ������%� �������� ������, �������������� �������� ����� �����.");
			set(Dodged);
		}
		break;
	case Disengage:
		if(is(Disengaged))
			return false;
		if(run) {
			act("%����� ����� ��� � ����� �������%��� �����.");
			set(Disengaged);
		}
		break;
	case StandUp:
		if(!is(Prone))
			return false;
		if(run) {
		}
		break;
	default:
		return false;
	}
	return true;
}

bool creature::use(action_s id, varianta& source, bool run) {
	auto& ei = bsmeta<actioni>::elements[id];
	varianta result;
	result.select(source, *this, ei.target);
	result.match(*this, id, false);
	if(!result)
		return false;
	if(run) {
		auto pt = ei.choose_target;
		if(!pt)
			pt = "��������� ����";
		auto v = result.choose(isplayer(), getposition(), pt);
		if(!v)
			return false;
		return use(id, *v.getcreature(), run);
	}
	return true;
}

reaction_s creature::getfriendly() const {
	return reaction;
}

reaction_s creature::gethostile() const {
	switch(reaction) {
	case Helpful: return Hostile;
	case Hostile: return Helpful;
	default: return Hostile;
	}
}

bool creature::isblocked() const {
	return true;
}

void creature::moveto(indext i) {
	auto sp = getmove();
	auto ps = getposition();
	if(ps > i) {
		ps -= sp;
		if(ps < i)
			ps = i;
	} else {
		ps += sp;
		if(ps > i)
			ps = i;
	}
	setposition(ps);
}

variant	creature::getid() const {
	auto i = bsmeta<creature>::source.indexof(this);
	if(i == -1)
		return variant();
	return variant(Creature, i);
}

const char* posable::getdistance(char* temp, int value) {
	stringbuilder sb(temp, temp + 256);
	auto vm = value*Feet5 / 2;
	switch(vm) {
	case 1: sb.add("1 ����"); break;
	case 2: sb.add("2 �����"); break;
	default: sb.add("%1i ������", vm); break;
	}
	return temp;
}

bool creature::set(variant id, bool run) {
	switch(id.type) {
	case Feat:
		if(is((feat_s)id.value))
			return false;
		if(run)
			set((feat_s)id.value);
		break;
	case State:
		if(is((state_s)id.value))
			return false;
		if(run)
			set((state_s)id.value);
		break;
	default:
		return false;
	}
	return true;
}

bool creature::remove(variant id, bool run) {
	switch(id.type) {
	case Feat:
		if(!is((feat_s)id.value))
			return false;
		if(run)
			remove((feat_s)id.value);
		break;
	case State:
		if(!is((state_s)id.value))
			return false;
		if(run)
			remove((state_s)id.value);
		break;
	default:
		return false;
	}
	return true;
}