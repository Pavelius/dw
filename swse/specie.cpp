#include "main.h"

speciei bsmeta<speciei>::elements[] = {{"No species", "��� ����"},
{"Human", "�������", {0, 0, 0, 0, 0, 0}, {BonusFeat, BonusSkill}},
{"Bothan", "�����", {0, 2, -2, 0, 0, 0}, {IronWill, SkillFocusGatherInformation}},
{"Cerean", "������", {0, -2, 0, 2, 2, 0}, {IntuitiveInitiative, SkillFocusInitiative}},
{"Duros", "�����", {0, 2, -2, 2, 0, 0}, {ExpertPilot}},
{"Ewoks", "����", {-2, 2, 0, 0, 0, 0}, {Primitive, Scent, Sneaky, SkillFocusSurvival}},
{"Gammorean", "����������", {2, -2, 0, -2, 0, 0}, {Primitive, GreatFortitude, ImprovedDamageThreshold}},
{"Gungans", "������", {0, 2, 0, -2, 0, -2}, {ExpertSwimmer, HoldBreath, LightingReflexes, LowlightVision}},
{"Ithorians", "���������", {0, -2, 0, 0, 2, 2}, {IronWill, Bellow, SurvivalInstinct, SkillFocusLifeSciences}},
{"KelDor", "�����������", {0, 2, -2, 0, 2, 0}, {KeenForceSence, LowlightVision}},
{"Mon Calamari", "��� ���������", {0, 0, -2, 2, 2, 0}, {BreathUnderwater, ExpertSwimmer, LowlightVision, SkillFocusPerception}},
{"Quarren", "�������", {0, 0, 2, 0, -2, -2}, {BreathUnderwater, ExpertSwimmer, LowlightVision, SkillFocusPersuasion}},
{"Rodians", "������", {0, 2, 0, 0, -2, -2}, {HeightenAwareness, LowlightVision, SkillFocusSurvival}},
{"Sullustans", "�����������", {0, 2, -2, 0, 0, 0}, {Darkvision, ExpertClimber, HeightenAwareness}},
{"Trandoshans", "�����������", {2, -2, 0, 0, 0, 0}, {Darkvision, LimbRegeneration, NaturalArmor, Toughness}},
{"Twileks", "���\'���", {0, 0, 0, -2, 0, 2}, {Deceptive, GreatFortitude, LowlightVision}},
{"Zabrak", "������", {0, 0, 0, 0, 0, 0}, {HeightenAwareness, SuperiorDefences}},
{"Wookie", "����", {4, -2, 2, 0, -2, -2}, {ExtraordinaryRecuperation, Rage}},
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