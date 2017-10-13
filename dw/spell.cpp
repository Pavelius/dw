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
	logs::add("%1 ���������%2 ����������� �������.", getname(), getA());
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