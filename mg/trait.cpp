#include "main.h"

static struct trait_i {
	const char*	id;
	const char*	name;
	skill_s	bonus[4];
} trait_data[] = {{"Bigpaw", "�����������", {Fighter, Hunter, Laborer, Harvester}},
{"Bitter", "��������", {Fighter, Militarist, Instructor, Administrator}},
{"Bodyguard", "�������������", {Fighter, Militarist, Healer, Pathfinder}},
{"Bold", "�������", {Fighter, Orator, Haggler, Scout}},
{"Brave", "�������", {Fighter, Insectrist, Militarist, Scout}},
{"Calm", "���������", {Orator, Persuader, Scientist, Archivist}},
{"Clever", "��������������", {Orator, Persuader, Loremouse, Scientist}},
{"Compassionate", "�������������", {Persuader, Orator, Healer, Brewer}},
{"Cunning", "������", {Deceiver, Persuader, Haggler, Orator}},
{"Curious", "����������", {Scientist, Archivist, Administrator, Scout}},
{"Deep Ear", "���������", {Scout, Pathfinder, Loremouse, Scientist}},
{"Defender", "�������", {Fighter, Hunter, Scout, Pathfinder}},
{"Determined", "�����������", {Administrator, Fighter, Militarist, Deceiver}},
{"Driven", "���������", {Fighter, Militarist, Laborer, Instructor}},
{"Early Riser", "������ ������", {Laborer}},
{"Extrovert", "����������", {}},
{"Fat", "�������", {Miller, Baker, Cook, Brewer}},
{"Fearful", "����������", {Scout, Scientist, Weaver, Harvester}},
{"Fearless", "�����������", {Fighter, Hunter, Pathfinder, Scout}},
{"Fiery", "��������", {Fighter, Hunter, Militarist, Instructor}},
{"Generous", "������������", {Orator, Persuader, Haggler, Healer}},
{"Graceful", "����������", {Scout, Orator, Healer, Brewer}},
{"Guard's Honor", "����� ���������", {Fighter, Administrator, Scientist, Orator}},
{"Innocent", "��������", {Deceiver, Scout, Persuader, Harvester}},
{"Jaded", "����������", {Archivist, Survivalist, Deceiver, Haggler}},
{"Leader", "�����", {Administrator, Orator, Persuader, Instructor}},
{"Longtail", "�������������", {Scout, WeatherWatcher}},
{"Lost", "����������", {}},
{"Natural Bearings", "��������", {}},
{"Nimble", "�������", {Haggler, Deceiver, Harvester, Survivalist}},
{"Nocturnal", "������ ����", {}},
{"Oldfur", "������ ���", {Fighter, Hunter, Scientist, Administrator}},
{"Quick-witted", "����������", {}},
{"Quiet", "���������", {Scout, Harvester, Pathfinder, Survivalist}},
{"Scarred", "���� � ������", {Fighter, Militarist, Instructor, Smith}},
{"Sharpeyed", "�����������", {}},
{"Sharptooth", "����������", {Fighter, Harvester, Survivalist, Laborer}},
{"Short", "��������", {Scout, Pathfinder, Glazier, Brewer}},
{"Skeptical", "������", {}},
{"Skinny", "�����", {Carpenter, Potter, Glazier, Archivist}},
{"Stoic", "����������", {}},
{"Stubborn", "�������", {}},
{"Suspicious", "��������������", {}},
{"Tall", "�������", {Carpenter, Laborer, Potter, Smith}},
{"Thoughtful", "������������", {Scout, Pathfinder, Apiarist, Insectrist}},
{"Tough", "�������", {Laborer, Fighter, Stonemason, Potter}},
{"Weather Sense", "��������� ������", {WeatherWatcher, Healer, Scientist, Insectrist}},
{"Wise", "������", {Scientist, Healer, Archivist, Orator}},
{"Wolf's Snout", "������ ���", {Scout, Pathfinder, Hunter, Survivalist}},
{"Young", "�������", {Laborer, Fighter, Harvester, Deceiver}},
{"Alert", "����������", {}},
{"Hard Worker", "��������", {Laborer, Stonemason, Potter, Smith}},
{"Independent", "�����������", {}},
{"Open-minded", "���������������", {Scientist, Healer, Cartographer, Archivist}},
{"Steady Paw", "������������", {}},
{"Inquisitive", "��������������", {Scientist, Healer, Orator, Persuader}},
{"Rational", "��������", {Scientist, Healer, Orator, Archivist}},
};
assert_enum(trait, Rational);
getstr_enum(trait);

bool hero::isbonus(trait_s base, skill_s value) {
	for(auto e : trait_data[base].bonus) {
		if(e == value)
			return true;
	}
	return false;
}