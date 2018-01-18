#include "main.h"

static struct spell_i
{
	const char*		id;
	const char*		name;
	char			level[2];
	target_s		target;
	bool			ongoing;
	dice			random;
	const char*		effect;
	const char*		remove;
} spell_data[] = {
	{"Light", "����", {0, -1}},
	//
	{"Unseen Servant", "��������� �����", {0, -1}, TargetSelf, true},
	{"Prestidigitation", "������", {0, -1}},
	{"Contact Spirits", "����� �����", {1, -1}},
	{"Detect Magic", "���������� �����", {1, -1}},
	{"Telepathy", "���������", {1, -1}, TargetSelf, true},
	{"Charm Person", "��������� �������", {1, -1}, TargetSelf, true},
	{"Invisibility", "�����������", {1, -1}, TargetAlly, true, {}, "�������� %����� �����%�� �� ����.", "����� ������ �� �������� ������%��� %�����."},
	{"Magic Missile", "��������� ������", {1, -1}, TargetEnemy, false, {2, 4}, "� ������� ��������� ��������� ������������ �������, ������� �������� [%1]."},
	{"Alarm", "�������", {1, -1}},
	//
	{"Dispel Magic", "�������� �����", {3, -1}},
	{"Visions through Time", "������� ������ �����", {3, -1}},
	{"Fireball", "�������� ���", {3, -1}, TargetEnemy},
	{"Mimic", "�����", {3, -1}},
	{"Mirror Image", "���������� �����������", {3, -1}},
	{"Sleep", "���", {3, -1}},
	//
	{"Cage", "������", {5, -1}},
	{"Contact Other Plane", "��������� � ������ ����������", {5, -1}},
	{"Polymorph", "����������", {5, -1}},
	{"Summon Monster", "����� �������", {5, -1}},
	//
	{"Dominate", "�������������", {7, -1}},
	{"True Seeing", "�������� ������", {7, -1}},
	{"ShadowWalk", "������ �� ��������� �����", {7, -1}},
	{"Contingency", "�����������", {7, -1}},
	{"Cloudkill", "����� ������", {7, -1}},
	//
	{"Antipathy", "���������", {9, -1}},
	{"Alert", "����������", {9, -1}},
	{"Soul Gem", "������� ��� ����", {9, -1}},
	{"Shelter", "�������", {9, -1}},
	{"Perfect Summons", "��������� �����", {9, -1}},
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
	// Prodigy
	if(result && prodigy.is(value))
		result--;
	return result;
}

static int range(int c, int d, int b, bool effect_maximizd)
{
	if(effect_maximizd)
		return c*d + b;
	return dice::roll(c, d) + b;
}

void hero::cast(spell_s value, targetinfo ti)
{
	char temp[260];
	auto ability = getstat(CastASpell);
	auto result = roll(get(ability));
	bool effect_maximized = false;
	bool target_doubled = false;
	act("%����� ���������%� ����������� �������.");
	switch(result)
	{
	case Fail:
		logs::add("��� ������� �������, ������� ������� ���� ������ ����.");
		sufferharm(dice::roll(1, 6));
		logs::add("���������� '%1' ���� ������.", getstr(value));
		setprepared(value, false);
		return;
	case PartialSuccess:
		logs::add("�� ���-�� ����� �� ���.");
		logs::add(1, "�� ��������� ������������� �������� � ������������ ��� ����.");
		logs::add(2, "���������� ��������� ���������� - ���������� ������� ������� ���������� ����� ���� � [--1].");
		logs::add(3, "����� �������� ���������� ��� ����� ������. �� �� ������� ��� ������������ ����� ���� �� �����������.");
		switch(logs::input(true, false, "�������� ���� [������������]"))
		{
		case 1:
			logs::add("����� ������� ���������� ��������� ���� ����.");
			sufferharm(dice::roll(1, 6));
			break;
		case 2:
			logs::add("���������� ��������� ���� ����� � �����������.");
			castpenalty++;
			break;
		case 3:
			logs::add("���������� '%1' ���� ������.", getstr(value));
			setprepared(value, false);
			break;
		}
		break;
	case Success:
		if(is(EmpoweredMagic))
		{
			logs::add(1, "������ ���������� ����� [������������], �� �� �������� 1-3 �����.");
			logs::add(2, "[���������] ���������� �����, �� ���������� ����� ������.");
			logs::add(0, "������ �� ����. ������ ������� ������.");
			switch(logs::input(true, false, "[%1] ����� ������� ���������� �� ��������� �����", getname()))
			{
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
	if(spell_data[value].random)
	{
		if(effect_maximized)
			random_effect = spell_data[value].random.maximal();
		else
			random_effect = spell_data[value].random.roll();
	}
	if(spell_data[value].effect)
		act(spell_data[value].effect, grammar::of(temp, ti.enemy->getname()));
	switch(value)
	{
	case SpellMagicMissile:
		inflictharm(*ti.enemy, random_effect);
		break;
	}
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

void hero::cast(targetinfo& ti)
{
	for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1))
	{
		if(!isprepared(e))
			continue;
		if(spell_data[e].target == TargetEnemy && !ti.enemy)
			continue;
		logs::add(e, getstr(e));
	}
	logs::sort();
	auto e = (spell_s)logs::input(true, false, "����� ���������� ������ ������� [%1]?", getname());
	cast(e, ti);
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

void hero::preparespells(bool interactive)
{
	if(!iscaster())
		return;
	memset(spells_prepared, 0, sizeof(spells_prepared));
	castpenalty = 0;
	for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1))
	{
		if(getlevel(e) == 0)
			setprepared(e, true);
	}
	auto cup = level + 1;
	while(true)
	{
		auto left = cup - getpreparedlevels();
		if(left <= 0)
			break;
		for(auto e = FirstSpell; e <= LastSpell; e = (spell_s)(e + 1))
		{
			auto level = getlevel(e);
			if(level < 1)
				continue;
			if(!isknown(e))
				continue;
			if(isprepared(e))
				continue;
			if(level<=1)
				logs::add(e, getstr(e));
			else
				logs::add(e, "%1. ����� [%2i].", getstr(e), level);
		}
		auto value = (spell_s)logs::input(interactive, false,
			(type==Cleric || type==Paladin) ?
			"[%1] �������%2 ������ � �����%2 ��������. ����� ������� �����������? (�������� [%3i])":
			"[%1] ������� ������� �� ������ ������� � �������� ������� ����� ����������. ����� ���������� �����������? (�������� [%3i])",
			getname(), getA(), left);
		setprepared(value, true);
	}
}

void spell_state::remove() {
	auto player = target.ally;
	if(player) {
		if(spell_data[spell].remove)
			player->act(spell_data[spell].remove);
	}
}