#include "main.h"

int dicew::roll() const {
	auto r = bonus;
	for(int i = 0; i < dice; i++)
		r += rand() % 6 + 1;
	return r;
}