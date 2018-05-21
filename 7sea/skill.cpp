#include "main.h"

static struct skill_i
{
	const char*			name[2];
	adat<knack_s, 16>	knacks;
	adat<knack_s, 16>	knacks_advanced;
} skill_data[] = {
	{{"Artist", "������� ���������"}, {6, {Composer, Drawing, Musician, Sculpting, Singing, Writing}}},
	{{"Courtier", "����������"}, {4, {Dancing, Etiquette, Fashion, Oratory}}},
	{{"Criminal", "����������"}, {3, {Gambling, Shadowing, Stealth}}},
	{{"Doctor", "������"}, {2, {Diagnosis, FirstAid}}},
	{{"Hunter", "�������"}, {7, {Fishing, Skinning, Stealth, Survival, Tracking, TrailSigns, Traps}}},
	{{"Merchant", "��������"}, {9, {Blacksmith, Butcher, Cooking, Fletcher, Furrier, Glassblower, Innkeeper, Jeweler, Potter}}},
	{{"Performer", "������"}, {4, {Acting, Dancing, Oratory, Singing}}},
	{{"Sailor", "�����"}, {4, {Balance, Climbing, Knotwork, Rigging}}},
	{{"Scholar", "������"}, {4, {History, Mathematics, Philosophy, Research}}},
	{{"Servant", "�����"}, {4, {Etiquette, Fashion, MenitalTask, Unobrusive}}},
	{{"Spy", "�����"}, {2, {Shadowing, Stealth}}},
	{{"Streetwise", "������� �����"}, {2, {Socializing, StreetNavigation}}},
	// Martial skills
	{{"Archer", "������"}},
	{{"Athlete", "�����"}},
	{{"Buckler", "���"}},
	{{"Commander", "������������"}},
	{{"Crossbow", "�������"}},
	{{"Dirty Fighting", "������� ���"}},
	{{"Fencing", "����������"}},
	{{"Firearms", "������������� ������"}},
	{{"Heavy weapon", "������� ������"}},
	{{"Knife", "���"}},
	{{"Panzerhand", "����������"}},
	{{"Polearm", "�����"}},
	{{"Pugilism", "����"}},
	{{"Rider", "��������"}},
	{{"Wrestling", "������"}},
};
assert_enum(skill, LastSkill);
getstr_enum(skill);

void hero::set(skill_s value, bool interacive, char* skills)
{
	skills[value]++;
	switch(value)
	{
	case Hunter:
		break;
	case Artist:
		break;
	case Merchant:
		break;
	default:
		for(auto e : skill_data[value].knacks)
			knacks[e]++;
		break;
	}
}

int hero::getcost(skill_s value) const
{
	if(iscivil(value))
	{
		if(get(University))
			return 1;
	}
	else
	{
		if(get(Academy))
			return 1;
	}
	return 2;
}

bool hero::iscivil(skill_s value)
{
	return value >= Artist && value <= Streetwise;
}