#include "main.h"

static struct skill_i {
	const char*			id;
	const char*			name;
	adat<knack_s, 16>	knacks;
	adat<knack_s, 16>	knacks_advanced;
} skill_data[] = {{"Artist", "������� ���������", {Composer, Drawing, Musician, Sculpting, Singing, Writing}},
{"Courtier", "����������", {Dancing, Etiquette, Fashion, Oratory}},
{"Criminal", "����������", {Gambling, Shadowing, Stealth}},
{"Doctor", "������", {Diagnosis, FirstAid}},
{"Hunter", "�������", {Fishing, Skinning, Stealth, Survival, Tracking, TrailSigns, Traps}},
{"Merchant", "��������", {Blacksmith, Butcher, Cooking, Fletcher, Furrier, Glassblower, Innkeeper, Jeweler, Potter}},
{"Performer", "������", {Acting, Dancing, Oratory, Singing}},
{"Sailor", "�����", {Balance, Climbing, Knotwork, Rigging}},
{"Scholar", "������", {History, Mathematics, Philosophy, Research}},
{"Servant", "�����", {Etiquette, Fashion, MenitalTask, Unobrusive}},
{"Spy", "�����", {Shadowing, Stealth}},
{"Streetwise", "������� �����", {Socializing, StreetNavigation}},
// Martial skills
{"Archer", "������"},
{"Athlete", "�����"},
{"Buckler", "���"},
{"Commander", "������������"},
{"Crossbow", "�������"},
{"Dirty Fighting", "������� ���"},
{"Fencing", "����������"},
{"Firearms", "������������� ������"},
{"Heavy weapon", "������� ������"},
{"Knife", "���"},
{"Panzerhand", "����������"},
{"Polearm", "�����"},
{"Pugilism", "����"},
{"Rider", "��������"},
{"Wrestling", "������"},
};
assert_enum(skill, LastSkill);
getstr_enum(skill);

void hero::set(skill_s value, bool interacive, char* skills) {
	skills[value]++;
	switch(value) {
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

int hero::getcost(skill_s value) const {
	if(iscivil(value)) {
		if(get(University))
			return 1;
	} else {
		if(get(Academy))
			return 1;
	}
	return 2;
}

bool hero::iscivil(skill_s value) {
	return value >= Artist && value <= Streetwise;
}