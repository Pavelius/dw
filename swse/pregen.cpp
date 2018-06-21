#include "main.h"

static struct pregen_info {
	const char*			id;
	const char*			name;
	char				classes[NonHero + 1];
	char				ability[Charisma + 1];
	adat<feat_s, 16>	feats;
} pregen_data[] = {
	{},
{"Stormtrooper", "Штурмовик", {0, 0, 0, 0, 0, 0, 4}, {12, 11, 11, 10, 10, 10},
{ArmourProficienceLight, WeaponProficiencySimpleWeapons, WeaponProficiencyPistols, WeaponProficiencyRifles, CoordinatedAttack, WeaponFocusRifles}},
{"Heavy stormtrooper", "Штурмовик", {0, 0, 0, 0, 0, 0, 8}, {15, 11, 10, 12, 9, 8},
{ArmourProficienceLight, WeaponProficiencySimpleWeapons, WeaponProficiencyPistols, WeaponProficiencyRifles, WeaponProficiencyHeavyWeapons, WeaponFocusRifles, BurstFire, PointBlankShoot}},
};
assert_enum(pregen, StromtrooperHeavy);
getstr_enum(pregen);

creature::creature(pregen_s value) {
	auto pm = pregen_data + value;
	clear();
	memcpy(abilities, pm->ability, sizeof(abilities));
	memcpy(classes, pm->classes, sizeof(classes));
	gender = Male;
	specie = Human;
	pregen = value;
	for(auto e : pm->feats)
		set(e, false);
}