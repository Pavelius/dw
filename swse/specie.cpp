#include "main.h"

speciei bsmeta<speciei>::elements[] = {{"No species", "Нет расы"},
{"Human", "Человек", {0, 0, 0, 0, 0, 0}, {BonusFeat, BonusSkill}},
{"Bothan", "Ботан", {0, 2, -2, 0, 0, 0}, {IronWill, SkillFocusGatherInformation}},
{"Cerean", "Цереан", {0, -2, 0, 2, 2, 0}, {IntuitiveInitiative, SkillFocusInitiative}},
{"Duros", "Дурос", {0, 2, -2, 2, 0, 0}, {ExpertPilot}},
{"Ewoks", "Эвок", {-2, 2, 0, 0, 0, 0}, {Primitive, Scent, Sneaky, SkillFocusSurvival}},
{"Gammorean", "Гамореанец", {2, -2, 0, -2, 0, 0}, {Primitive, GreatFortitude, ImprovedDamageThreshold}},
{"Gungans", "Гунган", {0, 2, 0, -2, 0, -2}, {ExpertSwimmer, HoldBreath, LightingReflexes, LowlightVision}},
{"Ithorians", "Иторианец", {0, -2, 0, 0, 2, 2}, {IronWill, Bellow, SurvivalInstinct, SkillFocusLifeSciences}},
{"KelDor", "Келдорианец", {0, 2, -2, 0, 2, 0}, {KeenForceSence, LowlightVision}},
{"Mon Calamari", "Мон Каламарец", {0, 0, -2, 2, 2, 0}, {BreathUnderwater, ExpertSwimmer, LowlightVision, SkillFocusPerception}},
{"Quarren", "Кваррен", {0, 0, 2, 0, -2, -2}, {BreathUnderwater, ExpertSwimmer, LowlightVision, SkillFocusPersuasion}},
{"Rodians", "Родиан", {0, 2, 0, 0, -2, -2}, {HeightenAwareness, LowlightVision, SkillFocusSurvival}},
{"Sullustans", "Суллустанец", {0, 2, -2, 0, 0, 0}, {Darkvision, ExpertClimber, HeightenAwareness}},
{"Trandoshans", "Трандошанец", {2, -2, 0, 0, 0, 0}, {Darkvision, LimbRegeneration, NaturalArmor, Toughness}},
{"Twileks", "Тви\'лек", {0, 0, 0, -2, 0, 2}, {Deceptive, GreatFortitude, LowlightVision}},
{"Zabrak", "Забрак", {0, 0, 0, 0, 0, 0}, {HeightenAwareness, SuperiorDefences}},
{"Wookie", "Вуки", {4, -2, 2, 0, -2, -2}, {ExtraordinaryRecuperation, Rage}},
};
assert_enum(specie, Wookie);

void creature::set(specie_s id) {
	specie = id;
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
		abilities[i] += bsmeta<speciei>::elements[id].abilities[i];
	for(auto e = FirstFeat; e <= LastFeat; e = (feat_s)(e + 1)) {
		if(is(e))
			continue;
		if(!isallow(e))
			continue;
		set(e);
	}
}