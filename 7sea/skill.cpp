#include "main.h"

static struct skill_i {
	const char*			id;
	const char*			name;
	adat<knack_s, 16>	knacks;
	adat<knack_s, 16>	knacks_advanced;
} skill_data[] = {{"Artist", "Человек исскуства", {Composer, Drawing, Musician, Sculpting, Singing, Writing}},
{"Courtier", "Придворный", {Dancing, Etiquette, Fashion, Oratory}},
{"Criminal", "Преступник", {Gambling, Shadowing, Stealth}},
{"Doctor", "Доктор", {Diagnosis, FirstAid}},
{"Hunter", "Охотник", {Fishing, Skinning, Stealth, Survival, Tracking, TrailSigns, Traps}},
{"Merchant", "Торговец", {Blacksmith, Butcher, Cooking, Fletcher, Furrier, Glassblower, Innkeeper, Jeweler, Potter}},
{"Performer", "Артист", {Acting, Dancing, Oratory, Singing}},
{"Sailor", "Моряк", {Balance, Climbing, Knotwork, Rigging}},
{"Scholar", "Ученый", {History, Mathematics, Philosophy, Research}},
{"Servant", "Слуга", {Etiquette, Fashion, MenitalTask, Unobrusive}},
{"Spy", "Шпион", {Shadowing, Stealth}},
{"Streetwise", "Человек улицы", {Socializing, StreetNavigation}},
// Martial skills
{"Archer", "Лучник"},
{"Athlete", "Атлет"},
{"Buckler", "Щит"},
{"Commander", "Коммандующий"},
{"Crossbow", "Арбалет"},
{"Dirty Fighting", "Грязный бой"},
{"Fencing", "Фехтование"},
{"Firearms", "Огнестрельное оружие"},
{"Heavy weapon", "Тяжелое оружие"},
{"Knife", "Нож"},
{"Panzerhand", "Панцерханд"},
{"Polearm", "Копье"},
{"Pugilism", "Бокс"},
{"Rider", "Наездник"},
{"Wrestling", "Борьба"},
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