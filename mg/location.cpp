#include "main.h"

BSDATA(locationi) = {{"Unknown lands", "����������� �����"},
//
{"Barkstone", "����������", "���������", {Carpenter, Potter, Glazier}, {SteadyPaw}, BarkstoneWise},
{"Cooperwood", "�����������", "�����������", {Smith, Haggler}, {Independent}, CooperwoodWise},
{"Elmoss", "�������", "��������", {Carpenter, Harvester}, {Alert}, ElmossWise},
{"Ivydale", "�����������", "�����������", {Harvester, Baker}, {HardWorker}, IvydaleWise},
{"Lockhaven", "��������", "���������", {Weaver, Armorer}, {Generous, GuardsHonor}, LockhavenWise},
{"Port Sumac", "���� ������", "����� �������", {Boatcrafter, WeatherWatcher}, {Tough, WeatherSense}, PortSumacWise},
{"Shaleburrow", "����������", "����������", {Stonemason, Harvester, Miller}, {OpenMinded}, ShaleburrowWise},
{"Sprucetuck", "������", "�������", {Scientist, Loremouse}, {Inquisitive, Rational}, SprucetuckWise},
};
assert_enum(locationi, Sprucetuck)

bool hero::ismatch(location_s value, wise_s wise) {
	if(value)
		return bsdata<locationi>::elements[value].wise == wise;
	return false;
}