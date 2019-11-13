#include "main.h"

void living::kill() {
	if(!count)
		return;
	hp = 0;
	count--;
}