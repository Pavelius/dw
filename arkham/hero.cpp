#include "main.h"

hero					player;

static struct hero_info {
	const char*			id;
	const char*			name;
	special_s			special;
	location_s			location;
	char				sanity, stamina, focus;
	char				stats[Luck - Speed + 1];
	action_s			possessions[8];
	card_s				possessions_items[4];
} hero_data[] = {
	{"ashcan", "Ашхан \"Пит\"", Scrounge, RiverDocks, 4, 6, 1, {0, 6, 2, 5, 0, 3}, {Add1Money, Add3Clue, AddCommonItem, AddUniqueItem, AddSpell}, {Duke}},
	{"joe", "Джо Диамонд", Hunches, PoliceStation, 4, 6, 3, {3, 4, 2, 3, 0, 3}, {Add7Money, Add3Clue, Add2CommonItem, AddSkill}, {PistolAutomatic45}},
};

static hero_info* find(const char* id) {
	for(auto& e : hero_data) {
		if(strcmp(e.id, id) == 0)
			return &e;
	}
	return 0;
}

static card_s getskill(stat_s id) {
	switch(id) {
	case Fight: return SkillFight;
	case Will: return SkillWill;
	case Speed: return SkillSpeed;
	case Sneak: return SkillSneak;
	case Lore: return SkillLore;
	case Luck: return SkillLuck;
	default: return NoItem;
	}
}

static stat_s getstat(stat_s id) {
	switch(id) {
	case CombatCheck: return Fight;
	case EvadeCheck: return Sneak;
	case HorrorCheck: return Will;
	case SpellCheck: return Will;
	default: return id;
	}
}

char hero::getfocus(stat_s id) const {
	switch(id) {
	case Fight: case Will: return 1;
	case Lore: case Luck: return 2;
	default: return 0;
	}
}

char hero::get(stat_s id) const {
	switch(id) {
	case Speed: return stats[Speed] + focus[getfocus(Speed)] + get(SkillSpeed) + getbonus(Speed);
	case Fight: return stats[Fight] + focus[getfocus(Fight)] + get(SkillFight) + getbonus(Fight);
	case Lore: return stats[Lore] + focus[getfocus(Lore)] + get(SkillLore) + getbonus(Lore);
	case Sneak: return stats[Sneak] - focus[getfocus(Sneak)] + get(SkillSneak) + getbonus(Sneak);
	case Will: return stats[Will] - focus[getfocus(Will)] + get(SkillWill) + getbonus(Will);
	case Luck: return stats[Luck] - focus[getfocus(Luck)] + get(SkillLuck) + getbonus(Luck);
	default: return stats[id];
	}
}

void hero::clear() {
	memset(this, 0, sizeof(*this));
}

void hero::create(const char* id) {
	clear();
	auto p = find(id);
	if(!p)
		return;
	set(p->special);
	set(p->location);
	setname(p->name);
	set(StaminaMaximum, p->stamina);
	set(SanityMaximum, p->sanity);
	set(Focus, p->focus);
	for(auto& e : focus)
		e = 2;
	for(auto i = Speed; i <= Luck; i = (stat_s)(i + 1))
		set(i, p->stats[i - Speed]);
	for(auto e : p->possessions)
		apply(e);
	for(auto e : p->possessions_items)
		add(e);
	set(Stamina, get(StaminaMaximum));
	set(Sanity, get(SanityMaximum));
	changeweapons(false);
}

bool hero::remove(card_s v) {
	if(!cards[v])
		return false;
	cards[v]--;
	counter[v] = 0;
	return true;
}

static char* dices(char* result, const char* result_maximum, const char* source) {
	for(auto i = 0; source[i]; i++) {
		if(i)
			zcat(result, ", ");
		szprints(zend(result), result_maximum, "%1i", source[i]);
	}
	return result;
}

static int getresult(const char* result, int success_number) {
	auto r = 0;
	for(auto i = 0; result[i] > 0; i++) {
		if(result[i] >= success_number)
			r++;
	}
	return r;
}

static void addie(char* result) {
	zcat(result, (char)(1 + (rand() % 6)));
}

char* getstr(char* result, const char* result_maximum, stat_s id, int bonus) {
	if(bonus > 0)
		return szprints(result, result_maximum, "%1+%2i", getstr(id), bonus);
	else if(bonus < 0)
		return szprints(result, result_maximum, "%1-%2i", getstr(id), -bonus);
	else
		return szprints(result, result_maximum, "%1", getstr(id));
}

char hero::getbonus(stat_s id, card_s from, card_s to) const {
	char result = 0;
	for(auto i = from; i <= to; i = (card_s)(i + 1)) {
		if(cards[i])
			result += item::get(i, id);
	}
	return result;
}

char hero::getbonus(stat_s id) const {
	return getbonus(id, AnnaKaslow, TomMountainMurphy);
}

int hero::roll(stat_s id_origin, int bonus, int difficult, bool interactive) {
	const int itemuse = 2000;
	int i; char result[32]; result[0] = 0; char temp[512];
	auto id = getstat(id_origin);
	auto skill = getskill(id);
	auto success_number = getsuccess();
	auto count = get(id) + bonus;
	for(auto i = 0; i < count; i++)
		addie(result);
	if(difficult == 0)
		difficult = 1;
	while(true) {
		char skill_temp[512]; getstr(skill_temp, zendof(skill_temp), id, bonus);
		if(result[0]) {
			szprints(temp, zendof(temp), "Вы сделали бросок [%1] и выбросили: ", skill_temp);
			dices(zend(temp), zendof(temp), result);
			szprints(zend(temp), zendof(temp), ".");
		} else {
			szprints(temp, zendof(temp), "У вас недостаточно кубиков для броска [%1].", skill_temp);
		}
		auto success = getresult(result, success_number) - (difficult-1);
		if(success < 0)
			success = 0;
		if(success) {
			if(difficult==0)
				logs::add(1, "Принять результат с [%1i] успехами.", success);
			else
				logs::add(1, "Принять удачный результат.", success);
		}
		else
			logs::add(1, "Принять провал.");
		auto add_die_count = 1;
		if(get(skill))
			add_die_count++;
		if(is(Hunches))
			add_die_count++;
		if(get(Clue))
			logs::add(2, "Потратить улику, чтобы добавить к броску [%2i] кубик (осталось [%1i] улик).", get(Clue), add_die_count);
		for(auto i = PistolDerringer18; i <= WardingStatue; i = (card_s)(i + 1)) {
			if(!get(i))
				continue;
			if(id_origin == CombatCheck
				&& item::is(i, AutoCombatCheck)
				&& isallow(item::getuse(i).before)) {
				szprints(skill_temp, zendof(skill_temp), "Использовать [%1], чтобы сделать бросок удачным.");
				required(skill_temp, zendof(skill_temp), item::getuse(i).before);
				logs::add(itemuse + i, skill_temp);
			}
		}
		auto id = logs::input(interactive, false, temp);
		switch(id) {
		case 1:
			return success;
		case 2:
			addie(result);
			if(get(skill))
				addie(result);
			if(is(Hunches))
				addie(result);
			add(Clue, NoItem, AnyLocation, -1, false);
			break;
		case 3:
			i = zlen(result); result[0] = 0;
			while(i-- > 0)
				addie(result);
			break;
		default:
			if(id >= itemuse && id <= itemuse + LastItem) {
				auto i = (card_s)(id - itemuse);
				if(id_origin == CombatCheck && item::is(i, AutoCombatCheck)) {
					use(i);
					return 1;
				}
			}
			break;
		}
	}
}

void hero::choose(stat_s stat, int count, int draw_count, int draw_bottom, bool interactive, tag_s* filter, bool buymode, int more_cost) {
	if(is(Scrounge)) {
		if(stat == CommonItem || stat == UniqueItem || stat == Spell)
			draw_bottom++;
	}
	deck result;
	deck& source = deck::getdeck(stat);
	if(filter)
		result.draw(source, draw_count, *filter);
	else
		result.draw(source, draw_count);
	result.drawb(source, draw_bottom);
	if(!result.count)
		return;
	char temp[260];
	while(count > 0) {
		if(buymode) {
			for(unsigned i = 0; i < result.count; i++) {
				item::getname(temp, zendof(temp), result.data[i], true, false, 0, true, more_cost);
				logs::add(i, temp);
			}
		} else {
			for(unsigned i = 0; i < result.count; i++)
				logs::add(i, getstr(result.data[i]));
		}
		logs::sort();
		if(buymode)
			logs::add(-1, "Ничего из этого не надо.");
		const char* text = (count > 1) ? "Выберите [%1] (осталось %2i):" : "Выберите [%1]:";
		if(buymode)
			text = (count > 1) ? "Что хотите купить? (осталось %2i):" : "Что хотите купить?:";
		auto i = logs::input(interactive, false, text, getstr(stat), count);
		if(i==-1)
			break;
		if(buymode) {
			auto cost = item::getcost(result.data[i]) + more_cost;
			if(get(Money) < cost) {
				logs::add(1, "Продолжить");
				logs::input(interactive, false, "[-У вас не хватает денег.]");
				continue;
			}
			set(Money, get(Money) - cost);
		}
		add(result.data[i]);
		result.remove(i);
		count--;
	}
}

void hero::select(deck& result, stat_s group) const {
	for(auto i = PistolDerringer18; i <= LastItem; i = (card_s)(i + 1)) {
		if(group && group != item::getgroup(i))
			continue;
		if(!get(i))
			continue;
		result.add(i);
	}
}

char hero::get(card_s id) const {
	return cards[id] - exhause[id];
}

void hero::discard(card_s id) {
	if(remove(id))
		deck::discard(id);
}

int	hero::getspells() const {
	auto result = 0;
	for(auto i = BindMonster; i <= Wither; i = (card_s)(i + 1))
		result += get(i);
	return result;
}

int	hero::getskills() const {
	auto result = 0;
	for(auto i = SkillBarvery; i <= SkillLuck; i = (card_s)(i + 1))
		result += get(i);
	return result;
}

char hero::getsuccess() const {
	auto bless = get(Blessed);
	if(bless > 0)
		return 4;
	else if(bless < 0)
		return 6;
	return 5;
}

void hero::exhausecard(card_s i) {
	exhause[i]++;
}

void hero::ask(card_s i, const char* custom) const {
	if(!get(i))
		return;
	auto& ti = item::getuse(i);
	if(!isallow(ti.before))
		return;
	if(!custom) {
		if(item::is(i, Tome))
			custom = "Прочитать [%1].";
		else if(ti.script)
			custom = "Изучить [%1].";
		else
			custom = "Использовать [%1].";
	}
	char temp[512]; szprints(temp, zendof(temp), custom, getstr(i));
	required(temp, zendof(temp), ti.before);
	logs::add(ItemUse + i, temp);
}

void hero::use(card_s i) {
	bool p_discard = false;
	bool p_usepart = false;
	auto& ti = item::getuse(i);
	apply(ti.before, false, &p_discard, &p_usepart);
	if(ti.script)
		run(ti.script, &p_discard, &p_usepart);
	if(p_usepart && (++counter[i]) >= ti.usable)
		p_discard = true;
	if(p_discard || item::is(i, DiscardAfterUse))
		discard(i);
	if(item::is(i, ExhaustToEffect))
		exhausecard(i);
}

void hero::run(const quest* q, bool* discard, bool* usepart, bool* tryagain) {
	auto interactive = true;
	if(!q)
		return;
	if(!isready())
		return;
	logs::clear(true);
	logs::add(q->text);
	if(tryagain) {
		if(logs::getcount())
			logs::add(1, "Продолжить.");
		if(get(DragonsEye) && get(Sanity) > 1)
			logs::add(DragonsEye, "Использовать [%1] чтобы выбрать другое приключение.");
		auto id = whatdo(true, false);
		switch(id) {
		case DragonsEye:
			*tryagain = true;
			use(DragonsEye);
			logs::clear();
			return;
		}
	}
	auto count_time = 1;
	if(q->roll.id == TestTwoDie)
		count_time = 2;
	while(count_time > 0) {
		auto result = 0;
		if(q->roll.id == TestOneDie || q->roll.id == TestTwoDie) {
			auto die = 1 + rand() % 6;
			if(die >= getsuccess())
				result = 1;
		} else if(q->roll.id == Money) {
			if(get(Money) < q->roll.bonus)
				logs::add("У вас не хватило денег.");
			else if(logs::yesno(true, "Будете платить [%1i$]?", q->roll.bonus)) {
				set(Money, get(Money) - q->roll.bonus);
				result = 1;
			}
		} else {
			if(q->roll.optional) {
				if(q->roll.id) {
					char skill_temp[128]; q->roll.getname(skill_temp, zendof(skill_temp));
					if(!logs::yesno(true, "Будете делать бросок [%1]?", skill_temp))
						return;
				} else {
					if(!logs::yesno(true))
						return;
				}
			}
			if(q->roll.id)
				result = roll(q->roll.id, q->roll.bonus, q->roll.difficult, true);
		}
		int result_maximum = zlen(q->results);
		if(result_maximum < 2)
			result_maximum = 2;
		if(result >= result_maximum)
			result = result_maximum - 1;
		auto apply_actions = 0;
		if(q->results[result].text)
			logs::add(q->results[result].text);
		for(auto a : q->results[result].results) {
			if(!isready())
				break;
			if(!a)
				break;
			apply(a, interactive, discard, usepart);
			apply_actions++;
		}
		if(q->results[result].next) {
			q = q->results[result].next;
			if(q->text)
				logs::add(q->text);
			continue;
		}
		if(!apply_actions)
			logs::next();
		count_time--;
	}
}