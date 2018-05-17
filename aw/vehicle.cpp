#include "main.h"

char vehicle::get(vehicle_stat_s id) const {
	if(id == Armor)
		return getarmor();
	return stats[id];
}

void vehicle::set(vehicle_stat_s id, int value) {
	if(id == Armor)
		setarmor(value);
	stats[id] = value;
}