#include "main.h"

monsteri bsmeta<monsteri>::elements[] = {{},
{"Kobold", "�������", NoRace, Male, {1, 8}, 2, {7, 15, 9, 8, 7, 8}, {PackTactics, Darkvision, SunlightSensitivity}, {Dagger, Sling}, {LanguageCommon, LanguageDraconic}},
{"Orc", "���", NoRace, Male, {1, 8}, 2, {16, 12, 16, 7, 11, 10}, {Aggressive, Darkvision}, {Greataxe, Javelin, HideArmour}, {LanguageCommon, LanguageOrc}},
};
assert_enum(monster, Orc);

void creature::create(monster_s id, reaction_s reaction) {
	clear();
	auto& ei = bsmeta<monsteri>::elements[id];
	this->type = Monster;
	this->value = id;
	setgender(ei.gender);
	this->reaction = reaction;
	classes[0] = ei.hd;
	// ��������
	memcpy(ability, ei.ability, sizeof(ability));
	// ������� ������
	for(auto e : ei.feats)
		set(e);
	// ������� ��������
	for(auto e : ei.items) {
		if(!e)
			break;
		feats.add(bsmeta<itemi>::elements[e].proficiency);
		add(e);
	}
	// ������� �����
	for(auto e : ei.languages)
		set(e);
	// ��������� �����
	dice hitdie = {0};
	hitdie.c = ei.hd;
	hitdie.d = 6;
	hp_rolled = hitdie.roll();
	hp = gethpmax();
}