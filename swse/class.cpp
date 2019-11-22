#include "main.h"

classi bsmeta<classi>::elements[] = {{"Jedi", "Джедай", 10, 2, {ForceSensitivity, WeaponProficiencyLightsabers, WeaponProficiencySimpleWeapons}},
{"Noble", "Аристократ", 6, 6, {Linguist, WeaponProficiencyPistols, WeaponProficiencySimpleWeapons}},
{"Scoundrel", "Негодяй", 6, 4, {PointBlankShoot, WeaponProficiencyPistols, WeaponProficiencySimpleWeapons}},
{"Scout", "Скаут", 8, 5, {ShakeItOff, WeaponProficiencyPistols, WeaponProficiencyRifles, WeaponProficiencySimpleWeapons}},
{"Soldier", "Солдат", 10, 3, {ArmourProficienceLight, ArmourProficienceMedium, WeaponProficiencyPistols, WeaponProficiencyRifles, WeaponProficiencySimpleWeapons}},
{"Beast", "Бестия", 10},
{"Non-Hero", "Не герой", 6},
};
assert_enum(class, NonHero);

void creature::set(class_s id, bool interactive) {
	classes[id]++;
	for(auto e : bsmeta<classi>::elements[id].starting_feats) {
		if(is(e))
			continue;
		if(!isallow(e))
			continue;
		set(e);
	}
}

int creature::getskillpoints(class_s id) {
	return bsmeta<classi>::elements[id].skills;
}

aref<feat_s> creature::getfeats(class_s id) {
	return bsmeta<classi>::elements[id].starting_feats;
}

int creature::getdice(class_s id) {
	return bsmeta<classi>::elements[id].dice;
}