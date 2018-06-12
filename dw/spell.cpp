#include "main.h"

static struct spell_info {
	const char*		id;
	const char*		name;
	char			level[2];
	target_s		target;
	bool			ongoing;
	dice			random;
	const char*		effect;
	const char*		remove;
} spell_data[] = {
	{"Guidance", "Направление", {-1, 0}},
	{"Light", "Свет", {0, 0}},
	{"Prestidigitation", "Фокусы", {0, -1}},
	{"Sanctify", "Очищение", {-1, 0}},
	{"UnseenServant", "Невидимый слуга", {0, -1}, Self, true},
	//
	{"Bless", "Благословение", {-1, 1}, Self, true, {}, "Поле боя озарилось светом."},
	{"CauseFear", "Вызвать страх", {-1, 1}, Self, true, {}, "Ваша фигура озарилась темным светом."},
	{"ContactSpirits", "Вызов духов", {1, -1}},
	{"CureLightWounds", "Лечить легкие ранения", {-1, 1}, Hero, false, {1, 8}, "%герой озарился белым светом."},
	{"DetectAlignment", "Определить мировозрение", {-1, 1}},
	{"DetectMagic", "Определить магию", {1, -1}},
	{"Telepathy", "Телепатия", {1, -1}, Self, true},
	{"CharmPerson", "Очаровать персону", {1, -1}, Self, true},
	{"Invisibility", "Невидимость", {1, -1}, Self, true, {}, "Внезапно все ваши герои исчезли из виду.", "Вдруг откуда ни возьмись появились все персонажи."},
	{"MagicMissile", "Волшебный снаряд", {1, -1}, Monster, false, {2, 4}, "С пальцев сорвалось несколько разноцветных шариков, которые поразили врага."},
	{"MagicWeapon", "Волшебное оружие", {-1, 1}, Self, false},
	{"Sanctuary", "Убежище", {1, -1}, Self, false},
	{"SpeakWithDead", "Разговор с мертвецами", {-1, 1}, Self, false},
	{"Alarm", "Тревога", {1, -1}},
	//
	{"DispelMagic", "Рассеять магию", {3, -1}},
	{"VisionsThroughTime", "Видения сквозь время", {3, -1}},
	{"Fireball", "Огненный шар", {3, -1}, Monster},
	{"Mimic", "Мимик", {3, -1}},
	{"MirrorImage", "Зеркальное отображение", {3, -1}},
	{"Sleep", "Сон", {3, -1}},
	//
	{"Cage", "Клетка", {5, -1}},
	{"ContactOtherPlane", "Связаться с другим измерением", {5, -1}},
	{"Polymorph", "Превратить", {5, -1}},
	{"SummonMonster", "Вызов монстра", {5, -1}},
	//
	{"Dominate", "Доминирование", {7, -1}},
	{"TrueSeeing", "Истинное зрение", {7, -1}},
	{"ShadowWalk", "Ходьба по измерению Теней", {7, -1}},
	{"Contingency", "Постоянство", {7, -1}},
	{"Cloudkill", "Туман убийца", {7, -1}},
	//
	{"Antipathy", "Антипатия", {9, -1}},
	{"Alert", "Оповещение", {9, -1}},
	{"SoulGem", "Изумруд для души", {9, -1}},
	{"Shelter", "Убежище", {9, -1}},
	{"PerfectSummons", "Идеальный вызов", {9, -1}},
};
assert_enum(spell, LastSpell);
getstr_enum(spell);

int	hero::getlevel(spell_s value) const {
	int result = 0;
	switch(type) {
	case Cleric:
		result = spell_data[value].level[1];
		break;
	case Wizard:
		if(value == SpellDetectMagic && race == Elf)
			result = 0;
		else if(race == Human && spell_data[value].level[0] == -1 && spell_data[value].level[0] != -1 && isknown(value))
			result = spell_data[value].level[1];
		else
			result = spell_data[value].level[0];
		break;
	default:
		return -1;
	}
	// Prodigy
	if(result && prodigy.is(value))
		result--;
	return result;
}

static int range(int c, int d, int b, bool effect_maximizd) {
	if(effect_maximizd)
		return c*d + b;
	return dice::roll(c, d) + b;
}

result_s hero::cast(spell_s value, monster* te) {
	auto ability = getstat(CastASpell);
	auto result = roll(get(ability));
	bool effect_maximized = false;
	bool target_doubled = false;
	act("%герой выкрикнул%а мистическую формулу.");
	switch(result) {
	case Fail:
		logs::add("Вас озарила вспышка, которая нанесла урон вашему телу.");
		sufferharm(dice::roll(1, 6));
		logs::add("Заклинание '%1' было забыто.", getstr(value));
		setprepared(value, false);
		return Fail;
	case PartialSuccess:
		logs::add("Но что-то пошло не так.");
		logs::add(1, "Вы привлекли нежелательное внимание и подставились под удар.");
		logs::add(2, "Заклинание повредило мироздания - дальнейшие попытки создать заклинания будут идти с [--1].");
		logs::add(3, "После создания заклинания оно будет забыто. Вы не сможете его использовать снова пока не подготовите.");
		switch(logs::input(true, false, "Выберите одну [неприятность]")) {
		case 1:
			logs::add("Часть энергии заклинания повредило ваше тело.");
			sufferharm(dice::roll(1, 6));
			break;
		case 2:
			logs::add("Заклинание повредило вашу связь с мирозданием.");
			castpenalty++;
			break;
		case 3:
			logs::add("Заклинание '%1' было забыто.", getstr(value));
			setprepared(value, false);
			break;
		}
		break;
	case Success:
		if(is(EmpoweredMagic)) {
			logs::add(1, "Эффект заклинания будет [максимальный], но вы получите 1-3 урона.");
			logs::add(2, "[Удвоенное] количество целей, но заклинание будет забыто.");
			logs::add(0, "Ничего не надо. Просто обычный эффект.");
			switch(logs::input(true, false, "[%1] может усилить заклинание за небольшую плату", getname())) {
			case 1:
				effect_maximized = true;
				sufferharm(xrand(1, 3));
				break;
			case 2:
				target_doubled = true;
				setprepared(value, false);
				break;
			}
		}
	}
	int random_effect = 0;
	if(spell_data[value].random) {
		if(effect_maximized)
			random_effect = spell_data[value].random.maximal();
		else
			random_effect = spell_data[value].random.roll();
	}
	hero* th = 0;
	switch(spell_data[value].target) {
	case Self: th = this; break;
	case Hero: th = game::whodo("На кого создать заклинание [%1]?", getstr(value)); break;
	}
	if(spell_data[value].effect) {
		if(th)
			th->act(spell_data[value].effect, random_effect);
		else
			act(spell_data[value].effect, random_effect);
	}
	void* target = th;
	switch(spell_data[value].target) {
	case Monster:
		if(te) {
			switch(value) {
			case SpellMagicMissile:
				inflictharm(*te, random_effect);
				break;
			case SpellFireball:
				inflictharm(*te, random_effect);
				inflictharm(*te, (random_effect * 2) / 3);
				inflictharm(*te, random_effect / 2);
				break;
			}
		}
		break;
	case Hero:
	case Self:
		switch(value) {
		case SpellCureLightWounds:
			th->healharm(random_effect);
			break;
		}
		break;
	}
	if(spell_data[value].ongoing)
		add(value);
	return result;
}

bool hero::isknown(spell_s value) const {
	return (spells_known[value / 8] & (1 << (value % 8))) != 0;
}

bool hero::isprepared(spell_s value) const {
	return (spells_prepared[value / 8] & (1 << (value % 8))) != 0;
}

void hero::setknown(spell_s value, bool state) {
	if(state)
		spells_known[value / 8] |= 1 << (value % 8);
	else
		spells_known[value / 8] &= ~(1 << (value % 8));
}

void hero::setprepared(spell_s value, bool state) {
	if(state)
		spells_prepared[value / 8] |= 1 << (value % 8);
	else
		spells_prepared[value / 8] &= ~(1 << (value % 8));
}

unsigned hero::getspells(spell_s* source, unsigned maximum) {
	if(!iscaster())
		return 0;
	auto pb = source;
	auto pe = pb + maximum;
	for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1)) {
		if(pb >= pe)
			break;
		if(!isprepared(e))
			continue;
		auto n = getlevel(e);
		if(n == -1 || n > level)
			continue;
		if(pb < pe)
			*pb++ = e;
	}
	return pb - source;
}

int hero::getpreparedlevels() const {
	int result = 0;
	for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1)) {
		if(!isprepared(e))
			continue;
		result += getlevel(e);
	}
	return result;
}

void hero::preparespells(bool interactive) {
	if(!iscaster())
		return;
	memset(spells_prepared, 0, sizeof(spells_prepared));
	castpenalty = 0;
	for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1)) {
		if(getlevel(e) == 0)
			setprepared(e, true);
	}
	auto cup = level + 1;
	while(true) {
		auto left = cup - getpreparedlevels();
		if(left <= 0)
			break;
		for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1)) {
			auto level = getlevel(e);
			if(level < 1)
				continue;
			if(!isknown(e))
				continue;
			if(isprepared(e))
				continue;
			if(level <= 1)
				logs::add(e, getstr(e));
			else
				logs::add(e, "%1. Стоит [%2i].", getstr(e), level);
		}
		auto value = (spell_s)logs::input(interactive, false,
			(type == Cleric || type == Paladin) ?
			"[%1] склонил%2 голову и начал%2 молиться. Какие молитвы подготовить? (осталось [%3i])" :
			"[%1] остался наедине со своими книгами и принялся изучать книгу заклинаний. Какое заклинание подготовить? (осталось [%3i])",
			getname(), getA(), left);
		setprepared(value, true);
	}
}

void spell_state::remove() {
	if(caster && spell_data[spell].remove)
		caster->act(spell_data[spell].remove);
	clear();
}