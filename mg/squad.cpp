#include "main.h"

season_s squadi::year_cicle[] = {
	Spring, Spring, Spring,
	Summer, Summer, Summer, Summer,
	Autum, Autum,
	Winter, Winter, Winter, Winter, Winter
};

void squadi::clear() {
	memset(this, 0, sizeof(*this));
}