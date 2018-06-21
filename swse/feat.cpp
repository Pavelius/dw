#include "main.h"

struct prerequisit_i {
	adat<feat_s, 8>			feats;
	char					abilities[Charisma + 1];
	char					base_attack_bonus;
};
static struct feat_i {
	const char*				id;
	const char*				name;
	talent_s				tree;
	prerequisit_i			require;
} feat_data[] = {{"", ""},
{"Adept negotiator", "", JediConsular},
{"Force persuasion", "", JediConsular, {{AdeptNegotiator}}},
{"Master negotiator", "", JediConsular, {{AdeptNegotiator}}},
{"Skilled advisor", "", JediConsular},
{"Acrobatic recovery", "", JediGuardian},
{"Battle Meditation", "", JediGuardian},
{"Elusive Target", "", JediGuardian},
{"Force Intuition", "", JediGuardian},
{"Resilience", "", JediGuardian},
{"Clear Mind", "", JediSentinel},
{"Dark Side Sence", "", JediSentinel},
{"Dark Side Scourge", "", JediSentinel, {{DarkSideSence}}},
{"Force Haze", "", JediSentinel},
{"Resist Dark Side", "", JediSentinel, {{DarkSideSence}}},
{"Block", "", LightsaberCombat},
{"Deflect", "", LightsaberCombat},
{"Lightsaber Defence", "", LightsaberCombat},
{"Lightsaber Defence II", "", LightsaberCombat, {{LightsaberDefence}}},
{"Lightsaber Defence III", "", LightsaberCombat, {{LightsaberDefenceII}}},
{"Weapon Specialization (Lightsaber)", "", LightsaberCombat},
{"Lightsaber Throw", "", LightsaberCombat},
{"Redirect Shot", "", LightsaberCombat, {{Deflect}, {}, 5}},
//
{"Presence", "", Influence},
{"Demand Surrender", "", Influence, {{Presence}}},
{"Improved Weaken Resolve", "", Influence, {{Presence, WeakenResolve}}},
{"Weaken Resolve", "", Influence, {{Presence}}},
{"Bolster Ally", "", Inspiration},
{"Ignite Ferver", "", Inspiration, {{BolsterAlly, InspireConfidence}}},
{"Inspire Confidence", "", Inspiration},
{"Inspire Haste", "", Inspiration},
{"Inspire Zeal", "", Inspiration, {{BolsterAlly, InspireConfidence, IgniteFerver}}},
{"Born Leader", "", Leadership},
{"Coordinate", "", Leadership},
{"Distant Command", "", Leadership},
{"Fearless Leader", "", Leadership},
{"Rally", "", Leadership},
{"Trust", "", Leadership},
{"Connections", "", Lineage},
{"Educated", "", Lineage},
{"Spontaneous Skill", "", Lineage, {{Educated}}},
{"Wealth", "", Lineage},
//
{"Acrobatic Strike", "������������� ����", General, {{Acrobatic}}},
{"Armour Proficience Light", "������� ������ �����", General},
{"Armour Proficience Medium", "������� ������� �����", General, {{ArmourProficienceLight}}},
{"Armour Proficience Heavy", "������� ������� �����", General, {{ArmourProficienceLight, ArmourProficienceMedium}}},
{"Bantha Rush", "������", General, {{}, {13}, 1}},
{"Burst Fire", "�������� ��������� ���������", General, {{WeaponProficiencyHeavyWeapons}, {13}, 1}},
{"Careful Shoot", "���������� ��������", General, {{PointBlankShoot}, {}, 2}},
{"Charging Fire", "�������� ��� ���������", General},
{"Cleave", "����������", General},
{"Combat Reflexes", "������ ��������", General},
{"Coordinated Attack", "����������������� �����", General},
{"Crush", "��������", General},
{"Cybernetic Surgery", "��������������� ��������������", General},
{"Deadeye", "������� ����", General},
{"Dodge", "���������", General},
{"Double Attack", "������� �����", General},
{"Dreadful Rage", "������� ���������", General},
{"Dual weapon Mastery", "�������� ����� ��������", General},
{"Extra Rage", "�������������� ���������", General},
{"Extra Second Wind", "�������������� ������ �������", General},
{"Far Shoot", "������� �������", General},
{"Force Boon", "��������������� ����", General},
{"Force Sensitivity", "������� ����", General},
{"Force Training", "�������� ����", General},
{"Improved Charge", "���������� ���������", General},
{"Improved Defences", "���������� ������", General},
{"Improved Disarm", "���������� ��������������", General},
{"Improved Damage Threshold", "���������� ������������� �����", General},
{"Linguist", "��������", General},
{"Martial Arts", "���������� ���", General},
{"Martial Arts II", "���������� ��� II", General},
{"Martial Arts III", "���������� ��� III", General},
{"Melee Defence", "������ � ������� ���", General},
{"Mighty Swing", "������ ������", General},
{"Mobility", "�����������", General},
{"Pin", "������", General},
{"Point-blank Shoot", "������� ���������", General},
{"Power Attack", "������ �����", General},
{"Powerful Charge", "������ ���������", General},
{"Precise Shoot", "���������� �������", General},
{"Quick Draw", "������� ������������ ������", General},
{"Rapid Shoot", "���������� �������", General},
{"Rapid Strike", "���������� ����", General},
{"Running Attack", "����� �� ����", General},
{"Shake it off", "�������� �� �����", General},
{"Sniper", "�������", General},
{"Skill focus (Acrobatic)", "����� �� ����������", General},
{"Skill focus (Climb)", "����� �� �������", General},
{"Skill focus (Deception)", "����� �� ������", General},
{"Skill focus (Endurance)", "����� �� ������������", General},
{"Skill focus (Gather Information)", "����� �� ��������� ����������", General},
{"Skill focus (Initiative)", "����� �� ����������", General},
{"Skill focus (Jump)", "����� �� �������", General},
{"Skill focus (Buerocracy)", "����� �� ����������", General},
{"Skill focus (Galactic Lore)", "����� �� ������� ���������", General},
{"Skill focus (Life Sciences)", "����� �� ����� ������", General},
{"Skill focus (Physical Sciences)", "����� �� ���������� ������", General},
{"Skill focus (Social Sciences)", "����� �� ���������� ������", General},
{"Skill focus (Tactics)", "����� �� �������", General},
{"Skill focus (Technology)", "����� �� �����������", General},
{"Skill focus (Mechanics)", "����� �� ��������", General},
{"Skill focus (Perception)", "����� �� ����������", General},
{"Skill focus (Persuasion)", "����� �� ���������", General},
{"Skill focus (Pilot)", "����� �� �������������", General},
{"Skill focus (Ride)", "����� �� ���� ������", General},
{"Skill focus (Stealth)", "����� �� ����������", General},
{"Skill focus (Survival)", "����� �� ���������", General},
{"Skill focus (Swim)", "����� �� ��������", General},
{"Skill focus (Treat Injury)", "����� �� �������� �������", General},
{"Skill focus (Use Computer)", "����� �� ������������� ����������", General},
{"Skill focus (Use Force)", "����� �� ������������� ����", General},
{"Strong in the Force", "��������� � ����", General},
{"Surgical Expertise", "������������� �������", General},
{"Throw", "������", General},
{"Toughness", "���������", General},
{"Trip", "��������", General},
{"Triple attack", "������� �����", General},
{"Triple critical", "������� �����������", General},
{"Vehicular combat", "��� �� ����������", General},
{"Weapon finess", "����������", General},
{"Weapon proficiency (Advanced Melee Weapons)", "�������� ���������� ������� �������� ���", General},
{"Weapon proficiency (Exotic Weapons)", "�������� ������������ �������", General},
{"Weapon proficiency (Heavy Weapons)", "�������� ������� �������", General},
{"Weapon proficiency (Lightsabers)", "�������� �������� �����", General},
{"Weapon proficiency (Pistols)", "�������� �����������", General},
{"Weapon proficiency (Rifles)", "�������� ����������", General},
{"Weapon proficiency (Simple Weapons)", "�������� ������� �������", General},
{"Weapon focus (Advanced Melee Weapons)", "����� �� ���������� ������ �������� ���", General, {{WeaponProficiencyAdvancedMeleeWeapons}}},
{"Weapon focus (Exotic Weapons)", "����� �� ������������ ������", General, {{WeaponProficiencyExoticWeapons}}},
{"Weapon focus (Heavy Weapons)", "����� �� ������� ����������", General, {{WeaponProficiencyHeavyWeapons}}},
{"Weapon focus (Lightsabers)", "����� �� �������� ����", General, {{WeaponProficiencyLightsabers}}},
{"Weapon focus (Pistols)", "����� �� ����������", General, {{WeaponProficiencyPistols}}},
{"Weapon focus (Rifles)", "����� �� ���������", General, {{WeaponProficiencyRifles}}},
{"Weapon focus (Simple Weapons)", "����� �� ������� ������", General, {{WeaponProficiencySimpleWeapons}}},
{"Whirlwind attack", "����� ������", General},
//
{"Acrobatic", "����������", Skills},
{"Climb", "������", Skills},
{"Deception", "�����", Skills},
{"Endurance", "������������", Skills},
{"Gather Information", "��������� ����������", Skills},
{"Initiative", "����������", Skills},
{"Jump", "������", Skills},
{"Buerocracy", "����������", Skills},
{"Galactic Lore", "������ ���������", Skills},
{"Life Sciences", "������������� �����", Skills},
{"Physical Sciences", "���������� �����", Skills},
{"Social Sciences", "���������� �����", Skills},
{"Tactics", "�������", Skills},
{"Technology", "����������", Skills},
{"Mechanics", "��������", Skills},
{"Perception", "��������������", Skills},
{"Persuasion", "���������", Skills},
{"Pilot", "�����", Skills},
{"Ride", "���� ������", Skills},
{"Stealth", "����������", Skills},
{"Survival", "���������", Skills},
{"Swim", "��������", Skills},
{"Treat Injury", "������ �������", Skills},
{"Use Computer", "������������ ���������", Skills},
{"Use Force", "������������ ����", Skills},
//
{"Bonus Trained Skill", "�������������� �����", RacialFeat},
{"Bonus Feat", "�������������� �����������", RacialFeat},
{"Primitive", "�����������", RacialFeat},
{"Lowlight Vision", "������������� ������", RacialFeat},
{"Darkvision", "�����������", RacialFeat},
{"Expert Swimmer", "���������� ������", RacialFeat},
{"Expert Pilot", "���������� �����", RacialFeat},
{"Expert Climber", "������ �������", RacialFeat},
{"Sneaky", "��������", RacialFeat},
{"Survival Instinct", "�������� ���������", RacialFeat},
{"Intuitive Initiative", "����������� ����������", RacialFeat},
{"Keen Force Sence", "������ ������� ����", RacialFeat},
{"Heighten Awareness", "���������� ���������������", RacialFeat},
{"Deceptive", "���������� ����", RacialFeat},
{"Extraordinary Recuperation", "���������� ������������ ���", RacialFeat},
{"Hold Breath", "�������� �������", RacialFeat},
{"Breath Underwater", "����� ��� �����", RacialFeat},
{"Bellow", "���", RacialFeat},
{"Limb Regeneration", "����������� �����������", RacialFeat},
{"Natural Armour", "����������� �����", RacialFeat},
{"Iron Will", "�������� ����", RacialFeat},
{"Great Fortitude", "�������� ���������", RacialFeat},
{"Lighting Reflexes", "������������ ��������", RacialFeat},
{"Superior Defences", "������������ ������", RacialFeat},
{"Rage", "���������", RacialFeat},
{"Scent", "���", RacialFeat},
};
assert_enum(feat, Scent);
getstr_enum(feat);

bool creature::isallow(feat_s id) const {
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1)) {
		if(feat_data[id].require.abilities[i]
			&& abilities[i] < feat_data[id].require.abilities[i])
			return false;
	}
	for(auto e : feat_data[id].require.feats) {
		if(!is(e))
			return false;
	}
	return true;
}

unsigned creature::select(feat_s* result, unsigned result_count, talent_s talent) const {
	auto p = result;
	auto pe = p + result_count;
	for(auto i = FirstFeat; i <= LastFeat; i = (feat_s)(i + 1)) {
		if(feat_data[i].tree != talent)
			continue;
		if(is(i))
			continue;
		if(!isallow(i))
			continue;
		if(p < pe)
			*p++ = i;
		else
			break;
	}
	return p - result;
}