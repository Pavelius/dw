#include "main.h"

static struct monster_info {
	const char*			id;
	const char*			name;
	race_s				race;
	gender_s			gender;
	char				cr[2];
	char				hd;
	char				ability[6];
	feat_s				feats[8];
	item_s				items[4];
	language_s			languages[4];
} monster_data[] = {{},
{"Kobold", "�������", NoRace, Male, {1, 8}, 2, {7, 15, 9, 8, 7, 8}, {PackTactics, Darkvision, SunlightSensitivity}, {Dagger, Sling}, {LanguageCommon, LanguageDraconic}},
{"Orc", "���", NoRace, Male, {1, 8}, 2, {16, 12, 16, 7, 11, 10}, {Aggressive, Darkvision}, {Greataxe, Javelin, HideArmour}, {LanguageCommon, LanguageOrc}},
};

creature::creature(monster_s id) {
	clear();
	this->monster = id;
	this->race = monster_data[id].race;
	this->gender = monster_data[id].gender;
	this->classes[0] = monster_data[id].hd;
	// ��������
	memcpy(ability, monster_data[id].ability, sizeof(ability));
	// ������� ������
	for(auto e : monster_data[id].feats)
		set(e);
	// ������� ��������
	for(auto e : monster_data[id].items) {
		if(!e)
			break;
		set(item_data[e].proficiency[0]);
		add(e);
	}
	// ������� �����
	for(auto e : monster_data[id].languages)
		set(e);
	// ��������� �����
	dice hitdie = {0};
	hitdie.c = monster_data[id].hd;
	hitdie.d = 6;
	hp_rolled = hitdie.roll();
	hp = gethpmax();
}