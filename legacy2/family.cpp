#include "main.h"

void family::add(resource_s i) {
	if(needs.is(i))
		needs.remove(i);
	else
		surpluses.add(i);
}

void family::remove(resource_s i) {
	if(surpluses.is(i))
		surpluses.remove(i);
	else
		needs.add(i);
}