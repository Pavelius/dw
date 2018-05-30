#include "main.h"

hero					player;

static struct hero_i {
	const char*			id;
	const char*			name;
	special_s			special;
	location_s			location;
	char				sanity, stamina, focus;
	char				stats[Luck + 1];
	action_s			possessions[8];
	item_s				possessions_items[4];
} hero_data[] = {
	{"ashcan", "Ашхан \"Пит\"", Scrounge, RiverDocks, 4, 6, 1, {0, 6, 2, 5, 0, 3}, {Add1Money, Add3Clue, AddCommonItem, AddUniqueItem, AddSpell}, {AllyDuke}},
	{"joe", "Джо Диамонд", Hunches, PoliceStation, 4, 6, 3, {3, 4, 2, 3, 0, 3}, {Add7Money, Add3Clue, Add2CommonItem, AddSkill}, {PistolAutomatic45}},
};

static hero_i* find(const char* id) {
	for(auto& e : hero_data) {
		if(strcmp(e.id, id) == 0)
			return &e;
	}
	return 0;
}

static item_s getskill(stat_s id) {
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

char hero::get(stat_s id) const {
	switch(id) {
	case Speed: return stats[Speed] + focus[Speed / 2] + get(SkillSpeed);
	case Fight: return stats[Fight] + focus[Fight / 2] + get(SkillFight);
	case Lore: return stats[Lore] + focus[Lore / 2] + get(SkillLore);
	case Sneak: return stats[Sneak] - focus[Sneak / 2] + get(SkillSneak);
	case Will: return stats[Will] - focus[Will / 2] + get(SkillWill);
	case Luck: return stats[Luck] - focus[Luck / 2] + get(SkillLuck);
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
		set(i, p->stats[i]);
	for(auto e : p->possessions)
		apply(e);
	for(auto e : p->possessions_items)
		add(e);
	set(Stamina, get(StaminaMaximum));
	set(Sanity, get(SanityMaximum));
}

bool hero::remove(item_s v) {
	if(!cards[v])
		return false;
	cards[v]--;
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

int hero::roll(stat_s id_origin, int bonus, int difficult, bool interactive) {
	int i; char result[32]; result[0] = 0; char temp[512];
	auto id = getstat(id_origin);
	auto skill = getskill(id);
	auto success_number = 5;
	auto count = get(id) + bonus;
	for(auto i = 0; i < count; i++)
		addie(result);
	while(true) {
		char skill_temp[128]; getstr(skill_temp, zendof(skill_temp), id, bonus);
		if(result[0]) {
			szprints(temp, zendof(temp), "Вы сделали бросок [%1] и выбросили: ", skill_temp);
			dices(zend(temp), zendof(temp), result);
			szprints(zend(temp), zendof(temp), ".");
		} else {
			szprints(temp, zendof(temp), "У вас недостаточно кубиков для броска [%1].", skill_temp);
		}
		szprints(zend(temp), zendof(temp), " Что будете делать?");
		auto success = getresult(result, success_number) - difficult;
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
			add(Clue, -1, false);
			break;
		case 3:
			i = zlen(result); result[0] = 0;
			while(i-- > 0)
				addie(result);
			break;
		}
	}
}

void hero::choose(stat_s id, int count, int draw_count, int draw_bottom, bool interactive) {
	deck result;
	deck& source = deck::getdeck(id);
	result.draw(source, draw_count);
	result.drawb(source, draw_bottom);
	if(!result.count)
		return;
	while(count-- > 0) {
		for(unsigned i = 0; i < result.count; i++)
			logs::add(i, getstr(result.data[i]));
		logs::sort();
		auto i = logs::input(interactive, false, (count > 0) ? "Выберите [%1] (осталось %2i):" : "Выберите [%1]:", getstr(id), count + 1);
		add(result.data[i]);
		result.remove(i);
	}
}

void hero::choose(stat_s id, int count, bool interactive) {
	auto draw_count = count;
	auto draw_bottom = 0;
	if(is(Scrounge)) {
		if(id == CommonItem || id == UniqueItem || id == Spell)
			draw_bottom++;
	}
	choose(id, count, draw_count, draw_bottom, interactive);
}

void hero::select(deck& result, stat_s group) const {
	for(auto i = PistolDerringer18; i <= AllyDuke; i = (item_s)(i + 1)) {
		if(group && group != deck::getgroup(i))
			continue;
		if(!get(i))
			continue;
		result.add(i);
	}
}

char hero::get(item_s id) const {
	return cards[id] - exhause[id];
}

void hero::discard(item_s id) {
	if(cards[id])
		cards[id]--;
	deck::discard(id);
}