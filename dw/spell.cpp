#include "main.h"

static struct spell_i
{
	const char*		name[2];
	char			level[2];
	target_s		target;
	bool			ongoing;
} spell_data[] = {
	{{"Light", "����"}, {0, -1}},
	//
	{{"Unseen Servant", "��������� �����"}, {0, -1}, TargetSelf, true},
	{{"Prestidigitation", "������"}, {0, -1}},
	{{"Contact Spirits", "����� �����"}, {1, -1}},
	{{"Detect Magic", "���������� �����"}, {1, -1}},
	{{"Telepathy", "���������"}, {1, -1}, TargetSelf, true},
	{{"Charm Person", "��������� �������"}, {1, -1}, TargetSelf, true},
	{{"Invisibility", "�����������"}, {1, -1}, TargetSelf, true},
	{{"Magic Missile", "��������� ������"}, {1, -1}, TargetEnemy},
	{{"Alarm", "�������"}, {1, -1}},
	//
	{{"Dispel Magic", "�������� �����"}, {3, -1}},
	{{"Visions through Time", "������� ������ �����"}, {3, -1}},
	{{"Fireball", "�������� ���"}, {3, -1}, TargetEnemy},
	{{"Mimic", "�����"}, {3, -1}},
	{{"Mirror Image", "���������� �����������"}, {3, -1}},
	{{"Sleep", "���"}, {3, -1}},
	//
	{{"Cage", "������"}, {5, -1}},
	{{"Contact Other Plane", "��������� � ������ ����������"}, {5, -1}},
	{{"Polymorph", "����������"}, {5, -1}},
	{{"Summon Monster", "����� �������"}, {5, -1}},
	//
	{{"Dominate", "�������������"}, {7, -1}},
	{{"True Seeing", "�������� ������"}, {7, -1}},
	{{"ShadowWalk", "������ �� ��������� �����"}, {7, -1}},
	{{"Contingency", "�����������"}, {7, -1}},
	{{"Cloudkill", "����� ������"}, {7, -1}},
	//
	{{"Antipathy", "���������"}, {9, -1}},
	{{"Alert", "����������"}, {9, -1}},
	{{"Soul Gem", "������� ��� ����"}, {9, -1}},
	{{"Shelter", "�������"}, {9, -1}},
	{{"Perfect Summons", "��������� �����"}, {9, -1}},
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
	logs::add("%1 ���������%2 ����������� �������.", getname(), getA());
	if(result == Fail)
	{
		logs::add("��� ������� �������, ������� ������� ���� ������ ����.");
		sufferharm(dice::roll(2, 6));
		return Fail;
	}
	if(result == PartialSuccess)
	{
		logs::add("�� ���-�� ����� �� ���.");
		logs::add(1, "�� ��������� ������������� �������� � ������������ ��� ����.");
		logs::add(2, "���������� ��������� ���������� - ���������� ������� ������� ���������� ����� ���� � [-1].");
		logs::add(3, "����� �������� ���������� ��� ����� ������. �� �� ������� ��� ������������ ����� ���� �� �����������.");
		auto id = logs::input(true, false, "�������� ���� ������������");
		switch(id)
		{
		case 1:
			logs::add("��� ������� �������, ������� ������� ���� ������ ����.");
			sufferharm(dice::roll(2, 6));
			break;
		case 2:
			logs::add("���������� ��������� ���� ����� � �����������.");
			castpenalty++;
			break;
		case 3:
			logs::add("�� ������ ���������� '%1'.", getstr(value));
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
	auto id = logs::input(true, false, "����� ���������� ������ �������?");
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
		logs::add("%1 �������%2 ������ � �����%2 ��������.", getname(), getA());
		break;
	case Wizard:
		logs::add("%1 ������� ������� �� ������ ������� � ��������� ������� ����� ����������.", getname());
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
		auto value = (spell_s)logs::input(true, false, "����� ���������� �����������?");
		setprepared(value, true);
	}
}