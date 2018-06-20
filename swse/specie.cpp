#include "main.h"

static struct specie_i
{
	const char*			name[2];
	char				abilities[6];
	feata				starting_feats;
} specie_data[] = {
	{{"No species", "Нет расы"}},
	{{"Human", "Человек"}, {0, 0, 0, 0, 0, 0}, {2, {BonusFeat, BonusSkill}}},
	{{"Bothan", "Ботан"}, {0, 2, -2, 0, 0, 0}, {2, {IronWill, SkillFocusGatherInformation}}},
	{{"Cerean", "Цереан"}, {0, -2, 0, 2, 2, 0}, {2, {IntuitiveInitiative, SkillFocusInitiative}}},
	{{"Duros", "Дурос"}, {0, 2, -2, 2, 0, 0}, {1, {ExpertPilot}}},
	{{"Ewoks", "Эвок"}, {-2, 2, 0, 0, 0, 0}, {4, {Primitive, Scent, Sneaky, SkillFocusSurvival}}},
	{{"Gammorean", "Гамореанец"}, {2, -2, 0, -2, 0, 0}, {3, {Primitive, GreatFortitude, ImprovedDamageThreshold}}},
	{{"Gungans", "Гунган"}, {0, 2, 0, -2, 0, -2}, {4, {ExpertSwimmer, HoldBreath, LightingReflexes, LowlightVision}}},
	{{"Ithorians", "Иторианец"}, {0, -2, 0, 0, 2, 2}, {4, {IronWill, Bellow, SurvivalInstinct, SkillFocusLifeSciences}}},
	{{"KelDor", "Келдорианец"}, {0, 2, -2, 0, 2, 0}, {2, {KeenForceSence, LowlightVision}}},
	{{"Mon Calamari", "Мон Каламарец"}, {0, 0, -2, 2, 2, 0}, {4, {BreathUnderwater, ExpertSwimmer, LowlightVision, SkillFocusPerception}}},
	{{"Quarren", "Кваррен"}, {0, 0, 2, 0, -2, -2}, {4, {BreathUnderwater, ExpertSwimmer, LowlightVision, SkillFocusPersuasion}}},
	{{"Rodians", "Родиан"}, {0, 2, 0, 0, -2, -2}, {3, {HeightenAwareness, LowlightVision, SkillFocusSurvival}}},
	{{"Sullustans", "Суллустанец"}, {0, 2, -2, 0, 0, 0}, {3, {Darkvision, ExpertClimber, HeightenAwareness}}},
	{{"Trandoshans", "Трандошанец"}, {2, -2, 0, 0, 0, 0}, {4, {Darkvision, LimbRegeneration, NaturalArmor, Toughness}}},
	{{"Twileks", "Тви\'лек"}, {0, 0, 0, -2, 0, 2}, {3, {Deceptive, GreatFortitude, LowlightVision}}},
	{{"Zabrak", "Забрак"}, {0, 0, 0, 0, 0, 0}, {2, {HeightenAwareness, SuperiorDefences}}},
	{{"Wookie", "Вуки"}, {4, -2, 2, 0, -2, -2}, {2, {ExtraordinaryRecuperation, Rage}}},
};
assert_enum(specie, Wookie);
getstr_enum(specie);

void creature::set(specie_s id)
{
	specie = id;
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
		abilities[i] += specie_data[id].abilities[i];
	for(auto e : specie_data[id].starting_feats)
	{
		if(is(e))
			continue;
		if(!isallow(e))
			continue;
		set(e);
	}
}