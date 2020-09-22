#include "main.h"

BSDATA(locationi) = {{"Unknown lands", "Неизвестные земли"},
//
{"Barkstone", "Коракамень", "Коракамня", {Carpenter, Potter, Glazier}, {SteadyPaw}, BarkstoneWise},
{"Cooperwood", "Краснолесье", "Краснолесья", {Smith, Haggler}, {Independent}, CooperwoodWise},
{"Elmoss", "Дубомох", "Дубомоха", {Carpenter, Harvester}, {Alert}, ElmossWise},
{"Ivydale", "Плющедолина", "Плющедолины", {Harvester, Baker}, {HardWorker}, IvydaleWise},
{"Lockhaven", "Локхавен", "Локхавена", {Weaver, Armorer}, {Generous, GuardsHonor}, LockhavenWise},
{"Port Sumac", "Порт Сумрак", "Порта Сумрака", {Boatcrafter, WeatherWatcher}, {Tough, WeatherSense}, PortSumacWise},
{"Shaleburrow", "Глиноземье", "Глиноземья", {Stonemason, Harvester, Miller}, {OpenMinded}, ShaleburrowWise},
{"Sprucetuck", "Ельник", "Ельника", {Scientist, Loremouse}, {Inquisitive, Rational}, SprucetuckWise},
};
assert_enum(locationi, Sprucetuck)

bool hero::ismatch(location_s value, wise_s wise) {
	if(value)
		return bsdata<locationi>::elements[value].wise == wise;
	return false;
}