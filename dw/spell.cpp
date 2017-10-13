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
};
assert_enum(spell, SpellSleep);
getstr_enum(spell);

int	hero::getlevel(spell_s value) const
{
	switch(type)
	{
	case Cleric: return spell_data[value].level[1];
	case Wizard: return spell_data[value].level[0];
	default: return -1;
	}
}

result_s hero::cast(spell_s value, targetinfo& ti)
{
	auto ability = (type == Wizard) ? Intellegence : Wisdow;
	auto result = roll(get(ability));
	logs::add("%1 выкрикнул%2 мистическую формулу.", getname(), getA());
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