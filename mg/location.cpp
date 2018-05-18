#include "main.h"

static struct location_info {
	const char*				id;
	const char*				name;
	const char*				nameof;
	skilla					skills;
	traita					traits;
	wise_s					wise;
	location_size_s			size;
} location_data[] = {{"Unknown lands", "Неизвестные земли"},
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
assert_enum(location, Sprucetuck);
getstr_enum(location);

template<> const char* getstf<location_s>(location_s value) {
	return location_data[value].nameof;
}

template<> const skilla& getskills<location_s>(location_s value) {
	return location_data[value].skills;
}

template<> const traita& gettraits(location_s value) {
	return location_data[value].traits;
}

bool hero::ismatch(location_s value, wise_s wise) {
	if(value)
		return location_data[value].wise == wise;
	return false;
}