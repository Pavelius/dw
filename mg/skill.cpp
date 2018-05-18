#include "main.h"

static struct skill_i {
	const char*	id;
	const char*	name;
	skilla	help;
} skill_data[] = {{"Nature", "������"},
{"Will", "����"},
{"Health", "��������"},
{"Resources", "�������"},
{"Circles", "�����"},
//
{"Administrator", "�������������", {Archivist, Orator}},
{"Apiarist", "��������", {Scientist, Insectrist, Loremouse}},
{"Archivist", "����������", {Cartographer, Administrator}},
{"Armorer", "���������", {Smith, Scientist}},
{"Baker", "������", {Scientist}},
{"Boatcrafter", "��������", {Carpenter, Scientist}},
{"Brewer", "������", {Scientist}},
{"Carpenter", "�������", {Scientist}},
{"Cartographer", "���������", {Archivist, Pathfinder}},
{"Cook", "�����", {Baker}},
{"Deceiver", "����", {Persuader}},
{"Fighter", "����", {Hunter}},
{"Glazier", "���������", {Scientist}},
{"Haggler", "��������", {Persuader}},
{"Harvester", "����������", {WeatherWatcher}},
{"Healer", "������", {Scientist}},
{"Hunter", "�������", {Loremouse}},
{"Insectist", "�����������", {Loremouse}},
{"Instructor", "����������"},
{"Laborer", "������������"},
{"Loremouse", "��������", {Hunter, Scientist}},
{"Militarist", "����������"},
{"Miller", "�������"},
{"Orator", "������"},
{"Pathfinder", "���������"},
{"Persuader", "��������"},
{"Potter", "������"},
{"Scientist", "�������"},
{"Scout", "���������"},
{"Smith", "������"},
{"Stonemason", "���������"},
{"Survivalist", "�����������"},
{"Weather Watcher", "������������� ������"},
{"Weaver", "����"},
};
assert_enum(skill, Weaver);
getstr_enum(skill);

template<> const skilla& getskills<skill_s>(skill_s value) {
	return skill_data[value].help;
}