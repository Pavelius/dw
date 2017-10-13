#include "main.h"

static struct spell_i
{
	const char*		name[2];
	char			level[2];
	target_s		target;
	bool			ongoing;
} spell_data[] = {
	{{"Light", "Свет"}, {0, -1}},
	//
	{{"Unseen Servant", "Невидимый слуга"}, {0, -1}, TargetSelf, true},
	{{"Prestidigitation", "Фокусы"}, {0, -1}},
	{{"Contact Spirits", "Вызов духов"}, {1, -1}},
	{{"Detect Magic", "Определить магию"}, {1, -1}},
	{{"Telepathy", "Телепатия"}, {1, -1}, TargetSelf, true},
	{{"Charm Person", "Очаровать персону"}, {1, -1}, TargetSelf, true},
	{{"Invisibility", "Невидимость"}, {1, -1}, TargetSelf, true},
	{{"Magic Missile", "Волшебный снаряд"}, {1, -1}, TargetEnemy},
	{{"Alarm", "Тревога"}, {1, -1}},
	//
	{{"Dispel Magic", "Рассеять магию"}, {3, -1}},
	{{"Visions through Time", "Видения сквозь время"}, {3, -1}},
	{{"Fireball", "Огненный шар"}, {3, -1}, TargetEnemy},
	{{"Mimic", "Мимик"}, {3, -1}},
	{{"Mirror Image", "Зеркальное отображение"}, {3, -1}},
	{{"Sleep", "Сон"}, {3, -1}},
	//
	{{"Cage", "Клетка"}, {5, -1}},
	{{"Contact Other Plane", "Связаться с другим измерением"}, {5, -1}},
	{{"Polymorph", "Превратить"}, {5, -1}},
	{{"Summon Monster", "Вызов монстра"}, {5, -1}},
	//
	{{"Dominate", "Доминирование"}, {7, -1}},
	{{"True Seeing", "Истинное зрение"}, {7, -1}},
	{{"ShadowWalk", "Ходьба по измерению Теней"}, {7, -1}},
	{{"Contingency", "Постоянство"}, {7, -1}},
	{{"Cloudkill", "Туман убийца"}, {7, -1}},
	//
	{{"Antipathy", "Антипатия"}, {9, -1}},
	{{"Alert", "Оповещение"}, {9, -1}},
	{{"Soul Gem", "Изумруд для души"}, {9, -1}},
	{{"Shelter", "Убежище"}, {9, -1}},
	{{"Perfect Summons", "Идеальный вызов"}, {9, -1}},
};
assert_enum(spell, LastSpell);
getstr_enum(spell);

int	hero::getlevel(spell_s value) const
{
	int result = 0;
	switch(type)
	{
	case Cleric:
		result = spell_data[value].level[1];
		break;
	case Wizard:
		if(value == SpellDetectMagic && race == Elf)
			result = 0;
		else if(race==Human && spell_data[value].level[0]==-1 && spell_data[value].level[0] != -1 && isknown(value))
			result = spell_data[value].level[1];
		else
			result = spell_data[value].level[0];
		break;
	default:
		return -1;
	}
	if(result && choosenone.is(value))
		result--;
	return result;
}

result_s hero::cast(spell_s value, targetinfo& ti)
{
	auto ability = (type == Wizard) ? Intellegence : Wisdow;
	auto result = roll(get(ability));
	logs::add("%1 выкрикнул%2 мистическую формулу.", getname(), getA());
	if(result == Fail)
	{
		logs::add("Вас озарила вспышка, которая нанесла урон вашему телу.");
		sufferharm(dice::roll(2, 6));
		return Fail;
	}
	if(result == PartialSuccess)
	{
		logs::add("Но что-то пошло не так.");
		logs::add(1, "Вы привлекли нежелательное внимание и подставились под удар.");
		logs::add(2, "Заклинание повредило мироздания - дальнейшие попытки создать заклинания будут идти с [-1].");
		logs::add(3, "После создания заклинания оно будет забыто. Вы не сможете его использовать снова пока не подготовите.");
		auto id = logs::input(true, false, "Выберите одну неприятность");
		switch(id)
		{
		case 1:
			logs::add("Вас озарила вспышка, которая нанесла урон вашему телу.");
			sufferharm(dice::roll(2, 6));
			break;
		case 2:
			logs::add("Заклинание повредило вашу связь с мирозданием.");
			castpenalty++;
			break;
		case 3:
			logs::add("Вы забыли заклинание '%1'.", getstr(value));
			setprepared(value, false);
			break;
		}
	}
	return result;
}

bool hero::isknown(spell_s value) const
{
	return (spells_known[value / 8] & (1 << (value % 8))) != 0;
}

bool hero::isprepared(spell_s value) const
{
	return (spells_prepared[value / 8] & (1 << (value % 8))) != 0;
}

void hero::setknown(spell_s value, bool state)
{
	if(state)
		spells_known[value / 8] |= 1 << (value % 8);
	else
		spells_known[value / 8] &= ~(1 << (value % 8));
}

void hero::setprepared(spell_s value, bool state)
{
	if(state)
		spells_prepared[value / 8] |= 1 << (value % 8);
	else
		spells_prepared[value / 8] &= ~(1 << (value % 8));
}

unsigned hero::getspells(spell_s* source, unsigned maximum, targetinfo& ti)
{
	if(!iscaster())
		return 0;
	auto pb = source;
	auto pe = pb + maximum;
	for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1))
	{
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

result_s hero::cast(spell_s* source, unsigned count, targetinfo& ti)
{
	for(unsigned i = 0; i < count; i++)
		logs::add(i, getstr(source[i]));
	auto id = logs::input(true, false, "Какое заклинание хотите создать?");
	if(id == 500)
		return Success;
	return cast(source[id], ti);
}

int hero::getpreparedlevels() const
{
	int result = 0;
	for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1))
	{
		if(!isprepared(e))
			continue;
		result += getlevel(e);
	}
	return result;
}

bool hero::isongoing(spell_s value) const
{
	for(auto& e : ongoing)
	{
		if(e.type == value)
			return true;
	}
	return false;
}

void hero::preparespells()
{
	if(!iscaster())
		return;
	switch(type)
	{
	case Cleric:
		logs::add("%1 склонил%2 голову и начал%2 молиться.", getname(), getA());
		break;
	case Wizard:
		logs::add("%1 остался наедине со своими книгами и проинялся изучать книгу заклинаний.", getname());
		break;
	}
	memset(spells_prepared, 0, sizeof(spells_prepared));
	castpenalty = 0;
	for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1))
	{
		if(getlevel(e) == 0)
			setprepared(e, true);
	}
	auto cup = level + 1;
	while(getpreparedlevels() < cup)
	{
		for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1))
		{
			if(getlevel(e) < 1)
				continue;
			if(!isknown(e))
				continue;
			if(isprepared(e))
				continue;
			logs::add(e, getstr(e));
		}
		auto value = (spell_s)logs::input(true, false, "Какое заклинание подготовить?");
		setprepared(value, true);
	}
}