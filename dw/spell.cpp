#include "main.h"

spelli bsmeta<spelli>::elements[] = {{"Guidance", "Направление", {-1, 0}},
{"Light", "Свет", {0, 0}},
{"Prestidigitation", "Фокусы", {0, -1}},
{"Sanctify", "Очищение", {-1, 0}},
{"UnseenServant", "Невидимый слуга", {0, -1}, TargetSelf, true},
//
{"Bless", "Благословение", {-1, 1}, TargetSelf, true, "Поле боя озарилось светом."},
{"CauseFear", "Вызвать страх", {-1, 1}, TargetSelf, true, "Ваша фигура озарилась темным светом."},
{"ContactSpirits", "Вызов духов", {1, -1}},
{"CureLightWounds", "Лечить легкие ранения", {-1, 1}, TargetHero, false, "%герой озарился белым светом."},
{"DetectAlignment", "Определить мировозрение", {-1, 1}},
{"DetectMagic", "Определить магию", {1, -1}},
{"Telepathy", "Телепатия", {1, -1}, TargetSelf, true},
{"CharmPerson", "Очаровать персону", {1, -1}, TargetSelf, true},
{"Invisibility", "Невидимость", {1, -1}, TargetSelf, true, "Внезапно все ваши герои исчезли из виду.", "Вдруг откуда ни возьмись появились все персонажи."},
{"MagicMissile", "Волшебный снаряд", {1, -1}, TargetMonster, false, "С пальцев сорвалось несколько разноцветных шариков, которые поразили врага."},
{"MagicWeapon", "Волшебное оружие", {-1, 1}, TargetSelf, false},
{"Sanctuary", "Убежище", {1, -1}, TargetSelf, false},
{"SpeakWithDead", "Разговор с мертвецами", {-1, 1}, TargetSelf, false},
{"Alarm", "Тревога", {1, -1}},
//
{"DispelMagic", "Рассеять магию", {3, -1}},
{"VisionsThroughTime", "Видения сквозь время", {3, -1}},
{"Fireball", "Огненный шар", {3, -1}, TargetMonster},
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

int casti::roll() const {
	auto r = 0;
	auto& ed = bsmeta<spelli>::elements[id];
	//if(ed.random) {
	//	if(maximized)
	//		r = ed.random.maximal();
	//	else
	//		r = ed.random.roll();
	//}
	return r;
}

int	hero::getlevel(spell_s subtype) const {
	int result = 0;
	auto& ed = bsmeta<spelli>::elements[subtype];
	switch(type) {
	case Cleric:
		result = ed.level[1];
		break;
	case Wizard:
		if(subtype == SpellDetectMagic && race == Elf)
			result = 0;
		else if(race == Human && ed.level[0] == -1 && ed.level[0] != -1 && is(subtype))
			result = ed.level[1];
		else
			result = ed.level[0];
		break;
	default:
		return -1;
	}
	// Prodigy
	if(result && prodigy.is(subtype))
		result--;
	return result;
}

static int range(int c, int d, int b, bool effect_maximizd) {
	if(effect_maximizd)
		return c*d + b;
	return dice::roll(c, d) + b;
}

result_s hero::cast(casti& ci) {
	auto ability = getstat(CastASpell);
	auto result = roll(get(ability));
	auto spell_name = getstr(ci.id);
	act("%герой выкрикнул%а мистическую формулу.");
	switch(result) {
	case Fail:
		sb.add("Вас озарила вспышка, которая нанесла урон вашему телу.");
		sufferharm(dice::roll(1, 6));
		sb.add("Заклинание '%1' было забыто.", spell_name);
		setprepared(ci.id, false);
		return Fail;
	case PartialSuccess:
		sb.add("Но что-то пошло не так.");
		an.add(1, "Вы привлекли нежелательное внимание и подставились под удар.");
		an.add(2, "Заклинание повредило мироздания - дальнейшие попытки создать заклинания будут идти с [--1].");
		an.add(3, "После создания заклинания оно будет забыто. Вы не сможете его использовать снова пока не подготовите.");
		switch(an.choose(true, false, "Выберите одну [неприятность]")) {
		case 1:
			sb.add("Часть энергии заклинания повредило ваше тело.");
			sufferharm(dice::roll(1, 6));
			break;
		case 2:
			sb.add("Заклинание повредило вашу связь с мирозданием.");
			castpenalty++;
			break;
		case 3:
			sb.add("Заклинание '%1' было забыто.", spell_name);
			setprepared(ci.id, false);
			break;
		}
		break;
	case Success:
		if(is(EmpoweredMagic)) {
			an.add(1, "Эффект заклинания будет [максимальный], но вы получите 1-3 урона.");
			an.add(2, "[Удвоенное] количество целей, но заклинание будет забыто.");
			an.add(0, "Ничего не надо. Просто обычный эффект.");
			switch(an.choose(false, "[%1] может усилить заклинание за небольшую плату", getname())) {
			case 1:
				ci.maximized = true;
				sufferharm(xrand(1, 3));
				break;
			case 2:
				ci.doubled = true;
				setprepared(ci.id, false);
				break;
			}
		}
	}
}

bool hero::cast(spell_s subtype, thing& enemy) {
	casti ci = subtype;
	auto result = cast(ci);
	auto success = (result == Success || result == PartialSuccess);
	return success;
}

//result_s hero::cast(spell_s subtype, monster* te) {
//	int random_effect = 0;
//	casti ci = subtype;
//	auto& ed = bsmeta<spelli>::elements[subtype];
//	auto result = cast(ci);
//	if(ed.random) {
//		if(ci.maximized)
//			random_effect = ed.random.maximal();
//		else
//			random_effect = ed.random.roll();
//	}
//	hero* th = 0;
//	switch(ed.target) {
//	case TargetSelf: th = this; break;
//	case TargetHero: th = game::whodo("На кого создать заклинание [%1]?", getstr(subtype)); break;
//	}
//	if(ed.effect) {
//		if(th)
//			th->act(ed.effect, random_effect);
//		else
//			act(ed.effect, random_effect);
//	}
//	void* target = th;
//	switch(ed.target) {
//	case TargetMonster:
//		if(te) {
//			switch(subtype) {
//			case SpellMagicMissile:
//				inflictharm(*te, random_effect);
//				break;
//			case SpellFireball:
//				inflictharm(*te, random_effect);
//				inflictharm(*te, (random_effect * 2) / 3);
//				inflictharm(*te, random_effect / 2);
//				break;
//			}
//		}
//		break;
//	case TargetHero:
//	case TargetSelf:
//		switch(subtype) {
//		case SpellCureLightWounds:
//			th->healharm(random_effect);
//			break;
//		}
//		break;
//	}
//	if(ed.ongoing)
//		add(subtype);
//	return result;
//}

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
	spells_prepared.clear();
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
			if(!is(e))
				continue;
			if(isprepared(e))
				continue;
			if(level <= 1)
				an.add(e, getstr(e));
			else
				an.add(e, "%1. Стоит [%2i].", getstr(e), level);
		}
		char temp[512]; stringbuilder sbn(temp);
		auto format = "[%герой] остал%ась наедине со своими книгами и принял%ась изучать книгу заклинаний. Какое заклинание подготовить? (осталось [%1i])";
		if(type == Cleric || type == Paladin)
			format = "[%герой] склонил%а голову и начал%а молиться. Какие молитвы подготовить? (осталось [%1i])";
		act(sbn, format, left);
		auto subtype = (spell_s)an.choose(interactive, true, temp);
		setprepared(subtype, true);
	}
}

void spell_state::remove() {
	if(caster && bsmeta<spelli>::elements[spell].remove)
		caster->act(bsmeta<spelli>::elements[spell].remove);
	clear();
}