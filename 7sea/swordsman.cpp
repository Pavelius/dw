#include "main.h"

static struct swordsman_i
{
	const char*		name[2];
	skill_s			skills[2];
	knack_s			knacks[4];
} swordsman_data[] = {
	{{"", ""}},
	{{"Aldana", "�������"}, {Courtier, Fencing}, {Feint, Riposte, Togging, FindWeakness}},
	{{"Ambrogia", "���������"}, {DirtyFighting, Fencing}, {Feint, PommelStrike, Riposte, FindWeakness}},
	{{"Donowan", "�������"}, {Buckler, Fencing}, {Bind, Disarm, Riposte, FindWeakness}},
	{{"Eisenfaust", "����������"}, {HeavyWeapon, PanzerhandSkill}, {Beat, Bind, Disarm, FindWeakness}},
	{{"Leegstra", "�������"}, {HeavyWeapon, Wrestling}, {Beat, CorpseACorpse, Lunge, FindWeakness}},
	{{"Valroux", "��������"}, {Knife, Fencing}, {DoubleParry, Feint, Togging, FindWeakness}},
};
assert_enum(swordsman, LastSwordsmansSchool);
getstr_enum(swordsman);

void hero::set(swordsman_s value, bool interactive, char* skills)
{
	for(auto e : swordsman_data[value].skills)
		set(e, false, skills);
	for(auto e : swordsman_data[value].knacks)
		set(e, 1);
}
